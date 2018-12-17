
namespace Amalgamation {

	GLFrameBuffer::GLFrameBuffer()
	{
		GLCall(glGenFramebuffers(1, &m_BufferID));
	}

	GLFrameBuffer::~GLFrameBuffer()
	{
		try {
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			GLCall(glDeleteFramebuffers(1, &m_BufferID); );
		}
		catch (...) {
			return;
		}
	}

	inline void GLFrameBuffer::Bind() const
	{
		if (!m_Bound) {
			m_Bound = true;
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID));
		}
	}

	inline void GLFrameBuffer::Unbind() const
	{
		if (m_Bound) {
			m_Bound = false;
			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}
	}

}