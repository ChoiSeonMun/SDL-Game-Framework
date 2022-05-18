#pragma once

#include "Type.h"

// ���� �ʱ�ȭ
void Random_Init(void);

/// <summary>
/// ������ ������ �����´�.
/// </summary>
/// <param name="minInclusive">�ּڰ�</param>
/// <param name="maxExclusive">�ִ�</param>
/// <returns>[minInclusive, maxExclusive) ������ ������ ����</returns>
int32 Random_GetNumberFromRange(int32 minInclusive, int32 maxExclusive);

/// <summary>
/// ������ �Ǽ��� �����´�.
/// </summary>
/// <param name="minInclusive">�ּڰ�</param>
/// <param name="maxInclusive">�ִ�</param>
/// <returns>[minInclusive, maxInclusive] ������ ������ �Ǽ�</returns>
float Random_GetFNumberFromRange(float minInclusive, float maxInclusive);
