#pragma once

#include "../Event/EventHandler.hpp"
#include "../Types/Singleton.hpp"

namespace Amalgamation {

	enum class Key : unsigned short {
		Unknown = 0,

		Q = 'Q', W = 'W', E = 'E', R = 'R', T = 'T', Y = 'Y', U = 'U', I = 'I', O = 'O', P = 'P', A = 'A', S = 'S',
		D = 'D', F = 'F', G = 'G', H = 'H', J = 'J', K = 'K', L = 'L', Z = 'Z', X = 'X', C = 'C', V = 'V', B = 'B', N = 'N', M = 'M',

		LeftBracket = '[', RightBracket = ']', BackSlash = '\\', SemiColon = ';', Apostrophe = '\'', Comma = ',', Period = '.', Slash = '/', Grave = '`',
		Minus = '-', Equals = '=',

		Space = ' ', Ctrl, Alt, LShift, RShift, RAlt, RCtrl, Tab, Enter,

		One = '1', Two = '2', Three = '3', Four = '4', Five = '5', Six = '6', Seven = '7', Eight = '8', Nine = '9', Zero = '0',
	};

	enum class Button : unsigned short {
		Left = 1, Middle = 2, Right = 3, WheelUp = 4, WheelDown = 5
	};

	class InputManager : public EventHandler {

		void RegisterEvent(const std::string& Name, Event* EventPtr) {
			if (m_Events.count(Name) < 1) {
				m_Events[Name] = std::make_unique<Event>(EventPtr);
			}
		}

	public:

		 InputManager() {}
		~InputManager() {}

		SINGLETON_INSTANCE(InputManager)

		void RegisterKeyAction(const std::string& Name, Key Key) {

		}
		void RegisterButtonAction(const std::string& Name, Button Button) {

		}

	};

}