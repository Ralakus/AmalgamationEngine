#pragma once

#include "../Platform/Platform.hpp"
#include "Event.hpp"
#include <string>
#include <unordered_map>

namespace Amalgamation{
    class EventHandler {

	protected:

        std::unordered_map<std::string, Event*> m_Events;

    public:

		EventHandler();
		virtual ~EventHandler();

		FORCEINLINE void RegisterCallback(const std::string& Name, IEventCallback* Callback);
		FORCEINLINE void RegisterEvent(const std::string& Name, Event* EventPtr);
		FORCEINLINE void TriggerEvent(const std::string& Name);
		FORCEINLINE void DeregisterCallback(IEventCallback* Callback);
    };
}

#if !defined(AE_NO_IMPL)
	#include "EventHandler.inl"
#endif