
namespace Amalgamation {

	FORCEINLINE void Event::AddListener(std::shared_ptr<IEventCallback> Callback) {
		std::vector<std::shared_ptr<IEventCallback>>::iterator Index = std::find(m_Callbacks.begin(), m_Callbacks.end(), Callback);
		if (Index != m_Callbacks.end()) {
			return;
		}
		else {
			m_Callbacks.push_back(Callback);
		}
	}

	FORCEINLINE void Event::RemoveListener(std::shared_ptr<IEventCallback> Callback) {
		std::vector<std::shared_ptr<IEventCallback>>::iterator Index = std::find(m_Callbacks.begin(), m_Callbacks.end(), Callback);
		if (Index == m_Callbacks.end()) {
			return;
		}
		else {
			m_Callbacks.erase(Index);
		}
	}

	FORCEINLINE void Event::Trigger() {
		if (m_Callbacks.size() > 0) {
			for (auto Function : m_Callbacks) {
				(*Function)();
			}
		}
	}
}