#pragma once

#include <Core/Graphics/Window.hpp>
#include "VKInstancePackage.hpp"

namespace Amalgamation {

    class VKWindow : public Window {
		
		GLFWwindow* m_Window;
		GLFWmonitor* m_Monitor;
		const GLFWvidmode* m_Mode;

		bool Create();

		AEVK Vulkan;

	public:
		

		VKWindow();
		VKWindow(const std::string& title, uint32_t width, uint32_t height, bool Fullscreen = false);

		~VKWindow();

		void LockMouse(bool set) override;

		void Close() override;

		void Update() override;
		void Terminate() override;

		void SetTitle(const std::string& Title) override;
		void SetTitle(const char* Title) override;

		void SetFullscreen(bool Set) override;

		void Resize(uint32_t Width, uint32_t Height) override;

		GLFWwindow* GetGLFWWindowPtr();

    };

}

#if !defined(AE_NO_IMPL)
    #include "VKWindow.inl"
#endif