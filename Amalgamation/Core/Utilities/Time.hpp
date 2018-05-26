#pragma once

#include "Timer.hpp"

namespace Amalgamation {

	class Time {
		Timer m_Timer;

		bool m_OnSecond = false;
		float m_Delta = 0.f;

		float m_AVGFPS = 0.f;
		uint32 m_FramesInSecond = 0;
		float m_FPSIS = 0.f;

		float m_OnSecondTimer = 0.f;

	public:

		FORCEINLINE  Time();
		FORCEINLINE ~Time();

		FORCEINLINE void Update();

		FORCEINLINE float GetDelta()   const;

		//FORCEINLINE float GetElapsed() const { return ((float)(m_TP1 - m_Start).count() / 10000000); } Depreciated code

		FORCEINLINE bool  OnSecond()   const;

		FORCEINLINE float GetAvgFPS()  const;

		FORCEINLINE float GetFPS()     const;

	};

}

#include "Time.inl"
