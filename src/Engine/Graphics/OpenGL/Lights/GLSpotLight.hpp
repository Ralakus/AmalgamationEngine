#pragma once

#include <Core/Graphics/Light.hpp>

namespace Amalgamation {

	class GLSpotLight : public Light {

	public:

		//float CutOff      = glm::cos(glm::radians(12.5f));
		//float OuterCutOff = glm::cos(glm::radians(25.f));

		float CutOff = cos(Math::Radians(12.5f));
		float OuterCutOff = cos(Math::Radians(25.f));

		float Constant = 1.0f;
		float Linear = 0.09f;
		float Quadratic = 0.032f;

		GLSpotLight() : Light(API::OpenGL, Type::Spot) {}
		~GLSpotLight() {}

	};

}