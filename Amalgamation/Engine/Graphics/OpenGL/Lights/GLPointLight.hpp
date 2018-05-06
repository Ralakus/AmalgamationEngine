#pragma once

#include <Core/Graphics/Light.hpp>

namespace Amalgamation {

	class GLPointLight : public Light {

	public:

		float Constant = 1.f;
		float Linear = 0.09f;
		float Quadratic = 0.032f;

		GLPointLight() : Light(API::OpenGL, Type::Point) {}
		~GLPointLight() {}

	};

}