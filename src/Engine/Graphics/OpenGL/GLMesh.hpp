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

		GLMesh(GLShader* ShaderPtr);
		~GLMesh();

		bool PushData(const MeshData& Data) override;

		bool AddTexture(Texture* TexturePtr) override;

		const GLArrayBuffer&   GetArrayBuffer()   const;
		const GLElementBuffer& GetElementBuffer() const;
		const GLVertexArray&   GetVertexArray()   const;

		GLShader* GetShader();
		const GLShader* GetShader() const;

	};

}

#ifndef AE_NO_IMPL
	#include "GLMesh.inl"
#endif