#pragma once

#include "../GLCommon.hpp"
#include <vector>

namespace Amalgamation {

	class GLArrayElement {
	public:
		GLArrayElement(uint32 Type, uint32 Count, int8 Normalized) : Type(Type), Count(Count), Normalized(Normalized) {}
		uint32 Type;
		uint32 Count;
		int8 Normalized;
	};

	//using VertexElement = ArrayElement;
	typedef GLArrayElement VertexElement;


	class ArrayBufferLayout {
	public:
		static uint32 GetSizeOfType(uint32 Type) {
			switch (Type) {
			case GL_FLOAT:         return sizeof(GLfloat);
			case GL_INT:           return sizeof(GLint);
			case GL_UNSIGNED_INT:  return sizeof(GLuint);
			case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
			default: return 0;
			}
			return 0;
		}

	private:
		std::vector<GLArrayElement> m_Elements;
		uint32 m_Stride;
	public:

		ArrayBufferLayout() : m_Stride(0) {}

		template<typename Type>
		void Push(int Count) {
			static_assert(false, "Element push type is not supported!");
		}

		template<>
		void Push<float>(int Count) {
			m_Elements.emplace_back(GL_FLOAT, Count, GL_FALSE);
			m_Stride += Count * GetSizeOfType(GL_FLOAT);
		}

		template<>
		void Push<int>(int Count) {
			m_Elements.emplace_back(GL_FLOAT, Count, GL_FALSE);
			m_Stride += Count * GetSizeOfType(GL_INT);
		}

		template<>
		void Push<uint32>(int Count) {
			m_Elements.emplace_back(GL_UNSIGNED_INT, Count, GL_FALSE);
			m_Stride += Count * GetSizeOfType(GL_UNSIGNED_INT);
		}

		template<>
		void Push<uint8>(int Count) {
			m_Elements.emplace_back(GL_UNSIGNED_BYTE, Count, GL_TRUE);
			m_Stride += Count * GetSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline const std::vector<GLArrayElement>& GetElements() const { return m_Elements; }

		inline uint32 GetStride() const { return m_Stride; }

	};

	//using VertexBufferLayout = ArrayBufferLayout;
	typedef ArrayBufferLayout VertexBufferLayout;

	/*
	ARRAY BUFFER LAYOUT MUST BE INTERLACED!
	*/
	class GLArrayBuffer {

		uint32 m_BufferID;

		ArrayBufferLayout m_Layout;

	public:

		GLArrayBuffer() {
			GLCall(glGenBuffers(1, &m_BufferID));
		}

		GLArrayBuffer(const void* Data, size_t Size) {
			GLCall(glGenBuffers(1, &m_BufferID));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
			GLCall(glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW));
		}

		~GLArrayBuffer() {
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
			GLCall(glDeleteBuffers(GL_ARRAY_BUFFER, &m_BufferID));
		}

		void Bind() const {
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
		}

		void Unbind() const {
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}

		inline void PushData(const void* Data, size_t Size) {
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_BufferID));
			GLCall(glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_STATIC_DRAW));
		}

		ArrayBufferLayout& GetLayout() { return m_Layout; }
		const ArrayBufferLayout& GetLayout() const { return m_Layout; }

		uint32 GetID() const { return m_BufferID; }

	};

	//using VertexBuffer = ArrayBuffer;
	typedef GLArrayBuffer VertexBuffer;

}