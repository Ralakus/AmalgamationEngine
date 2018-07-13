
namespace Amalgamation {

	InputControl::InputControl() : m_InstanceStr(std::to_string(reinterpret_cast<size_t>(this)))
	{}

	InputControl::~InputControl(){}

	FORCEINLINE void InputControl::AddInput(Key KeyCode, float Value) {
		if (InputManager) {
			InputManager->RegisterKeyAction(m_InstanceStr + std::to_string(static_cast<unsigned short>(KeyCode)) + std::to_string(static_cast<unsigned char>(InputAction::Pressed)) + std::to_string(Value), KeyCode, InputAction::Pressed);
			m_Callbacks.emplace_back(std::make_shared<EventLambdaCallback>(std::function<void()>(
				[this, Value]() -> void {
				m_Value += Value;
			})));
			InputManager->RegisterCallback(m_InstanceStr + std::to_string(static_cast<unsigned short>(KeyCode)) + std::to_string(static_cast<unsigned char>(InputAction::Pressed)) + std::to_string(Value), m_Callbacks.back());
			InputManager->RegisterKeyAction(m_InstanceStr + std::to_string(static_cast<unsigned short>(KeyCode)) + std::to_string(static_cast<unsigned char>(InputAction::Released)) + std::to_string(Value), KeyCode, InputAction::Released);
			m_Callbacks.emplace_back(std::make_shared<EventLambdaCallback>(std::function<void()>(
				[this, Value]() -> void {
				m_Value -= Value;
			})));
			InputManager->RegisterCallback(m_InstanceStr + std::to_string(static_cast<unsigned short>(KeyCode)) + std::to_string(static_cast<unsigned char>(InputAction::Released)) + std::to_string(Value), m_Callbacks.back());
		}
	}

	FORCEINLINE float InputControl::Value() const {
		return m_Value;
	}

}