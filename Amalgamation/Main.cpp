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

using namespace Amalgamation;

int main() {

	LuaScript Path;
	Path.LoadFile("Path.lua");

	LuaScript Settings;
	Settings.LoadFile(Path.Get["Path"]["UserSettings"]);
	Settings.Get["CheckUserSettings"]();

	LuaScript LTest;
	LTest.LoadFile(Path.Get["Path"]["LTest"]);

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

	GLShader Shader(Settings.Get["TexturedShaderglsl"], true);

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
	Player->GetTransform()->Position.z = -5;


	FloorPlane = World.CreateEntity<BasicEntity>();
	FloorPlane->AddComponent<MeshComponent>(&Renderer)->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Plane), &Shader)->AddTexture(&T2);
	FloorPlane->GetTransform()->SetTransform({ 0, -1.25f, 0 }, { glm::vec3(glm::radians(90.f),0 ,0) }, { 5, 5, 1 });

	World.Awake();

	GLCall(glClearColor(0.8f, 0.8f, 0.8f, 1.0f));

	glm::vec2 MouseOffset;
	glm::vec2 LastMousePos;

	GLint viewPort[4];

	Window->LockMouse(true);

	Renderer.SetCamera(Cam);

	LTest.Get["Awake"]();

	while (Window->IsValid()) {

		Time.Update();

		Window->Update();

		World.Update(Time.GetDelta());

		LTest.Get["Update"]();

		Cube->GetTransform()->Rotation *= glm::angleAxis(Time.GetDelta(), glm::vec3(0, 1, 0));

		GLCall(glGetIntegerv(GL_VIEWPORT, viewPort));
		Cam->SetProjection(glm::perspective(glm::radians(CamFOV), (float)viewPort[2] / (float)viewPort[3], 0.001f, 100.f));

		MouseOffset.x = Mouse::Instance().GetX() - LastMousePos.x;
		MouseOffset.y = Mouse::Instance().GetY() - LastMousePos.y;
		Cam->Pitch(MouseOffset.y * Time.GetDelta() * MSensitivity);
		Cam->Yaw(MouseOffset.x * Time.GetDelta() * MSensitivity);
		LastMousePos.x = Mouse::Instance().GetX();
		LastMousePos.y = Mouse::Instance().GetY();

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

		if (Keyboard::Instance().GetKeyState(GLFW_KEY_ESCAPE)) {
			Window->Close();
		}

		Renderer.Flush();

		if (Time.OnSecond()) {
			Window->SetTitle(("FPS: " + std::to_string(Time.GetAvgFPS())));
		}

	}

	LTest.Get["Destroy"]();

	World.Destroy();

}