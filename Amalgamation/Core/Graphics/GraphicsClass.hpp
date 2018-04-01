#pragma once

#include <Core/Platform/API.hpp>

namespace Amalgamation {

	class GraphicsClass {
	protected:

		API m_API;

	public:

		GraphicsClass(API API) : m_API(API) {}
		virtual ~GraphicsClass()            {}

		API GetAPI() const { return m_API; }

	};

}