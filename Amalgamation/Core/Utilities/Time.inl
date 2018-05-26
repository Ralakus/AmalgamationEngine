
namespace Amalgamation {

	FORCEINLINE Time::Time() { m_Timer.Start(); }

	FORCEINLINE Time::~Time() {}

	FORCEINLINE void Time::Update() {
		m_Timer.Stop();
		m_Delta = m_Timer.GetTimeSec();
		m_Timer.Start();

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

	FORCEINLINE bool Time::OnSecond() const { return m_OnSecond; }

	FORCEINLINE float Time::GetAvgFPS() const { return m_AVGFPS; }

	FORCEINLINE float Time::GetFPS() const { return 1.f / m_Delta; }

}