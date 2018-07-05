#pragma once

#include "TransformComponent.hpp"
#include <Core/Level/Component.hpp>
#include <Core/Level/Entity.hpp>

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Amalgamation {

	/*At 0,0,0 Rotation, camera faces towrard Z+ axis*/
	class CameraComponent : public Component {

		TransformComponent* m_Transform;

		TransformData* m_TransformPtr;

		glm::mat4 m_Projection;

		glm::vec2 m_LastMousePos;
		glm::vec2 m_MouseDelta;

		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_Right = glm::vec3();

	public:

		CameraComponent() {}
		~CameraComponent() {}

		float Sensitivity = 1.f;
		bool ConstrainPitch = true;

		glm::mat4 View() const {
			return glm::translate(glm::mat4_cast(m_TransformPtr->Rotation), m_TransformPtr->Position);
		}

		void Translate(const glm::vec3& Translation) {
			m_TransformPtr->Position += Translation * m_TransformPtr->Rotation;
		}
		void Translate(float X, float Y, float Z) {
			m_TransformPtr->Position += glm::vec3(X, Y, Z) * m_TransformPtr->Rotation;
		}

		void Rotate(float Angle, const glm::vec3& Axis) {
			m_TransformPtr->Rotation *= glm::angleAxis(Angle, Axis * m_TransformPtr->Rotation);
		}
		void Rotate(float Angle, float X, float Y, float Z) {
			m_TransformPtr->Rotation *= glm::angleAxis(Angle, glm::vec3(X, Y, Z) * m_TransformPtr->Rotation);
		}

		void Yaw(float Angle) {
			Rotate(Angle, 0.f, 1.f, 0.f);
		}
		void Pitch(float Angle) {
			Rotate(Angle, 1.f, 0.f, 0.f);
		}
		void Roll(float Angle) {
			Rotate(Angle, 0.f, 0.f, 1.f);
		}

		const glm::vec2& GetMouseDelta() const {
			return m_MouseDelta;
		}

		const glm::vec2& GetLastMousePos() const {
			return m_LastMousePos;
		}

		const glm::vec3& GetFront() const {
			return m_Front;
		}

		const glm::vec3 GetRight() const {
			return m_Right;
		}

		glm::vec3 GetUp() const {
			return m_Up;
		}

		void SetProjection(const glm::mat4 Projection) {
			m_Projection = Projection;
		}

		const glm::mat4 GetProjection() {
			return m_Projection;
		}

		virtual void Awake() override {
			if (static_cast<Entity*>(m_Parent)->GetComponentByType<TransformComponent>()) {
				m_Transform = static_cast<Entity*>(m_Parent)->GetComponentByType<TransformComponent>();
			}
			else {
				m_Transform = static_cast<Entity*>(m_Parent)->AddComponent<TransformComponent>();
			}

			m_TransformPtr = &m_Transform->GetTransform();
		}

		virtual void Update(float Delta) override {
			m_MouseDelta   = Input::Instance().GetMousePos() - m_LastMousePos;
			m_LastMousePos = Input::Instance().GetMousePos();

			m_MouseDelta *= Sensitivity;

			m_Front = glm::vec3(
				2.0f * (m_TransformPtr->Rotation.x * m_TransformPtr->Rotation.z + m_TransformPtr->Rotation.w * m_TransformPtr->Rotation.y),
				2.0f * (m_TransformPtr->Rotation.y * m_TransformPtr->Rotation.z - m_TransformPtr->Rotation.w * m_TransformPtr->Rotation.x),
				1.0f - 2.0f * (m_TransformPtr->Rotation.x * m_TransformPtr->Rotation.x + m_TransformPtr->Rotation.y * m_TransformPtr->Rotation.y)
			);

			m_Up = glm::vec3(
				2.0f * (m_TransformPtr->Rotation.x * m_TransformPtr->Rotation.y - m_TransformPtr->Rotation.w * m_TransformPtr->Rotation.z),
				1.0f - 2.0f * (m_TransformPtr->Rotation.x * m_TransformPtr->Rotation.x + m_TransformPtr->Rotation.z * m_TransformPtr->Rotation.z),
				2.0f * (m_TransformPtr->Rotation.y * m_TransformPtr->Rotation.z + m_TransformPtr->Rotation.w * m_TransformPtr->Rotation.x)
			);

			m_Right = glm::vec3(
				-(1.0f - 2.0f * (m_TransformPtr->Rotation.y * m_TransformPtr->Rotation.y + m_TransformPtr->Rotation.z * m_TransformPtr->Rotation.z)),
				-(2.0f * (m_TransformPtr->Rotation.x * m_TransformPtr->Rotation.y + m_TransformPtr->Rotation.w * m_TransformPtr->Rotation.z)),
				-(2.0f * (m_TransformPtr->Rotation.x * m_TransformPtr->Rotation.z - m_TransformPtr->Rotation.w * m_TransformPtr->Rotation.y))
			);
		}

		virtual void Destroy() override {

		}

	};

}