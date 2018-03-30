#pragma once

#include "../GLCommon.hpp"

namespace Amalgamation {

	class ElementBuffer {

	private:

		uint32 m_BufferID;
		uint32 m_Count;

	public:
		ElementBuffer() {
			GLCall(glGenBuffers(1, &m_BufferID));
		}
		ElementBuffer(const uint32* Data, uint32 Count) : m_Count(Count) {
			GLCall(glGenBuffers(1, &m_BufferID));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
			GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32), Data, GL_STATIC_DRAW));
		}
		~ElementBuffer() {
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			GLCall(glDeleteBuffers(1, &m_BufferID));
		}

		inline void PushData(const uint32* Data, uint32 Count) {
			m_Count = Count;
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
			GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32), Data, GL_STATIC_DRAW));
		}
		inline void Bind() const { GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID)); }
		inline void Unbind() const { GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); }

		inline const uint32 GetCount() const { return m_Count; }
		inline const uint32& GetID() const { return m_BufferID; }

	};

	//using IndexBuffer = ElementBuffer;
	typedef ElementBuffer IndexBuffer;
}