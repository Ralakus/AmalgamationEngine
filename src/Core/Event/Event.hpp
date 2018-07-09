#pragma once

#include "EventCallback.hpp"
#include <vector>
#include <algorithm>

namespace Amalgamation{

    class Event {

        std::vector<std::shared_ptr<IEventCallback>> m_Callbacks;

    public:

        Event()  {}
        ~Event() {}

		FORCEINLINE void AddListener(const std::shared_ptr<IEventCallback>& Callback);
		FORCEINLINE void RemoveListener(const std::shared_ptr<IEventCallback>& Callback);
		FORCEINLINE void Trigger();
    };

}

#if !defined(AE_NO_IMPL)
    #include "Event.inl"
#endif
