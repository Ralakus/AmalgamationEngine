#pragma once

#include <Core/World/WorldPlugin.hpp>
#include <Core/Platform/Platform.hpp>
#include <btBulletDynamicsCommon.h>

namespace Amalgamation {

	class BulletPhysicsPlugin : public WorldPlugin {

	private:

		btBroadphaseInterface * m_Broadphase;
		btDefaultCollisionConfiguration* m_CollisionConfig;
		btCollisionDispatcher* m_CollisionDispatcher;
		btSequentialImpulseConstraintSolver* m_Solver;
		btDiscreteDynamicsWorld* m_DynamicsWorld;

		std::vector<btRigidBody*> m_RigidBodies;

		bool RegisterRigidBody(btRigidBody* RB) {

		}

	public:

		BulletPhysicsPlugin() : m_Broadphase(new btDbvtBroadphase()), m_CollisionConfig(new btDefaultCollisionConfiguration()), m_CollisionDispatcher(new btCollisionDispatcher(m_CollisionConfig)), m_Solver(new btSequentialImpulseConstraintSolver),
		m_DynamicsWorld(new btDiscreteDynamicsWorld(m_CollisionDispatcher, m_Broadphase, m_Solver, m_CollisionConfig)) {
			m_DynamicsWorld->setGravity(btVector3(0, -9.81, 0));
		}
		~BulletPhysicsPlugin() {
			SafeDelete(m_Broadphase);
			SafeDelete(m_CollisionConfig);
			SafeDelete(m_CollisionDispatcher);
			SafeDelete(m_Solver);
			SafeDelete(m_DynamicsWorld);
		}

		const btDiscreteDynamicsWorld* GetDynamics() const  {
			return m_DynamicsWorld;
		}

		void Awake() override {

		}

		void Update(float Delta) override {
			m_DynamicsWorld->stepSimulation(1 / 60.f, 10);
		}

		void Destroy() override {

		}

	};

}