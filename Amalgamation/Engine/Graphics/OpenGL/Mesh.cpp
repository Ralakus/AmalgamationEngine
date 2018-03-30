#include "Mesh.hpp"

#include "GLShader.hpp"

namespace Amalgamation {

	Mesh::Mesh(const std::vector<glm::vec3>& Verticies, const std::vector<glm::vec3>& Normals, const std::vector<glm::vec2>& TextureCoords, const std::vector<uint32>& Indices, Shader* Shader)
		: m_Vertices(Verticies), m_Normals(Normals), m_TextureCoords(TextureCoords), m_Indices(Indices), m_Shader(Shader)
	{

		[&, this]() -> void // Lambda to parse and interlace data
		{
			for (uint64 i = 0; i < m_Vertices.size(); i++) {

				m_Data.emplace_back(m_Vertices[i].x);
				m_Data.emplace_back(m_Vertices[i].y);
				m_Data.emplace_back(m_Vertices[i].z);

				m_Data.emplace_back(m_Normals[i].x);
				m_Data.emplace_back(m_Normals[i].y);
				m_Data.emplace_back(m_Normals[i].z);

				m_Data.emplace_back(m_TextureCoords[i].x);
				m_Data.emplace_back(m_TextureCoords[i].y);

			}

		}();

		m_Buffer.PushData(m_Data.data(), sizeof(float) * m_Data.size());
		m_ElementBuffer.PushData(m_Indices.data(), m_Indices.size());

		m_Buffer.GetLayout().Push<float>(3);
		m_Buffer.GetLayout().Push<float>(3);
		m_Buffer.GetLayout().Push<float>(2);

		m_VAO.AddBuffer(m_Buffer);

	}

	Mesh::Mesh(const MeshData& Data, Shader* Shader)
		: m_Vertices(Data.Vertices), m_Normals(Data.Normals), m_TextureCoords(Data.TextureCoords), m_Indices(Data.Indices), m_Shader(Shader)
	{

		[&, this]() -> void // Lambda to parse and interlace data
		{
			for (uint64 i = 0; i < m_Vertices.size(); i++) {

				m_Data.emplace_back(m_Vertices[i].x);
				m_Data.emplace_back(m_Vertices[i].y);
				m_Data.emplace_back(m_Vertices[i].z);

				m_Data.emplace_back(m_Normals[i].x);
				m_Data.emplace_back(m_Normals[i].y);
				m_Data.emplace_back(m_Normals[i].z);

				m_Data.emplace_back(m_TextureCoords[i].x);
				m_Data.emplace_back(m_TextureCoords[i].y);

			}

		}();

		m_Buffer.PushData(m_Data.data(), sizeof(float) * m_Data.size());
		m_ElementBuffer.PushData(m_Indices.data(), m_Indices.size());

		m_Buffer.GetLayout().Push<float>(3);
		m_Buffer.GetLayout().Push<float>(3);
		m_Buffer.GetLayout().Push<float>(2);

		m_VAO.AddBuffer(m_Buffer);
	}

	Mesh::~Mesh()
	{
	}

	struct CubeMeshData {

		std::vector<glm::vec3> Vertices = {
			{ -0.5f, -0.5f, -0.5f },
			{  0.5f, -0.5f, -0.5f },
			{  0.5f,  0.5f, -0.5f },
			{  0.5f,  0.5f, -0.5f },
			{ -0.5f,  0.5f, -0.5f },
			{ -0.5f, -0.5f, -0.5f },

			{ -0.5f, -0.5f,  0.5f },
			{  0.5f, -0.5f,  0.5f },
			{  0.5f,  0.5f,  0.5f },
			{  0.5f,  0.5f,  0.5f },
			{ -0.5f,  0.5f,  0.5f },
			{ -0.5f, -0.5f,  0.5f },

			{ -0.5f,  0.5f,  0.5f },
			{ -0.5f,  0.5f, -0.5f },
			{ -0.5f, -0.5f, -0.5f },
			{ -0.5f, -0.5f, -0.5f },
			{ -0.5f, -0.5f,  0.5f },
			{ -0.5f,  0.5f,  0.5f },

			{  0.5f,  0.5f,  0.5f },
			{  0.5f,  0.5f, -0.5f },
			{  0.5f, -0.5f, -0.5f },
			{  0.5f, -0.5f, -0.5f },
			{  0.5f, -0.5f,  0.5f },
			{  0.5f,  0.5f,  0.5f },

			{ -0.5f, -0.5f, -0.5f },
			{  0.5f, -0.5f, -0.5f },
			{  0.5f, -0.5f,  0.5f },
			{  0.5f, -0.5f,  0.5f },
			{ -0.5f, -0.5f,  0.5f },
			{ -0.5f, -0.5f, -0.5f },

			{ -0.5f,  0.5f, -0.5f },
			{  0.5f,  0.5f, -0.5f },
			{  0.5f,  0.5f,  0.5f },
			{  0.5f,  0.5f,  0.5f },
			{ -0.5f,  0.5f,  0.5f },
			{ -0.5f,  0.5f, -0.5f }
		};
		std::vector<glm::vec3> Normals = {
			{ 0.0f,  0.0f, -1.0f },
			{ 0.0f,  0.0f, -1.0f },
			{ 0.0f,  0.0f, -1.0f },
			{ 0.0f,  0.0f, -1.0f },
			{ 0.0f,  0.0f, -1.0f },
			{ 0.0f,  0.0f, -1.0f },

			{ 0.0f,  0.0f, 1.0f },
			{ 0.0f,  0.0f, 1.0f },
			{ 0.0f,  0.0f, 1.0f },
			{ 0.0f,  0.0f, 1.0f },
			{ 0.0f,  0.0f, 1.0f },
			{ 0.0f,  0.0f, 1.0f },

			{ 1.0f,  0.0f,  0.0f },
			{ 1.0f,  0.0f,  0.0f },
			{ 1.0f,  0.0f,  0.0f },
			{ 1.0f,  0.0f,  0.0f },
			{ 1.0f,  0.0f,  0.0f },
			{ 1.0f,  0.0f,  0.0f },

			{ 1.0f,  0.0f,  0.0f },
			{ 1.0f,  0.0f,  0.0f },
			{ 1.0f,  0.0f,  0.0f },
			{ 1.0f,  0.0f,  0.0f },
			{ 1.0f,  0.0f,  0.0f },
			{ 1.0f,  0.0f,  0.0f },

			{ 0.0f, -1.0f,  0.0f },
			{ 0.0f, -1.0f,  0.0f },
			{ 0.0f, -1.0f,  0.0f },
			{ 0.0f, -1.0f,  0.0f },
			{ 0.0f, -1.0f,  0.0f },
			{ 0.0f, -1.0f,  0.0f },

			{ 0.0f,  1.0f,  0.0f },
			{ 0.0f,  1.0f,  0.0f },
			{ 0.0f,  1.0f,  0.0f },
			{ 0.0f,  1.0f,  0.0f },
			{ 0.0f,  1.0f,  0.0f },
			{ 0.0f,  1.0f,  0.0f }
		};
		std::vector<glm::vec2> TextureCoords = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
			{ 0.0f, 0.0f },

			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
			{ 0.0f, 0.0f },

			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
			{ 0.0f, 1.0f },
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },

			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
			{ 0.0f, 1.0f },
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },

			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 0.0f, 0.0f },
			{ 0.0f, 1.0f },

			{ 0.0f, 1.0f },
			{ 1.0f, 1.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 0.0f, 0.0f },
			{ 0.0f, 1.0f }
		};
		std::vector<uint32> Indices = {
			0,  1,  2,
			3,  4,  5,
			6,  7,  8,
			9,  10, 11,
			12, 13, 14,
			15, 16, 17,
			18, 19, 20,
			21, 22, 23,
			24, 25, 26,
			27, 28, 29,
			30, 31, 32,
			33, 34, 35,
		};

	};

	struct PlaneMeshData {

		std::vector<glm::vec3> Vertices = {
			{ -0.5, -0.5, 0 },
			{  0.5, -0.5, 0 },
			{  0.5,  0.5, 0 },
			{ -0.5,  0.5, 0 }
		};
		std::vector<glm::vec3> Normals = {
			{ 0,0,1 },
			{ 0,0,1 },
			{ 0,0,1 },
			{ 0,0,1 }
		};
		std::vector<glm::vec2> TextureCoords = {
			{ 0,0 },
			{ 1,0 },
			{ 1,1 },
			{ 0,1 }
		};
		std::vector<uint32> Indices = {
			0, 1, 2,
			2, 3, 0
		};

	};

	MeshData Mesh::MakeMeshData(const std::vector<glm::vec3>& Verticies, const std::vector<glm::vec3>& Normals, const std::vector<glm::vec2>& TextureCoords, const std::vector<uint32>& Indices)
	{
		return MeshData({Verticies, Normals, TextureCoords, Indices});
	}

	MeshData Mesh::MakeMeshData(Primitive Shape)
	{
		static CubeMeshData CubeMesh;
		static PlaneMeshData PlaneMesh;
		switch (Shape) {
		case Amalgamation::Mesh::Primitive::Cube:
			return MeshData({ CubeMesh.Vertices, CubeMesh.Normals, CubeMesh.TextureCoords, CubeMesh.Indices });
			break;
		case Amalgamation::Mesh::Primitive::Plane:
			return MeshData({ PlaneMesh.Vertices, PlaneMesh.Normals, PlaneMesh.TextureCoords, PlaneMesh.Indices });
			break;
		default:
			return MeshData();
			break;
		}
	}

}