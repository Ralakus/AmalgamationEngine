#include <Engine/Graphics/Vulkan/VKWindow.hpp>


int main(int argc, char* argv[]) {

	Amalgamation::VKWindow AEWindow("Noice", 1280, 720, false);

	while (AEWindow.IsValid()) {
		AEWindow.Update();
	}

	return 0;

}