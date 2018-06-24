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

		Transform* m_TransformPtr;

		glm::mat4 m_Projection;

		glm::vec2 m_LastMousePos;
		glm::vec2 m_MouseDelta;

		union {
			float Vec3[3];
			struct { float m_Pitch, m_Roll, m_Yaw; };
		};

		glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 Right = glm::vec3();

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

		glm::vec3 GetFront() const {
			glm::vec3 CamEuler = glm::eulerAngles(m_TransformPtr->Rotation);
			glm::vec3 CamFront = glm::normalize(glm::vec3(

				cos(CamEuler.y) * cos(CamEuler.x),
				sin(CamEuler.x),
				sin(CamEuler.y) * cos(CamEuler.x)

			)) * m_TransformPtr->Rotation;
			return CamFront;
		}

		glm::vec3 GetRight() const {
			//return glm::Normalize(glm::Cross(GetFront(), glm::Vec3(0, 1, 0)));
			return glm::normalize(glm::cross(GetFront(), glm::vec3(0, 1, 0)));
		}

		glm::vec3 GetUp() const {
			//return glm::Normalize(glm::Cross(GetRight(), GetUp()));
			return glm::normalize(glm::cross(GetRight(), GetUp()));
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

			if (ConstrainPitch)
			{
				if (m_Pitch > 89.0f) {
					m_Pitch = 89.0f;
				}
				if (m_Pitch < -89.0f) {
					m_Pitch = -89.0f;
				}
			}

			m_Yaw += m_MouseDelta.x;
			m_Pitch += m_MouseDelta.y;


			Front = glm::normalize(glm::vec3(
				cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)),
				sin(glm::radians(m_Pitch)),
				sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch))
			));

			Right = glm::normalize(glm::cross(Front, glm::vec3(0, 1, 0)));
			Up = glm::normalize(glm::cross(Right, Front));

			m_TransformPtr->Rotation = glm::lookAt(m_TransformPtr->Position, m_TransformPtr->Position - Front, Up);
		}

		virtual void Destroy() override {

		}

	};

}