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

	Log::Note("TODO:" + Config.Get<std::string>("TODO", " Error reading TODO"));

	std::unique_ptr<Window> Window = std::make_unique<GLWindow>(
		Config.Get<std::string> ("WindowName", "Noice"), 
		Config.Get<unsigned int>("WindowWidth", 1280), 
		Config.Get<unsigned int>("WindowHeight", 720),
		Config.Get<bool>        ("WindowFullscreen", false)
	);

	Window->LockMouse(true);

	Time T;

	GLint ViewPort[4];

	float CamFOV = Config.Get<float>("CamFOV", 90.f);
	float MovementSpeed = Config.Get<float>("MovementSpeed", 3.5f);
	float MouseSensitivity = Config.Get<float>("MouseSensitivity", 3.5f);

	//================================================
	//Binds input
	//================================================


	EventLambdaCallback ECCloseWindow([&]() -> void { Window->Close(); });
	Input::Instance().RegisterKeyAction("CloseWindow", Input::Instance().KeyFromAesset(Config, "CloseWindowKey"), InputAction::Held);
	Input::Instance().RegisterCallback("CloseWindow", &ECCloseWindow);

	EventLambdaCallback ECToggleMouseLock([&]() -> void { Window->LockMouse(!Window->IsMouseLocked()); });
	Input::Instance().RegisterKeyAction("ToggleMouseLock", Input::Instance().KeyFromAesset(Config, "ToggleMouseLockKey"), InputAction::Held);
	Input::Instance().RegisterCallback("ToggleMouseLock", &ECToggleMouseLock);

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

	Entity* Cube;
	Cube = Level.CreateEntity<Entity>();
	Cube->AddComponent<TransformComponent>();
	Cube->AddComponent<MeshComponent>(Window._Myptr())->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Cube), &Shader)->GetMeshPtr()->SetDrawFunction([&](Mesh* M) {

		GLMesh* GLM = static_cast<GLMesh*>(M);

		GLM->GetVertexArray().Bind();

		GLM->GetElementBuffer().Bind();
		GLM->GetShader()->Bind();

		GLM->GetShader()->SetUniform("u_Projection", Cam->GetProjection());
		GLM->GetShader()->SetUniform("u_View", Cam->View());
		GLM->GetShader()->SetUniform("u_Model", Math::MakeModelMatrix(*GLM->GetTransform()));
		GLM->GetShader()->SetUniform("u_Color", 1.f, 0.5f, 0.3f, 1.f);

		GLCall(glDrawElements(GL_TRIANGLES, GLM->GetElementBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));

	});
	Cube->GetComponentByType<TransformComponent>()->GetTransform().Position.z = -1.f;
	Cube->GetComponentByType<TransformComponent>()->GetTransform().Scale = glm::vec3(0.5);


	//================================================
	//Begin game loop
	//================================================

	glm::vec2 LastMousePos;
	glm::vec2 MouseDelta;

	Level.Awake();

	while (Window->IsValid()) {

		T.Update();
		Level.Update(T.GetDelta());
		Window->Update(); 

		GLCall(glGetIntegerv(GL_VIEWPORT, ViewPort));
		Cam->SetProjection(glm::perspective(CamFOV, (float)ViewPort[2] / (float)ViewPort[3], 0.001f, 100.f));
		
		MouseDelta   = Input::Instance().GetMousePos() - LastMousePos;
		LastMousePos = Input::Instance().GetMousePos();

		Cam->Translate(0, 0, -1 * ICMoveForward.Value() * T.GetDelta() * MovementSpeed);
		Cam->Translate(ICMoveRight.Value() * T.GetDelta() * MovementSpeed, 0, 0);
		Cam->Roll(ICRollRight.Value() * T.GetDelta() * MovementSpeed / 2);
		Cam->Translate(0, ICMoveUp.Value() * T.GetDelta() * MovementSpeed, 0);
		Cam->Pitch(MouseDelta.y * T.GetDelta() * MouseSensitivity);
		Cam->Yaw(MouseDelta.x * T.GetDelta() * MouseSensitivity);

		//printf("Pos: X: %f, Y: %f, Z: %f       \r", PlayerTrans->GetTransform().Position.x, PlayerTrans->GetTransform().Position.y, PlayerTrans->GetTransform().Position.z);

		if (T.OnSecond()) {
			Window->SetTitle("FPS: " + std::to_string(T.GetAvgFPS()));
		}
	}

	Level.Destroy();

	return 0;

}