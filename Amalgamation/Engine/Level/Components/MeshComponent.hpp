#pragma once

#include <Engine/Graphics/OpenGL/GLMesh.hpp>
#include <Core/Graphics/Shader.hpp>
#include "TransformComponent.hpp"
#include <Core/Level/Entity.hpp>
#include <Core/Graphics/Renderer.hpp>

namespace Amalgamation {

	class MeshComponent : public Component, public GraphicsClass {

		TransformComponent* m_TransformComponentPtr;
		Mesh* m_Mesh;
		Shader* m_Shader;
		Window* m_Window;

	public:

		MeshComponent(Window* Window) : GraphicsClass(Window->GetAPI()), m_Window(Window) {}
		~MeshComponent() { SafeDelete(m_Mesh); }

		MeshComponent* CreateMesh(const MeshData& Data, Shader* Shader) {
			if (m_API == API::OpenGL && Shader->GetAPI() == API::OpenGL) {
				m_Mesh = new GLMesh(static_cast<GLShader*>(Shader));
				m_Mesh->PushData(Data);
			}
			else {
				throw Error("AE: Invalid API");
			}

			if (static_cast<Entity*>(m_Parent)->GetComponentByType<TransformComponent>()) {
				m_TransformComponentPtr = static_cast<Entity*>(m_Parent)->GetComponentByType<TransformComponent>();
			}
			else {
				m_TransformComponentPtr = static_cast<Entity*>(m_Parent)->AddComponent<TransformComponent>();
			}

			m_Mesh->SetTransform(&m_TransformComponentPtr->GetTransform());

			return this;
		}

		MeshComponent* AddTexture(Texture* TexturePtr) {
			m_Mesh->AddTexture(TexturePtr);
			return this;
		}

		Mesh* GetMeshPtr() {
			return m_Mesh;
		}

		void Awake() override {}

		void Update(float Delta) override {
			m_Mesh->Draw();
		}

		void Destroy() override {}

	};

}