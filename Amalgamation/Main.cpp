#include <Core/Event/EventHandler.hpp>
#include <Core/Utilities/Time.hpp>
#include <Core/Utilities/Aesset.hpp>
#include <Core/Level/Level.hpp>
#include <Core/Graphics/Mesh.hpp>
#include <Core/Utilities/Random.hpp>
#include <Core/Input/InputControl.hpp>
#include <Engine/Graphics/OpenGL/GLWindow.hpp>
#include <Engine/Level/Components/MeshComponent.hpp>
#include <Engine/Graphics/OpenGL/Renderers/GLBasicRenderer.hpp>

using namespace Amalgamation;

int main(int argc, char* args[]) {


	//================================================
	//Loads config file and creates window
	//================================================


	Aesset Config;
	Config.LoadFile("Config.aesset");

	AE_LOG_NOTE(("TODO:" + Config.Get<std::string>("TODO")).c_str());

	std::unique_ptr<Window> Window = std::make_unique<GLWindow>(
		Config.Get<std::string> ("WindowName"), 
		Config.Get<unsigned int>("WindowWidth"), 
		Config.Get<unsigned int>("WindowHeight"),
		Config.Get<bool>        ("WindowFullscreen")
	);

	Time T;

	GLint ViewPort[4];

	float CamFOV = 90.f;

	//================================================
	//Binds input
	//================================================


	EventLambdaCallback ECCloseWindow([&]() -> void { Window->Close(); });
	Input::Instance().RegisterKeyAction("CloseWindow", Input::Instance().KeyFromAesset(Config, "CloseWindowKey"), InputAction::Held);
	Input::Instance().RegisterCallback("CloseWindow", &ECCloseWindow);

	EventLambdaCallback ECMakeFullscreen([&]()-> void { Window->SetFullscreen(!Window->IsFullscreen()); });
	Input::Instance().RegisterKeyAction("MakeFullscreen", Key::P, InputAction::Pressed);
	Input::Instance().RegisterCallback("MakeFullscreen", &ECMakeFullscreen);


	GLFW_KEY_UP;

	InputControl ICMoveForward;
	ICMoveForward.AddInput(Key::W,  1.f);
	ICMoveForward.AddInput(Key::S, -1.f);

	InputControl ICMoveRight;
	ICMoveRight.AddInput(Key::D,  1.f);
	ICMoveRight.AddInput(Key::A, -1.f);

	InputControl ICRollRight;
	ICRollRight.AddInput(Key::E,  1.f);
	ICRollRight.AddInput(Key::Q, -1.f);

	InputControl ICMoveUp;
	ICMoveUp.AddInput(Key::Space, 1.f);
	ICMoveUp.AddInput(Key::C,    -1.f);

	InputControl ICMakeFullscreen;
	ICMakeFullscreen.AddInput(Key::P, 1.f);

	//================================================
	//Create renderer and shaders
	//================================================



	GLBasicRenderer Renderer;
	GLShader Shader;
	Shader.LoadFromStr(Config.Get<std::string>("Shader"));
	Shader.SupportsLighting = false;
		







	//================================================
	//Create entities and components
	//================================================







	Level Level;

	Entity* Player = Level.CreateEntity<Entity>();
	TransformComponent* PlayerTrans = Player->AddComponent<TransformComponent>();
	CameraComponent* Cam = Player->AddComponent<CameraComponent>();
	Renderer.SetCamera(Cam);

	Entity* Cube;
	Cube = Level.CreateEntity<Entity>();
	Cube->AddComponent<MeshComponent>(&Renderer)->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Cube), &Shader);
	Cube->GetComponentByType<TransformComponent>()->GetTransform().Position.Z = 5.f;









	//================================================
	//Begin game loop
	//================================================


	Level.Awake();

	while (Window->IsValid()) {

		T.Update();
		Level.Update(T.GetDelta());
		Window->Update();

		GLCall(glGetIntegerv(GL_VIEWPORT, ViewPort));
		Cam->SetProjection(Math::Mat4::Perspective(Math::Radians(CamFOV), (float)ViewPort[2] / (float)ViewPort[3], 0.001f, 100.f));

		Cam->Translate(0, 0, ICMoveForward.Value() * T.GetDelta() * 3.5);
		Cam->Translate(ICMoveRight.Value() * T.GetDelta() * 3.5, 0, 0);
		Cam->Roll(ICRollRight.Value() * T.GetDelta());
		Cam->Translate(0, ICMoveUp.Value() * T.GetDelta(), 0);

		printf("Pos: X: %f, Y: %f, Z: %f       \r", PlayerTrans->GetTransform().Position.X, PlayerTrans->GetTransform().Position.Y, PlayerTrans->GetTransform().Position.Z);

		Renderer.Flush();

		if (T.OnSecond()) {
			Window->SetTitle("FPS: " + std::to_string(T.GetAvgFPS()));
		}
	}

	Level.Destroy();

	return 0;

}