#pragma once

#include "../GLCommon.hpp"
#include "GLArrayBuffer.hpp"

namespace Amalgamation {

	class GLVertexArray {
	private:

		uint32 m_ArrayID;

		mutable bool m_Bound;

	public:

		GLVertexArray() {
			GLCall(glGenVertexArrays(1, &m_ArrayID));
		}
		~GLVertexArray() {
			try {
				GLCall(glDeleteVertexArrays(1, &m_ArrayID));
			}
			catch (...) {
				return;
			}
		}

		inline void Bind() const { if (!m_Bound) { GLCall(glBindVertexArray(m_ArrayID)); } }
		inline void Unbind() const { if (m_Bound) { GLCall(glBindVertexArray(0)); } }
		inline uint32 GetID() const { return m_ArrayID; }

		void AddBuffer(const GLArrayBuffer& Buffer) {
			Bind();
			Buffer.Bind();
			const auto& Elements = Buffer.GetLayout().GetElements();
			uint64 Offset = 0;
			for (uint32 i = 0; i < Elements.size(); i++) {
				GLCall(glEnableVertexAttribArray(i));
				GLCall(glVertexAttribPointer(i, Elements[i].Count, Elements[i].Type, Elements[i].Normalized, Buffer.GetLayout().GetStride(), (const void*)Offset);
				Offset += Elements[i].Count * ArrayBufferLayout::GetSizeOfType(Elements[i].Type));
			}
		}

	};

}