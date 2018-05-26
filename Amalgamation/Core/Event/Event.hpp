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

		FORCEINLINE void AddListener(IEventCallback* Callback);
		FORCEINLINE void RemoveListener(IEventCallback* Callback);
		FORCEINLINE void Trigger();
    };

}
#include "Event.inl"
