#pragma once

#include "../../Graphics/OpenGL/Mesh.hpp"
#include "TransformComponent.hpp"
#include <Core/World/Component/Component.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <Engine/Graphics/OpenGL/Renderers/IRenderer.hpp>

namespace Amalgamation {

	/* The mesh component requires a transformation component, if one is not found on the entity, it will create one */
	class MeshComponent : public Component {

		TransformComponent* m_Transform;

		Mesh* m_Mesh;

		IRenderer* m_Renderer;

	public:

		MeshComponent(IRenderer* Renderer) : Component(), m_Renderer(Renderer) {}
		virtual ~MeshComponent() { delete m_Mesh; }

		void CreateMesh(const std::vector<glm::vec3>& Vertices, const std::vector<glm::vec3>& Normals, const std::vector<glm::vec2>& TextureCoords, const std::vector<uint32>& Indices, Shader* Shader) {
			m_Mesh = new Mesh(Vertices, Normals, TextureCoords, Indices, Shader);

			if (static_cast<Entity*>(m_Parent)->GetComponentByType<TransformComponent>()) {
				m_Transform = static_cast<Entity*>(m_Parent)->GetComponentByType<TransformComponent>();
			}
			else {
				m_Transform = static_cast<Entity*>(m_Parent)->AddComponent<TransformComponent>();
			}

			m_Mesh->SetTransform(&m_Transform->GetTransform());
		}

		MeshComponent* CreateMesh(const MeshData& Data, Shader* Shader) {
			m_Mesh = new Mesh(Data, Shader);

			if (static_cast<Entity*>(m_Parent)->GetComponentByType<TransformComponent>()) {
				m_Transform = static_cast<Entity*>(m_Parent)->GetComponentByType<TransformComponent>();
			}
			else {
				m_Transform = static_cast<Entity*>(m_Parent)->AddComponent<TransformComponent>();
			}

			m_Mesh->SetTransform(&m_Transform->GetTransform());

			return this;
		}

		bool AddTexture(Texture* TextureIn) {
			return m_Mesh->AddTexture(TextureIn);
		}

		virtual void Awake() override {
		}

		virtual void Update(float Delta) override {
			if (m_Mesh) {
				m_Renderer->Submit(m_Mesh);
			}
		}

		virtual void Destroy() override {
		}



	};

}