#include "stdafx.h"
#include "Common.h"
#include "Timer.h"

static clock_t s_prevTick;
static float s_deltaTime;
static float s_fixedTime;

void Timer_Init(int32 fps)
{
	// ���� �ð��� ����Ѵ�.
	s_fixedTime = 1.0 / fps;

	// ������ �ϳ� ����ش�.
	s_prevTick = clock();
}

bool Timer_Update(void)
{
	// 1. ���� ������ ���Ѵ�.
	clock_t currentTick = clock();

	// 2. ���� ������ ���� ������ ���̸� ���� �帥 �ð��� ���Ѵ�.
	float deltaTime = (float)(currentTick - s_prevTick) / CLOCKS_PER_SEC;

	// 3. ���� ���������κ��� �ð��� �� ������ �ʾҴٸ�
	if (deltaTime < s_fixedTime)
	{
		return false;
	}

	// 4. ������ ������Ʈ�Ѵ�.
	s_deltaTime = deltaTime;
	s_prevTick = currentTick;

	return true;
}

float Timer_GetDeltaTime(void)
{
	return s_deltaTime;
}
