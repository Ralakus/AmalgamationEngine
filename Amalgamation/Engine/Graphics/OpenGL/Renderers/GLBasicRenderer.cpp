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
			GLMesh* CastedMesh = static_cast<GLMesh*>(MeshPtr);
			CastedMesh->GetVertexArray().Bind();
			CastedMesh->GetElementBuffer().Bind();

			m_BufferedTransform = glm::translate(m_BufferedTransform, MeshPtr->GetTransform()->Position) * glm::mat4_cast(MeshPtr->GetTransform()->Rotation);
			m_BufferedTransform = glm::scale(m_BufferedTransform, MeshPtr->GetTransform()->Scale);

			CastedMesh->GetShader()->Bind();
			CastedMesh->GetShader()->SetUniform("u_Model", m_BufferedTransform);
			if (m_Cam) {
				CastedMesh->GetShader()->SetUniform("u_View", m_Cam->View());
				CastedMesh->GetShader()->SetUniform("u_Projection", m_Cam->GetProjection());
			}

			if (MeshPtr->GetTextures().size() <= 0) {
				GLCall(glBindTexture(GL_TEXTURE_2D, 0));
			}
			else {
				for (Texture* TexturePtr : MeshPtr->GetTextures()) {
					TexturePtr->Bind();
					CastedMesh->GetShader()->SetUniform(("u_Texture" + std::to_string(TexturePtr->GetLayer())).c_str(), TexturePtr->GetLayer());
				}
			}

			GLCall(glDrawElements(GL_TRIANGLES, CastedMesh->GetElementBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));

			CastedMesh->GetShader()->Unbind();

			CastedMesh->GetElementBuffer().Unbind();
			CastedMesh->GetVertexArray().Unbind();

			m_BufferedTransform = glm::mat4(1);
		}

		m_Meshes.clear();
	}


}