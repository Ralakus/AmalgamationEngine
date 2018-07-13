#ifndef AE_NO_GLIMGUI
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#endif
#include "GLWindow.hpp"

namespace Amalgamation {

	FORCEINLINE bool GLWindow::m_Init() {
		m_Window = nullptr;

		if (!glfwInit()) {
			std::cerr << rang::fgB::red << "[ gl::error ]: " << rang::fg::reset << "Failed to initialize glfw!" << rang::fgB::yellow << "\nEND" << rang::fg::reset << std::endl;
			return false;
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		m_Monitor = glfwGetPrimaryMonitor();
		m_Mode    = glfwGetVideoMode(m_Monitor);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), m_Fullscreen ? m_Monitor : nullptr, nullptr);

		if (!m_Window) {
			std::cerr << rang::fgB::red << "[ gl::error ]: " << rang::fg::reset << "Failed to assign window!" << rang::fgB::yellow << "\nEND" << rang::fg::reset << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* Window, int Width, int Height) { GLCall(glViewport(0, 0, Width, Height)); });
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			GLWindow* AEWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
			AEWindow->UpdateButtonInput(button, action);
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			GLWindow* AEWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
			AEWindow->UpdateKeyInput(key, action);
		});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int c) { 
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) { 
			GLWindow* AEWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
			AEWindow->UpdateMousePos(static_cast<float>(xpos), static_cast<float>(ypos));
		});
		glfwSetCursorEnterCallback(m_Window, [](GLFWwindow* window, int entered) { GLWindow* AEWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window)); AEWindow->m_CursorOnWindow = entered; });


		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
			std::cerr << rang::fgB::red << "[ gl::error ]: " << rang::fg::reset << "Failed to initialize GLAD!" << rang::fgB::yellow << "\nEND" << rang::fg::reset << std::endl;
			return false;
		}

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_MULTISAMPLE));

		m_Valid = true;

		return true;
	}

	FORCEINLINE GLWindow::GLWindow() : Window(API::OpenGL) {
		if (!m_Init()) {
			std::cerr << rang::fgB::red << "[ gl::error ]: " << rang::fg::reset << "Failed to create OpenGL window!" << rang::fgB::yellow << "\nEND" << rang::fg::reset << std::endl;
			glfwDestroyWindow(m_Window);
		}
	}

	FORCEINLINE GLWindow::GLWindow(const std::string & title, uint32_t width, uint32_t height, bool Fullscreen)
		: Window(title, width, height, Fullscreen, API::OpenGL)
	{
		if (!m_Init()) {
			std::cerr << rang::fgB::red << "[ gl::error ]: " << rang::fg::reset << "Failed to create OpenGL window!" << rang::fgB::yellow << "\nEND" << rang::fg::reset << std::endl;
			glfwDestroyWindow(m_Window);
		}
	}

	FORCEINLINE GLWindow::~GLWindow() { glfwTerminate(); }

	FORCEINLINE void GLWindow::LockMouse(bool set) { if (set) { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); } else { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); } m_MouseLocked = set; }

	FORCEINLINE void GLWindow::Close() { m_Valid = false; glfwSetWindowShouldClose(m_Window, GLFW_TRUE); }

	FORCEINLINE void GLWindow::Update() {
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

	FORCEINLINE void GLWindow::Terminate() {
		m_Valid = false;
		glfwDestroyWindow(m_Window);
	}

	FORCEINLINE void GLWindow::SetTitle(const std::string & Title) { m_Title = Title; glfwSetWindowTitle(m_Window, Title.c_str()); }

	FORCEINLINE void GLWindow::SetTitle(const char * Title) { m_Title = Title; glfwSetWindowTitle(m_Window, Title); }

	FORCEINLINE void GLWindow::SetFullscreen(bool Set) {
		if (Set != m_Fullscreen) {
			m_Fullscreen = Set;
			glfwSetWindowMonitor(m_Window, Set ? m_Monitor : nullptr, 0, 0, m_Width, m_Height, m_Mode->refreshRate);
		}
	}

	FORCEINLINE void GLWindow::Resize(uint32_t Width, uint32_t Height) {
		if (!m_Fullscreen) {
			glfwSetWindowSize(m_Window, Width, Height);
		}
		else {
			glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, Width, Height, m_Mode->refreshRate);
		}
		m_Width = Width; m_Height = Height;
	}

	/*ONLY INTEDED FOR DEBUG*/
	FORCEINLINE GLFWwindow * GLWindow::GetGLFWWindowPtr() { return m_Window; }


}