#pragma once

#include <Core/Graphics/Mesh.hpp>
#include "GLShader.hpp"
#include "Buffers/GLArrayBuffer.hpp"
#include "Buffers/GLElementBuffer.hpp"
#include "Buffers/GLVertexArray.hpp"

namespace Amalgamation {

	class GLMesh : public Mesh {

		GLShader* m_ShaderPtr;

		GLArrayBuffer m_ArrayBuffer;
		GLElementBuffer m_ElementBuffer;
		GLVertexArray m_VertexArray;

	public:

		GLMesh(GLShader* ShaderPtr) : Mesh(API::OpenGL), m_ShaderPtr(ShaderPtr)  {}
		~GLMesh()                     {} 

		bool PushData(const MeshData& Data) override {
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

		bool AddTexture(Texture* TexturePtr) override {
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

		const GLArrayBuffer&   GetArrayBuffer()   const { return m_ArrayBuffer;   }
		const GLElementBuffer& GetElementBuffer() const { return m_ElementBuffer; }
		const GLVertexArray&   GetVertexArray()   const { return m_VertexArray;   }

		GLShader* GetShader() { return m_ShaderPtr; }
		const GLShader* GetShader() const { return m_ShaderPtr; }

	};

}