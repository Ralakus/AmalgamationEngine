#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "../Types/Macros.hpp"

namespace Amalgamation {

	struct MeshData {

		std::vector<glm::vec3> Vertices;
		std::vector<glm::vec3> Normals;
		std::vector<glm::vec2> TextureCoords;
		std::vector<uint64> Indices;

	};

	class IMesh {

		IMesh() {}
		virtual ~IMesh() {}

	};

}