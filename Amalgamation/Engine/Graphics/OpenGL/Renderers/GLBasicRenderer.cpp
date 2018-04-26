#include "GLBasicRenderer.hpp"
#include "../GLMesh.hpp"
#include "../GLShader.hpp"
#include "../GLCommon.hpp"
#include <Engine/World/Components/CameraComponent.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

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
		m_BufferedTransform = glm::mat4(1);

		for (Mesh* MeshPtr : m_Meshes) {
			GLMesh* CastMesh = static_cast<GLMesh*>(MeshPtr);
			GLShader* CastShader = static_cast<GLShader*>(CastMesh->GetShader());
			CastMesh->GetVertexArray().Bind();
			CastMesh->GetElementBuffer().Bind();

			m_BufferedTransform = glm::translate(m_BufferedTransform, MeshPtr->GetTransform()->Position) * glm::mat4_cast(MeshPtr->GetTransform()->Rotation);
			m_BufferedTransform = glm::scale(m_BufferedTransform, MeshPtr->GetTransform()->Scale);

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
					CastShader->SetUniform(("u_Texture" + std::to_string(TexturePtr->GetLayer())).c_str(), TexturePtr->GetLayer());
				}
			}

			if (CastShader->SupportsLighting()) {
				// TODO: Add lighting code to shaders
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