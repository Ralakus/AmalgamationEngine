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

		glm::mat4 m_BufferedTransform;
		CameraComponent* m_Cam;

	public:

		GLBasicRenderer() : Renderer(API::OpenGL)  {}
		~GLBasicRenderer()                         {}

		void SetCamera(CameraComponent* Cam) { m_Cam = Cam; }

		void Render() override;
	};

}

#ifndef AE_NO_IMPL
	#include "GLBasicRenderer.inl"
#endif