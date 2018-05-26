#include "EventHandler.hpp"

namespace Amalgamation {

	FORCEINLINE EventHandler::EventHandler()
	{}

	EventHandler::~EventHandler() {
		for (auto E : m_Events) {
			SafeDelete(E.second);
		}
	}

	FORCEINLINE void EventHandler::RegisterCallback(const std::string & Name, IEventCallback * Callback) {
		if (m_Events.count(Name) < 1) {
			return;
		}
		else {
			Callback->m_EventName = Name;
			m_Events[Name]->AddListener(Callback);
		}
	}

	FORCEINLINE void EventHandler::RegisterEvent(const std::string & Name, Event * EventPtr) {
		if (m_Events.count(Name) < 1) {
			m_Events[Name] = EventPtr;
		}
	}

	FORCEINLINE void EventHandler::TriggerEvent(const std::string & Name) {
		if (m_Events.count(Name) > 0) {
			m_Events[Name]->Trigger();
		}
	}

	FORCEINLINE void EventHandler::DeregisterCallback(IEventCallback * Callback) {
		if (m_Events.count(Callback->m_EventName) > 0) {
			m_Events[Callback->m_EventName]->RemoveListener(Callback);
		}
	}


}