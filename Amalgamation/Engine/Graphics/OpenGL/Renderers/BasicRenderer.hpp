#pragma once

#include "IRenderer.hpp"
#include <vector>
#include <glm/glm.hpp>

namespace Amalgamation {

	class CameraComponent;

	class BasicRenderer : public IRenderer {

		std::vector<Mesh*> m_Meshes;
		std::vector<Light*> m_Lights;
		glm::mat4 m_BufferedTransform;
		CameraComponent* m_Cam;

	public:

		void SetCamera(CameraComponent* Cam);

		virtual void Begin() override;

		virtual void Submit(Mesh* Mesh) override;

		virtual void End() override;

		virtual void Flush() override;

		virtual void AddLight(Light* Light) override;

	};

}