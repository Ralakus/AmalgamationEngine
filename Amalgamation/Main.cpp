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
#include <Engine/Graphics/OpenGL/GLWindow.hpp>

using namespace Amalgamation;

int main() {

	Time::RegisterToLuaStack();

	LuaScript Settings;
	Settings.LoadFile("UserSettings.lua");
	Settings.ExecFunction("CheckUserSettings");

	float MSensitivity  = Settings.GetLuaRef("UserSettings")["MouseSensitivity"].cast<float>();
	float MovementSpeed = Settings.GetLuaRef("UserSettings")["MouseSensitivity"].cast<float>();
	float CamFOV        = Settings.GetLuaRef("UserSettings")["CameraFOV"].cast<float>();

	std::unique_ptr<Window> Window = std::make_unique<GLWindow>(
		Settings.GetLuaRef("UserSettings")["Window"].cast<luabridge::LuaRef>()["Title"].cast<std::string>(),
		Settings.GetLuaRef("UserSettings")["Window"].cast<luabridge::LuaRef>()["Width"].cast<uint32>(),
		Settings.GetLuaRef("UserSettings")["Window"].cast<luabridge::LuaRef>()["Height"].cast<uint32>(),
		Settings.GetLuaRef("UserSettings")["Window"].cast<luabridge::LuaRef>()["Fullscreen"].cast<bool>()
	);

	World World;

	Time Time;

	BasicEntity* Player;
	BasicEntity* Cube;
	BasicEntity* FloorPlane;
	BasicEntity* Cube2;

	GLBasicRenderer Renderer;

	GLShader Shader(Settings.GetLuaRef("TexturedShaderglsl").cast<std::string>(), true);

	GLTexture T1;
	if (T1.LoadTexture(
		Settings.GetLuaRef("UserSettings")["TextureVariable0"].cast<std::string>(),
		true, 0, 0))
	{
		std::cout << "Texture load successful" << std::endl;
	}
	else {
		std::cout << "Texture load failed!" << std::endl;
	}

	GLTexture T2;
	if (T2.LoadTexture(
		Settings.GetLuaRef("UserSettings")["TextureVariable1"].cast<std::string>(),
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

	while (Window->IsValid()) {

		Time.Update();

		Window->Update();

		World.Update(Time.GetDelta());

		Cube->GetTransform()->Rotation *= glm::angleAxis(Time.GetDelta(), glm::vec3(0, 1, 0));

		GLCall(glGetIntegerv(GL_VIEWPORT, viewPort));
		Cam->SetProjection(glm::perspective(glm::radians(CamFOV), (float)viewPort[2] / (float)viewPort[3], 0.001f, 100.f));

		MouseOffset.x = Mouse::Instance().GetX() - LastMousePos.x;
		MouseOffset.y = Mouse::Instance().GetY() - LastMousePos.y;
		Cam->Pitch(MouseOffset.y * Time.GetDelta() * MSensitivity);
		Cam->Yaw(MouseOffset.x * Time.GetDelta() * MSensitivity);
		LastMousePos.x = Mouse::Instance().GetX();
		LastMousePos.y = Mouse::Instance().GetY();

		if (Keyboard::Instance().GetKeyState(GLFW_KEY_UP)) {
			Cam->Pitch(-1 * Time.GetDelta());
		}
		if (Keyboard::Instance().GetKeyState(GLFW_KEY_DOWN)) {
			Cam->Pitch(1 * Time.GetDelta());
		}
		if (Keyboard::Instance().GetKeyState(GLFW_KEY_LEFT)) {
			Cam->Yaw(-1 * Time.GetDelta());
		}
		if (Keyboard::Instance().GetKeyState(GLFW_KEY_RIGHT)) {
			Cam->Yaw(1 * Time.GetDelta());
		}

		if (Keyboard::Instance().GetKeyState(GLFW_KEY_W)) {
			Cam->Translate(0, 0, -1 * Time.GetDelta() * MovementSpeed);
		}
		if (Keyboard::Instance().GetKeyState(GLFW_KEY_S)) {
			Cam->Translate(0, 0, 1 * Time.GetDelta() * MovementSpeed);
		}
		if (Keyboard::Instance().GetKeyState(GLFW_KEY_A)) {
			Cam->Translate(-1 * Time.GetDelta() * MovementSpeed, 0, 0);
		}
		if (Keyboard::Instance().GetKeyState(GLFW_KEY_D)) {
			Cam->Translate(1 * Time.GetDelta() * MovementSpeed, 0, 0);
		}

		if (Keyboard::Instance().GetKeyState(GLFW_KEY_Q)) {
			Cam->Roll(-1 * Time.GetDelta());
		}
		if (Keyboard::Instance().GetKeyState(GLFW_KEY_E)) {
			Cam->Roll(1 * Time.GetDelta());
		}

		if (Keyboard::Instance().GetKeyState(GLFW_KEY_C)) {
			Cam->Translate(0, -2 * Time.GetDelta(), 0);
		}
		if (Keyboard::Instance().GetKeyState(GLFW_KEY_SPACE)) {
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

	World.Destroy();

}