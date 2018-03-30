#pragma once

#include "TransformComponent.hpp"
#include <Core/World/Component/Component.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Amalgamation {

	/*At 0,0,0 Rotation, camera faces towrard -Z axis*/
	class CameraComponent : public Component {

		TransformComponent* m_Transform;

		Transform* m_TransformPtr;

		glm::mat4 m_Projection;

	public:

		CameraComponent() {}

		~CameraComponent() {}

		glm::mat4 View() const {
			return glm::translate(glm::mat4_cast(-m_TransformPtr->Rotation), -m_TransformPtr->Position);
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

		/*Need to fix by finding the correct math*/
		glm::vec3 GetFront() const {
			//glm::vec3 Euler = glm::eulerAngles(m_TransformPtr->Rotation);
			//return glm::vec3(sin(Euler.x), -tan(Euler.y), cos(Euler.z));
			return glm::normalize(View()[3]);
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

		}

		virtual void Destroy() override {

		}

	};

}