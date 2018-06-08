#pragma once

#include "Vector/Vector3.hpp"
#include "Quaternion/Quaternion.hpp"
#include "Matrix/Matrix4x4.hpp"

namespace Amalgamation {

	class Transform {

	public:

		Math::Vec3 Position;
		Math::Vec3 Scale;
		Math::Quat Rotation;

	};

	namespace Math {
		template<class MathType = MATH_TYPE>
		TMatrix4x4<MathType> MakeModelMatrix(const Transform& TransformData);
	}

}

#include "Transform.inl"