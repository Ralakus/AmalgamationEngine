#pragma once

#include "../GLCommon.hpp"

namespace Amalgamation {

	class GLFrameBuffer {

		uint32_t m_BufferID;

		mutable bool m_Bound;

	public:

		GLFrameBuffer();
		~GLFrameBuffer();

		void Bind()   const;
		void Unbind() const;

	};

}

#include "GLFrameBuffer.inl"