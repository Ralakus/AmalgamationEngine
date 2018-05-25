#include <Core/Event/EventHandler.hpp>
#include <Core/Utilities/Time.hpp>
#include <Core/Utilities/Aesset.hpp>
#include <Core/Scene/Scene.hpp>
#include <Engine/Graphics/OpenGL/GLWindow.hpp>
#include <Engine/Scene/Components/TransformComponent.hpp>

using namespace Amalgamation;

class TComp : public Component {
	friend class TCompSys;
	EventCallback<TComp> m_Callback;
	Math::Vec2 m_Pos[3];
public:
	TComp(Key InteractKey) : m_Callback(this, &TComp::Print), 
		m_Pos{
			{ 0.0f, 0.5f }, { -0.5f, -0.5f }, { 0.5f, -0.5f }
		} {
		Input::Instance().RegisterKeyAction("TComp", InteractKey, InputAction::Pressed);
		Input::Instance().RegisterCallback("TComp", &m_Callback);
	}
	~TComp() {
		AE_LOG_SUCCESS("Deletion works!");
		Input::Instance().DeregisterCallback(&m_Callback);
	}
	void Print() {
		AE_LOG_SUCCESS("Scene works");
	}
};

class TCompSys : public TComponentSystem < TComp > {
public:

	void Update() override {

		for (size_t i = 0; i < m_RegisteredComponents.size(); i++) {
			GLCall(glBegin(GL_TRIANGLES));
			GLCall(glVertex2f(static_cast<TComp*>(m_RegisteredComponents[i])->m_Pos[0][0], static_cast<TComp*>(m_RegisteredComponents[i])->m_Pos[0][1])); //Top
			GLCall(glVertex2f(static_cast<TComp*>(m_RegisteredComponents[i])->m_Pos[1][0], static_cast<TComp*>(m_RegisteredComponents[i])->m_Pos[1][1])); //Bottom Left
			GLCall(glVertex2f(static_cast<TComp*>(m_RegisteredComponents[i])->m_Pos[2][0], static_cast<TComp*>(m_RegisteredComponents[i])->m_Pos[2][1])); //Bottom Right
			glEnd();
		}

	}
};

int main(int argc, char* args[]) {

	Aesset Config;
	Config.LoadFile("Config.aesset");

	std::unique_ptr<Window> Window = std::make_unique<GLWindow>(
		Config.Get<std::string>("WindowName"), 
		Config.Get<unsigned int>("WindowWidth"), 
		Config.Get<unsigned int>("WindowHeight"),
		Config.Get<bool>("WindowFullscreen")
	);

	Time T;

	EventLambdaCallback CloseWindow([&]() -> void { Window->Close(); });
	Input::Instance().RegisterKeyAction("CloseWindow", Input::Instance().KeyFromAesset(Config, "CloseWindowKey"), InputAction::Held);
	Input::Instance().RegisterCallback ("CloseWindow", &CloseWindow);

	Scene  S;
	Actor* Player = S.CreateActor<Actor>();
	TCompSys* TCS = S.AddSystem<TCompSys>();
	TComp*    TC  = S.AddComponent<TComp>(Player, Input::Instance().KeyFromAesset(Config, "InteractKey"));

	TransformComponent* PlayerTransform = S.AddComponent<TransformComponent>(Player);
	TransformSystem* TransformationSystem = S.AddSystem<TransformSystem>();

	TransformationSystem->GetTransform(PlayerTransform).Position = { 1, 3, 5 };

	EventLambdaCallback DelAct([&]() -> void { S.DeleteActor(Player); });
	Input::Instance().RegisterKeyAction("DelAct", Input::Instance().KeyFromAesset(Config, "TestKey"), InputAction::Pressed);
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