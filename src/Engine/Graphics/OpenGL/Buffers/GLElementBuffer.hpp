#pragma once

#include "../GLCommon.hpp"

namespace Amalgamation {

	class GLElementBuffer {

	private:

		uint32_t m_BufferID;
		size_t m_Count;

		mutable bool m_Bound;

	public:
		GLElementBuffer();
		GLElementBuffer(const uint32_t* Data, size_t Count);
		~GLElementBuffer();

		inline void PushData(const uint32_t* Data, size_t Count);
		inline void Bind() const;
		inline void Unbind() const;

		inline size_t GetCount() const;
		inline uint32_t GetID() const;

	};

	using GLIndexBuffer = GLElementBuffer;
	//typedef GLElementBuffer IndexBuffer;
}

#ifndef AE_NO_IMPL
	#include "GLElementBuffer.inl"
#endif