#pragma once

#include <Core/Math/Transform.hpp>
#include <Core/Scene/ComponentSystem.hpp>

namespace Amalgamation {

	class TransformComponent : public Component {
		friend class TransformSystem;
		Transform m_Transform;
	};

	class TransformSystem : public TComponentSystem < TransformComponent >{
	public:
		TransformSystem() {}
		~TransformSystem() {}
		Transform & GetTransform(TransformComponent* TransComponent) {
			return TransComponent->m_Transform;
		}
	};

}