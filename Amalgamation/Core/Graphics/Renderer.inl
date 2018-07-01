
namespace Amalgamation {

	FORCEINLINE bool Renderer::RegisterMesh(Mesh* MeshPtr) {
		if (std::find(m_Meshes.begin(), m_Meshes.end(), MeshPtr) == m_Meshes.end() && MeshPtr->GetAPI() == this->m_API) {
			m_Meshes.emplace_back(MeshPtr);
			return true;
		}
		else {
			return false;
		}
	}

	FORCEINLINE bool Renderer::DeregisterMesh(Mesh* MeshPtr) {
		std::vector<Mesh*>::iterator i = std::find(m_Meshes.begin(), m_Meshes.end(), MeshPtr);
		if (i != m_Meshes.end()) {
			m_Meshes.erase(i);
			return true;
		}
		else {
			return false;
		}
	}

	FORCEINLINE bool Renderer::AddLight(Light * LightPtr) {
		if (std::find(m_Lights.begin(), m_Lights.end(), LightPtr) != m_Lights.end() && LightPtr->GetAPI() == this->m_API) {
			m_Lights.emplace_back(LightPtr);
			return true;
		}
		else {
			return false;
		}
	}

	FORCEINLINE bool Renderer::RemoveLight(Light * LightPtr) {
		std::vector<Light*>::iterator i = std::find(m_Lights.begin(), m_Lights.end(), LightPtr);
		if (i != m_Lights.end()) {
			m_Lights.erase(i);
			return true;
		}
		else {
			return false;
		}
	}

}