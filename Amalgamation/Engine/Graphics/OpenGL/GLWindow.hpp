#pragma once

#include <Core/Graphics/Window.hpp>
#include "GLCommon.hpp"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>

namespace Amalgamation {

	class GLWindow : public Window {

		GLFWwindow* m_Window;
		GLFWmonitor* m_Monitor;

		bool m_Init();

	public:

		GLWindow();
		GLWindow(const std::string& title, uint32 width, uint32 height, bool Fullscreen = false);

		~GLWindow();

		void LockMouse(bool set) override;

		void Close() override;

		void Update() override;
		void Terminate() override;

		void SetTitle(const std::string& Title) override;
		void SetTitle(const char* Title) override;

		void SetFullscreen(bool Set) override;

		GLFWwindow* GetGLFWWindowPtr();

	};

}

#include "GLWindow.inl"