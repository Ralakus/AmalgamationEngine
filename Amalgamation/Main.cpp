//#define AE_FORCE_TIMER_CHRONO

#include <Core/Event/EventHandler.hpp>
#include <Core/Utilities/Time.hpp>
#include <Core/Utilities/Aesset.hpp>
#include <Core/Scene/Scene.hpp>
#include <Engine/Graphics/OpenGL/GLWindow.hpp>

using namespace Amalgamation;

class TComp : public Component {
	EventCallback<TComp> m_Callback;
public:
	TComp() : m_Callback(this, &TComp::Print) {
		Input::Instance().RegisterKeyAction("TComp", Key::E, InputAction::Pressed);
		Input::Instance().RegisterCallback("TComp", &m_Callback);
	}
	~TComp() {
		Input::Input().DeregisterCallback(&m_Callback);
	}
	void Print() {
		AE_LOG_SUCCESS("Scene works");
	}
};

class TCompSys : public TComponentSystem < TComp > {
public:

	void Update() override {

		for (size_t i = 0; i < m_RegisteredComponents.size(); i++) {
			if (m_RegisteredComponents[i] == nullptr) {
				DeregisterComponent(m_RegisteredComponents[i]);
			}
		}

		for (size_t i = 0; i < m_RegisteredComponents.size(); i++) {
			glBegin(GL_TRIANGLES);
			glVertex2f(0.0, 0.5);   //Top
			glVertex2f(-0.5, -0.5); //Bottom Left
			glVertex2f(0.5, -0.5);  //Bottom Right
			glEnd();
		}

	}
};

int main(int argc, char* args[]) {

	Aesset Config;
	Config.LoadFile("Config.aesset");

	std::unique_ptr<Window> Window = std::make_unique<GLWindow>(Config.Get<std::string>("WindowName"), Config.Get<unsigned int>("WindowWidth"), Config.Get<unsigned int>("WindowHeight"));

	Time T;

	EventLambdaCallback CloseWindow([&]() -> void { Window->Close(); });
	Input::Instance().RegisterKeyAction("CloseWindow", Key::Escape, InputAction::Held);
	Input::Instance().RegisterCallback ("CloseWindow", &CloseWindow);

	EventFunctionCallback TestCallback([]() -> void {
		AE_LOG_SUCCESS("Key W pressed");
	});
	Input::Instance().RegisterKeyAction("Test1", Key::W, InputAction::Pressed);
	Input::Instance().RegisterCallback ("Test1", &TestCallback);

	Scene  S;
	Actor* Player = S.CreateActor<Actor>();
	TCompSys* TCS = S.AddSystem<TCompSys>();
	TComp* TC = S.AddComponent<TComp>(Player);

	EventLambdaCallback DelAct([&]() -> void { S.DeleteActor(Player); });
	Input::Instance().RegisterKeyAction("DelAct", Key::Q, InputAction::Pressed);
	Input::Instance().RegisterCallback("DelAct", &DelAct);

	S.Awake();

	while (Window->IsValid()) {
		S.Update();
		Window->Update();
		T.Update();

		if (T.OnSecond()) {
			Window->SetTitle("FPS: " + std::to_string(T.GetAvgFPS()));
		}
	}

	S.Destroy();

	return 0;

}