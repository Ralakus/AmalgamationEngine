
#include <Core/Input/InputControl.hpp>
#include <Engine/Graphics/Vulkan/VKWindow.hpp>
#include <WIP/Aesset2.hpp>

int main(int argc, char* argv[]) {

	Amalgamation::Aesset2 Config;
	Config.LoadFile("Config.aesset");

	Amalgamation::Input InputManager;
	Amalgamation::VKWindow AEWindow(
		Config["Window"]["Name"]      .As<std::string>("Noice"),
		Config["Window"]["Width"]     .As<unsigned int>(1280),
		Config["Window"]["Height"]    .As<unsigned int>(720),
		Config["Window"]["Fullscreen"].As<bool>(false)
	);
	AEWindow.InputManager = &InputManager;

	Amalgamation::InputControl ICKeyF;
	ICKeyF.InputManager = &InputManager;
	ICKeyF.AddInput(Amalgamation::Key::F, 1.f);

	std::shared_ptr<Amalgamation::EventLambdaCallback> ECCloseWindow = std::make_shared<Amalgamation::EventLambdaCallback>([&]() { AEWindow.Close(); });
	InputManager.RegisterKeyAction("ECCloseWindow", Amalgamation::Key::Escape, Amalgamation::InputAction::Held);
	InputManager.RegisterCallback("ECCloseWindow", ECCloseWindow);

	while (AEWindow.IsValid()) {
		AEWindow.Update();
		if (ICKeyF.Value()) {
			std::cout << rang::fgB::green << "Noice" << rang::fg::reset << std::endl;
		}
	}

	return 0;
}