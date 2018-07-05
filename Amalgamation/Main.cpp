#include <Engine/Application/AppPackage.hpp>

#include <WIP/Scene/Scene.hpp>

using namespace Amalgamation;

int main(int argc, char* argv[]) {

#ifdef AE_WINDOWS
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
#endif

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

	AppPackage::ConstructParams Params;
	Params.RenderWindowName       = WindowConfig.Get<std::string>("Name", "Noice");
	Params.RenderWindowWitdh      = WindowConfig.Get<uint32>     ("Width", 1280u);
	Params.RenderWindowHeight     = WindowConfig.Get<uint32>     ("Height", 720u);
	Params.RenderWindowFullscreen = WindowConfig.Get<bool>       ("Fullscreen", false);

	AppPackage App(argc, argv, Params);

	App.DebugMenuEdgePadding = MiscConfig.Get<float>("InfoMenuPadding");

	EventLambdaCallback ECCloseWindow([&]() -> void { App.RenderWindow.Close(); });
	Input::Instance().RegisterKeyAction("CloseWindow", Input::Instance().KeyFromAesset(InputConfig, "CloseKey"), InputAction::Held);
	Input::Instance().RegisterCallback("CloseWindow", &ECCloseWindow);

	EventLambdaCallback ECToggleMouseLock([&]() -> void { App.RenderWindow.LockMouse(!App.RenderWindow.IsMouseLocked()); });
	Input::Instance().RegisterKeyAction("ToggleMouseLock", Input::Instance().KeyFromAesset(InputConfig, "ToggleMouseLockKey"), InputAction::Pressed);
	Input::Instance().RegisterCallback("ToggleMouseLock", &ECToggleMouseLock);

	GLint ViewPort[4];

	App.OnAwake = [&]() {
		GLCall(glClearColor(0.7f, 0.7f, 0.7f, 0.7f));
	};

	App.OnUpdate = [&](float Delta) {
		GLCall(glGetIntegerv(GL_VIEWPORT, ViewPort));
	};

	App.OnCleanUp = [&]() {

	};

	App.DebugMenuMoreInfoFunction = [&]() {
		if (Input::Instance().IsCursorOnWindow()) {
			ImGui::Text("Mouse Position: %0.0f, %0.0f", Input::Instance().GetMousePos().x, Input::Instance().GetMousePos().y);
		}
		else {
			ImGui::Text("Mouse Position: <Invalid>");
		}
		ImGui::Text("OpenGL Viewport Size: %i, %i", ViewPort[2], ViewPort[3]);
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