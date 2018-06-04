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




	InputControl ICMoveForward;
	ICMoveForward.AddInput(Key::W, InputAction::Pressed,  1.f);
	ICMoveForward.AddInput(Key::W, InputAction::Held,     1.f);
	ICMoveForward.AddInput(Key::S, InputAction::Pressed, -1.f);
	ICMoveForward.AddInput(Key::S, InputAction::Held,    -1.f);
	ICMoveForward.AddInput(Key::W, InputAction::Released, 0.f);
	ICMoveForward.AddInput(Key::S, InputAction::Released, 0.f);

	InputControl ICMoveLeft;
	ICMoveLeft.AddInput(Key::A, InputAction::Pressed,  1.f);
	ICMoveLeft.AddInput(Key::A, InputAction::Held,     1.f);
	ICMoveLeft.AddInput(Key::D, InputAction::Pressed, -1.f);
	ICMoveLeft.AddInput(Key::D, InputAction::Held,    -1.f);
	ICMoveLeft.AddInput(Key::A, InputAction::Released, 0.f);
	ICMoveLeft.AddInput(Key::D, InputAction::Released, 0.f);

	InputControl ICRollLeft;
	ICRollLeft.AddInput(Key::Q, InputAction::Pressed,  1.f);
	ICRollLeft.AddInput(Key::Q, InputAction::Held,     1.f);
	ICRollLeft.AddInput(Key::E, InputAction::Pressed, -1.f);
	ICRollLeft.AddInput(Key::E, InputAction::Held,    -1.f);
	ICRollLeft.AddInput(Key::Q, InputAction::Released, 0.f);
	ICRollLeft.AddInput(Key::E, InputAction::Released, 0.f);

	InputControl ICMoveUp;
	ICMoveUp.AddInput(Key::Space, InputAction::Pressed,  1.f);
	ICMoveUp.AddInput(Key::Space, InputAction::Held,     1.f);
	ICMoveUp.AddInput(Key::C,     InputAction::Pressed, -1.f);
	ICMoveUp.AddInput(Key::C,     InputAction::Held,    -1.f);
	ICMoveUp.AddInput(Key::Space, InputAction::Released, 0.f);
	ICMoveUp.AddInput(Key::C,     InputAction::Released, 0.f);

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
	CameraComponent* Cam = Player->AddComponent<CameraComponent>();

	Entity* Cube;
	Cube = Level.CreateEntity<Entity>();
	Cube->AddComponent<MeshComponent>(&Renderer)->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Cube), &Shader);









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

		Cam->Translate(0, 0, -1 * ICMoveForward.Value() * T.GetDelta() * 3.5);
		Cam->Translate(-1 * ICMoveLeft.Value() * T.GetDelta() * 3.5, 0, 0);
		Cam->Roll(ICRollLeft.Value() * -1 * T.GetDelta());
		Cam->Translate(0, -1 * ICMoveUp.Value() * T.GetDelta(), 0);

		Renderer.Flush();

		if (T.OnSecond()) {
			Window->SetTitle("FPS: " + std::to_string(T.GetAvgFPS()));
		}
	}

	Level.Destroy();

	return 0;

}