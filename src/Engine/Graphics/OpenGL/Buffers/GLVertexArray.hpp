#pragma once

#include "../GLCommon.hpp"
#include "GLArrayBuffer.hpp"

namespace Amalgamation {

	class GLVertexArray {
	private:

		uint32 m_ArrayID;

		mutable bool m_Bound;

	public:

		GLVertexArray();
		~GLVertexArray();

		inline void Bind() const;
		inline void Unbind() const;
		inline uint32 GetID() const;

		void SetBuffer(const GLArrayBuffer& Buffer);

	};

}

#include "GLVertexArray.inl"