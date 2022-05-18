#pragma once

#include "Type.h"

typedef struct App
{
	struct SDL_Window*		Window;
	struct SDL_Renderer*	Renderer;
} App;

extern App g_App;

/// <summary>
/// ���� �ʱ�ȭ�Ѵ�.
/// </summary>
/// <returns>�ʱ�ȭ�� �����ߴٸ� true, �ƴϸ� false</returns>
bool App_Init(void);

/// <summary>
/// ���� �����Ѵ�.
/// </summary>
/// <returns>���������� �����ߴٸ� 0</returns>
int32 App_Run(void);