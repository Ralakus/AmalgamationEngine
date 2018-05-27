
namespace Amalgamation {

	FORCEINLINE GLMesh::GLMesh(GLShader * ShaderPtr) : Mesh(API::OpenGL), m_ShaderPtr(ShaderPtr) {}

	FORCEINLINE GLMesh::~GLMesh() {}

	FORCEINLINE bool GLMesh::PushData(const MeshData & Data) {
		if (Data.Vertices.size() > 0) {
			m_MeshData = Data;
			InterlaceData();

			m_ArrayBuffer.PushData(m_InterlacedData.data(), sizeof(float) * m_InterlacedData.size());
			m_ElementBuffer.PushData(m_MeshData.Indices.data(), m_MeshData.Indices.size());

			m_ArrayBuffer.GetLayout().Push<float>(3);
			m_ArrayBuffer.GetLayout().Push<float>(3);
			m_ArrayBuffer.GetLayout().Push<float>(2);

			m_VertexArray.AddBuffer(m_ArrayBuffer);

			return true;
		}
		else {
			return false;
		}
	}

	FORCEINLINE bool GLMesh::AddTexture(Texture * TexturePtr) {
		if (reinterpret_cast<GraphicsClass*>(TexturePtr)->GetAPI() == API::OpenGL) {
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
		}
		return false;
	}

	FORCEINLINE const GLArrayBuffer & GLMesh::GetArrayBuffer() const { return m_ArrayBuffer; }

	FORCEINLINE const GLElementBuffer & GLMesh::GetElementBuffer() const { return m_ElementBuffer; }

	FORCEINLINE const GLVertexArray & GLMesh::GetVertexArray() const { return m_VertexArray; }

	FORCEINLINE GLShader * GLMesh::GetShader() { return m_ShaderPtr; }

	FORCEINLINE const GLShader * GLMesh::GetShader() const { return m_ShaderPtr; }


}