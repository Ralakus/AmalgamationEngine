#pragma once

#include "GraphicsClass.hpp"
#include "Texture.hpp"

#include <vector>

namespace Amalgamation {


	class Material : public GraphicsClass {

		Texture* m_Diffuse   = nullptr;
		Texture* m_Specular  = nullptr;
		float    m_Shininess = 0.5f;

	public:

		Material(API API);
		virtual ~Material();

		bool SetDiffuse(Texture* Diffuse);
		bool SetSpecular(Texture* Specular);

		bool HasDiffuse() const;
		bool HasSpecular() const;

		Texture* GetDiffuse();
		Texture* GetSpecular();

		float GetShininess() const;
		float SetShininess(float Shininess);
	};

}

#include "Material.inl"