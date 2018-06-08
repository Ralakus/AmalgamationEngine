#include "../GLMesh.hpp"
#include "../GLShader.hpp"
#include "../GLCommon.hpp"
#include "../Lights/GLDirectionalLight.hpp"
#include "../Lights/GLPointLight.hpp"
#include "../Lights/GLSpotLight.hpp"
#include <Engine/Level/Components/CameraComponent.hpp>


namespace Amalgamation {

	void Amalgamation::GLBasicRenderer::Begin()
	{
	}

	void Amalgamation::GLBasicRenderer::Submit(Mesh* Mesh)
	{
		m_Meshes.push_back(Mesh);
	}

	void Amalgamation::GLBasicRenderer::End()
	{
	}

	void Amalgamation::GLBasicRenderer::Flush()
	{
		m_BufferedTransform = glm::mat4(1.f);;

		for (Mesh* MeshPtr : m_Meshes) {
			GLMesh* CastMesh = static_cast<GLMesh*>(MeshPtr);
			GLShader* CastShader = static_cast<GLShader*>(CastMesh->GetShader());
			CastMesh->GetVertexArray().Bind();
			CastMesh->GetElementBuffer().Bind();

			/*m_BufferedTransform = Math::Matrix4::Translate(MeshPtr->GetTransform()->Position);
			m_BufferedTransform *= MeshPtr->GetTransform()->Rotation;
			m_BufferedTransform *= Math::Mat4::Scale(MeshPtr->GetTransform()->Scale);*/

			CastShader->Bind();
			CastShader->SetUniform("u_Model", m_BufferedTransform);
			if (m_Cam) {
				CastShader->SetUniform("u_View", m_Cam->View());
				CastShader->SetUniform("u_Projection", m_Cam->GetProjection());
			}

			if (MeshPtr->GetTextures().size() <= 0) {
				GLCall(glBindTexture(GL_TEXTURE_2D, 0));
			}
			else {
				for (Texture* TexturePtr : MeshPtr->GetTextures()) {
					TexturePtr->Bind();
					CastShader->SetUniform("u_Material.Diffuse", TexturePtr->GetLayer());
					CastShader->SetUniform("u_Material.Shininess", 32.f);
				}
			}

			if (CastShader->SupportsLighting) {
				size_t Pi = 0;
				size_t Si = 0;
				size_t Di = 0;
				for (size_t i = 0; i < m_Lights.size(); i++) {
					if (m_Lights[i]->LightType == Light::Type::Point) {
						GLPointLight* PLight = static_cast<GLPointLight*>(m_Lights[i]);
						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Position").c_str(), PLight->GetTransform()->Position);

						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Constant").c_str(), PLight->Constant);
						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Linear").c_str(), PLight->Linear);
						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Quadratic").c_str(), PLight->Quadratic);

						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Ambient").c_str(), PLight->Ambient);
						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Diffuse").c_str(), PLight->Diffuse);
						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Specular").c_str(), PLight->Specular);
						Pi++;
					}
					else if (m_Lights[i]->LightType == Light::Type::Directional) {
						GLDirectionalLight* DLight = static_cast<GLDirectionalLight*>(m_Lights[i]);
						CastShader->SetUniform(("u_DirLights[" + std::to_string(Di) + "].Direction").c_str(), glm::eulerAngles(DLight->GetTransform()->Rotation));

						CastShader->SetUniform(("u_DirLights[" + std::to_string(Di) + "].Ambient").c_str(),  DLight->Ambient);
						CastShader->SetUniform(("u_DirLights[" + std::to_string(Di) + "].Diffuse").c_str(),  DLight->Diffuse);
						CastShader->SetUniform(("u_DirLights[" + std::to_string(Di) + "].Specular").c_str(), DLight->Specular);
						Di++;
					}
					else if (m_Lights[i]->LightType == Light::Type::Spot) {
						GLSpotLight* SLight = static_cast<GLSpotLight*>(m_Lights[i]);
						CastShader->SetUniform(("u_SpotLights[" + std::to_string(Si) + "].Position").c_str(), SLight->GetTransform()->Position);
						CastShader->SetUniform(("u_SpotLights[" + std::to_string(Si) + "].Direction").c_str(), glm::eulerAngles(SLight->GetTransform()->Rotation));

						CastShader->SetUniform(("u_SpotLights[" + std::to_string(Si) + "].CutOff").c_str(), SLight->CutOff);
						CastShader->SetUniform(("u_SpotLights[" + std::to_string(Si) + "].OuterCutOff").c_str(), SLight->OuterCutOff);

						CastShader->SetUniform(("u_SpotLights[" + std::to_string(Si) + "].Constant").c_str(), SLight->Constant);
						CastShader->SetUniform(("u_SpotLights[" + std::to_string(Si) + "].Linear").c_str(), SLight->Linear);
						CastShader->SetUniform(("u_SpotLights[" + std::to_string(Si) + "].Quadratic").c_str(), SLight->Quadratic);

						CastShader->SetUniform(("u_SpotLights[" + std::to_string(Si) + "].Ambient").c_str(), SLight->Ambient);
						CastShader->SetUniform(("u_SpotLights[" + std::to_string(Si) + "].Diffuse").c_str(), SLight->Diffuse);
						CastShader->SetUniform(("u_SpotLights[" + std::to_string(Si) + "].Specular").c_str(), SLight->Specular);
						Si++;
					}
					else {

					}
				}
				if (Di == 0) {
					CastShader->SetUniform("u_HasDirLights", 0);
				}
				if (Pi == 0) {
					CastShader->SetUniform("u_HasPointLights", 0);
				}
				if (Si == 0) {
					CastShader->SetUniform("u_HasSpotLights", 0);
				}
			}

			GLCall(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(CastMesh->GetElementBuffer().GetCount()), GL_UNSIGNED_INT, nullptr));

			CastShader->Unbind();

			CastMesh->GetElementBuffer().Unbind();
			CastMesh->GetVertexArray().Unbind();

			m_BufferedTransform = glm::mat4(1);
		}

		m_Meshes.clear();
	}


	bool GLBasicRenderer::AddLight(Light* LightPtr) {
		if (LightPtr->GetAPI() == API::OpenGL) {
			if (m_Lights.size() > 0) {
				for (Light* L : m_Lights) {
					if (L != LightPtr) {
						continue;
					}
					else {
						m_Lights.emplace_back(LightPtr);
						return true;
					}
				}
				return false;
			}
			else {
				m_Lights.emplace_back(LightPtr);
				return true;
			}
		}
		else{
			return false;
		}
	}
	
	bool GLBasicRenderer::RemoveLight(Light* LightPtr) {
		if (m_Lights.size() > 0) {
			size_t i = 0;
			bool Found = false;
			for (Light* L : m_Lights) { i++;
				if (L != LightPtr) {
					continue;
				}
				else {
					Found = true;
					break;
				}
			}
			if (Found) {
				m_Lights.erase(m_Lights.begin() + i);
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}


}