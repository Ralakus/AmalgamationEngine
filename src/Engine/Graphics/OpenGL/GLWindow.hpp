#pragma once

#include <Core/Graphics/Window.hpp>
#include "GLCommon.hpp"

#undef APIENTRY
#include <GLFW/glfw3.h>

namespace Amalgamation {

	class GLWindow : public Window {

		GLFWwindow* m_Window;
		GLFWmonitor* m_Monitor;
		const GLFWvidmode* m_Mode;

		bool m_Init();

	public:

		GLWindow();
		GLWindow(const std::string& title, uint32_t width, uint32_t height, bool Fullscreen = false);

		~GLWindow();

		void LockMouse(bool set) override;

		void Close() override;

		void Update() override;
		void Terminate() override;

		void SetTitle(const std::string& Title) override;
		void SetTitle(const char* Title) override;

		void SetFullscreen(bool Set) override;

		void Resize(uint32_t Width, uint32_t Height) override;

		GLFWwindow* GetGLFWWindowPtr();

	};

}

#ifndef AE_NO_IMPL
	#include "GLWindow.inl"
#endif