#include <iostream>
#include <Core/World/World.hpp>
#include <Core/Utilities/Time.hpp>
#include <Core/Utilities/AessetReader.hpp>
#include <Engine/World/Components/MeshComponent.hpp>
#include <Engine/Graphics/OpenGL/GLTexture.hpp>
#include <Engine/Graphics/OpenGL/Renderers/GLBasicRenderer.hpp>
#include <Engine/World/Components/CameraComponent.hpp>
#include <Engine/World/Entities/BasicEntity.hpp>
#include <Engine/Graphics/OpenGL/GLWindow.hpp>

using namespace Amalgamation;

class TestRenderer : public Renderer {

	DArray<GLMesh*> m_Meshes;

public:

	TestRenderer() : Renderer(API::OpenGL) {}
	~TestRenderer()                        {}

	void Begin() override {}
	void Submit(Mesh* Mesh) override {
		m_Meshes.push_back(static_cast<GLMesh*>(Mesh));
	}
	void End() override {}
	void Flush() override {
		for (GLMesh* M : m_Meshes) {

			M->GetVertexArray().Bind();
			M->GetElementBuffer().Bind();

			M->GetShader()->Bind();

			GLCall(glDrawElements(GL_TRIANGLES, M->GetElementBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));

		}
		m_Meshes.clear();
	}

};

int main() {

	AessetReader::Instance().LoadAeseet("UserSettings.aesset");

	float MSensitivity = AessetReader::Instance().GetProperty<float>("Mouse_Sensitivity") <= 0 ? 1 : AessetReader::Instance().GetProperty<float>("Mouse_Sensitivity");
	float MovementSpeed = AessetReader::Instance().GetProperty<float>("Movement_Speed") <= 0 ? 1 : AessetReader::Instance().GetProperty<float>("Movement_Speed");
	float CamFOV = AessetReader::Instance().GetProperty<float>("Camera_FOV") <= 0 ? 90 : AessetReader::Instance().GetProperty<float>("Camera_FOV");

	std::unique_ptr<Window> Window = std::make_unique<GLWindow>(
		"Noice", AessetReader::Instance().GetProperty<int>("Window_Width") == 0 ? 800 : AessetReader::Instance().GetProperty<int>("Window_Width"),
		AessetReader::Instance().GetProperty<int>("Window_Height") == 0 ? 600 : AessetReader::Instance().GetProperty<int>("Window_Height"),
		AessetReader::Instance().GetProperty<int>("Window_Fullscreen"));

	World World;

	Time Time;

	BasicEntity* Player;
	BasicEntity* Cube;
	BasicEntity* FloorPlane;
	BasicEntity* Cube2;

	GLBasicRenderer Renderer;

	GLShader Shader("TexturedShader.glsl");

	GLTexture T1;
	if (T1.LoadTexture(
		AessetReader::Instance().GetProperty<std::string>("Texture_Variable_0").c_str() == AessetReader::Instance().ReadError ? "NULL" : AessetReader::Instance().GetProperty<std::string>("Texture_Variable_0").c_str(),
		true, 0, 0))
	{
		std::cout << "Texture load successful" << std::endl;
	}
	else {
		std::cout << "Texture load failed!" << std::endl;
	}

	GLTexture T2;
	if (T2.LoadTexture(
		AessetReader::Instance().GetProperty<std::string>("Texture_Variable_1").c_str() == AessetReader::Instance().ReadError ? "NULL" : AessetReader::Instance().GetProperty<std::string>("Texture_Variable_1").c_str(),
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

	AessetReader::Instance().UnloadAesset();

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


		//glm::vec3 CamEuler = glm::eulerAngles(Player->GetTransform()->Rotation);
		//glm::vec3 CamFront = glm::normalize(glm::vec3(
		//
		//	cos(glm::radians(CamEuler.x)) * cos(glm::radians(CamEuler.y)),
		//	sin(glm::radians(CamEuler.y)),
		//	sin(glm::radians(CamEuler.x)) * cos(glm::radians(CamEuler.y))
		//
		//)) * Player->GetTransform()->Rotation;

		//printf("%f, %f, %f    \r", CamFront.x, CamFront.y, CamFront.z);

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