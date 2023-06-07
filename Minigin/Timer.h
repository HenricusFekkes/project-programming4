#pragma once

#include <chrono>
#include "Singleton.h"

namespace dae
{
	class Timer final : public Singleton<Timer>
	{
	public:
		using clock = std::chrono::high_resolution_clock;
		using time_unit = std::chrono::nanoseconds;
		using time_point = std::chrono::time_point<clock, time_unit>;

		void Start();
		void Update();
		bool FixedUpdate();
		void SetFixedStep(time_unit time);
		void SetFixedStep(float seconds);
		void SetDesiredDeltaTime(time_unit time);
		void SetDesiredDeltaTime(float seconds);
		void SetActiveWait(time_unit time);
		void SetActiveWait(float seconds);

		float GetDeltaTime() const;
		float GetDesiredDeltaTime() const;
		float GetFixedStep() const;
		void SleepForRemainder() const;

	private:
		void PreciseSleep(time_point timePoint, time_unit activeWait) const;
		void SpinLock(time_point timePoint) const;

		time_unit m_DeltaTime{};
		time_unit m_DesiredDeltaTime{};
		time_unit m_FixedStep{};
		time_unit m_Lag{};
		time_unit m_ActiveWait{};
		time_point m_StartUpdate{};
	};
}


