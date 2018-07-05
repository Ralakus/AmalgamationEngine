#pragma once

#include <Core/Scene/Component.hpp>
#include <Core/Math/Transform.hpp>

namespace Amalgamation {

	class TransformComponent : public TComponent<TransformComponent> {

		TransformData Transfrom;

	};

}