#include "../GLMesh.hpp"
#include "../GLShader.hpp"
#include "../GLCommon.hpp"
#include "../Lights/GLDirectionalLight.hpp"
#include "../Lights/GLPointLight.hpp"
#include "../Lights/GLSpotLight.hpp"
#include <Engine/Level/Components/CameraComponent.hpp>


namespace Amalgamation {

	FORCEINLINE void GLBasicRenderer::Render() {

		for (Mesh* MeshPtr : m_Meshes) {
			m_BufferedTransform = glm::mat4(1.f);
			GLMesh* CastMesh = static_cast<GLMesh*>(MeshPtr);
			GLShader* CastShader = static_cast<GLShader*>(CastMesh->GetShader());
			CastMesh->GetVertexArray().Bind();
			CastMesh->GetElementBuffer().Bind();

			CastShader->Bind();
			CastShader->SetUniform("u_Model", Math::MakeModelMatrix(*MeshPtr->GetTransform()));
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
					switch (m_Lights[i]->LightType) {
					case Light::Type::Point: {
						GLPointLight* PLight = static_cast<GLPointLight*>(m_Lights[i]);
						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Position").c_str(), PLight->GetTransform()->Position);

						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Constant").c_str(), PLight->Constant);
						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Linear").c_str(), PLight->Linear);
						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Quadratic").c_str(), PLight->Quadratic);

						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Ambient").c_str(), PLight->Ambient);
						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Diffuse").c_str(), PLight->Diffuse);
						CastShader->SetUniform(("u_PointLights[" + std::to_string(Pi) + "].Specular").c_str(), PLight->Specular);
						Pi++;
					} break;
					case Light::Type::Directional: {
						GLDirectionalLight* DLight = static_cast<GLDirectionalLight*>(m_Lights[i]);
						CastShader->SetUniform(("u_DirLights[" + std::to_string(Di) + "].Direction").c_str(), glm::eulerAngles(DLight->GetTransform()->Rotation));

						CastShader->SetUniform(("u_DirLights[" + std::to_string(Di) + "].Ambient").c_str(), DLight->Ambient);
						CastShader->SetUniform(("u_DirLights[" + std::to_string(Di) + "].Diffuse").c_str(), DLight->Diffuse);
						CastShader->SetUniform(("u_DirLights[" + std::to_string(Di) + "].Specular").c_str(), DLight->Specular);
						Di++;
					} break;
					case Light::Type::Spot: {
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
					} break;
					default: {} break;
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
		}


	}
}