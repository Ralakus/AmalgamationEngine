#pragma once

#include "../Platform/Platform.hpp"
#include "GraphicsClass.hpp"
#include "../Input/InputManager.hpp"

#include <string>

namespace Amalgamation {


	class Window : public GraphicsClass {

	protected:

		uint32 m_Width, m_Height;
		std::string m_Title;

		bool m_Valid       = false;
		bool m_Fullscreen  = false;
		bool m_MouseLocked = false;

	protected:

		static void UpdateKeyInput(int KeyCode, int Action);
		static void UpdateButtonInput(int ButtonCode, int Action);
		static void UpdateMousePos(float X, float Y);

	public:

		Window(const std::string& title, uint32 width, uint32 height, bool Fullscreen, API API);
		Window(API API);
		virtual ~Window();

		uint32 GetHeight() const;
		uint32 GetWidth()  const;

		virtual void SetTitle(const std::string& Title);
		virtual void SetTitle(const char* Title);
		const std::string& GetTitle() const;

		bool IsValid()       const;
		bool IsFullscreen()  const;
		bool IsMouseLocked() const;

		virtual void SetFullscreen(bool Set) = 0;
		virtual void LockMouse(bool Set)     = 0;
		virtual void Update()    = 0;
		virtual void Close()     = 0;
		virtual void Terminate() = 0;

	};


}

#include "Window.inl"