#pragma once

#include "Event.hpp"
#include "../Platform/Platform.hpp"
#include <string>
#include <unordered_map>

namespace Amalgamation{
    class EventHandler {

	protected:

        std::unordered_map<std::string, Event*> m_Events;

    public:

        EventHandler() {}
        virtual ~EventHandler() {
			for (auto E : m_Events) {
				SafeDelete(E.second);
			}
		}

		FORCEINLINE void RegisterCallback(const std::string& Name, IEventCallback* Callback) {
            if(m_Events.count(Name) < 1){
                return;
            }
            else{
				Callback->m_EventName = Name;
                m_Events[Name]->AddListener(Callback);
            }
        }
		FORCEINLINE void RegisterEvent(const std::string& Name, Event* EventPtr){
            if(m_Events.count(Name) < 1){
                m_Events[Name] = EventPtr;
            }
        }
        FORCEINLINE void TriggerEvent(const std::string& Name){
            if(m_Events.count(Name) > 0){
                m_Events[Name]->Trigger();
            }
        }
		FORCEINLINE void DeregisterCallback(IEventCallback* Callback) {
			if (m_Events.count(Callback->m_EventName) > 0) {
				m_Events[Callback->m_EventName]->RemoveListener(Callback);
			}
		}
    };
}
