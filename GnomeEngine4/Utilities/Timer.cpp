#include "..\Misc\stdafx.h"

// To start the timer
void Timer::Start(void)
{
	memset(this, 0, sizeof(Timer));

	if (!QueryPerformanceFrequency((LARGE_INTEGER*)&this->frequency))
	{
		this->performance_timer = FALSE;
		this->mm_timer_start = timeGetTime();
		this->resolution = 1.0f / 1000.0f;
		this->frequency = 1000;
	}
	else
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&this->performance_timer_start);
		this->performance_timer = TRUE;
		this->resolution = (float)(((double)1.0f) / ((double)this->frequency));
	}
}

// To get the elapsed time since last request or start
// NOTE: this method call resets the start to current time
float Timer::getElapsedTime(void)
{
	__int64 time;
	float elapsed;

	if (this->performance_timer)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&time);
		elapsed =
		  ((float)(time - this->performance_timer_start) * this->resolution);
		this->performance_timer_start = time;
	}
	else
	{
		unsigned long temp = timeGetTime();
		elapsed = ((float)(temp - this->mm_timer_start) * this->resolution);
		this->mm_timer_start = temp;
	}
	return elapsed;
}
