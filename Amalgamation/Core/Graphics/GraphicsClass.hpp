#pragma once

namespace Amalgamation {

	enum class API {
		OpenGL, Vulkan, Undefined
	};

	class GraphicsClass {
	protected:

		const API m_API;

	public:

		GraphicsClass(API API) : m_API(API) {}
		virtual ~GraphicsClass() {}

		API GetAPI() const { return m_API; }

	};

}