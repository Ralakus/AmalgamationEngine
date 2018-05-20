#pragma once

#include <Core/Types/Singleton.hpp>
#include <memory>

namespace Amalgamation {

#define MAX_KEYS    1024
#define MAX_BUTTONS 8

	class Keyboard : public Singleton<Keyboard> {

		friend class Window;

		bool m_Keys[MAX_KEYS];

		inline void SetKeyState(unsigned int key, bool state) {
			if (key < MAX_KEYS) {
				m_Keys[key] = state;
			}
		}
	public:


		Keyboard() { memset(m_Keys, false, sizeof(m_Keys)); }
		~Keyboard() {}

		inline bool GetKeyState(unsigned int key) const {
			return key >= MAX_KEYS ? false : m_Keys[key];
		}

	};

	class Mouse : public Singleton<Mouse> {

		friend class Window;

		bool m_Buttons[MAX_BUTTONS];

		float X, Y;

		inline void SetPos(float X, float Y) { this->X = X; this->Y = Y; }
		inline void SetButtonState(unsigned int button, bool state) {
			if (button < MAX_BUTTONS) {
				m_Buttons[button] = state;
			}
		}

	public:


		Mouse() { memset(m_Buttons, false, sizeof(m_Buttons)); }
		~Mouse() {}

		inline float GetX() const { return X; }
		inline float GetY() const { return Y; }

		inline bool GetButtonState(unsigned int button) {
			return button >= MAX_BUTTONS ? false : m_Buttons[button];
		}

	};

}