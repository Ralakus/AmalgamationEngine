#pragma once

#include <glm/common.hpp>
#include "Buffers/GLArrayBuffer.hpp"
#include "Buffers/GLElementBuffer.hpp"
#include "Buffers/GLVertexArray.hpp"
#include "../../World/Components/TransformComponent.hpp"
#include "Texture.hpp"

namespace Amalgamation {

	class Shader;

	struct MeshData {
		std::vector<glm::vec3> Vertices;
		std::vector<glm::vec3> Normals;
		std::vector<glm::vec2> TextureCoords;
		std::vector<uint32> Indices;
	};

	class Mesh {

		friend class MeshComponent;

		std::vector<glm::vec3> m_Vertices;
		std::vector<glm::vec3> m_Normals;
		std::vector<glm::vec2> m_TextureCoords;
		std::vector<uint32> m_Indices;

		std::vector<Texture*> m_Textures;

		std::vector<float> m_Data;
		ArrayBuffer m_Buffer;
		ElementBuffer m_ElementBuffer;
		VertexArray m_VAO;

		Transform* m_Transform;

		Shader* m_Shader;

		void SetTransform(Transform* Transform) { m_Transform = Transform; }

	public:

		enum class Primitive {
			Cube, Plane
		};

		static MeshData MakeMeshData(const std::vector<glm::vec3>& Verticies, const std::vector<glm::vec3>& Normals, const std::vector<glm::vec2>& TextureCoords, const std::vector<uint32>& Indices);
		static MeshData MakeMeshData(Primitive Shape);

		Mesh(const std::vector<glm::vec3>& Verticies, const std::vector<glm::vec3>& Normals, const std::vector<glm::vec2>& TextureCoords, const std::vector<uint32>& Indices, Shader* Shader);
		Mesh(const MeshData& Data, Shader* Shader);
		~Mesh();

		bool AddTexture(Texture* TextureIn) {

			if (m_Textures.size() <= 0) {
				m_Textures.push_back(TextureIn);
				return true;
			}
			else {
				for (size_t i = 0; i <= m_Textures.size(); i++) {
					if (m_Textures[i]->GetFilePath() == TextureIn->GetFilePath()) {

					}
					else {
						m_Textures.push_back(TextureIn);
						return true;
					}
				}
			}

			return false;

		}

		const std::vector<Texture*> GetTextures() { return m_Textures; }

		const std::vector<glm::vec3>& GetVertices() const { return m_Vertices; }
		const std::vector<glm::vec3>& GetNormals() const { return m_Normals; }
		const std::vector<glm::vec2>& GetTextureCoords() const { return m_TextureCoords; }
		const std::vector<uint32>& GetIndices() const { return m_Indices; }
		const std::vector<float>& GetInerlacedData() const { return m_Data; }

		const ArrayBuffer& GetBuffer() const { return m_Buffer; }
		const ElementBuffer& GetElementBuffer() const { return m_ElementBuffer; }
		const VertexArray& GetVAO() const { return m_VAO; }

		const Shader* GetShader() const { return m_Shader; }
		Shader* GetShader() { return m_Shader; }

		const Transform* GetTransform() const { return m_Transform; }

	};

}