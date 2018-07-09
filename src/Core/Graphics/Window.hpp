#pragma once

#include <Core/Platform/HelperMacros.hpp>
#include <Core/Input/InputManager.hpp>

#include <GLFW/glfw3.h>

#include <string>
#include <functional>

namespace Amalgamation {

	class Window {

	protected:

		GLFWwindow*        m_Window;
		GLFWmonitor*       m_Monitor;
		const GLFWvidmode* m_VidMode;

		int  m_Width, m_Height;
		bool m_Valid, m_Fullscreen,
			 m_CursorOnWindow, m_MouseLocked;
		
		std::string m_Title;

	public:

		 Window();
		 Window(const std::string& Title, int Width, int Height, bool Fullscreen = false);
		~Window();

		virtual bool Create(const std::string& Title, int Width, int Height, bool Fullscreen = false);
		virtual bool Close();

		virtual void Update();

		virtual void Terminate();

		void SetTitle(const std::string& Title);
		void SetTitle(const char* Title);
		FORCEINLINE const std::string& GetTitle() const { return m_Title; }

		virtual void SetFullscreen(bool Set);

		void LockMouse(bool set);

		virtual void Resize(int Width, int Height);
		int  GetWidth()  const { return m_Width;  }
		int  GetHeight() const { return m_Height; }

		FORCEINLINE bool IsMouseLocked()    const { return m_MouseLocked; }
		FORCEINLINE bool IsFullScreen()     const { return m_Fullscreen; }
		FORCEINLINE bool IsValid()          const { return m_Valid; }
		FORCEINLINE bool IsCursorOnWindow() const { return m_CursorOnWindow; }

		const GLFWwindow* GetGLFWPtr() const { return m_Window; }

	};

}

#if !defined(AE_NO_IMPL)
	#include "Window.inl"
#endif