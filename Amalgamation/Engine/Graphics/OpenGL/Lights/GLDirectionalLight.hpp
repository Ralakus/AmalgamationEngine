#pragma once

#include <Core/Graphics/Light.hpp>

namespace Amalgamation {

	class GLDirectionalLight : public Light {

	public:

		GLDirectionalLight() : Light(API::OpenGL) {}
		~GLDirectionalLight() {}

	};

}
