#include <Engine/Graphics/Vulkan/VKWindow.hpp>

#include <iostream>

int main(int argc, char* argv[]) {

	Amalgamation::VKWindow Window;
	Window.CreateVK("AEVK", 1280, 720, false);

	while (Window.IsValid()) {
		Window.Update();
	}

	return 0;
}
