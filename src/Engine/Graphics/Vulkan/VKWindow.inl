#include <imgui.h>
#include <imgui_impl_glfw.h>

namespace Amalgamation {

	FORCEINLINE bool VKWindow::Create() {
		m_Window = nullptr;

		if (!glfwInit()) {
			std::cerr << rang::fgB::red << "[ vk::error ]: " << rang::fg::reset << "Failed to initialize glfw!" << rang::fgB::yellow << "\nEND" << rang::fg::reset << std::endl;
			return false;
		}

		//glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_Monitor = glfwGetPrimaryMonitor();
		m_Mode = glfwGetVideoMode(m_Monitor);

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), m_Fullscreen ? m_Monitor : nullptr, nullptr);

		if (!m_Window) {
			std::cerr << rang::fgB::red << "[ vk::error ]: " << rang::fg::reset << "Failed to assign window!" << rang::fgB::yellow << "\nEND" << rang::fg::reset << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* Window, int Width, int Height) {});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) { Window::UpdateButtonInput(button, action); ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods); });
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) { ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset); });
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) { Window::UpdateKeyInput(key, action); ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);  });
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int c) { ImGui_ImplGlfw_CharCallback(window, c); });
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) { Window::UpdateMousePos(static_cast<float>(xpos), static_cast<float>(ypos)); });
		glfwSetCursorEnterCallback(m_Window, [](GLFWwindow* window, int entered) { VKWindow* AEWindow = static_cast<VKWindow*>(glfwGetWindowUserPointer(window)); AEWindow->m_CursorOnWindow = entered; });

		Vulkan.InitVulkan(m_Window, m_Width, m_Height);

		m_Valid = true;

		return true;
	}

	FORCEINLINE VKWindow::VKWindow() : Window(API::Vulkan) {
		if (!Create()) {
			std::cerr << rang::fgB::red << "[ vk::error ]: " << rang::fg::reset << "Failed to create OpenGL window!" << rang::fgB::yellow << "\nEND" << rang::fg::reset << std::endl;
			glfwDestroyWindow(m_Window);
		}
	}

	FORCEINLINE VKWindow::VKWindow(const std::string & title, uint32_t width, uint32_t height, bool Fullscreen)
		: Window(title, width, height, Fullscreen, API::Vulkan)
	{
		if (!Create()) {
			std::cerr << rang::fgB::red << "[ vk::error ]: " << rang::fg::reset << "Failed to create OpenGL window!" << rang::fgB::yellow << "\nEND" << rang::fg::reset << std::endl;
			glfwDestroyWindow(m_Window);
		}
	}

	FORCEINLINE VKWindow::~VKWindow() { Vulkan.VulkanCleanUp(); glfwTerminate(); }

	FORCEINLINE void VKWindow::LockMouse(bool set) { if (set) { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); } else { glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); } m_MouseLocked = set; }

	FORCEINLINE void VKWindow::Close() { m_Valid = false; glfwSetWindowShouldClose(m_Window, GLFW_TRUE); }

	FORCEINLINE void VKWindow::Update() {
		if (!glfwWindowShouldClose(m_Window) && m_Valid) {
			glfwGetFramebufferSize(m_Window, reinterpret_cast<int*>(&m_Width), reinterpret_cast<int*>(&m_Height));
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
		else {
			m_Valid = false;
		}
	}

	FORCEINLINE void VKWindow::Terminate() {
		m_Valid = false;
		glfwDestroyWindow(m_Window);
	}

	FORCEINLINE void VKWindow::SetTitle(const std::string & Title) { m_Title = Title; glfwSetWindowTitle(m_Window, Title.c_str()); }

	FORCEINLINE void VKWindow::SetTitle(const char * Title) { m_Title = Title; glfwSetWindowTitle(m_Window, Title); }

	FORCEINLINE void VKWindow::SetFullscreen(bool Set) {
		if (Set != m_Fullscreen) {
			m_Fullscreen = Set;
			glfwSetWindowMonitor(m_Window, Set ? m_Monitor : nullptr, 0, 0, m_Width, m_Height, m_Mode->refreshRate);
		}
	}

	FORCEINLINE void VKWindow::Resize(uint32_t Width, uint32_t Height) {
		if (!m_Fullscreen) {
			glfwSetWindowSize(m_Window, Width, Height);
		}
		else {
			glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, Width, Height, m_Mode->refreshRate);
		}
		m_Width = Width; m_Height = Height;
	}

	/*ONLY INTEDED FOR DEBUG*/
	FORCEINLINE GLFWwindow * VKWindow::GetGLFWWindowPtr() { return m_Window; }

}