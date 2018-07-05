#pragma once

#include <Core/Level/Entity.hpp>
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

		const TransformData* GetTransform() const { return &m_Transform->GetTransform(); }
		TransformData* GetTransform() { return &m_Transform->GetTransform(); }

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