#pragma once

#include "../GLCommon.hpp"

namespace Amalgamation {

	class GLElementBuffer {

	private:

		uint32 m_BufferID;
		size_t m_Count;

		mutable bool m_Bound;

	public:
		GLElementBuffer();
		GLElementBuffer(const uint32* Data, size_t Count);
		~GLElementBuffer();

		inline void PushData(const uint32* Data, size_t Count);
		inline void Bind() const;
		inline void Unbind() const;

		inline size_t GetCount() const;
		inline uint32 GetID() const;

	};

	using GLIndexBuffer = GLElementBuffer;
	//typedef GLElementBuffer IndexBuffer;
}

#include "GLElementBuffer.inl"