#include "InputManager.hpp"

namespace Amalgamation {

	class InputControl {

		mutable float m_Value = 0.f;
		std::string m_InstanceStr;
		std::vector<EventLambdaCallback*> m_Callbacks;

	public:

		InputControl();
		~InputControl();

		void AddInput(Key KeyCode, InputAction KeyAction, float Value);

		float Value() const;

	};

}

#include "InputControl.inl"