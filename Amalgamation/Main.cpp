#include <Core/Event/EventHandler.hpp>
#include <Core/Utilities/Time.hpp>
#include <Core/Utilities/Aesset.hpp>
#include <Core/Level/Level.hpp>
#include <Core/Graphics/Mesh.hpp>
#include <Core/Utilities/Random.hpp>
#include <Engine/Graphics/OpenGL/GLWindow.hpp>

using namespace Amalgamation;

int main(int argc, char* args[]) {

	Aesset Config;
	Config.LoadFile("Config.aesset");

	AE_LOG_NOTE(("TODO:" + Config.Get<std::string>("TODO")).c_str());

	std::unique_ptr<Window> Window = std::make_unique<GLWindow>(
		Config.Get<std::string> ("WindowName"), 
		Config.Get<unsigned int>("WindowWidth"), 
		Config.Get<unsigned int>("WindowHeight"),
		Config.Get<bool>        ("WindowFullscreen")
	);

	Time T;

	EventLambdaCallback CloseWindow([&]() -> void { Window->Close(); });
	Input::Instance().RegisterKeyAction("CloseWindow", Input::Instance().KeyFromAesset(Config, "CloseWindowKey"), InputAction::Held);
	Input::Instance().RegisterCallback ("CloseWindow", &CloseWindow);

	EventFunctionCallback WriteCube([]()-> void {
		Aesset Cube("Cube.aesset", true, std::ios::in | std::ios::out | std::ios::trunc);
		MeshData SphereMD = Mesh::MakeMeshData(Mesh::Primitive::Cube);
		Cube.WriteProperty("Vertices Size", std::to_string(SphereMD.Vertices.size() - 1));
		Cube.NewLine();
		Cube.NewLine();
		for (size_t i = 0; i < SphereMD.Vertices.size(); i++) {
			Cube.WriteProperty("VX" + std::to_string(i), std::to_string((SphereMD.Vertices[i].X)));
			Cube.WriteProperty("VY" + std::to_string(i), std::to_string((SphereMD.Vertices[i].Y)));
			Cube.WriteProperty("VZ" + std::to_string(i), std::to_string((SphereMD.Vertices[i].Z)));

			Cube.NewLine();

			Cube.WriteProperty("NX" + std::to_string(i), std::to_string((SphereMD.Normals[i].X)));
			Cube.WriteProperty("NY" + std::to_string(i), std::to_string((SphereMD.Normals[i].Y)));
			Cube.WriteProperty("NZ" + std::to_string(i), std::to_string((SphereMD.Normals[i].Z)));

			Cube.NewLine();

			Cube.WriteProperty("TCX" + std::to_string(i), std::to_string((SphereMD.TextureCoords[i].X)));
			Cube.WriteProperty("TCY" + std::to_string(i), std::to_string((SphereMD.TextureCoords[i].Y)));

			Cube.NewLine();
		}
		Cube.NewLine();
		Cube.WriteProperty("Indices Count", std::to_string(SphereMD.Indices.size() - 1));
		Cube.NewLine();
		Cube.NewLine();
		for (size_t i = 0; i < SphereMD.Indices.size(); i++) {
			Cube.WriteProperty("I" + std::to_string(i), std::to_string(SphereMD.Indices[i]));
			if (i % 4 == 0) {
				Cube.NewLine();
			}
		}
		AE_LOG_SUCCESS("Cube.aesset written");
	});
	Input::Instance().RegisterKeyAction("WriteCube", Input::Instance().KeyFromAesset(Config, "InteractKey"), InputAction::Pressed);
	Input::Instance().RegisterCallback("WriteCube", &WriteCube);

	EventFunctionCallback RandomName([]() -> void {
		AE_LOG(("Random Name: " + Random::Name(3, 8)).c_str());
	});
	Input::Instance().RegisterKeyAction("RandomName", Input::Instance().KeyFromAesset(Config, "RandomNameKey"), InputAction::Pressed);
	Input::Instance().RegisterCallback("RandomName", &RandomName);

	Level Level;

	Level.Awake();

	while (Window->IsValid()) {
		T.Update();
		Level.Update(T.GetDelta());
		Window->Update();

		if (T.OnSecond()) {
			Window->SetTitle("FPS: " + std::to_string(T.GetAvgFPS()));
		}
	}

	Level.Destroy();

	return 0;

}