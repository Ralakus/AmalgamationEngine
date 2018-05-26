#include "../Platform/Platform.hpp"

#if defined(AE_WINDOWS) && !defined(AE_FORCE_TIMER_CHRONO)
    #define AE_TIMER_USE_WINDOWS
#endif // AE_Windows

#if defined(AE_TIMER_USE_WINDOWS)
    #include <windows.h>
#else
    #include <chrono>
#endif // AE_TIMER_USE_WINDOWS

namespace Amalgamation{

    class Timer{

        bool m_Running;

        #if defined(AE_TIMER_USE_WINDOWS)
            float m_InvFreqMilli;
            unsigned long long m_Now;
            unsigned long long m_Start;
            unsigned long long m_Frequency;
        #else
            std::chrono::high_resolution_clock::time_point m_Start = std::chrono::high_resolution_clock::now();
            mutable std::chrono::high_resolution_clock::time_point m_End   = std::chrono::high_resolution_clock::now();
        #endif

    public:

		FORCEINLINE  Timer();
		FORCEINLINE ~Timer();

		FORCEINLINE void Start();

		FORCEINLINE void Stop();

		FORCEINLINE float GetTimeNano() const;

		FORCEINLINE float GetTimeMirco() const;

		FORCEINLINE float GetTimeMilli() const;

		FORCEINLINE float GetTimeSec() const;

		FORCEINLINE bool IsRunning() const;

    };

}

#include "Timer.inl"