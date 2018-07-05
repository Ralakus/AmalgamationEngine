#include "AppPackage.hpp"

namespace Amalgamation {
	AppPackage::AppPackage(int argc, char * argv[], ConstructParams & Params)
		: RenderWindow(Params.RenderWindowName, Params.RenderWindowWitdh,
			Params.RenderWindowHeight, Params.RenderWindowFullscreen),
		EngineTime(),
		OnAwake([]() {}),
		OnUpdate([](float) {}),
		OnCleanUp([]() {}),
		DebugMenuEdgePadding(10.f),
		ShowDebugMenu(true),
		DebugMenuMoreInfo(true),
		DebugMenuMoreInfoFunction([]() {}),
		DebugPopupMenuFunction([]() {})
	{
		if (argc > 0) {
			for (int i = 0; i < argc; i++) {
				if (argv[i] == "-HideInfoMenu") {
					ShowDebugMenu = false;
				}
			}
		}
	}

	FORCEINLINE int AppPackage::Runtime() {

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplGlfw_InitForOpenGL(RenderWindow.GetGLFWWindowPtr(), false);
		ImGui_ImplOpenGL3_Init();

		ImGui::StyleColorsDark();
		ImGuiStyle* Style = &ImGui::GetStyle();
		Style->WindowRounding = 1.0f;
		Style->FrameRounding = 1.0f;

		ImVec2 DebugMenuPos; DebugMenuPos.y = DebugMenuEdgePadding;
		GLCall(const char* GLVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION)));

		try {
			OnAwake();
		}
		catch (std::exception& e) {
#ifdef AE_WINDOWS
			::ShowWindow(::GetConsoleWindow(), SW_SHOW);
#endif
			std::cout << rang::fgB::red << "[ERROR]: Unhandled exception: " << e.what() << rang::fg::reset << std::endl;
			RenderWindow.Terminate();
			return -1;
		}

		while (RenderWindow.IsValid()) {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			RenderWindow.Update();
			EngineTime.Update();

			if (ShowDebugMenu) {
				DebugMenuPos.x = ImGui::GetIO().DisplaySize.x - DebugMenuEdgePadding;
				ImGui::SetNextWindowPos(DebugMenuPos, ImGuiCond_Always, ImVec2(1.f, 0.f));
				ImGui::SetNextWindowBgAlpha(0.3f);
				ImGui::Begin("Amalgamation Info Menu", &ShowDebugMenu, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
				ImGui::Text("Amalgamation Engine (Right-click window for more options)");
				ImGui::Text("OpenGL Version: %s", GLVersion);
				ImGui::Separator();
				ImGui::Text("FPS: %f", EngineTime.GetAvgFPS());
				ImGui::Text("Frame Delta: %f", EngineTime.GetDelta());
				ImGui::Text("Elapsed Time: %0.1f", EngineTime.GetElapsed());
				if (DebugMenuMoreInfo) {
					ImGui::Separator();
					DebugMenuMoreInfoFunction();
				}
				if (ImGui::BeginPopupContextWindow()) {
					if (DebugMenuMoreInfo) {
						if (ImGui::MenuItem("Show Less Info")) { DebugMenuMoreInfo = false; }
					}
					else {
						if (ImGui::MenuItem("Show More Info")) { DebugMenuMoreInfo = true; }
					}

					DebugPopupMenuFunction();

					if (ImGui::MenuItem("Close Program")) { RenderWindow.Close(); }
					ImGui::EndPopup();
				}
				ImGui::End();
			}


			try {
				OnUpdate(EngineTime.GetDelta());
			}
			catch (std::exception& e) {
#ifdef AE_WINDOWS
				::ShowWindow(::GetConsoleWindow(), SW_SHOW);
#endif
				std::cout << rang::fgB::red << "[ERROR]: Unhandled exception: " << e.what() << rang::fg::reset << std::endl;
				RenderWindow.Terminate();
				return -1;
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		}

		try {
			OnCleanUp();
		}
		catch (std::exception& e) {
#ifdef AE_WINDOWS
			::ShowWindow(::GetConsoleWindow(), SW_SHOW);
#endif
			std::cout << rang::fgB::red << "[ERROR]: Unhandled exception: " << e.what() << rang::fg::reset << std::endl;
			RenderWindow.Terminate();
			return -1;
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		return 0;
	}

}