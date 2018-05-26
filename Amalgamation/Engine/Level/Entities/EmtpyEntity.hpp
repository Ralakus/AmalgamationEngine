#pragma once

#include <Core/Level/Entity.hpp>

namespace Amalgamation {
	/* This is an entity that can be constructed and doesn't have any special functions */
	class EmptyEntity : public Entity {

	public:

		EmptyEntity() : Entity() {
		}

		virtual void Awake() override {
			AwakeComponets();
		}
		virtual void Update(float Delta) override {
			UpdateComponents(Delta);
		}
		virtual void Destroy() override {
			DestroyComponents();
		}

	};

}