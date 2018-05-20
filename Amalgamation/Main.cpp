#include <Engine/Graphics/OpenGL/GLWindow.hpp>
#include <Core/Event/EventHandler.hpp>

using namespace Amalgamation;

int main(int argc, char* args[]) {

	std::unique_ptr<Window> Window = std::make_unique<GLWindow>("Noice", 1920, 1080);

	EventHandler EventSystem;
	Event TestEvent;
	EventSystem.RegisterEvent("Test", &TestEvent);

	EventFunctionCallback TestCallback([]() -> void { AE_LOG_SUCCESS("Key pressed registered"); });
	EventSystem.RegisterCallback("Test", &TestCallback);

	while (Window->IsValid()) {
		Window->Update();
		
		glBegin(GL_TRIANGLES);
		glVertex2f(0.0, 0.5);   //Top
		glVertex2f(-0.5, -0.5); //Bottom Left
		glVertex2f(0.5, -0.5);  //Bottom Right
		glEnd();

		if (Keyboard::Instance().GetKeyState('W')) {
			EventSystem.TriggerEvent("Test");
		}

		if (Keyboard::Instance().GetKeyState(GLFW_KEY_ESCAPE)) {
			Window->Close();
		}
	}

	return 0;

}