#pragma once

#include "Timer.hpp"

namespace Amalgamation {

	class Time {
		Timer m_Timer;

		bool m_OnSecond = false;
		float m_Delta = 0.f;

		float m_AVGFPS = 0.f;
		uint32 m_FramesInSecond = 0;

		float m_OnSecondTimer = 0.f;

	public:

		FORCEINLINE  Time() { m_Timer.Start(); }
		FORCEINLINE ~Time() {}

		FORCEINLINE void Update() {
			m_Timer.Stop();
			m_Delta = m_Timer.GetTimeMilli();
			m_Timer.Start();

			m_OnSecond = false;

			m_OnSecondTimer += m_Delta;
			m_FramesInSecond++;

			if (m_OnSecondTimer > 1.f) {
				m_AVGFPS = (1.f / static_cast<float>(m_FramesInSecond)) / static_cast<float>(m_FramesInSecond);
				m_OnSecondTimer = 0.f;
				m_OnSecond = true;
			}
		}

		FORCEINLINE float GetDelta()   const { return m_Delta; }

		//FORCEINLINE float GetElapsed() const { return ((float)(m_TP1 - m_Start).count() / 10000000); } Depreciated code

		FORCEINLINE bool  OnSecond()   const { return m_OnSecond; }

		FORCEINLINE float GetAvgFPS()  const { return m_AVGFPS; }

		FORCEINLINE float GetFPS()     const { return 1.f / m_Delta; }

	};

}
