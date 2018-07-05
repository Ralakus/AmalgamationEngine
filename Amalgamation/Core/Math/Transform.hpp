#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Amalgamation {

	class TransformData {

	public:

		glm::vec3 Position;
		glm::vec3 Scale = { 1.f, 1.f, 1.f };
		glm::quat Rotation;

	};

	namespace Math {
		glm::mat4 MakeModelMatrix(const TransformData& TransformData);
	}

}

#include "Transform.inl"