#pragma once

namespace Amalgamation {

	FORCEINLINE Timer::Timer() {
#if defined(AE_TIMER_USE_WINDOWS)
		QueryPerformanceFrequency(const_cast<LARGE_INTEGER*>(reinterpret_cast<const LARGE_INTEGER*>(&m_Frequency)));
		m_InvFreqMilli = 1.0f / static_cast<float>((static_cast<double>(m_Frequency) / 1000.0));
#endif
	}

	FORCEINLINE Timer::~Timer() {}

	FORCEINLINE void Timer::Start() {
#if defined(AE_TIMER_USE_WINDOWS)
		QueryPerformanceCounter(const_cast<LARGE_INTEGER*>(reinterpret_cast<const LARGE_INTEGER*>(&m_Start)));
#else
		m_Start = std::chrono::high_resolution_clock::now();
#endif
		m_Running = true;
	}

	FORCEINLINE void Timer::Stop() {
		if (m_Running) {
#if defined(AE_TIMER_USE_WINDOWS)
			QueryPerformanceCounter(const_cast<LARGE_INTEGER*>(reinterpret_cast<const LARGE_INTEGER*>(&m_Now)));
#else
			m_End = std::chrono::high_resolution_clock::now();
#endif
			m_Running = false;
		}
	}

	FORCEINLINE float Timer::GetTimeNano() const {
#if defined(AE_TIMER_USE_WINDOWS)
		if (m_Running)
		{
			QueryPerformanceCounter(const_cast<LARGE_INTEGER*>(reinterpret_cast<const LARGE_INTEGER*>(&m_Now)));
		}
		return static_cast<float>((m_Now - m_Start)) * m_InvFreqMilli * 1000000.0f;
#else
		if (m_Running)
		{
			m_End = std::chrono::high_resolution_clock::now();
		}
		return std::chrono::duration_cast<std::chrono::nanoseconds>(m_End - m_Start).count();
#endif
	}

	FORCEINLINE float Timer::GetTimeMirco() const {
#if defined(AE_TIMER_USE_WINDOWS)
		if (m_Running)
		{
			QueryPerformanceCounter(const_cast<LARGE_INTEGER*>(reinterpret_cast<const LARGE_INTEGER*>(&m_Now)));
		}
		return static_cast<float>((m_Now - m_Start)) * m_InvFreqMilli * 1000.0f;
#else
		if (m_Running)
		{
			m_End = std::chrono::high_resolution_clock::now();
		}
		return std::chrono::duration_cast<std::chrono::nanoseconds>(m_End - m_Start).count() / 1000.f;
#endif
	}

	FORCEINLINE float Timer::GetTimeMilli() const {
#if defined(AE_TIMER_USE_WINDOWS)
		if (m_Running)
		{
			QueryPerformanceCounter(const_cast<LARGE_INTEGER*>(reinterpret_cast<const LARGE_INTEGER*>(&m_Now)));
		}
		return static_cast<float>((m_Now - m_Start)) * m_InvFreqMilli;
#else
		if (m_Running)
		{
			m_End = std::chrono::high_resolution_clock::now();
		}
		return std::chrono::duration_cast<std::chrono::microseconds>(m_End - m_Start).count() / 1000.f;
#endif
	}

	FORCEINLINE float Timer::GetTimeSec() const {
		return GetTimeMilli() / 1000.0f;
	}

	FORCEINLINE bool Timer::IsRunning() const { return m_Running; }


}