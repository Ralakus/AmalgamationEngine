#pragma once

#include <Core/Platform/Platform.hpp>
#include "Texture.hpp"
#include "GraphicsClass.hpp"
#include <Core/Math/Transform.hpp>
#include <Core/Math/Vector/Vector2.hpp>

#include <vector>

namespace Amalgamation {

	struct MeshData {
		std::vector<Math::Vec3> Vertices;
		std::vector<Math::Vec3> Normals;
		std::vector<Math::Vec2> TextureCoords;
		std::vector<uint32> Indices;
	};

	struct CubeMeshData {

		std::vector<Math::Vec3> Vertices = {
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
		std::vector<Math::Vec3> Normals = {
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
		std::vector<Math::Vec2> TextureCoords = {
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

		std::vector<Math::Vec3> Vertices = {
			{ -0.5, -0.5, 0 },
			{  0.5, -0.5, 0 },
			{  0.5,  0.5, 0 },
			{ -0.5,  0.5, 0 }
		};
		std::vector<Math::Vec3> Normals = {
			{ 0,0,1 },
			{ 0,0,1 },
			{ 0,0,1 },
			{ 0,0,1 }
		};
		std::vector<Math::Vec2> TextureCoords = {
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

	class Mesh : public GraphicsClass {

		friend class MeshComponent;

	protected:

		MeshData m_MeshData;

		std::vector<float> m_InterlacedData;

		std::vector<Texture*> m_Textures;

		Transform* m_TransformPtr;

		void SetTransform(Transform* TransformPtr) { m_TransformPtr = TransformPtr; }


		void InterlaceData() {
			for (size_t i = 0; i < m_MeshData.Vertices.size(); i++) {
				m_InterlacedData.emplace_back(m_MeshData.Vertices[i].X);
				m_InterlacedData.emplace_back(m_MeshData.Vertices[i].Y);
				m_InterlacedData.emplace_back(m_MeshData.Vertices[i].Z);

				m_InterlacedData.emplace_back(m_MeshData.Normals[i].X);
				m_InterlacedData.emplace_back(m_MeshData.Normals[i].Y);
				m_InterlacedData.emplace_back(m_MeshData.Normals[i].Z);

				m_InterlacedData.emplace_back(m_MeshData.TextureCoords[i].X);
				m_InterlacedData.emplace_back(m_MeshData.TextureCoords[i].Y);
			}
		}

	public:

		Mesh(API API) : GraphicsClass(API) {}
		virtual ~Mesh()                    {}

		enum class Primitive {
			Plane, Cube, Sphere, Cone, Cylinder
		};

		virtual bool PushData(const MeshData& Data) {
			if (Data.Vertices.size() > 0) {
				m_MeshData = Data;
				InterlaceData();
				return true;
			}
			else {
				return false;
			}
		}

		static MeshData MakeMeshData(const std::vector<Math::Vec3>& Verticies, const std::vector<Math::Vec3>& Normals, const std::vector<Math::Vec2>& TextureCoords, const std::vector<uint32>& Indices) {
			return MeshData({ Verticies, Normals, TextureCoords, Indices });
		}

		static MeshData MakeMeshData(Primitive Shape) {
			static CubeMeshData CubeMesh;
			static PlaneMeshData PlaneMesh;
			switch (Shape) {
			case Primitive::Cube:
				return MeshData({ CubeMesh.Vertices, CubeMesh.Normals, CubeMesh.TextureCoords, CubeMesh.Indices });
				break;
			case Primitive::Plane:
				return MeshData({ PlaneMesh.Vertices, PlaneMesh.Normals, PlaneMesh.TextureCoords, PlaneMesh.Indices });
				break;
			case Primitive::Sphere: 
				return MeshData();
				break;
			case Primitive::Cone:
				return MeshData();
				break;
			case Primitive::Cylinder:
				return MeshData();
				break;
			default:
				return MeshData();
				break;
			}
		}

		const Transform* GetTransform() const { return m_TransformPtr; }

		const std::vector<Math::Vec3>& GetVertices()       const { return m_MeshData.Vertices; }
		const std::vector<Math::Vec3>& GetNormals()        const { return m_MeshData.Normals; }
		const std::vector<Math::Vec2>& GetTextureCoords()  const { return m_MeshData.TextureCoords; }
		const std::vector<uint32>&    GetIndices()        const { return m_MeshData.Indices; }

		const std::vector<float>&     GetInterlacedData() const { return m_InterlacedData; }

		const std::vector<Texture*>& GetTextures() const { return m_Textures; }

		virtual bool AddTexture(Texture* TexturePtr) {
			if (m_Textures.size() <= 0) {
				m_Textures.push_back(TexturePtr);
				return true;
			}
			else {
				for (size_t i = 0; i <= m_Textures.size(); i++) {
					if (m_Textures[i]->GetFilePath() == TexturePtr->GetFilePath()) {
						continue;
					}
					else {
						m_Textures.push_back(TexturePtr);
						return true;
					}
				}
			}
			return false;
		}

		virtual bool RemoveTexture(Texture* TexturePtr) {
			if (m_Textures.size() > 0) {
				for (size_t i = 0; i < m_Textures.size(); i++) {
					if (TexturePtr == m_Textures[i]) {
						m_Textures.erase(m_Textures.begin() + i);
						return true;
					}
					else {
						continue;
					}
				}
				return false;
			}
			else {
				return false;
			}
		}

		virtual bool HasTexture(Texture* TexturePtr) {
			if (m_Textures.size() > 0) {
				for (size_t i = 0; i < m_Textures.size(); i++) {
					if (TexturePtr == m_Textures[i]) {
						return true;
					}
					else {
						continue;
					}
				}
				return false;
			}
			else {
				return false;
			}
		}


	};
}