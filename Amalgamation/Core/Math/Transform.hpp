#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Amalgamation {

	class Transform {

	public:

		glm::vec3 Position;
		glm::vec3 Scale;
		glm::quat Rotation;

	};

	namespace Math {
		glm::mat4 MakeModelMatrix(const Transform& TransformData);
	}

}

#include "Transform.inl"