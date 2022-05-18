#include "stdafx.h"
#include "Timer.h"

static clock_t s_prevTick;
static float s_deltaTime;
static float s_fixedTime;

void Timer_Init(int32 fps)
{
	s_fixedTime = 1.0 / fps;
	s_prevTick = clock();
}

bool Timer_Update(void)
{
	clock_t currentTick = clock();

	float deltaTime = (float)(currentTick - s_prevTick) / CLOCKS_PER_SEC;

	if (deltaTime < s_fixedTime)
	{
		return false;
	}

	s_deltaTime = deltaTime;
	s_prevTick = currentTick;

	return true;
}

float Timer_GetDeltaTime(void)
{
	return s_deltaTime;
}
