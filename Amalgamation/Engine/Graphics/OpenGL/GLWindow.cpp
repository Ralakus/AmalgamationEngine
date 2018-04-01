#include "GLWindow.hpp"
#include <Core/Input/Input.hpp>

namespace Amalgamation {

	void WindowSizeCallback(GLFWwindow* window, int width, int height);
	void OnKeyChange(GLFWwindow* window, int key, int scancode, int action, int mods);
	void OnMouseChange(GLFWwindow* window, int button, int action, int mods);
	void OnMouseMove(GLFWwindow* window, double xpos, double ypos);

	GLWindow::GLWindow() : Window(API::OpenGL) {

		if (!m_Init()) {
			//LOG_ERROR("Failed to create OpenGL Window!");
			printf("ERROR: Failed to create OpenGL Window!");
			glfwTerminate();
		}

	}

	GLWindow::GLWindow(const std::string& title, uint32 width, uint32 height, bool Fullscreen) : Window(title, width, height, Fullscreen, API::OpenGL) {

		if (!m_Init()) {
			//LOG_ERROR("Failed to create OpenGL Window!");
			printf("ERROR: Failed to create OpenGL Window!");
			glfwTerminate();
		}

	}

	GLWindow::~GLWindow() {

		glfwTerminate();

	}

	bool GLWindow::m_Init() {

		if (!glfwInit()) {
			//LOG_ERROR("Failed to initlize GLFW!");
			printf("ERROR: Failed to initlize GLFW!");
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
			//LOG_ERROR("Failed to assign GLFW Window!");
			printf("ERROR: Failed to assign GLFW Window!");
			return false;
		}

		glfwMakeContextCurrent(m_Window);

		glfwSetWindowUserPointer(m_Window, this);

		glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);

		glfwSetMouseButtonCallback(m_Window, OnMouseChange);

		glfwSetKeyCallback(m_Window, OnKeyChange);

		glfwSetCursorPosCallback(m_Window, OnMouseMove);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			//LOG_ERROR("GLAD failed to intilize!");
			printf("ERROR: Failed to initlize GLAD!");
			return false;
		}

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_MULTISAMPLE));

		m_Valid = true;

		return true;

	}

	void GLWindow::Update() {
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

	void GLWindow::Terminate() {
		m_Valid = false;
		glfwTerminate();
	}

	void WindowSizeCallback(GLFWwindow* window, int width, int height) {
		GLCall(glViewport(0, 0, width, height));
	}

	void OnKeyChange(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window::SetInputKey(key, action != GLFW_RELEASE);
	}
	void OnMouseChange(GLFWwindow* window, int button, int action, int mods) {
		Window::SetMouseButton(button, action != GLFW_RELEASE);
	}
	void OnMouseMove(GLFWwindow* window, double xpos, double ypos) {
		Window::SetMousePos(static_cast<float>(xpos), static_cast<float>(ypos));
	}
}