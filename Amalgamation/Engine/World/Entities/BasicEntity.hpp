#pragma once

#include <Core/World/Entity.hpp>
#include "../Components/TransformComponent.hpp"

namespace Amalgamation {

	class BasicEntity : public Entity {

		TransformComponent* m_Transform;

	public:

		BasicEntity() : Entity() {
			m_Transform = AddComponent<TransformComponent>();
		}

		~BasicEntity() {}

		const TransformComponent* GetTransformComponent() const { return m_Transform; }
		TransformComponent* GetTransformComponent() { return m_Transform; }

		const Transform* GetTransform() const { return &m_Transform->GetTransform(); }
		Transform* GetTransform() { return &m_Transform->GetTransform(); }

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