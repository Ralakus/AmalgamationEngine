#pragma once

#include "../Platform/Platform.hpp"

#include <memory>
#include <functional>

namespace Amalgamation{

    class IEventCallback {
		friend class EventHandler;
	protected:
		std::string m_EventName;
    public:

		NON_COPYABLE(IEventCallback)

		IEventCallback();
		virtual ~IEventCallback();

        virtual void operator()() = 0;
        virtual bool operator == (IEventCallback* Other) = 0;
		virtual bool IsValid() = 0;

		FORCEINLINE const std::string& GetRegisteredEvent() const;
    };

    template<class T>
    class EventCallback : public IEventCallback {

        T* m_Instance;
        void (T::*m_Function)();

    public:

		EventCallback(T* Instance, void (T::*Function)());
		~EventCallback();

		virtual void operator()() override;

		virtual bool IsValid() override;

		virtual bool operator == (IEventCallback* Other) override;

    };


    class EventFunctionCallback : public IEventCallback {

        void (*m_Function)();

    public:

		EventFunctionCallback(void(*Function)());
		~EventFunctionCallback();

		virtual void operator()() override;

		virtual bool IsValid() override;

		virtual bool operator == (IEventCallback* Other) override;

	};



	class EventLambdaCallback : public IEventCallback {

		std::function<void()> m_Function;

	public:
		
		template<class T>
		EventLambdaCallback(const T& Function);
		EventLambdaCallback(const std::function<void()>& Function);
		~EventLambdaCallback();

		virtual void operator()() override;

		virtual bool IsValid() override;

		virtual bool operator == (IEventCallback* Other) override;

	};

}
#include "EventCallback.inl"