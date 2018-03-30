#pragma once

#include <Core/Graphics/Window.hpp>
#include "GLCommon.hpp"
#include <GLFW/glfw3.h>

namespace Amalgamation {


	class GLWindow : public Window {
	private:

		GLFWwindow* m_Window;

		bool m_Init() override;

		friend void OnKeyChange(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void OnMouseChange(GLFWwindow* window, int button, int action, int mods);
		friend void OnMouseMove(GLFWwindow* window, double xpos, double ypos);

	public:

		GLWindow();
		GLWindow(const std::string& title, uint32 width, uint32 height, bool Fullscreen);

		~GLWindow();

		void LockMouse(bool set) override { if (set) { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); } else { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); } }

		void Close() override { m_Valid = false; glfwSetWindowShouldClose(m_Window, GLFW_TRUE); }

		void Update() override;
		void Terminate() override;

		void SetTitle(const std::string& title) override { m_Title = title; glfwSetWindowTitle(m_Window, title.c_str()); }
		void SetTitle(const char* title) override { m_Title = title; glfwSetWindowTitle(m_Window, title); }

		GLFWwindow* GetGLFWWindowPtr() { return m_Window; }

	};


}