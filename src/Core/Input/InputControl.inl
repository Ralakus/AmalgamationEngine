
namespace Amalgamation {

	InputControl::InputControl() : m_InstanceStr(std::to_string(reinterpret_cast<size_t>(this)))
	{}

	InputControl::~InputControl()
	{
		for (auto* C : m_Callbacks) {
			SafeDelete(C);
		}
	}

	FORCEINLINE void InputControl::AddInput(Key KeyCode, float Value) {
		Input::Instance().RegisterKeyAction(m_InstanceStr + std::to_string(static_cast<unsigned short>(KeyCode)) + std::to_string(static_cast<unsigned char>(InputAction::Pressed)) + std::to_string(Value), KeyCode, InputAction::Pressed);
		m_Callbacks.emplace_back(new EventLambdaCallback(std::function<void()>(
			[this, Value]() -> void {
			m_Value += Value;
		})));
		Input::Instance().RegisterCallback(m_InstanceStr + std::to_string(static_cast<unsigned short>(KeyCode)) + std::to_string(static_cast<unsigned char>(InputAction::Pressed)) + std::to_string(Value), m_Callbacks.back());
		Input::Instance().RegisterKeyAction(m_InstanceStr + std::to_string(static_cast<unsigned short>(KeyCode)) + std::to_string(static_cast<unsigned char>(InputAction::Released)) + std::to_string(Value), KeyCode, InputAction::Released);
		m_Callbacks.emplace_back(new EventLambdaCallback(std::function<void()>(
			[this, Value]() -> void {
			m_Value -= Value;
		})));
		Input::Instance().RegisterCallback(m_InstanceStr + std::to_string(static_cast<unsigned short>(KeyCode)) + std::to_string(static_cast<unsigned char>(InputAction::Released)) + std::to_string(Value), m_Callbacks.back());
	}

	FORCEINLINE float InputControl::Value() const {
		return m_Value;
	}

}