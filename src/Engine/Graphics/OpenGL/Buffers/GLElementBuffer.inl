
namespace Amalgamation {

	FORCEINLINE GLElementBuffer::GLElementBuffer() {
		GLCall(glGenBuffers(1, &m_BufferID));
	}

	FORCEINLINE GLElementBuffer::GLElementBuffer(const uint32_t * Data, size_t Count) : m_Count(Count) {
		GLCall(glGenBuffers(1, &m_BufferID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32_t), Data, GL_STATIC_DRAW));
	}

	FORCEINLINE GLElementBuffer::~GLElementBuffer() {
		try {
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			GLCall(glDeleteBuffers(1, &m_BufferID));
		}
		catch (...) {
			return;
		}
	}

	FORCEINLINE void GLElementBuffer::PushData(const uint32_t * Data, size_t Count) {
		m_Count = Count;
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32_t), Data, GL_STATIC_DRAW));
	}

	FORCEINLINE void GLElementBuffer::Bind() const { if (!m_Bound) { GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID)); } }

	FORCEINLINE void GLElementBuffer::Unbind() const { if (m_Bound) { GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); } }

	FORCEINLINE size_t GLElementBuffer::GetCount() const { return m_Count; }

	FORCEINLINE uint32_t GLElementBuffer::GetID() const { return m_BufferID; }


}