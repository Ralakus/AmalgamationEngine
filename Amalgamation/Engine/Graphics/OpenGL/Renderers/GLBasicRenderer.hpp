#pragma once

#include <Core/Graphics/Renderer.hpp>
#include <vector>
#include <Core/Math/Vector/Vector3.hpp>
#include <Core/Math/Quaternion/Quaternion.hpp>
#include <Core/Math/Matrix/Matrix4x4.hpp>
#include <deque>

namespace Amalgamation {

	class CameraComponent;

	class GLBasicRenderer : public Renderer {

		std::deque<Mesh*> m_Meshes;
		std::vector<Light*> m_Lights;
		std::vector<Light*> m_SpotLights;
		glm::mat4 m_BufferedTransform;
		CameraComponent* m_Cam;

	public:

		GLBasicRenderer() : Renderer(API::OpenGL)  {}
		~GLBasicRenderer()                         {}

		void SetCamera(CameraComponent* Cam) { m_Cam = Cam; }

		virtual void Begin() override;

		virtual void Submit(Mesh* Mesh) override;

		virtual void End() override;

		virtual void Flush() override;

		virtual bool AddLight(Light* LightPtr) override;
		virtual bool RemoveLight(Light* LightPtr) override;
	};

}
#include "GLBasicRenderer.inl"