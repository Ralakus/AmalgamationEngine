#pragma once

#include "../GLCommon.hpp"

namespace Amalgamation {

	class GLElementBuffer {

	private:

		uint32 m_BufferID;
		size_t m_Count;

		mutable bool m_Bound;

	public:
		GLElementBuffer() {
			GLCall(glGenBuffers(1, &m_BufferID));
		}
		GLElementBuffer(const uint32* Data, size_t Count) : m_Count(Count) {
			GLCall(glGenBuffers(1, &m_BufferID));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
			GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32), Data, GL_STATIC_DRAW));
		}
		~GLElementBuffer() {
			try{
				GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
				GLCall(glDeleteBuffers(1, &m_BufferID));
			}
			catch (...) {
				return;
			}
		}

		inline void PushData(const uint32* Data, size_t Count) {
			m_Count = Count;
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
			GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32), Data, GL_STATIC_DRAW));
		}
		inline void Bind() const { if (!m_Bound) { GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID)); } }
		inline void Unbind() const { if (m_Bound) { GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); } }

		inline size_t GetCount() const { return m_Count; }
		inline uint32 GetID() const { return m_BufferID; }

	};

	//using IndexBuffer = ElementBuffer;
	typedef GLElementBuffer IndexBuffer;
}