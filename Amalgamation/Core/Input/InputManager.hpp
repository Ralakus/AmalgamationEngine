#pragma once

#include "../Event/EventHandler.hpp"
#include "../Types/Singleton.hpp"
#include "../Math/Vector/Vector2.hpp"
#include "../Utilities/Aesset.hpp"

#include <tuple>

namespace Amalgamation {

	enum class Key : unsigned short {
		Unknown = 0,

		Q = 'Q', W = 'W', E = 'E', R = 'R', T = 'T', Y = 'Y', U = 'U', I = 'I', O = 'O', P = 'P', A = 'A', S = 'S',
		D = 'D', F = 'F', G = 'G', H = 'H', J = 'J', K = 'K', L = 'L', Z = 'Z', X = 'X', C = 'C', V = 'V', B = 'B', N = 'N', M = 'M',

		LeftBracket = '[', RightBracket = ']', BackSlash = '\\', SemiColon = ';', Apostrophe = '\'', Comma = ',', Period = '.', Slash = '/', Grave = '`',
		Minus = '-', Equals = '=',

		Space = ' ', Ctrl = 341, Alt = 342, LShift = 340, RShift = 344, RAlt = 346, RCtrl = 345, Tab = 258, Enter = 257, Escape = 256,

		One = '1', Two = '2', Three = '3', Four = '4', Five = '5', Six = '6', Seven = '7', Eight = '8', Nine = '9', Zero = '0',
	};

	enum class Button : unsigned short {
		Left = 0, Middle = 2, Right = 1, WheelUp = 3, WheelDown = 4
	};

	enum class InputAction : unsigned char {
		Pressed = 1, Released = 0, Held = 2
	};

	class Input : public EventHandler {

		friend class Window;

		std::vector<std::tuple<Key,    InputAction, std::string>> m_RKeys;
		std::vector<std::tuple<Button, InputAction, std::string>> m_RButtons;

		FORCEINLINE void UpdateKeys(Key KeyCode, InputAction Action);

		FORCEINLINE void UpdateButtons(Button ButtonCode, InputAction Action);

		FORCEINLINE void UpdateMousePos(MATH_TYPE X, MATH_TYPE Y);

		FORCEINLINE void RegisterEvent(const std::string& Name, Event* EventPtr);

		FORCEINLINE void TriggerEvent(const std::string& Name);

		Math::Vec2 m_MousePos;

	public:

		Input();
		~Input();

		SINGLETON_INSTANCE(Input)

			FORCEINLINE void RegisterKeyAction(const std::string& Name, Key KeyCode, InputAction Action);
		FORCEINLINE void RegisterButtonAction(const std::string& Name, Button ButtonCode, InputAction Action);

		FORCEINLINE const Math::Vec2& GetMousePos() const;

		Key KeyFromAesset(const Aesset& File, const std::string& Name);

	};

}

#include "InputManager.inl"