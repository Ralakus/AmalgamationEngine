
namespace Amalgamation {

	//============================================
	//Event Callback Interface
	//============================================

	FORCEINLINE IEventCallback::IEventCallback()
	{}

	FORCEINLINE IEventCallback::~IEventCallback()
	{}

	FORCEINLINE const std::string& IEventCallback::GetRegisteredEvent() const
	{ return m_EventName; }

	//============================================
	//Event Callback
	//============================================

	template<class T>
	EventCallback<T>::EventCallback(T * Instance, void(T::* Function)())
		: IEventCallback(), m_Instance(Instance), m_Function(Function) {}

	template<class T>
	FORCEINLINE EventCallback<T>::~EventCallback()
	{ m_Function = nullptr; }

	template<class T>
	FORCEINLINE void EventCallback<T>::operator()()
	{ if (m_Function) { (m_Instance->*m_Function)(); } }

	template<class T>
	FORCEINLINE bool EventCallback<T>::IsValid()
	{ return (m_Function != nullptr); }

	template<class T>
	FORCEINLINE bool EventCallback<T>::operator==(IEventCallback * Other)
	{
		EventCallback<T>* OtherEC = dynamic_cast<EventCallback<T>*>(Other);
		if (OtherEC == nullptr) {
			return false;
		}
		return  (this->m_Function == OtherEC->m_Function) &&
				(this->m_Instance == OtherEC->m_Instance);
	}

	//============================================
	//Event Function Callback
	//============================================

	EventFunctionCallback::EventFunctionCallback(void(*Function)())
		: IEventCallback(), m_Function(Function)
	{}

	FORCEINLINE EventFunctionCallback::~EventFunctionCallback()
	{ m_Function = nullptr; }

	FORCEINLINE void EventFunctionCallback::operator()()
	{ if (m_Function) { (*m_Function)(); } }

	FORCEINLINE bool EventFunctionCallback::IsValid()
	{ return (m_Function != nullptr); }

	FORCEINLINE bool EventFunctionCallback::operator==(IEventCallback * Other) {
		EventFunctionCallback* OtherEC = dynamic_cast<EventFunctionCallback*>(Other);
		if (OtherEC == nullptr) {
			return false;
		}
		return  (this->m_Function == OtherEC->m_Function);
	}

	//============================================
	//Event Lambda Callback
	//============================================

	template<class T>
	EventLambdaCallback::EventLambdaCallback(const T & Function)
		: IEventCallback(), m_Function(Function) {}

	EventLambdaCallback::EventLambdaCallback(const std::function<void()>& Function)
		: IEventCallback(), m_Function(Function) {}

	FORCEINLINE EventLambdaCallback::~EventLambdaCallback()
	{}

	FORCEINLINE void EventLambdaCallback::operator()()
	{ m_Function(); }

	FORCEINLINE bool EventLambdaCallback::IsValid()
	{ return (m_Function != nullptr); }

	FORCEINLINE bool EventLambdaCallback::operator==(IEventCallback * Other)
	{ return  false; }
}