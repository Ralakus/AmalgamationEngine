#pragma once

#include "Event.hpp"
#include "../Platform/Typedef.hpp"
#include <string>
#include <unordered_map>

namespace Amalgamation{
    class EventHandler {

	protected:

        std::unordered_map<std::string, Event*> m_Events;

    public:

        EventHandler() {}
        virtual ~EventHandler() {}

        void RegisterCallback(const std::string& Name, IEventCallback* Callback) {
            if(m_Events.count(Name) < 1){
                return;
            }
            else{
                m_Events[Name]->AddListener(Callback);
            }
        }
        void RegisterEvent(const std::string& Name, Event* EventPtr){
            if(m_Events.count(Name) < 1){
                m_Events[Name] = EventPtr;
            }
        }
        void TriggerEvent(const std::string& Name){
            if(m_Events.count(Name) > 0){
                m_Events[Name]->Trigger();
            }
        }
    };
}
