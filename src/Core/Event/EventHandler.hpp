#pragma once

#include "../Platform/Platform.hpp"
#include "Event.hpp"
#include <string>
#include <unordered_map>

namespace Amalgamation{
    class EventHandler {

	protected:

        std::unordered_map<std::string, std::shared_ptr<Event>> m_Events;

    public:

		EventHandler();
		virtual ~EventHandler();

		FORCEINLINE void RegisterCallback(const std::string& Name, std::shared_ptr<IEventCallback> Callback);
		FORCEINLINE void RegisterEvent(const std::string& Name, std::shared_ptr<Event> EventPtr);
		FORCEINLINE void TriggerEvent(const std::string& Name);
		FORCEINLINE void DeregisterCallback(std::shared_ptr<IEventCallback> Callback);
    };
}

#if !defined(AE_NO_IMPL)
	#include "EventHandler.inl"
#endif