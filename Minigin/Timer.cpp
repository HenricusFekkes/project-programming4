#include "Timer.h"

using namespace dae;
using namespace std::chrono;

void Timer::Start()
{
	m_StartUpdate = clock::now();
}

void Timer::Update()
{
	m_DeltaTime = clock::now() - m_StartUpdate;
	m_StartUpdate += m_DeltaTime;
	m_Lag += m_DeltaTime;
}

bool Timer::FixedUpdate()
{
	if (m_Lag > m_FixedStep)
	{
		m_Lag -= m_FixedStep;
		return true;
	}
	return false;
}

void Timer::SetFixedStep(time_unit time)
{
	m_FixedStep = time;
}

void Timer::SetFixedStep(float seconds)
{
	m_FixedStep = duration_cast<time_unit>(duration<float>(seconds));
}

void Timer::SetDesiredDeltaTime(time_unit time)
{
	m_DesiredDeltaTime = time;
}

void Timer::SetDesiredDeltaTime(float seconds)
{
	m_DesiredDeltaTime = duration_cast<time_unit>(duration<float>(seconds));
}

void Timer::SetActiveWait(time_unit time)
{
	m_ActiveWait = time;
}

void Timer::SetActiveWait(float seconds)
{
	m_ActiveWait = duration_cast<time_unit>(duration<float>(seconds));
}

void Timer::PreciseSleep(time_point timePoint, time_unit activeWait) const
{
	std::this_thread::sleep_for((timePoint - clock::now()) - activeWait);
	SpinLock(timePoint);
}

void Timer::SpinLock(time_point timePoint) const
{
	while (clock::now() < timePoint);
}

float Timer::GetDeltaTime() const
{
	return duration<float>(m_DeltaTime).count();
}

float Timer::GetDesiredDeltaTime() const
{
	return duration<float>(m_DesiredDeltaTime).count();
}

float Timer::GetFixedStep() const
{
	return duration<float>(m_FixedStep).count();
}

void Timer::SleepForRemainder() const
{
	time_unit elapsed = clock::now() - m_StartUpdate;
	if (elapsed < m_DesiredDeltaTime)
	{
		PreciseSleep(m_StartUpdate + m_DesiredDeltaTime, m_ActiveWait);
	}
}
