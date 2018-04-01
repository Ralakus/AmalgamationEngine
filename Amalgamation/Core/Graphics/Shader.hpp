#pragma once

#include "GraphicsClass.hpp"

namespace Amalgamation {

	class Shader : public GraphicsClass {

	public:

		Shader(API API) : GraphicsClass(API) {}
		virtual ~Shader()                    {}

	};

}