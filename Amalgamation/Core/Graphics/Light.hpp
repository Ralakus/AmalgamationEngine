#pragma once

#include "GraphicsClass.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Amalgamation {


	class Light : public GraphicsClass {

	protected:

		glm::vec3 m_Location;
		glm::quat m_Rotation;
		glm::vec3 Diffuse;
		glm::vec3 Specular;

		glm::vec3 m_Coral; //Color

	public:

		enum class Type : unsigned char {
			Directional, Point, Spot
		} const LightType;

		Light(API API, Type LightType) : GraphicsClass(API), LightType(LightType) {}
		virtual ~Light() {}


	};


}