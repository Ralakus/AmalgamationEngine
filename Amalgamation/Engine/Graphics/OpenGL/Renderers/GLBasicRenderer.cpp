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
			CastMesh->GetVertexArray().Bind();
			CastMesh->GetElementBuffer().Bind();

			m_BufferedTransform = glm::translate(m_BufferedTransform, MeshPtr->GetTransform()->Position) * glm::mat4_cast(MeshPtr->GetTransform()->Rotation);
			m_BufferedTransform = glm::scale(m_BufferedTransform, MeshPtr->GetTransform()->Scale);

			CastMesh->GetShader()->Bind();
			CastMesh->GetShader()->SetUniform("u_Model", m_BufferedTransform);
			if (m_Cam) {
				CastMesh->GetShader()->SetUniform("u_View", m_Cam->View());
				CastMesh->GetShader()->SetUniform("u_Projection", m_Cam->GetProjection());
			}

			if (MeshPtr->GetTextures().size() <= 0) {
				GLCall(glBindTexture(GL_TEXTURE_2D, 0));
			}
			else {
				for (Texture* TexturePtr : MeshPtr->GetTextures()) {
					TexturePtr->Bind();
					CastMesh->GetShader()->SetUniform(("u_Texture" + std::to_string(TexturePtr->GetLayer())).c_str(), TexturePtr->GetLayer());
				}
			}

			GLCall(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(CastMesh->GetElementBuffer().GetCount()), GL_UNSIGNED_INT, nullptr));

			CastMesh->GetShader()->Unbind();

			CastMesh->GetElementBuffer().Unbind();
			CastMesh->GetVertexArray().Unbind();

			m_BufferedTransform = glm::mat4(1);
		}

		m_Meshes.clear();
	}


}