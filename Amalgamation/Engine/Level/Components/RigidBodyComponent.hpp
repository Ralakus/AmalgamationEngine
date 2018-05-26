#pragma once

#include <Core/Level/Component.hpp>
#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Amalgamation {

	btVector3 GLMToBT(const glm::vec3& Vec) {
		return btVector3(Vec.x, Vec.y, Vec.z);
	}
	btQuaternion GLMToBT(const glm::quat& Quat) {
		return btQuaternion(Quat.x, Quat.y, Quat.z, Quat.w);
	}

	glm::vec3 BTToGLM(const btVector3& Vec) {
		return glm::vec3(Vec.x, Vec.y, Vec.z);
	}
	glm::quat BTToGLM(const btQuaternion& Quat) {
		return glm::quat(Quat.w, Quat.x, Quat.y, Quat.z);
	}

	class RigidBodyComponent : public Component {

		btCollisionShape* m_Shape;
		btDefaultMotionState* m_MotionState;
		btRigidBody::btRigidBodyConstructionInfo m_ConstructionInfo;
		btRigidBody* m_RigidBody;

	public:

		RigidBodyComponent(btCollisionShape* Shape) : m_MotionState(new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)))), m_Shape(Shape),
			m_ConstructionInfo(1, m_MotionState, m_Shape, btVector3()) {}
		~RigidBodyComponent() {}

		void Awake() override {}
		void Update(float Delta) override {}
		void Destroy() override {}

	};

}