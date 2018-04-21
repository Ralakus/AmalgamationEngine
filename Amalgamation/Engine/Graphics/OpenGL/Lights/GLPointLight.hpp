#pragma once

#include <Core/Graphics/Light.hpp>

namespace Amalgamation {

	class GLPointLight : public Light {

	public:

		GLPointLight() : Light(API::OpenGL) {}
		~GLPointLight() {}

	};

}