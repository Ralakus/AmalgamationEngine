#pragma once

#include <Core/Platform/Platform.hpp>
#include <Core/Input/Input.hpp>
#include "GraphicsClass.hpp"
#include <string>

namespace Amalgamation {

	class Window : public GraphicsClass {
	protected:

		std::string m_Title;
		uint32 m_Width, m_Height;

		bool m_Valid = false;

		bool m_Fullscreen = false;

		virtual bool m_Init() = 0;

	public:
		static void SetInputKey(unsigned int key, bool state) { Keyboard::Instance().SetKeyState(key, state); }
		static void SetMouseButton(unsigned int button, bool state) { Mouse::Instance().SetButtonState(button, state); }
		static void SetMousePos(float x, float y) { Mouse::Instance().SetPos(x, y); }

	public:

		Window(const std::string& title, uint32 width, uint32 height, bool Fullscreen, API API) : GraphicsClass(API), m_Title(title), m_Width(width), m_Height(height), m_Fullscreen(Fullscreen) {}
		Window(API API) : GraphicsClass(API), m_Title("Amalgamation Default"), m_Width(1280), m_Height(720) {}
		virtual ~Window() {}

		inline virtual uint32 GetHeight() const { return m_Height; }
		inline virtual uint32 GetWidth() const { return m_Width; }

		virtual void SetTitle(const std::string& title) { m_Title = title; }
		virtual void SetTitle(const char* title) { m_Title = title; }
		inline virtual const std::string& GetTitle() const { return m_Title; }

		virtual void LockMouse(bool set) {}

		virtual void Close() = 0;

		virtual void Update() = 0;
		virtual void Terminate() = 0;

		virtual bool IsValid() { return m_Valid; }
		virtual bool IsFullscreen() { return m_Fullscreen; }
	};

}