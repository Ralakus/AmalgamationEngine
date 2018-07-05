#pragma once

#include <Core/Input/InputControl.hpp>
#include <Core/Utilities/Time.hpp>
#include <Core/Audio/Instance.hpp>
#include <Engine/Graphics/OpenGL/GLWindow.hpp>
#include <Engine/Graphics/ImGui/Console.hpp>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <rang.hpp>

namespace Amalgamation {

	class AppPackage {

	public:

		struct ConstructParams {
			std::string RenderWindowName;
			uint32 RenderWindowWitdh;
			uint32 RenderWindowHeight;
			bool RenderWindowFullscreen;
		};

	private:

		int Runtime();

	public:

		GLWindow RenderWindow;
		Time EngineTime;

		bool  ShowDebugMenu;
		bool  DebugMenuMoreInfo;
		float DebugMenuEdgePadding;

		std::function<void()>      OnAwake;
		std::function<void(float)> OnUpdate;
		std::function<void()>      OnCleanUp;

		std::function<void()> DebugMenuMoreInfoFunction;
		std::function<void()> DebugPopupMenuFunction;

		AppPackage(int argc, char* argv[], ConstructParams& Params);

		~AppPackage() {}

		FORCEINLINE int Start() { return Runtime(); }


	};

}

#include "AppPackage.inl"