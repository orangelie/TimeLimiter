#pragma once

#include "TimeServerInvoker.h"

namespace orangelie
{

	class TimeLimiter
	{
	public:
		TimeLimiter();
		TimeLimiter& operator=(const TimeServerInvoker&) = delete;
		TimeLimiter(const TimeServerInvoker&) = delete;
		~TimeLimiter();

		void SetTimeMaxLimits(
			int limitYears,
			int limitMonths,
			int limitDays,
			int limitHours,
			int limitMinutes,
			int limitSeconds);
		bool Limit(TimeServerInvoker* _timeServerInvoker);

	private:
		std::tm m_LimitsTime;

	};
}