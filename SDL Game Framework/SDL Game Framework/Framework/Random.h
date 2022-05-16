#pragma once

#include "Type.h"

// 랜덤 초기화
void Random_Init(void);

/// <summary>
/// 무작위 정수를 가져온다.
/// </summary>
/// <param name="minInclusive">최솟값</param>
/// <param name="maxExclusive">최댓값</param>
/// <returns>[minInclusive, maxExclusive) 범위의 무작위 정수</returns>
int32 Random_GetNumberFromRange(int32 minInclusive, int32 maxExclusive);

/// <summary>
/// 무작위 실수를 가져온다.
/// </summary>
/// <param name="minInclusive">최솟값</param>
/// <param name="maxInclusive">최댓값</param>
/// <returns>[minInclusive, maxInclusive] 범위의 무작위 실수</returns>
float Random_GetFNumberFromRange(float minInclusive, float maxInclusive);
