#include "BasicRenderer.hpp"
#include "../Mesh.hpp"

#include "../GLShader.hpp"
#include <Engine/World/Components/CameraComponent.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

void Amalgamation::BasicRenderer::SetCamera(CameraComponent* Cam){
	m_Cam = Cam;
}

void Amalgamation::BasicRenderer::Begin()
{
}

void Amalgamation::BasicRenderer::Submit(Mesh* Mesh)
{
	m_Meshes.push_back(Mesh);
}

void Amalgamation::BasicRenderer::End()
{
}

void Amalgamation::BasicRenderer::Flush()
{
	m_BufferedTransform = glm::mat4(1);

	for (Mesh* M : m_Meshes) {
		M->GetVAO().Bind();
		M->GetElementBuffer().Bind();

		m_BufferedTransform = glm::translate(m_BufferedTransform, M->GetTransform()->Position) * glm::mat4_cast(M->GetTransform()->Rotation);
		m_BufferedTransform = glm::scale(m_BufferedTransform, M->GetTransform()->Scale);

		M->GetShader()->Bind();
		M->GetShader()->SetUniform("u_Model", m_BufferedTransform);
		if (m_Cam) {
			M->GetShader()->SetUniform("u_View", m_Cam->View());
			M->GetShader()->SetUniform("u_Projection", m_Cam->GetProjection());
		}

		if (M->GetTextures().size() <= 0) {
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}
		else {
			for (Texture* T : M->GetTextures()) {
				T->Bind();
				M->GetShader()->SetUniform(("u_Texture" + std::to_string(T->GetLayer())).c_str(), T->GetLayer());
			}
		}

		GLCall(glDrawElements(GL_TRIANGLES, M->GetElementBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));

		M->GetShader()->Unbind();

		M->GetElementBuffer().Unbind();
		M->GetVAO().Unbind();

		m_BufferedTransform = glm::mat4(1);
	}

	m_Meshes.clear();
}

void Amalgamation::BasicRenderer::AddLight(Light* Light)
{
	m_Lights.push_back(Light);
}
