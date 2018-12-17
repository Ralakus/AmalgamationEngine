
namespace Amalgamation {

	FORCEINLINE GLVertexArray::GLVertexArray() {
		GLCall(glGenVertexArrays(1, &m_ArrayID));
	}

	FORCEINLINE GLVertexArray::~GLVertexArray() {
		try {
			GLCall(glDeleteVertexArrays(1, &m_ArrayID));
		}
		catch (...) {
			return;
		}
	}

	FORCEINLINE void GLVertexArray::Bind() const { if (!m_Bound) { GLCall(glBindVertexArray(m_ArrayID)); } }

	FORCEINLINE void GLVertexArray::Unbind() const { if (m_Bound) { GLCall(glBindVertexArray(0)); } }

	FORCEINLINE uint32_t GLVertexArray::GetID() const { return m_ArrayID; }

	FORCEINLINE void GLVertexArray::SetBuffer(const GLArrayBuffer & Buffer) {
		Bind();
		Buffer.Bind();
		const auto& Elements = Buffer.GetLayout().GetElements();
		size_t Offset = 0;
		for (uint32_t i = 0; i < Elements.size(); i++) {
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, Elements[i].Count, Elements[i].Type, Elements[i].Normalized, Buffer.GetLayout().GetStride(), (const void*)Offset);
			Offset += Elements[i].Count * GLArrayBufferLayout::GetSizeOfType(Elements[i].Type));
		}
	}


}