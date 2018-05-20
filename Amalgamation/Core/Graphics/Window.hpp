#pragma once

#include "../Platform/Typedef.hpp"
#include "GraphicsClass.hpp"
#include "../Input/ArchaicInput.hpp"

#include <string>

namespace Amalgamation {


	class Window : public GraphicsClass {

	protected:

		uint32 m_Width, m_Height;
		std::string m_Title;

		bool m_Valid      = false;
		bool m_Fullscreen = false;

	protected:

		static void SetInputKey(unsigned int key, bool state) { Keyboard::Instance().SetKeyState(key, state); }
		static void SetMouseButton(unsigned int button, bool state) { Mouse::Instance().SetButtonState(button, state); }
		static void SetMousePos(float x, float y) { Mouse::Instance().SetPos(x, y); }

	public:

		Window(const std::string& title, uint32 width, uint32 height, bool Fullscreen, API API) : GraphicsClass(API), m_Title(title), m_Width(width), m_Height(height), m_Fullscreen(Fullscreen) {}
		Window(API API) : GraphicsClass(API), m_Title("Amalgamation Default"), m_Width(1280), m_Height(720) {}
		virtual ~Window() {}

		uint32 GetHeight() const { return m_Height; }
		uint32 GetWidth()  const { return m_Width;  }

		virtual void SetTitle(const std::string& Title) { m_Title = Title; }
		virtual void SetTitle(const char* Title)        { m_Title = Title; }
		const std::string& GetTitle() const     { return m_Title;  }

		bool IsValid()      const { return m_Valid;      }
		bool IsFullscreen() const { return m_Fullscreen; }

		virtual void SetFullscreen(bool Set) = 0;
		virtual void LockMouse(bool Set)     = 0;
		virtual void Update()    = 0;
		virtual void Close()     = 0;
		virtual void Terminate() = 0;

	};


}