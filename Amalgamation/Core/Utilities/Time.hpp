#pragma once

#include "Timer.hpp"

#if defined(AE_USE_GLFW_TIME) && !defined(_glfw3_h_)
#include <GLFW/glfw3.h>
#endif

namespace Amalgamation {

	class Time {
#if !defined(AE_USE_GLFW_TIME)
		Timer m_ElapsedTimer;
		Timer m_Timer;
#else
		float LastTime = 0.f;
#endif

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

		FORCEINLINE float GetElapsed() const;

		FORCEINLINE bool  OnSecond()   const;

		FORCEINLINE float GetAvgFPS()  const;

		FORCEINLINE float GetFPS()     const;

	};

}

#include "Time.inl"
