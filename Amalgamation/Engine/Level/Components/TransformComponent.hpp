#pragma once

#include <Core/Level/Component.hpp>
#include <Core/Math/Transform.hpp>

namespace Amalgamation {

	class TransformComponent : public Component {

		Transform m_Transform;

	public:

		TransformComponent() : Component() {}

		const Transform& GetTransform() const { return m_Transform; }

		Transform& GetTransform() { return m_Transform; }

		virtual void Awake() override {
		}
		virtual void Update(float Delta) override {
		}
		virtual void Destroy() override {
		}


	};


}