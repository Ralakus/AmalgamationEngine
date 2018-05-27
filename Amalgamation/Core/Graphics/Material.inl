
namespace Amalgamation {

	FORCEINLINE Material::Material(API API) : GraphicsClass(API) {}

	FORCEINLINE Material::~Material() {}

	FORCEINLINE bool Material::SetDiffuse(Texture * Diffuse) {
		if (Diffuse->GetAPI() == this->GetAPI()) {
			m_Diffuse = Diffuse;
			return true;
		}
		else {
			return false;
		}
	}

	FORCEINLINE bool Material::SetSpecular(Texture * Specular) {
		if (Specular->GetAPI() == this->GetAPI()) {
			m_Specular = Specular;
			return true;
		}
		else {
			return false;
		}
	}

	FORCEINLINE bool Material::HasDiffuse() const {
		return m_Diffuse != nullptr;
	}

	FORCEINLINE bool Material::HasSpecular() const {
		return m_Specular != nullptr;
	}

	FORCEINLINE Texture * Material::GetDiffuse() {
		return m_Diffuse;
	}

	FORCEINLINE Texture * Material::GetSpecular() {
		return m_Specular;
	}

	FORCEINLINE float Material::GetShininess() const {
		return m_Shininess;
	}

	FORCEINLINE float Material::SetShininess(float Shininess) {
		return m_Shininess = Shininess;
	}


}