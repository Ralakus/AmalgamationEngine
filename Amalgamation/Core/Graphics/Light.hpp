#pragma once

#include "GraphicsClass.hpp"

#include <Core/Math/Transform.hpp>

namespace Amalgamation {


	class Light : public GraphicsClass {

	protected:

		Transform* m_TransformPtr = nullptr;

		void Parent() {

		}

	public:

		enum class Type : unsigned char {
			Directional, Point, Spot
		} const LightType;

		Light(API API, Type LightType) : GraphicsClass(API), LightType(LightType) {}
		virtual ~Light() {}


		glm::vec3 Diffuse;
		glm::vec3 Specular;


		Transform* GetTransform() {
			return m_TransformPtr;
		}

	};


}