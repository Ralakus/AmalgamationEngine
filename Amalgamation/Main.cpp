#include <iostream>
#include <Core/World/World.hpp>
#include <Engine/World/Components/MeshComponent.hpp>
#include <Engine/Graphics/OpenGL/Renderers/GLBasicRenderer.hpp>
#include <Engine/World/Components/CameraComponent.hpp>
#include <Engine/World/Entities/BasicEntity.hpp>
#include <Engine/Graphics/OpenGL/GLWindow.hpp>

using namespace Amalgamation;

class TestRenderer : public Renderer {

	std::vector<GLMesh*> m_Meshes;

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
	
	Window* Window = new GLWindow("Test", 1280, 720, false);

	Shader* Shader = new GLShader();

	World World;

	BasicEntity* Plane;

	TestRenderer Renderer;

	Plane = World.CreateEntity<BasicEntity>();
	Plane->AddComponent<MeshComponent>(&Renderer)->CreateMesh(Mesh::MakeMeshData(Mesh::Primitive::Plane), Shader);

	World.Awake();

	while (Window->IsValid()) {

		Window->Update();
		World.Update(0.f);

		Renderer.Flush();

	}

	World.Destroy();

	SafeDelete(Window);
	SafeDelete(Shader);

	return 0;
}