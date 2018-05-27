
namespace Amalgamation {

	//============================================
	//OpenGL Array Element
	//============================================

	FORCEINLINE GLArrayElement::GLArrayElement(uint32 Type, uint32 Count, int8 Normalized) : Type(Type), Count(Count), Normalized(Normalized) {}

	//============================================
	//OpenGL Array Buffer Layout
	//============================================

	FORCEINLINE uint32 GLArrayBufferLayout::GetSizeOfType(uint32 Type) {
		switch (Type) {
		case GL_FLOAT:         return sizeof(GLfloat);
		case GL_INT:           return sizeof(GLint);
		case GL_UNSIGNED_INT:  return sizeof(GLuint);
		case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
		default: return 0;
		}
		return 0;
	}

	FORCEINLINE GLArrayBufferLayout::GLArrayBufferLayout() : m_Stride(0) {}

	FORCEINLINE const std::vector<GLArrayElement>& GLArrayBufferLayout::GetElements() const { return m_Elements; }

	FORCEINLINE uint32 GLArrayBufferLayout::GetStride() const { return m_Stride; }

	//============================================
	//OpenGL Array Buffer
	//============================================

	FORCEINLINE GLArrayBuffer::GLArrayBuffer() {
		GLCall(glGenBuffers(1, &m_BufferID));
	}

	FORCEINLINE GLArrayBuffer::GLArrayBuffer(const void * Data, size_t Size) {
		GLCall(glGenBuffers(1, &m_BufferID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW));
	}

	FORCEINLINE GLArrayBuffer::~GLArrayBuffer() {
		try {
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
			GLCall(glDeleteBuffers(GL_ARRAY_BUFFER, &m_BufferID));
		}
		catch (...) {
			return;
		}
	}

	FORCEINLINE void GLArrayBuffer::Bind() const {
		if (!m_Bound) {
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
		}
	}

	FORCEINLINE void GLArrayBuffer::Unbind() const {
		if (m_Bound) {
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}
	}

	FORCEINLINE void GLArrayBuffer::PushData(const void * Data, size_t Size) {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW));
	}

	FORCEINLINE GLArrayBufferLayout & GLArrayBuffer::GetLayout() { return m_Layout; }

	FORCEINLINE const GLArrayBufferLayout & GLArrayBuffer::GetLayout() const { return m_Layout; }

	FORCEINLINE uint32 GLArrayBuffer::GetID() const { return m_BufferID; }

	template<typename Type>
	FORCEINLINE void GLArrayBufferLayout::Push(int Count) {
		static_assert(false, "Element push type is not supported!");
	}

	template<>
	FORCEINLINE void GLArrayBufferLayout::Push<float>(int Count) {
		m_Elements.emplace_back(GL_FLOAT, Count, GL_FALSE);
		m_Stride += Count * GetSizeOfType(GL_FLOAT);
	}

	template<>
	FORCEINLINE void GLArrayBufferLayout::Push<int>(int Count) {
		m_Elements.emplace_back(GL_FLOAT, Count, GL_FALSE);
		m_Stride += Count * GetSizeOfType(GL_INT);
	}

	template<>
	FORCEINLINE void GLArrayBufferLayout::Push<uint32>(int Count) {
		m_Elements.emplace_back(GL_UNSIGNED_INT, Count, GL_FALSE);
		m_Stride += Count * GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	FORCEINLINE void GLArrayBufferLayout::Push<uint8>(int Count) {
		m_Elements.emplace_back(GL_UNSIGNED_BYTE, Count, GL_TRUE);
		m_Stride += Count * GetSizeOfType(GL_UNSIGNED_BYTE);
	}

}