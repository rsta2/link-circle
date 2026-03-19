#pragma once

#include <chrono>
#include <circle/sched/scheduler.h>

namespace std
{

namespace this_thread
{

template<typename Rep, typename Period>
void sleep_for (const chrono::duration<Rep, Period> &rDuration)
{
	if (rDuration > rDuration.zero ())
	{
		unsigned us = chrono::duration_cast<chrono::microseconds>(rDuration).count ();

		CScheduler::Get ()->usSleep (us);
	}
}

}

}
