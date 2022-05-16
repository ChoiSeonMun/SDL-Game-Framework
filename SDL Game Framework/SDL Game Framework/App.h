#pragma once

#include "Common.h"

typedef struct tagApp
{
	SDL_Window*		Window;
	SDL_Renderer*	Renderer;
} App;

extern App g_App;

bool App_Init(void);
int32 App_Run(void);