#pragma once

#include "Type.h"

typedef struct App
{
	struct SDL_Window*		Window;
	struct SDL_Renderer*	Renderer;
} App;

extern App g_App;

/// <summary>
/// 앱을 초기화한다.
/// </summary>
/// <returns>초기화에 성공했다면 true, 아니면 false</returns>
bool App_Init(void);

/// <summary>
/// 앱을 실행한다.
/// </summary>
/// <returns>성공적으로 종료했다면 0</returns>
int32 App_Run(void);