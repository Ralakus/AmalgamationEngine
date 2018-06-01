#pragma once

#include "TransformComponent.hpp"
#include <Core/Level/Component.hpp>
#include <Core/Level/Entity.hpp>
#include <Core/Math/Vector/Vector3.hpp>
#include <Core/Math/Quaternion/Quaternion.hpp>
#include <Core/Math/Matrix/Matrix4x4.hpp>

namespace Amalgamation {

	/*At 0,0,0 Rotation, camera faces towrard Z+ axis*/
	class CameraComponent : public Component {

		TransformComponent* m_Transform;

		Transform* m_TransformPtr;

		Math::Mat4 m_Projection;

	public:

		CameraComponent() {}

		~CameraComponent() {}

		Math::Mat4 View() const {
			Math::Mat4 View(1);
			View *= m_TransformPtr->Rotation;
			return View.Multiply(Math::Matrix4::Translate((m_TransformPtr->Position * -1.f)));
			//return Math::Mat4(1);
		}

		void Translate(const Math::Vec3& Translation) {
			//m_TransformPtr->Position += (m_TransformPtr->Rotation.Multiply(Translation));
		}
		void Translate(float X, float Y, float Z) {
			//m_TransformPtr->Position += glm::vec3(X, Y, Z) * m_TransformPtr->Rotation;
		}

		void Rotate(float Angle, const Math::Vec3& Axis) {
			//m_TransformPtr->Rotation *= glm::angleAxis(Angle, Axis * m_TransformPtr->Rotation);
		}
		void Rotate(float Angle, float X, float Y, float Z) {
			//m_TransformPtr->Rotation *= glm::angleAxis(Angle, glm::vec3(X, Y, Z) * m_TransformPtr->Rotation);
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

		Math::Vec3 GetFront() const {
			/*glm::vec3 CamEuler = glm::eulerAngles(m_TransformPtr->Rotation);
			glm::vec3 CamFront = glm::normalize(glm::vec3(

				cos(CamEuler.y) * cos(CamEuler.x),
				sin(CamEuler.x),
				sin(CamEuler.y) * cos(CamEuler.x)

			)) * m_TransformPtr->Rotation;*/
			return m_TransformPtr->Rotation.Euler();
		}

		Math::Vec3 GetRight() const {
			return GetFront().Cross(Math::Vec3(0, 1, 0)).Normalize();
		}

		Math::Vec3 GetUp() const {
			return GetRight().Cross(GetFront()).Normalize();
		}

		void SetProjection(const Math::Mat4 Projection) {
			m_Projection = Projection;
		}

		const Math::Mat4 GetProjection() {
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