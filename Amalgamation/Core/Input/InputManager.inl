#include "InputManager.hpp"

namespace Amalgamation {

	FORCEINLINE void Input::UpdateKeys(Key KeyCode, InputAction Action) {
		for (auto K : m_RKeys) {
			if (std::get<0>(K) != KeyCode || std::get<1>(K) != Action) {
				continue;
			}
			else {
				TriggerEvent(std::get<2>(K));
			}
		}
	}

	FORCEINLINE void Input::UpdateButtons(Button ButtonCode, InputAction Action) {
		for (auto K : m_RButtons) {
			if (std::get<0>(K) != ButtonCode || std::get<1>(K) != Action) {
				continue;
			}
			else {
				TriggerEvent(std::get<2>(K));
			}
		}
	}

	FORCEINLINE void Input::UpdateMousePos(float X, float Y) { 
		m_MousePos.x = X;
		m_MousePos.y = Y;
	}

	FORCEINLINE void Input::RegisterEvent(const std::string & Name, Event * EventPtr) {
		if (m_Events.count(Name) < 1) {
			m_Events[Name] = EventPtr;
		}
	}

	FORCEINLINE void Input::TriggerEvent(const std::string & Name) {
		if (m_Events.count(Name) > 0) {
			m_Events[Name]->Trigger();
		}
	}

	FORCEINLINE Input::Input() {}

	FORCEINLINE Input::~Input() {}

	FORCEINLINE void Input::RegisterKeyAction(const std::string & Name, Key KeyCode, InputAction Action) {
		RegisterEvent(Name, new Event);
		m_RKeys.emplace_back(KeyCode, Action, Name);
	}

	FORCEINLINE void Input::RegisterButtonAction(const std::string & Name, Button ButtonCode, InputAction Action) {
		RegisterEvent(Name, new Event);
		m_RButtons.emplace_back(ButtonCode, Action, Name);
	}

	FORCEINLINE const glm::vec2 & Input::GetMousePos() const {
		return m_MousePos;
	}

	FORCEINLINE Key Input::KeyFromAesset(const Aesset & File, const std::string & Name, Key Default = Key::Unknown) {
		std::string KeyStr = File.Get<std::string>(Name, "Key Null");
		if (KeyStr == "Key Null") {
			return Default;
		}
		std::transform(KeyStr.begin(), KeyStr.end(), KeyStr.begin(), ::tolower);
		if (KeyStr == "escape") {
			return Key::Escape;
		}
		else if (KeyStr == "space") {
			return Key::Space;
		}
		else if (KeyStr == "ctrl") {
			return Key::Ctrl;
		}
		else if (KeyStr == "alt") {
			return Key::Alt;
		}
		else if (KeyStr == "lshift") {
			return Key::LShift;
		}
		else if (KeyStr == "rshift") {
			return Key::RShift;
		}
		else if (KeyStr == "ralt") {
			return Key::RAlt;
		}
		else if (KeyStr == "rctrl") {
			return Key::RCtrl;
		}
		else if (KeyStr == "tab") {
			return Key::Tab;
		}
		else if (KeyStr == "enter") {
			return Key::RAlt;
		}
		else if (KeyStr == "backspace") {
			return Key::Backspace;
		}
		else {
			std::transform(KeyStr.begin(), KeyStr.end(), KeyStr.begin(), ::toupper);
			return static_cast<Key>(KeyStr.c_str()[0]);
		}
	}
}