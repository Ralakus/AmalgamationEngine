#pragma once

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
			this->Scale    = Scale;
		}

		void SetTransform(const Transform& Other) {
			this->Position = Other.Position;
			this->Rotation = Other.Rotation;
			this->Scale    = Other.Scale;
		}

		void SetPosition(const glm::vec3 Position) {
			this->Position = Position;
		}

		void SetRotation(const glm::quat& Rotation) {
			this->Rotation = Rotation;
		}

		void SetScale(const glm::vec3& Scale) {
			this->Scale = Scale;
		}
	};

}