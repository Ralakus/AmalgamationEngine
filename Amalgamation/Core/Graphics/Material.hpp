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

		Material(API API) : GraphicsClass(API) {}
		virtual ~Material() {}

		bool SetDiffuse(Texture* Diffuse) {
			if (Diffuse->GetAPI() == this->GetAPI()) {
				m_Diffuse = Diffuse;
				return true;
			}
			else {
				return false;
			}
		}

		bool SetSpecular(Texture* Specular) {
			if (Specular->GetAPI() == this->GetAPI()) {
				m_Specular = Specular;
				return true;
			}
			else {
				return false;
			}
		}

		bool HasDiffuse() const {
			return m_Diffuse != nullptr;
		}

		bool HasSpecular() const {
			return m_Specular != nullptr;
		}

		Texture* GetDiffuse() {
			return m_Diffuse;
		}

		Texture* GetSpecular() {
			return m_Specular;
		}

		float GetShininess() const {
			return m_Shininess;
		}

		float SetShininess(float Shininess) {
			return m_Shininess = Shininess;
		}
	};

}