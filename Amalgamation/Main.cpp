#define AE_USE_GLFW_TIME
#include <Engine/Application/AppPackage.hpp>

#include <WIP/Scene/Scene.hpp>

using namespace Amalgamation;

int main(int argc, char* argv[]) {

#ifdef AE_WINDOWS
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif

	//================================================
	//Loads config file and creates application
	//================================================

	Aesset Config;
	Config.LoadFile("Config.aesset");
	Aesset WindowConfig;
	WindowConfig.LoadDataString(Config.Get<std::string>("Window"));
	Aesset CamConfig;
	CamConfig.LoadDataString(Config.Get<std::string>("Camera"));
	Aesset InputConfig;
	InputConfig.LoadDataString(Config.Get<std::string>("Input"));
	Aesset MovementConfig;
	MovementConfig.LoadDataString(InputConfig.Get<std::string>("Movement"));
	Aesset MiscConfig;
	MiscConfig.LoadDataString(Config.Get<std::string>("Misc"));

	GLint ViewPort[4];
	bool ShowSettingsMenu = false;

	AppPackage::ConstructParams Params;
	Params.RenderWindowName       = WindowConfig.Get<std::string>("Name", "Noice");
	Params.RenderWindowWitdh      = WindowConfig.Get<uint32>     ("Width", 1280u);
	Params.RenderWindowHeight     = WindowConfig.Get<uint32>     ("Height", 720u);
	Params.RenderWindowFullscreen = WindowConfig.Get<bool>       ("Fullscreen", false);

	int TargetResolution[2] = { Params.RenderWindowWitdh, Params.RenderWindowHeight };

	AppPackage App(argc, argv, Params);

	App.DebugMenuEdgePadding = MiscConfig.Get<float>("InfoMenuPadding");


	//================================================
	//Binds input
	//================================================

	EventLambdaCallback ECCloseWindow([&]() -> void { App.RenderWindow.Close(); });
	Input::Instance().RegisterKeyAction("CloseWindow", Input::Instance().KeyFromAesset(InputConfig, "CloseKey"), InputAction::Held);
	Input::Instance().RegisterCallback("CloseWindow", &ECCloseWindow);

	EventLambdaCallback ECToggleMouseLock([&]() -> void { App.RenderWindow.LockMouse(!App.RenderWindow.IsMouseLocked()); });
	Input::Instance().RegisterKeyAction("ToggleMouseLock", Input::Instance().KeyFromAesset(InputConfig, "ToggleMouseLockKey"), InputAction::Pressed);
	Input::Instance().RegisterCallback("ToggleMouseLock", &ECToggleMouseLock);

	InputControl ICMoveForward;
	ICMoveForward.AddInput(Input::Instance().KeyFromAesset(MovementConfig, "Forward", Key::W), 1.f);
	ICMoveForward.AddInput(Input::Instance().KeyFromAesset(MovementConfig, "Backwards", Key::S), -1.f);

	InputControl ICMoveRight;
	ICMoveRight.AddInput(Input::Instance().KeyFromAesset(MovementConfig, "Right", Key::D), 1.f);
	ICMoveRight.AddInput(Input::Instance().KeyFromAesset(MovementConfig, "Left", Key::A), -1.f);

	InputControl ICMoveUp;
	ICMoveUp.AddInput(Input::Instance().KeyFromAesset(MovementConfig, "Up", Key::Space), 1.f);
	ICMoveUp.AddInput(Input::Instance().KeyFromAesset(MovementConfig, "Down", Key::C), -1.f);

	InputControl ICRollRight;
	ICRollRight.AddInput(Input::Instance().KeyFromAesset(MovementConfig, "RollRight", Key::E), 1.f);
	ICRollRight.AddInput(Input::Instance().KeyFromAesset(MovementConfig, "RollLeft", Key::Q), -1.f);

	App.OnAwake = [&]() {
		GLCall(glClearColor(0.7f, 0.7f, 0.7f, 0.7f));
	};

	App.OnUpdate = [&](float Delta) {
		GLCall(glGetIntegerv(GL_VIEWPORT, ViewPort));

		if (ShowSettingsMenu) {
			ImGui::Begin("Settings");
			ImGui::Checkbox("Fullscreen", &Params.RenderWindowFullscreen);
			ImGui::InputInt2("Resolution", TargetResolution);
			ImGui::Separator();
			if (ImGui::Button("Apply")) {
				if (Params.RenderWindowFullscreen != App.RenderWindow.IsFullscreen()) {
					App.RenderWindow.Resize(TargetResolution[0], TargetResolution[1]);
					App.RenderWindow.SetFullscreen(Params.RenderWindowFullscreen);
				}
				if (TargetResolution[0] != App.RenderWindow.GetWidth() && TargetResolution[1] != App.RenderWindow.GetHeight()) {
					App.RenderWindow.Resize(TargetResolution[0], TargetResolution[1]);
				}
			} ImGui::SameLine();
			if (ImGui::Button("Close")) { ShowSettingsMenu = false; }
			ImGui::End();
		}

	};

	App.OnCleanUp = [&]() {

	};

	App.DebugMenuMoreInfoFunction = [&]() {
		ImGui::Text("OpenGL Viewport Size: %i x %i", ViewPort[2], ViewPort[3]);
		if (Input::Instance().IsCursorOnWindow()) {
			ImGui::Text("Mouse Position: %0.0f, %0.0f", Input::Instance().GetMousePos().x, Input::Instance().GetMousePos().y);
		}
		else {
			ImGui::Text("Mouse Position: <Invalid>");
		}
		ImGui::Separator();
		ImGui::Text("ICMoveForward: %0.1f", ICMoveForward.Value());
		ImGui::Text("ICMoveRight:   %0.1f", ICMoveRight.Value());
		ImGui::Text("ICMoveUp:      %0.1f", ICMoveUp.Value());
		ImGui::Text("ICRollRight:   %0.1f", ICRollRight.Value());
		ImGui::Separator();
		ImGui::Text("Target Resolution: %i x %i", TargetResolution[0], TargetResolution[1]);
		ImGui::Text("Current Resolution: %i x %i", App.RenderWindow.GetWidth(), App.RenderWindow.GetHeight());
	};

	App.DebugPopupMenuFunction = [&]() {
		if (ImGui::MenuItem("Settings Menu")) { ShowSettingsMenu = !ShowSettingsMenu; }
	};


	int AppResult = App.Start();

	if (AppResult == -1) {
#ifdef AE_WINDOWS
		::ShowWindow(::GetConsoleWindow(), SW_SHOW);
#endif
		std::cout << rang::fgB::cyan << "Press Enter to Close..." << rang::fg::reset << std::endl;
		std::cin.get();
	}

	return AppResult;
}