
namespace Amalgamation {

	FORCEINLINE void Window::UpdateKeyInput(int KeyCode, int Action) {
		Input::Instance().UpdateKeys(static_cast<Key>(KeyCode), static_cast<InputAction>(Action));
	}

	FORCEINLINE void Window::UpdateButtonInput(int ButtonCode, int Action) {
		Input::Instance().UpdateButtons(static_cast<Button>(ButtonCode), static_cast<InputAction>(Action));
	}

	FORCEINLINE void Window::UpdateMousePos(float X, float Y) {
		Input::Instance().UpdateMousePos(X, Y);
	}

	FORCEINLINE Window::Window(const std::string & title, uint32_t width, uint32_t height, bool Fullscreen, API API) : GraphicsClass(API), m_Title(title), m_Width(width), m_Height(height), m_Fullscreen(Fullscreen) {}

	FORCEINLINE Window::Window(API API) : GraphicsClass(API), m_Title("Amalgamation Default"), m_Width(1280), m_Height(720) {}

	FORCEINLINE Window::~Window() {}

	FORCEINLINE uint32_t Window::GetHeight() const { return m_Height; }

	FORCEINLINE uint32_t Window::GetWidth() const { return m_Width; }

	FORCEINLINE void Window::SetTitle(const std::string & Title) { m_Title = Title; }

	FORCEINLINE void Window::SetTitle(const char * Title) { m_Title = Title; }

	FORCEINLINE const std::string & Window::GetTitle() const { return m_Title; }

	FORCEINLINE bool Window::IsValid() const { return m_Valid; }

	FORCEINLINE bool Window::IsFullscreen() const { return m_Fullscreen; }

	FORCEINLINE bool Window::IsMouseLocked() const { return m_MouseLocked; }

	FORCEINLINE bool Window::IsCursorOnWindow() const { return m_CursorOnWindow; }

}