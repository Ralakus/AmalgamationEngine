#pragma once

#include "EventCallback.hpp"
#include <vector>
#include <algorithm>

namespace Amalgamation{

    class Event {

        std::vector<IEventCallback*> m_Callbacks;

    public:

        Event()  {}
        ~Event() {}

        void AddListener(IEventCallback* Callback){
            std::vector<IEventCallback*>::iterator Index = std::find(m_Callbacks.begin(), m_Callbacks.end(), Callback);
            if(Index != m_Callbacks.end()){
                return;
            }
            else{
                m_Callbacks.push_back(Callback);
            }
        }
        void RemoveListener(IEventCallback* Callback) {
			std::vector<IEventCallback*>::iterator Index = std::find(m_Callbacks.begin(), m_Callbacks.end(), Callback);
            if(Index == m_Callbacks.end()){
                return;
            }
            else{
                m_Callbacks.erase(Index);
            }
        }
        void Trigger() {
            for(auto& Function : m_Callbacks){
                (*Function)();
            }
        }
    };

}
