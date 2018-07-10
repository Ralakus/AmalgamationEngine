#pragma once

#include "../GLCommon.hpp"
#include <vector>

namespace Amalgamation {

	class GLArrayElement {
	public:
		GLArrayElement(uint32_t Type, uint32_t Count, int8 Normalized);
		uint32_t Type;
		uint32_t Count;
		int8 Normalized;
	};

	using GLVertexElement = GLArrayElement;
	//typedef GLArrayElement VertexElement;


	class GLArrayBufferLayout {
	public:
		static uint32_t GetSizeOfType(uint32_t Type);

	private:
		std::vector<GLArrayElement> m_Elements;
		uint32_t m_Stride;
	public:

		GLArrayBufferLayout();

		template<typename Type>
		void Push(int Count);
		template<>
		void Push<float>(int Count);
		template<>
		void Push<int>(int Count);
		template<>
		void Push<uint32_t>(int Count);
		template<>
		void Push<uint8>(int Count);

		inline const std::vector<GLArrayElement>& GetElements() const;
		inline uint32_t GetStride() const;

	};

	using GLVertexBufferLayout = GLArrayBufferLayout;
	//typedef ArrayBufferLayout VertexBufferLayout;

	/*
	ARRAY BUFFER LAYOUT MUST BE INTERLACED!
	*/
	class GLArrayBuffer {

		uint32_t m_BufferID;

		GLArrayBufferLayout m_Layout;

		mutable bool m_Bound;

	public:

		GLArrayBuffer();
		GLArrayBuffer(const void* Data, size_t Size);
		~GLArrayBuffer();

		void Bind() const;
		void Unbind() const;

		inline void PushData(const void* Data, size_t Size);

		GLArrayBufferLayout& GetLayout();
		const GLArrayBufferLayout& GetLayout() const;

		uint32_t GetID() const;

	};

	using GLVertexBuffer = GLArrayBuffer;
	//typedef GLArrayBuffer VertexBuffer;

}

#include "GLArrayBuffer.inl"