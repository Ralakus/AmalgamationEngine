#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Core/Lua/LuaState.hpp>

namespace Amalgamation {

	class Transform {
	public:
		Transform(const glm::vec3& Position = { 0.f,0.f,0.f }, const glm::quat& Rotation = { 1.f,0.f,0.f,0.f }, const glm::vec3& Scale = { 1.f,1.f,1.f }) : Position(Position), Rotation(Rotation), Scale(Scale),
			PX(this->Position.x), PY(this->Position.y), PZ(this->Position.z),
			RX(this->Rotation.x), RY(this->Rotation.y), RZ(this->Rotation.z), RW(this->Rotation.w),
			SX(this->Scale.x), SY(this->Scale.y), SZ(this->Scale.z)
		{}
		glm::vec3 Position;
		glm::quat Rotation;
		glm::vec3 Scale;

		float& PX, &PY, &PZ;
		float& RX, &RY, &RZ, &RW;
		float& SX, &SY, &SZ;

		void SetTransform(const glm::vec3 Position = { 0.f,0.f,0.f }, const glm::quat& Rotation = { 1.f, 0.f, 0.f, 0.f }, const glm::vec3& Scale = { 1.f, 1.f, 1.f }) {
			this->Position = Position;
			this->Rotation = Rotation;
			this->Scale = Scale;
		}

		void SetTransform(const Transform& Other) {
			this->Position = Other.Position;
			this->Rotation = Other.Rotation;
			this->Scale = Other.Scale;
		}

		void SetPosition(const glm::vec3 Position) {
			this->Position = Position;
		}

		void SetPosition(float X, float Y, float Z) {
			this->Position.x = X;
			this->Position.y = Y;
			this->Position.z = Z;
		}

		void SetRotation(const glm::quat& Rotation) {
			this->Rotation = Rotation;
		}

		void SetRotation(float X, float Y, float Z) {
			this->Rotation = glm::vec3(glm::radians(X), glm::radians(Y), glm::radians(Z));
		}

		void SetRotation(float X, float Y, float Z, float W) {
			this->Rotation.x = X;
			this->Rotation.y = Y;
			this->Rotation.z = Z;
			this->Rotation.w = W;
		}

		void SetScale(const glm::vec3& Scale) {
			this->Scale = Scale;
		}

		void SetScale(float X, float Y, float Z) {
			this->Scale.x = X;
			this->Scale.y = Y;
			this->Scale.z = Z;
		}

	};

}