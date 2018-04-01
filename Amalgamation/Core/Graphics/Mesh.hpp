#pragma once

#include <Core/Platform/Platform.hpp>

#include <vector>
#include <glm/glm.hpp>

namespace AmalgamationEngine {

	struct MeshData {

		std::vector<glm::vec3> Vertices;
		std::vector<glm::vec3> Normals;
		std::vector<glm::vec2> TextureCoords;
		std::vector<uint64> Indices;

	};

	class Mesh {

	private:

		MeshData m_MeshData;


	public:

		Mesh() {}
		virtual ~Mesh() {}

	};


}