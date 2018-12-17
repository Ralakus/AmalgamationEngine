
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

	FORCEINLINE void Input::RegisterEvent(const std::string & Name, const std::shared_ptr<Event>& EventPtr) {
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
		RegisterEvent(Name, std::make_shared<Event>());
		m_RKeys.emplace_back(KeyCode, Action, Name);
	}

	FORCEINLINE void Input::RegisterButtonAction(const std::string & Name, Button ButtonCode, InputAction Action) {
		RegisterEvent(Name, std::make_shared<Event>());
		m_RButtons.emplace_back(ButtonCode, Action, Name);
	}

	FORCEINLINE const glm::vec2 & Input::GetMousePos() const {
		return m_MousePos;
	}
}