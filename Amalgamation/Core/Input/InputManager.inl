
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

	FORCEINLINE void Input::UpdateMousePos(MATH_TYPE X, MATH_TYPE Y) {
		m_MousePos.X = X;
		m_MousePos.Y = Y;
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

	FORCEINLINE const Math::Vec2 & Input::GetMousePos() const {
		return m_MousePos;
	}

	FORCEINLINE Key Input::KeyFromAesset(const Aesset & File, const std::string & Name) {
		std::string KeyStr = File.Get<std::string>(Name);
		if (KeyStr == "Escape") {
			return Key::Escape;
		}
		else if (KeyStr == "Ctrl") {
			return Key::Ctrl;
		}
		else if (KeyStr == "Alt") {
			return Key::Alt;
		}
		else if (KeyStr == "LShift") {
			return Key::LShift;
		}
		else if (KeyStr == "RShift") {
			return Key::RShift;
		}
		else if (KeyStr == "RAlt") {
			return Key::RAlt;
		}
		else if (KeyStr == "RCtrl") {
			return Key::RCtrl;
		}
		else if (KeyStr == "Tab") {
			return Key::Tab;
		}
		else if (KeyStr == "Enter") {
			return Key::RAlt;
		}
		else {
			return static_cast<Key>(KeyStr.c_str()[0]);
		}
	}
}