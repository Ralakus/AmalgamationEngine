
namespace Amalgamation {
	FORCEINLINE GLFWWindow::GLFWWindow()
		: m_Window(nullptr), m_Monitor(nullptr), m_VidMode(nullptr),
		  m_Width(800), m_Height(600), m_Valid(false), m_Fullscreen(false),
		  m_CursorOnWindow(false), m_MouseLocked(false)
	{}

	FORCEINLINE GLFWWindow::~GLFWWindow() { Terminate(); }

	FORCEINLINE bool GLFWWindow::CreateWindow(const std::string& Title, int Width, int Height, bool Fullscreen) {
		m_Title = Title; m_Width = Width; m_Height = Height; m_Fullscreen = Fullscreen;

		if (m_Window) {
			return false;
		}
		else {

			if (!glfwInit()) {
				return false;
			}

			//glfwWindowHint(GLFW_SAMPLES, 4);
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			m_Monitor = glfwGetPrimaryMonitor();
			m_VidMode = glfwGetVideoMode(m_Monitor);

			if (m_Fullscreen) {
				m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), m_Monitor, nullptr);
			}
			else {
				m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
			}

			if (!m_Window) {
				return false;
			}

			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);

			glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) { Input::Instance().UpdateButtons(static_cast<Button>(button), static_cast<InputAction>(action)); });
			glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) { Input::Instance().UpdateKeys(static_cast<Key>(key), static_cast<InputAction>(action));  });
			glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) { Input::Instance().UpdateMousePos(static_cast<float>(xpos), static_cast<float>(ypos)); });
			glfwSetCursorEnterCallback(m_Window, [](GLFWwindow* Window, int Entered) {  GLFWWindow* AEWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(Window)); AEWindow->m_CursorOnWindow = Entered; });

			m_Valid = true;

			return true;

		}


		return false;
	}

	FORCEINLINE bool GLFWWindow::Close() {
		if (m_Valid) {
			glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
			m_Valid = false;
			return true;
		}
		else {
			return false;
		}
	}

	FORCEINLINE void GLFWWindow::Update() {

		if (!glfwWindowShouldClose(m_Window) && m_Valid) {
			glfwGetFramebufferSize(m_Window, reinterpret_cast<int*>(&m_Width), reinterpret_cast<int*>(&m_Height));
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
		else {
			m_Valid = false;
		}

	}

	FORCEINLINE void GLFWWindow::Terminate() {
		glfwDestroyWindow(m_Window);
	}

	FORCEINLINE void GLFWWindow::SetTitle(const std::string & Title) { m_Title = Title; glfwSetWindowTitle(m_Window, Title.c_str()); }

	FORCEINLINE void GLFWWindow::SetTitle(const char * Title) { m_Title = Title; glfwSetWindowTitle(m_Window, Title);  }

	FORCEINLINE void GLFWWindow::SetFullscreen(bool Set) {
		if (Set != m_Fullscreen) {
			m_Fullscreen = Set;
			glfwSetWindowMonitor(m_Window, Set ? m_Monitor : nullptr, 0, 0, m_Width, m_Height, m_VidMode->refreshRate);
		}
	}

	FORCEINLINE void GLFWWindow::LockMouse(bool set) {
		if (set) { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
		else { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); } m_MouseLocked = set;
	}

	FORCEINLINE void GLFWWindow::Resize(int Width, int Height) {
		if (!m_Fullscreen) {
			glfwSetWindowSize(m_Window, Width, Height);
		}
		else {
			glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, Width, Height, m_VidMode->refreshRate);
		}
		m_Width = Width; m_Height = Height;
	}

}