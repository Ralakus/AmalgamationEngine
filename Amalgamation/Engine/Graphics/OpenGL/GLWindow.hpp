#pragma once

#include <Core/Graphics/Window.hpp>
#include "GLCommon.hpp"
#include <GLFW/glfw3.h>

namespace Amalgamation {

	class GLWindow : public Window {

		GLFWwindow* m_Window;

		bool m_Init() {
			if (!glfwInit()) {
				AE_LOG_ERROR("Failed to initlize GLFW!");
				return false;
			}

			glfwWindowHint(GLFW_SAMPLES, 4);

			if (m_Fullscreen) {
				m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), glfwGetPrimaryMonitor(), nullptr);
			}
			else {
				m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
			}

			if (!m_Window) {
				AE_LOG_ERROR("Failed to assign GLFW Window!");
				return false;
			}

			glfwMakeContextCurrent(m_Window);

			glfwSetWindowUserPointer(m_Window, this);

			glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* Window, int Width, int Height) { GLCall(glViewport(0, 0, Width, Height)); });

			glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) { Window::UpdateButtonInput(button, action); });

			glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) { Window::UpdateKeyInput(key, action); });

			glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) { Window::UpdateMousePos(static_cast<MATH_TYPE>(xpos), static_cast<MATH_TYPE>(ypos)); });

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				AE_LOG_ERROR("Failed to initlize GLAD!");
				return false;
			}

			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			GLCall(glEnable(GL_DEPTH_TEST));
			GLCall(glEnable(GL_MULTISAMPLE));

			m_Valid = true;

			return true;
		}

	public:

		GLWindow() : Window(API::OpenGL) {
			if (!m_Init()) {
				AE_LOG_ERROR("Failed to create OpenGL Window!");
				glfwTerminate();
			}
		}
		GLWindow(const std::string& title, uint32 width, uint32 height, bool Fullscreen = false)
			: Window(title, width, height, Fullscreen, API::OpenGL) 
		{
			if (!m_Init()) {
				AE_LOG_ERROR("Failed to create OpenGL Window!");
				glfwTerminate();
			}
		}

		~GLWindow() { glfwTerminate(); }

		void LockMouse(bool set) override { if (set) { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); } else { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); } }

		void Close() override { m_Valid = false; glfwSetWindowShouldClose(m_Window, GLFW_TRUE); }

		void Update() override {
			if (!glfwWindowShouldClose(m_Window) && m_Valid) {
				glfwGetFramebufferSize(m_Window, reinterpret_cast<int*>(&m_Width), reinterpret_cast<int*>(&m_Height));
				glfwSwapBuffers(m_Window);
				glfwPollEvents();
				GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			}
			else {
				m_Valid = false;
			}
		}
		void Terminate() override {
			m_Valid = false;
			glfwTerminate();
		}

		void SetTitle(const std::string& Title) override { m_Title = Title; glfwSetWindowTitle(m_Window, Title.c_str()); }
		void SetTitle(const char* Title) override { m_Title = Title; glfwSetWindowTitle(m_Window, Title); }

		void SetFullscreen(bool Set) override {}

		/*ONLY INTEDED FOR DEBUG*/
		GLFWwindow* GetGLFWWindowPtr() { return m_Window; }

	};

}
