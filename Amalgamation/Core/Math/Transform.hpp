#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Amalgamation {

	class Transform {

	public:

		glm::vec3 Position;
		glm::vec3 Scale = { 1.f, 1.f, 1.f };
		glm::quat Rotation;

	};

	namespace Math {
		glm::mat4 MakeModelMatrix(const Transform& TransformData);
	}

}

#include "Transform.inl"