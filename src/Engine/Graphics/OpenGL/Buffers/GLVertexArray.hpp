#pragma once

#include "../GLCommon.hpp"
#include "GLArrayBuffer.hpp"

namespace Amalgamation {

	class GLVertexArray {
	private:

		uint32_t m_ArrayID;

		mutable bool m_Bound;

	public:

		GLVertexArray();
		~GLVertexArray();

		inline void Bind() const;
		inline void Unbind() const;
		inline uint32_t GetID() const;

		void SetBuffer(const GLArrayBuffer& Buffer);

	};

}

#ifndef AE_NO_IMPL
	#include "GLVertexArray.inl"
#endif