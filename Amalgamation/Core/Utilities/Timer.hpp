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

        FORCEINLINE  Timer()  {
            #if defined(AE_TIMER_USE_WINDOWS)
                QueryPerformanceFrequency(const_cast<LARGE_INTEGER*>(reinterpret_cast<const LARGE_INTEGER*>(&m_Frequency)));
                m_InvFreqMilli = 1.0f / static_cast<float>((static_cast<double>(m_Frequency) / 1000.0));
            #endif
        }
        FORCEINLINE ~Timer() {}

        FORCEINLINE void Start() {
            #if defined(AE_TIMER_USE_WINDOWS)
                QueryPerformanceCounter(const_cast<LARGE_INTEGER*>(reinterpret_cast<const LARGE_INTEGER*>(&m_Start)));
            #else
                m_Start = std::chrono::high_resolution_clock::now();
            #endif
            m_Running = true;
        }

        FORCEINLINE void Stop() {
            if(m_Running){
                #if defined(AE_TIMER_USE_WINDOWS)
                    QueryPerformanceCounter(const_cast<LARGE_INTEGER*>(reinterpret_cast<const LARGE_INTEGER*>(&m_Now)));
                #else
                    m_End = std::chrono::high_resolution_clock::now();
                #endif
                m_Running = false;
            }
        }

		FORCEINLINE float GetTimeNano() const {
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

        FORCEINLINE float GetTimeMirco() const{
            #if defined(AE_TIMER_USE_WINDOWS)
                if( m_Running )
                {
                    QueryPerformanceCounter(const_cast<LARGE_INTEGER*>(reinterpret_cast<const LARGE_INTEGER*>(&m_Now)) );
                }
                return static_cast<float>((m_Now - m_Start)) * m_InvFreqMilli * 1000.0f;
            #else
                if( m_Running )
                {
                    m_End = std::chrono::high_resolution_clock::now();
                }
                return std::chrono::duration_cast<std::chrono::nanoseconds>(m_End - m_Start).count() / 1000.f;
            #endif
        }

        FORCEINLINE float GetTimeMilli() const {
            #if defined(AE_TIMER_USE_WINDOWS)
                if( m_Running )
                {
                    QueryPerformanceCounter( const_cast<LARGE_INTEGER*>(reinterpret_cast<const LARGE_INTEGER*>(&m_Now)) );
                }
                return static_cast<float>((m_Now - m_Start)) * m_InvFreqMilli;
            #else
                if( m_Running )
                {
                    m_End = std::chrono::high_resolution_clock::now();
                }
                return std::chrono::duration_cast<std::chrono::microseconds>(m_End - m_Start).count() / 1000.f;
            #endif
        }

        FORCEINLINE float GetTimeSec() const {
            return GetTimeMilli() / 1000.0f;
        }

        FORCEINLINE bool IsRunning() const { return m_Running; }

    };

}
