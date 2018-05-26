#pragma once

#include "../Types/Noncopyable.hpp"
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

		IEventCallback()          {};
		virtual ~IEventCallback() {};

        virtual void operator()() = 0;
        virtual bool operator == (IEventCallback* Other) = 0;
		virtual bool IsValid() = 0;

		FORCEINLINE const std::string& GetRegisteredEvent() const { return m_EventName; }
    };

    template<class T>
    class EventCallback : public IEventCallback {

        T* m_Instance;
        void (T::*m_Function)();

    public:

		EventCallback(T* Instance, void (T::*Function)()) : IEventCallback(), m_Instance(Instance), m_Function(Function) {}
		~EventCallback (){ m_Function = nullptr; }

		virtual void operator()() override { if (m_Function) { (m_Instance->*m_Function)(); } };

		virtual bool IsValid() { return (m_Function != nullptr); }

		virtual bool operator == (IEventCallback* Other) override {
            EventCallback<T>* OtherEC = dynamic_cast<EventCallback<T>*>(Other);
            if(OtherEC == nullptr){
                return false;
            }
            return  (this->m_Function == OtherEC->m_Function) &&
                    (this->m_Instance == OtherEC->m_Instance);
        }

    };


    class EventFunctionCallback : public IEventCallback {

        void (*m_Function)();

    public:

		EventFunctionCallback(void (*Function)()) : IEventCallback(), m_Function(Function) {}
		~EventFunctionCallback (){ m_Function = nullptr; }

		virtual void operator()() override { if (m_Function) { (*m_Function)(); } };

		virtual bool IsValid() { return (m_Function != nullptr); }

		virtual bool operator == (IEventCallback* Other) override {
            EventFunctionCallback* OtherEC = dynamic_cast<EventFunctionCallback*>(Other);
            if(OtherEC == nullptr){
                return false;
            }
            return  (this->m_Function == OtherEC->m_Function);
        }

	};



	class EventLambdaCallback : public IEventCallback {

		std::function<void()> m_Function;

	public:
		
		template<class T>
		EventLambdaCallback(const T& Function) : IEventCallback(), m_Function(Function) {}
		EventLambdaCallback(const std::function<void()>& Function) : IEventCallback(), m_Function(Function) {}
		~EventLambdaCallback() {}

		virtual void operator()() override { m_Function(); };

		virtual bool IsValid() { return (m_Function != nullptr); }

		virtual bool operator == (IEventCallback* Other) override {
			return  false;
		}

	};

}
