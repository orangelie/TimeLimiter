#include "TimeLimiter.h"

namespace orangelie
{

	TimeLimiter::TimeLimiter()
	{
		m_LimitsTime = {};
	}

	TimeLimiter::~TimeLimiter()
	{
	}

	void TimeLimiter::SetTimeMaxLimits(
		int limitYears,
		int limitMonths,
		int limitDays,
		int limitHours,
		int limitMinutes,
		int limitSeconds)
	{
		m_LimitsTime.tm_year = limitYears - 1900;
		m_LimitsTime.tm_mon = limitMonths - 1;
		m_LimitsTime.tm_mday = limitDays;
		m_LimitsTime.tm_hour = limitHours;
		m_LimitsTime.tm_min = limitMinutes;
		m_LimitsTime.tm_sec = limitSeconds;
	}

	bool TimeLimiter::Limit(TimeServerInvoker* _timeServerInvoker)
	{
		std::time_t TimeTicks = _timeServerInvoker->QueryTimeFromServer();
		if (TimeTicks == -1)
		{
			return false;
		}

		auto timeServerTime = localtime(&TimeTicks);

		if (m_LimitsTime.tm_year < timeServerTime->tm_year)
		{
			return false;
		}
		else
		{
			if (m_LimitsTime.tm_mon < timeServerTime->tm_mon)
			{
				return false;
			}
			else
			{
				if (m_LimitsTime.tm_mday < timeServerTime->tm_mday)
				{
					return false;
				}
				else
				{
					if (m_LimitsTime.tm_hour < timeServerTime->tm_hour)
					{
						return false;
					}
					else
					{
						if (m_LimitsTime.tm_min < timeServerTime->tm_min)
						{
							return false;
						}
						else
						{
							if (m_LimitsTime.tm_sec < timeServerTime->tm_sec)
							{
								return false;
							}
							else
							{
								return true;
							}
						}
					}
				}
			}
		}

		return false;
	}
}