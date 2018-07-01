
namespace Amalgamation {

	FORCEINLINE bool GLWindow::m_Init() {
		m_Window = nullptr;

		if (!glfwInit()) {
			AE_LOG_ERROR("Failed to initlize GLFW!");
			return false;
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		m_Monitor = glfwGetPrimaryMonitor();

		if (m_Fullscreen) {
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), m_Monitor, nullptr);
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

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) { Window::UpdateButtonInput(button, action); ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods); });

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) { ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset); });

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) { Window::UpdateKeyInput(key, action); ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);  });

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int c) { ImGui_ImplGlfw_CharCallback(window, c); });

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) { Window::UpdateMousePos(static_cast<AE_MATH_TYPE>(xpos), static_cast<AE_MATH_TYPE>(ypos)); });

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

	FORCEINLINE GLWindow::GLWindow() : Window(API::OpenGL) {
		if (!m_Init()) {
			AE_LOG_ERROR("Failed to create OpenGL Window!");
			glfwDestroyWindow(m_Window);
		}
	}

	FORCEINLINE GLWindow::GLWindow(const std::string & title, uint32 width, uint32 height, bool Fullscreen)
		: Window(title, width, height, Fullscreen, API::OpenGL)
	{
		if (!m_Init()) {
			AE_LOG_ERROR("Failed to create OpenGL Window!");
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
			glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, m_Width, m_Height, NULL);
			/*if (!m_Init()) {
				AE_LOG_ERROR("Failed to create OpenGL Window!");
				glfwDestroyWindow(m_Window);
				throw Error("Failed to create OpenGL Window from function m_Init() called from function SetFullscreen(bool)");
			}*/
		}
	}

	/*ONLY INTEDED FOR DEBUG*/

	FORCEINLINE GLFWwindow * GLWindow::GetGLFWWindowPtr() { return m_Window; }


}