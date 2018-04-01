#pragma once

#include <Core/Graphics/Renderer.hpp>
#include <vector>
#include <glm/glm.hpp>

namespace Amalgamation {

	class CameraComponent;

	class GLBasicRenderer : public Renderer {

		std::vector<Mesh*> m_Meshes;
		glm::mat4 m_BufferedTransform;
		CameraComponent* m_Cam;

	public:

		GLBasicRenderer()  {}
		~GLBasicRenderer() {}

		void SetCamera(CameraComponent* Cam) { m_Cam = Cam; }

		virtual void Begin() override;

		virtual void Submit(Mesh* Mesh) override;

		virtual void End() override;

		virtual void Flush() override;


	};

}