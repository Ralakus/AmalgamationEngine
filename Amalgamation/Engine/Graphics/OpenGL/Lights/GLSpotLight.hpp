#pragma once

#include <Core/Graphics/Light.hpp>

namespace Amalgamation {

	class GLSpotLight : public Light {

	public:

		GLSpotLight() : Light(API::OpenGL) {}
		~GLSpotLight() {}

	};

}