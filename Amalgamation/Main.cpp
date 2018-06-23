#include <Core/Event/EventHandler.hpp>
#include <Core/Utilities/Time.hpp>
#include <Core/Utilities/Aesset.hpp>
#include <Core/Level/Level.hpp>
#include <Core/Graphics/Mesh.hpp>
#include <Core/Utilities/Random.hpp>
#include <Core/Input/InputControl.hpp>
#include <Core/Utilities/Random.hpp>
#include <Engine/Graphics/OpenGL/GLTexture.hpp>
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

	Aesset WindowConfig;
	WindowConfig.LoadDataString(Config.Get<std::string>("Window"));

	Aesset CamConfig;
	CamConfig.LoadDataString(Config.Get<std::string>("Camera"));

	Log::Note("TODO:" + Config.Get<std::string>("TODO", " Error reading TODO"));

	std::unique_ptr<Window> Window = std::make_unique<GLWindow>(
		WindowConfig.Get<std::string> ("Name", "Noice"), 
		WindowConfig.Get<unsigned int>("Width", 1280), 
		WindowConfig.Get<unsigned int>("Height", 720),
		WindowConfig.Get<bool>        ("Fullscreen", false)
	);

	Window->LockMouse(true);

	Time T;

	GLint ViewPort[4];

	float CamFOV = CamConfig.Get<float>("FOV", 90.f);
	float MovementSpeed = CamConfig.Get<float>("MovementSpeed", 3.5f);
	float MouseSensitivity = CamConfig.Get<float>("MouseSensitivity", 3.5f);

	//================================================
	//Binds input
	//================================================


	EventLambdaCallback ECCloseWindow([&]() -> void { Window->Close(); });
	Input::Instance().RegisterKeyAction("CloseWindow", Input::Instance().KeyFromAesset(WindowConfig, "CloseKey"), InputAction::Held);
	Input::Instance().RegisterCallback("CloseWindow", &ECCloseWindow);

	EventLambdaCallback ECToggleMouseLock([&]() -> void { Window->LockMouse(!Window->IsMouseLocked()); });
	Input::Instance().RegisterKeyAction("ToggleMouseLock", Input::Instance().KeyFromAesset(WindowConfig, "ToggleMouseLockKey"), InputAction::Held);
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

	
	Level TestLevel;

	Entity* Player = TestLevel.CreateEntity<Entity>();
	TransformComponent* PlayerTrans = Player->AddComponent<TransformComponent>();
	CameraComponent* Cam = Player->AddComponent<CameraComponent>();
	Renderer.SetCamera(Cam);

	GLTexture CrateTexture;
	CrateTexture.LoadTexture("container2.png", false, 0, 0);

	GLTexture OrangeTexture;
	Byte OrangeData[] = { 0xFF, 0x80, 0x4D };
	OrangeTexture.LoadTextureData(OrangeData, 1, 1, 3, 0, 0);

	GLTexture BlueTexture;
	Byte BlueData[] = { 0x40, 0x80, 0xFF };
	BlueTexture.LoadTextureData(BlueData, 1, 1, 3, 0, 0);

	Entity* Cube;
	Cube = TestLevel.CreateEntity<Entity>();
	auto& CubeTrans = Cube->AddComponent<TransformComponent>()->GetTransform();
	Cube->AddComponent<MeshComponent>(&Renderer)->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Cube), &Shader)->AddTexture(&CrateTexture);
	CubeTrans.Position.z = -1.f;

	Entity* Cube2;
	Cube2 = TestLevel.CreateEntity<Entity>();
	auto& Cube2Trans = Cube2->AddComponent<TransformComponent>()->GetTransform();
	Cube2->AddComponent<MeshComponent>(&Renderer)->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Pyramid), &Shader)->AddTexture(&OrangeTexture);
	Cube2Trans.Position.z = -1.f;
	Cube2Trans.Position.y = -0.5f;
	Cube2Trans.Scale = glm::vec3(0.5f);

	Entity* Cube3;
	Cube3 = TestLevel.CreateEntity<Entity>();
	auto& Cube3Trans = Cube3->AddComponent<TransformComponent>()->GetTransform();
	Cube3->AddComponent<MeshComponent>(&Renderer)->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Plane), &Shader)->AddTexture(&BlueTexture);
	Cube3Trans.Position.z = -2.f;



	Aesset PongConfig;
	PongConfig.LoadDataString(Config.Get<std::string>("Pong"));


	float PongZPlane      = PongConfig.Get<float>("ZPlane", -10.f);
	float PannelThickness = PongConfig.Get<float>("PannelThickness", 0.5f);
	float PannelHeight    = PongConfig.Get<float>("PannelHeight", 1.5f);
	float UpperBounds     = PongConfig.Get<float>("UpperBounds", 2.5);
	float LowerBounds     = PongConfig.Get<float>("LowerBounds", -2.5);
	float PannelSpeed     = PongConfig.Get<float>("PannelSpeed", 2.5f);

	Entity* Ball;
	Ball = TestLevel.CreateEntity<Entity>();
	auto& BallTrans = Ball->AddComponent<TransformComponent>()->GetTransform();
	Ball->AddComponent<MeshComponent>(&Renderer)->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Cube), &Shader)->AddTexture(&CrateTexture);
	BallTrans.Position.z = PongZPlane;
	BallTrans.Scale = { 0.25f, 0.25f, 0.25f };

	float BallAngle = 25.f;
	glm::vec3 BallVel = { 0.f, 0.25f, 0.f };
	float BallSpeed = PongConfig.Get<float>("BallSpeed", 1.5f);
	bool BallChangedThisFrame = false;
	bool HitDone = true;


	Entity* LPannel;
	LPannel = TestLevel.CreateEntity<Entity>();
	auto& LPannelTrans = LPannel->AddComponent<TransformComponent>()->GetTransform();
	LPannel->AddComponent<MeshComponent>(&Renderer)->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Cube), &Shader)->AddTexture(&BlueTexture);
	LPannelTrans.Position.z = PongZPlane;
	LPannelTrans.Scale = { PannelThickness, PannelHeight, 0.5f };
	LPannelTrans.Position.x = LowerBounds;
	bool LPannelSafe = false;

	Entity* RPannel;
	RPannel = TestLevel.CreateEntity<Entity>();
	auto& RPannelTrans = RPannel->AddComponent<TransformComponent>()->GetTransform();
	RPannel->AddComponent<MeshComponent>(&Renderer)->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Cube), &Shader)->AddTexture(&OrangeTexture);
	RPannelTrans.Position.z = PongZPlane;
	RPannelTrans.Scale = { PannelThickness, PannelHeight, 0.5f };
	RPannelTrans.Position.x = UpperBounds;
	bool RPannelSafe = false;


	auto LPannelLost = [&]() { Log::Text("Left Pannel Missed"); };
	auto RPannelLost = [&]() { Log::Text("Right Pannel Missed"); };


	//================================================
	//Begin game loop
	//================================================

	glm::vec2 LastMousePos;
	glm::vec2 MouseDelta;

	TestLevel.Awake();

	GLCall(glClearColor(0.7f, 0.7f, 0.7f, 0.7f));

	bool Cube2Up = true;

	bool Cube3ScaleUp = true;

	while (Window->IsValid()) {








		BallChangedThisFrame = false;

		if (BallAngle > 180) { BallAngle -= 360; }
		if (BallAngle < -180) { BallAngle += 360; }

		BallVel.x = sin(glm::radians(BallAngle));
		BallVel.y = cos(glm::radians(BallAngle));
		BallTrans.Position += (BallVel * T.GetDelta() * BallSpeed);





		if (BallTrans.Position.x > UpperBounds && !BallChangedThisFrame) {
			BallAngle *= -1;
			BallTrans.Position.x = UpperBounds;
			BallChangedThisFrame = true;
			HitDone = false;
			if (!RPannelSafe) {
				RPannelLost();
			}
		}
		else if (BallTrans.Position.x < LowerBounds && !BallChangedThisFrame) {
			BallAngle *= -1;
			BallTrans.Position.x = LowerBounds;
			BallChangedThisFrame = true;
			HitDone = false;
			if (!LPannelSafe) {
				LPannelLost();
			}
		}

		if (BallTrans.Position.y > UpperBounds && !BallChangedThisFrame) {
			BallAngle = (90 - BallAngle) * 2 + BallAngle;
			BallTrans.Position.y = UpperBounds;
			BallChangedThisFrame = true;
		}
		else if (BallTrans.Position.y < LowerBounds && !BallChangedThisFrame) {
			BallAngle = (90 - BallAngle) * 2 + BallAngle;
			BallTrans.Position.y = LowerBounds;
			BallChangedThisFrame = true;
		}


		if (BallTrans.Position.x < (UpperBounds - 0.5f) && BallTrans.Position.x > (LowerBounds - 0.5f)) {
			HitDone = true;
			LPannelSafe = false;
			RPannelSafe = false;
		}



		if ( //Left Pannel Collision
			((BallTrans.Position.x - (BallTrans.Scale.x / 2)) < (LPannelTrans.Position.x + (LPannelTrans.Scale.x / 2))) && //Horizontal bounds check
			((BallTrans.Position.y + (BallTrans.Scale.y / 2)) < (LPannelTrans.Position.y + (LPannelTrans.Scale.y / 2))) && //Upper Vertical bounds check
			((BallTrans.Position.y - (BallTrans.Scale.y / 2)) > (LPannelTrans.Position.y - (LPannelTrans.Scale.y / 2))) && //Lower Vertical bounds check
			HitDone
		) {
			BallAngle *= -1;
			//BallAngle *= (LPannelTrans.Position.y + BallTrans.Position.y) / 2;
			BallAngle += Random::Int(-25, 25);
			HitDone = false;
			LPannelSafe = true;
		}
		
		if ( //Right Pannel Collision
			((BallTrans.Position.x + (BallTrans.Scale.x / 2)) > (RPannelTrans.Position.x - (RPannelTrans.Scale.x / 2))) && //Horizontal bounds check
			((BallTrans.Position.y + (BallTrans.Scale.y / 2)) < (RPannelTrans.Position.y + (RPannelTrans.Scale.y / 2))) && //Upper Vertical bounds check
			((BallTrans.Position.y - (BallTrans.Scale.y / 2)) > (RPannelTrans.Position.y - (RPannelTrans.Scale.y / 2))) && //Lower Vertical bounds check
			HitDone
		) {
			BallAngle *= -1;
			//BallAngle *= (RPannelTrans.Position.y + BallTrans.Position.y) / 2;
			BallAngle += Random::Int(-25, 25);
			HitDone = false;
			RPannelSafe = true;
		}
		




		if (BallTrans.Position.x > 0 && BallVel.x > 0) {
			if (RPannelTrans.Position.y < LowerBounds + RPannelTrans.Scale.y / 2) {
				RPannelTrans.Position.y = LowerBounds + RPannelTrans.Scale.y / 2;
			}
			else if (RPannelTrans.Position.y > UpperBounds + RPannelTrans.Scale.y / 2) {
				RPannelTrans.Position.y = UpperBounds + RPannelTrans.Scale.y / 2;
			}
			else {
				RPannelTrans.Position.y = Math::Lerp(RPannelTrans.Position.y, BallTrans.Position.y, T.GetDelta() * BallSpeed * PannelSpeed);
			}
		}
		else {
			RPannelTrans.Position.y = Math::Lerp(RPannelTrans.Position.y, 0.f, T.GetDelta() * BallSpeed * PannelSpeed);
		}

		if (BallTrans.Position.x < 0 && BallVel.x < 0) {
			if (LPannelTrans.Position.y < LowerBounds + LPannelTrans.Scale.y / 2) {
				LPannelTrans.Position.y = LowerBounds + LPannelTrans.Scale.y / 2;
			}
			else if (LPannelTrans.Position.y > UpperBounds + LPannelTrans.Scale.y / 2) {
				LPannelTrans.Position.y = UpperBounds + LPannelTrans.Scale.y / 2;
			}
			else {
				LPannelTrans.Position.y = Math::Lerp(LPannelTrans.Position.y, BallTrans.Position.y, T.GetDelta() * BallSpeed * PannelSpeed);
			}
		}
		else {
			LPannelTrans.Position.y = Math::Lerp(LPannelTrans.Position.y, 0.f, T.GetDelta() * BallSpeed * PannelSpeed);
		}










		Cube3Trans.Scale.y = Math::Lerp(Cube3Trans.Scale.y, Cube3ScaleUp ? 2.5f : 1.f, T.GetDelta());
		Cube3Trans.Scale.x = Math::Lerp(Cube3Trans.Scale.x, Cube3ScaleUp ? 2.5f : 1.f, T.GetDelta());

		if (Cube3Trans.Scale.y > 2.4f) {
			Cube3ScaleUp = false;
		}
		else if (Cube3Trans.Scale.y < 1.1f) {
			Cube3ScaleUp = true;
		}
	
		Cube2Trans.Position.y = Math::Lerp(Cube2Trans.Position.y, Cube2Up ? 1.f : -1.f, T.GetDelta());

		if (Cube2Trans.Position.y > 0.9f) {
			Cube2Up = false;
		}
		else if (Cube2Trans.Position.y < -0.9f) {
			Cube2Up = true;
		}


		CubeTrans.Rotation *= glm::angleAxis(T.GetDelta(), glm::vec3(0.f, 1.f, 0.f));

		

		GLCall(glGetIntegerv(GL_VIEWPORT, ViewPort));
		Cam->SetProjection(glm::perspective(glm::radians(CamFOV), static_cast<float>(static_cast<float>(ViewPort[2]) / static_cast<float>(ViewPort[3])), 0.001f, 100.f));
		





		MouseDelta =   Input::Instance().GetMousePos() - LastMousePos;
		LastMousePos = Input::Instance().GetMousePos();

		Cam->Translate(0, 0, ICMoveForward.Value() * T.GetDelta() * MovementSpeed);
		Cam->Translate(ICMoveRight.Value() * T.GetDelta() * MovementSpeed * -1, 0, 0);
		Cam->Roll(ICRollRight.Value() * T.GetDelta() * MovementSpeed / 2);
		Cam->Translate(0, ICMoveUp.Value() * T.GetDelta() * MovementSpeed * -1, 0);
		Cam->Pitch(MouseDelta.y * T.GetDelta() * MouseSensitivity);
		Cam->Yaw(MouseDelta.x * T.GetDelta() * MouseSensitivity);






		T.Update();
		TestLevel.Update(T.GetDelta());
		Window->Update();
		Renderer.Flush();

		if (T.OnSecond()) {
			Window->SetTitle("FPS: " + std::to_string(T.GetAvgFPS()));
		}
	}

	TestLevel.Destroy();

	return 0;

}