
namespace Amalgamation {

	VKWindow::VKWindow() : GLFWWindow() {
		m_PreInit = []() {
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		};
	}
	VKWindow::~VKWindow() {}

}