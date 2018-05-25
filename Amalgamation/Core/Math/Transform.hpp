#pragma once

#include "Vector/Vector3.hpp"
#include "Quaternion/Quaternion.hpp"

namespace Amalgamation {

	class Transform {

	public:

		Math::Vec3 Position;
		Math::Vec3 Scale;
		Math::Quat Rotation;

	};

}