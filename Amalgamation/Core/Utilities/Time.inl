
namespace Amalgamation {

	FORCEINLINE Time::Time() { 
#if !defined(AE_USE_GLFW_TIME)
		m_Timer.Start(); m_ElapsedTimer.Start();
#endif
	}

	FORCEINLINE Time::~Time() {}

	FORCEINLINE void Time::Update() {
#if !defined(AE_USE_GLFW_TIME)
		m_Timer.Stop();
		m_Delta = m_Timer.GetTimeSec();
		m_Timer.Start();
#else
		m_Delta = glfwGetTime() - LastTime;
		LastTime += m_Delta;
#endif

		m_OnSecond = false;

		m_OnSecondTimer += m_Delta;
		m_FPSIS += 1.f / m_Delta;
		m_FramesInSecond++;

		if (m_OnSecondTimer > 1.f) {
			m_AVGFPS = m_FPSIS / static_cast<float>(m_FramesInSecond);
			m_OnSecondTimer = 0.f;
			m_OnSecond = true;
		}
	}

	FORCEINLINE float Time::GetDelta() const { return m_Delta; }

	FORCEINLINE float Time::GetElapsed() const {
#if !defined(AE_USE_GLFW_TIME)
		return m_ElapsedTimer.GetTimeSec();
#else
		return glfwGetTime();
#endif
	}

	FORCEINLINE bool Time::OnSecond() const { return m_OnSecond; }

	FORCEINLINE float Time::GetAvgFPS() const { return m_AVGFPS; }

	FORCEINLINE float Time::GetFPS() const { return 1.f / m_Delta; }

}