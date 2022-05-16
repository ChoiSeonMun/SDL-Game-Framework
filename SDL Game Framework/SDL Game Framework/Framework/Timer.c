#include "stdafx.h"
#include "Common.h"
#include "Timer.h"

static clock_t s_prevTick;
static float s_deltaTime;
static float s_fixedTime;

void Timer_Init(int32 fps)
{
	// 고정 시간을 계산한다.
	s_fixedTime = 1.0 / fps;

	// 시점을 하나 찍어준다.
	s_prevTick = clock();
}

bool Timer_Update(void)
{
	// 1. 현재 시점을 구한다.
	clock_t currentTick = clock();

	// 2. 현재 시점과 이전 시점의 차이를 통해 흐른 시간을 구한다.
	float deltaTime = (float)(currentTick - s_prevTick) / CLOCKS_PER_SEC;

	// 3. 이전 프레임으로부터 시간이 얼마 지나지 않았다면
	if (deltaTime < s_fixedTime)
	{
		return false;
	}

	// 4. 변수를 업데이트한다.
	s_deltaTime = deltaTime;
	s_prevTick = currentTick;

	return true;
}

float Timer_GetDeltaTime(void)
{
	return s_deltaTime;
}
