#pragma once

#include "GraphicsClass.hpp"

#include <Core/Math/Transform.hpp>

namespace Amalgamation {

	class Light : public GraphicsClass {

		friend class LightComponent;

	protected:

		Transform* m_TransformPtr = nullptr;

		void Parent(Transform* TransformPtr) {
			m_TransformPtr = TransformPtr;
		}

	public:

		enum class Type : unsigned char {
			Directional, Point, Spot
		} const LightType;

		Light(API API, Type LightType) : GraphicsClass(API), LightType(LightType) {}
		virtual ~Light() {}


		Math::Vec3 Diffuse = { 1.0f, 1.0f, 1.0f };
		Math::Vec3 Specular = { 1.0f, 1.0f, 1.0f };
		Math::Vec3 Ambient = { 0.05f, 0.05f, 0.05f };


		Transform* GetTransform() {
			return m_TransformPtr;
		}

	};


}