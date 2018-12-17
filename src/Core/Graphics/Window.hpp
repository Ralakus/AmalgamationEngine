#pragma once

#include "../Platform/Platform.hpp"
#include "GraphicsClass.hpp"
#include "../Input/InputManager.hpp"

#include <string>

namespace Amalgamation {


	class Window : public GraphicsClass {

	protected:

		uint32_t m_Width, m_Height;
		std::string m_Title;

		bool m_Valid          = false;
		bool m_Fullscreen     = false;
		bool m_MouseLocked    = false;
		bool m_CursorOnWindow = false;

		void UpdateKeyInput(int KeyCode, int Action);
		void UpdateButtonInput(int ButtonCode, int Action);
		void UpdateMousePos(float X, float Y);

	public:

		Input* InputManager = nullptr;

		Window(const std::string& title, uint32_t width, uint32_t height, bool Fullscreen, API API);
		Window(API API);
		virtual ~Window();

		uint32_t GetHeight() const;
		uint32_t GetWidth()  const;
		virtual void Resize(uint32_t Width, uint32_t Height) = 0;

		virtual void SetTitle(const std::string& Title);
		virtual void SetTitle(const char* Title);
		const std::string& GetTitle() const;

		bool IsValid()          const;
		bool IsFullscreen()     const;
		bool IsMouseLocked()    const;
		bool IsCursorOnWindow() const;

		virtual void SetFullscreen(bool Set) = 0;
		virtual void LockMouse(bool Set)     = 0;
		virtual void Update()    = 0;
		virtual void Close()     = 0;
		virtual void Terminate() = 0;

	};


}
#ifndef AE_NO_IMPL
	#include "Window.inl"
#endif