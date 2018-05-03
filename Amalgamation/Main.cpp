#include <iostream>
#include <Core/World/World.hpp>
#include <Core/Utilities/Time.hpp>
#include <Core/Utilities/AessetReader.hpp>
#include <Core/Lua/LuaScript.hpp>
#include <Engine/World/Components/MeshComponent.hpp>
#include <Engine/Graphics/OpenGL/GLTexture.hpp>
#include <Engine/Graphics/OpenGL/Renderers/GLBasicRenderer.hpp>
#include <Engine/World/Components/CameraComponent.hpp>
#include <Engine/World/Entities/BasicEntity.hpp>
#include <Engine/World/WorldPlugins/BulletPhysicsPlugin.hpp>
#include <Engine/Graphics/OpenGL/GLWindow.hpp>
#include <Engine/Graphics/OpenGL/Lights/GLPointLight.hpp>

using namespace Amalgamation;

int main() {

	REGISTER_LUA_CLASS(Keyboard);
	REGISTER_LUA_CLASS(Mouse);
	REGISTER_LUA_CLASS(Time);

	std::ios::sync_with_stdio(false);

	LuaScript Path;
	Path.LoadFile("Path.lua");
	if (!Path.IsValid()) {
		std::cout << "[READ ERROR]: Error reading file \"Path.lua\"" << std::endl
			<< "Press enter to close..." << std::endl;
		std::cin.get();
		return -1;
	}

	LuaScript Settings;
	Settings.LoadFile(Path.Get["Path"]["UserSettings"]);
	if (!Settings.IsValid()) {
		std::cout << "[READ ERROR]: Error reading file \"UserSettings.lua\" from path file" << std::endl
			<< "Press enter to close..." << std::endl;
		std::cin.get();
		return -1;
	}
	Settings.ExecFunction("CheckUserSettings");

	LuaScript LTest;
	LTest.LoadFile(Path.Get["Path"]["LTest"]);
	if (!LTest.IsValid()) {
		std::cout << "[READ ERROR]: Error reading file \"LTest.lua\" from path file" << std::endl
			<< "Press enter to close..." << std::endl;
		std::cin.get();
		return -1;
	}

	LuaScript Shaders;
	Shaders.LoadFile(Path.Get["Path"]["Shaders"]);
	if (!Shaders.IsValid()) {
		std::cout << "[READ ERROR]: Error reading file \"Shaders.lua\" from path file" << std::endl
			<< "Press enter to close..." << std::endl;
		std::cin.get();
		return -1;
	}

	float MSensitivity   = Settings.Get["UserSettings"]["MouseSensitivity"];
	float MovementSpeed  = Settings.Get["UserSettings"]["MouseSensitivity"];
	float CamFOV         = Settings.Get["UserSettings"]["CameraFOV"];
	float WMovementSpeed = MovementSpeed;

	std::unique_ptr<Window> Window = std::make_unique<GLWindow>(
		Settings.Get["UserSettings"]["Window"]["Title"],
		Settings.Get["UserSettings"]["Window"]["Width"],
		Settings.Get["UserSettings"]["Window"]["Height"],
		Settings.Get["UserSettings"]["Window"]["Fullscreen"]
	);

	World World;

	Time Time;

	BasicEntity* Player;
	BasicEntity* Cube;
	BasicEntity* FloorPlane;
	BasicEntity* Cube2;

	GLBasicRenderer Renderer;

	GLPointLight GLPL;
	GLPL.Diffuse = {1.f, 1.f, 1.f};
	Renderer.AddLight(&GLPL);

	GLShader Shader(Shaders.Get["glslShaders"]["GetLightingShader"](1, 1, 1), true);

	GLTexture T1;
	if (T1.LoadTexture(
		Settings.Get["UserSettings"]["TextureVariable0"],
		true, 0, 0))
	{
		std::cout << "Texture load successful" << std::endl;
	}
	else {
		std::cout << "Texture load failed!" << std::endl;
	}

	GLTexture T2;
	if (T2.LoadTexture(
		Settings.Get["UserSettings"]["TextureVariable1"],
		false, 0, 0))
	{
		std::cout << "Texture load successful" << std::endl;
	}
	else {
		std::cout << "Texture load failed!" << std::endl;
	}

	Cube = World.CreateEntity<BasicEntity>();
	Cube->AddComponent<MeshComponent>(&Renderer)->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Cube), &Shader)->AddTexture(&T1);


	Cube2 = World.CreateEntity<BasicEntity>();
	Cube2->AddComponent<MeshComponent>(&Renderer)->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Cube), &Shader)->AddTexture(&T1);
	Cube2->GetTransform()->SetTransform({ 0, -1.25, -5 });


	Player = World.CreateEntity<BasicEntity>();
	CameraComponent* Cam = Player->AddComponent<CameraComponent>();
	Player->GetTransform()->Position = { 0, 2, 1.5 };
	Player->GetTransform()->Rotation = glm::vec3(glm::radians(65.f), glm::radians(0.f), glm::radians(0.f));
	GLPL.Parent(Player->GetTransform());


	FloorPlane = World.CreateEntity<BasicEntity>();
	FloorPlane->AddComponent<MeshComponent>(&Renderer)->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Plane), &Shader)->AddTexture(&T2);
	FloorPlane->GetTransform()->SetTransform({ 0, -1.25f, 0 }, { glm::vec3(glm::radians(-90.f),0 ,0) }, { 5, 5, 1 });

	World.Awake();

	GLCall(glClearColor(0.8f, 0.8f, 0.8f, 1.0f));

	glm::vec2 MouseOffset;
	glm::vec2 LastMousePos;

	GLint viewPort[4];

	Window->LockMouse(true);

	Renderer.SetCamera(Cam);

	LTest.ExecFunction("Awake");

	while (Window->IsValid()) {

		Time.Update();

		Window->Update();

		World.Update(Time.GetDelta());

		LTest.ExecFunction("Update", Time.GetDelta());

		Cube->GetTransform()->Rotation *= glm::angleAxis(Time.GetDelta(), glm::vec3(0, 1, 0));

		GLCall(glGetIntegerv(GL_VIEWPORT, viewPort));
		Cam->SetProjection(glm::perspective(glm::radians(CamFOV), (float)viewPort[2] / (float)viewPort[3], 0.001f, 100.f));

		MouseOffset.x = Mouse::Instance().GetX() - LastMousePos.x;
		MouseOffset.y = Mouse::Instance().GetY() - LastMousePos.y;
		Cam->Pitch(MouseOffset.y * Time.GetDelta() * MSensitivity);
		Cam->Yaw(MouseOffset.x * Time.GetDelta() * MSensitivity);
		LastMousePos.x = Mouse::Instance().GetX();
		LastMousePos.y = Mouse::Instance().GetY();

		std::cout << "Camera Front: X: " << Cam->GetFront().x << ", Y: " << Cam->GetFront().y << ", Z: " << Cam->GetFront().z << "            \r";

		if (Keyboard::Instance().GetKeyState('W')) {
			Cam->Translate(0, 0, -1 * Time.GetDelta() * WMovementSpeed);
		}
		if (Keyboard::Instance().GetKeyState('S')) {
			Cam->Translate(0, 0, 1 * Time.GetDelta() * WMovementSpeed);
		}
		if (Keyboard::Instance().GetKeyState('A')) {
			Cam->Translate(-1 * Time.GetDelta() * WMovementSpeed, 0, 0);
		}
		if (Keyboard::Instance().GetKeyState('D')) {
			Cam->Translate(1 * Time.GetDelta() * WMovementSpeed, 0, 0);
		}

		if (Keyboard::Instance().GetKeyState(GLFW_KEY_LEFT_SHIFT)) {
			WMovementSpeed = MovementSpeed * 2;
		}
		else {
			WMovementSpeed = MovementSpeed;
		}

		if (Keyboard::Instance().GetKeyState('Q')) {
			Cam->Roll(-1 * Time.GetDelta());
		}
		if (Keyboard::Instance().GetKeyState('E')) {
			Cam->Roll(1 * Time.GetDelta());
		}

		if (Keyboard::Instance().GetKeyState('C')) {
			Cam->Translate(0, -2 * Time.GetDelta(), 0);
		}
		if (Keyboard::Instance().GetKeyState(' ')) {
			Cam->Translate(0, 2 * Time.GetDelta(), 0);
		}

		if (Keyboard::Instance().GetKeyState('F')) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		if (Keyboard::Instance().GetKeyState(GLFW_KEY_ESCAPE)) {
			Window->Close();
		}

		Renderer.Flush();

		if (Time.OnSecond()) {
			Window->SetTitle(("FPS: " + std::to_string(Time.GetAvgFPS())));
		}

	}

	LTest.ExecFunction("Destroy");

	World.Destroy();

	return 0;

}