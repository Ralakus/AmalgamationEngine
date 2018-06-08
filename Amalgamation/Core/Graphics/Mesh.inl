
namespace Amalgamation {

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

	FORCEINLINE void Mesh::SetTransform(Transform * TransformPtr) { m_TransformPtr = TransformPtr; }

	FORCEINLINE void Mesh::InterlaceData() {
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

	FORCEINLINE Mesh::Mesh(API API) : GraphicsClass(API) {}

	FORCEINLINE Mesh::~Mesh() {}

	FORCEINLINE bool Mesh::PushData(const MeshData & Data) {
		if (Data.Vertices.size() > 0) {
			m_MeshData = Data;
			InterlaceData();
			return true;
		}
		else {
			return false;
		}
	}

	FORCEINLINE MeshData Mesh::MakeMeshData(const std::vector<Math::Vec3>& Verticies, const std::vector<Math::Vec3>& Normals, const std::vector<Math::Vec2>& TextureCoords, const std::vector<uint32>& Indices) {
		return MeshData({ Verticies, Normals, TextureCoords, Indices });
	}

	FORCEINLINE MeshData Mesh::MakeMeshData(Primitive Shape) {
		static CubeMeshData CubeMesh;
		static PlaneMeshData PlaneMesh;
		switch (Shape) {
		case Primitive::Cube:
			return { CubeMesh.Vertices, CubeMesh.Normals, CubeMesh.TextureCoords, CubeMesh.Indices };
			break;
		case Primitive::Plane:
			return { PlaneMesh.Vertices, PlaneMesh.Normals, PlaneMesh.TextureCoords, PlaneMesh.Indices };
			break;
			/*case Primitive::Sphere:
			return MeshData();
			break;
			case Primitive::Cone:
			return MeshData();
			break;
			case Primitive::Cylinder:
			return MeshData();
			break;*/
		default:
			return MeshData();
			break;
		}
	}

	FORCEINLINE void Mesh::Draw() {
		m_DrawFunction(this);
	}

	template<class Lambda>
	FORCEINLINE void Mesh::SetDrawFunction(Lambda Function) {
		m_DrawFunction = Function;
	}

	FORCEINLINE const Transform * Mesh::GetTransform() const { return m_TransformPtr; }

	FORCEINLINE const std::vector<Math::Vec3>& Mesh::GetVertices() const { return m_MeshData.Vertices; }

	FORCEINLINE const std::vector<Math::Vec3>& Mesh::GetNormals() const { return m_MeshData.Normals; }

	FORCEINLINE const std::vector<Math::Vec2>& Mesh::GetTextureCoords() const { return m_MeshData.TextureCoords; }

	FORCEINLINE const std::vector<uint32>& Mesh::GetIndices() const { return m_MeshData.Indices; }

	FORCEINLINE const std::vector<float>& Mesh::GetInterlacedData() const { return m_InterlacedData; }

	FORCEINLINE const std::vector<Texture*>& Mesh::GetTextures() const { return m_Textures; }

	FORCEINLINE bool Mesh::AddTexture(Texture * TexturePtr) {
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

	FORCEINLINE bool Mesh::RemoveTexture(Texture * TexturePtr) {
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

	FORCEINLINE bool Mesh::HasTexture(Texture * TexturePtr) {
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


}