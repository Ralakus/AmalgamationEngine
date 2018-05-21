#pragma once

#include "../Event/EventHandler.hpp"
#include "../Types/Singleton.hpp"
#include "../Math/Vector/Vector2.hpp"

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

	enum class InputAction {
		Pressed = 1, Released = 0, Held = 2
	};

	class Input : public EventHandler {

		friend class Window;

		std::vector<std::tuple<Key,    InputAction, std::string>> m_RKeys;
		std::vector<std::tuple<Button, InputAction, std::string>> m_RButtons;

		void UpdateKeys(Key KeyCode, InputAction Action) {
			for (auto K : m_RKeys) {
				if (std::get<0>(K) != KeyCode || std::get<1>(K) != Action) {
					continue;
				}
				else {
					TriggerEvent(std::get<2>(K));
				}
			}
		}

		void UpdateButtons(Button ButtonCode, InputAction Action) {
			for (auto K : m_RButtons) {
				if (std::get<0>(K) != ButtonCode || std::get<1>(K) != Action) {
					continue;
				}
				else {
					TriggerEvent(std::get<2>(K));
				}
			}
		}

		void UpdateMousePos(MATH_TYPE X, MATH_TYPE Y) {
			m_MousePos.X = X;
			m_MousePos.Y = Y;
		}

		void RegisterEvent(const std::string& Name, Event* EventPtr) {
			if (m_Events.count(Name) < 1) {
				m_Events[Name] = EventPtr;
			}
		}

		void TriggerEvent(const std::string& Name) {
			if (m_Events.count(Name) > 0) {
				m_Events[Name]->Trigger();
			}
		}

		Math::Vec2 m_MousePos;

	public:

		 Input() {}
		~Input() {
			for (auto E : m_Events) {
				SafeDelete(E.second);
			}
		}

		SINGLETON_INSTANCE(Input)

		void RegisterKeyAction(const std::string& Name, Key KeyCode, InputAction Action) {
			RegisterEvent(Name, new Event);
			m_RKeys.emplace_back(KeyCode, Action, Name);
		}
		void RegisterButtonAction(const std::string& Name, Button ButtonCode, InputAction Action) {
			RegisterEvent(Name, new Event);
			m_RButtons.emplace_back(ButtonCode, Action, Name);
		}

		const Math::Vec2& GetMousePos() const {
			return m_MousePos;
		}

	};



}