#pragma once

#include "Type.h"

/// <summary>
/// Ÿ�̸Ӹ� �ʱ�ȭ�Ѵ�.
/// </summary>
/// <param name="fps">������ FPS</param>
void	Timer_Init(int32 fps);

/// <summary>
/// Ÿ�̸Ӹ� ������Ʈ�Ѵ�.
/// </summary>
/// <return>������Ʈ�� �����ߴٸ� true, �ƴ϶�� false</return>
bool	Timer_Update(void);

/// <summary>
/// ��ŸŸ���� ���Ѵ�.
/// </summary>
/// <return>������ ���� �ð�. ���� ���������κ��� ���� �������� ������ ������ �ɸ� �ð�</return>
float	Timer_GetDeltaTime(void);
