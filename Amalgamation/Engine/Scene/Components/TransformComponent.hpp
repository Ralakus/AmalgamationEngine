#pragma once

#include <Core/Math/Transform.hpp>
#include <Core/Scene/ComponentSystem.hpp>

namespace Amalgamation {

	class TransformComponent : public Component {
		friend class TransformSystem;
	public:
		Transform Transform;
	};

}