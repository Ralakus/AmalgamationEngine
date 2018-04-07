#pragma once

#include <Engine/Graphics/OpenGL/GLMesh.hpp>
#include <Core/Graphics/Shader.hpp>
#include "TransformComponent.hpp"
#include <Core/World/Entity.hpp>
#include <Core/Graphics/Renderer.hpp>

namespace Amalgamation {

	class MeshComponent : public Component, public GraphicsClass {

		TransformComponent* m_TransformComponentPtr;
		Mesh* m_Mesh;
		Renderer* m_Renderer;
		Shader* m_Shader;

	public:

		MeshComponent(Renderer* Renderer) : GraphicsClass(Renderer->GetAPI()), m_Renderer(Renderer) {}
		virtual ~MeshComponent() { SafeDelete(m_Mesh); }

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

		virtual void Awake() override {}

		virtual void Update(float Delta) override {
			if (m_Mesh) {
				m_Renderer->Submit(m_Mesh);
			}
		}

		virtual void Destroy() override {}

	};

}