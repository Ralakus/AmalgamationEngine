#pragma once

#include <Core/World/Component/Component.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Amalgamation {

	class Transform {
	public:
		Transform(const glm::vec3& Position = { 0.f,0.f,0.f }, const glm::quat& Rotation = { 1.f,0.f,0.f,0.f }, const glm::vec3& Scale = { 1.f,1.f,1.f }) : Position(Position), Rotation(Rotation), Scale(Scale) {}
		glm::vec3 Position;
		glm::quat Rotation;
		glm::vec3 Scale;

		void SetTransform(const glm::vec3 Position = { 0.f,0.f,0.f }, const glm::quat& Rotation = { 1.f, 0.f, 0.f, 0.f }, const glm::vec3& Scale = { 1.f, 1.f, 1.f }) {

			this->Position = Position;
			this->Rotation = Rotation;
			this->Scale = Scale;

		}

	};

	class TransformComponent : public Component {

		Transform m_Transform;

	public:

		TransformComponent() : Component() {}

		const Transform& GetTransform() const { return m_Transform; }

		Transform& GetTransform() { return m_Transform; }

		virtual void Awake() override {
		}
		virtual void Update(float Delta) override {
		}
		virtual void Destroy() override {
		}


	};


}