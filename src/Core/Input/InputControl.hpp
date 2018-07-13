#include "InputManager.hpp"

namespace Amalgamation {

	class InputControl {

		mutable float m_Value = 0.f;
		std::string m_InstanceStr;
		std::vector<std::shared_ptr<EventLambdaCallback>> m_Callbacks;

	public:

		Input* InputManager;

		 InputControl();
		~InputControl();

		void AddInput(Key KeyCode, float Value);

		float Value() const;

	};

}

#include "InputControl.inl"