#pragma once

#include "Common.h"

typedef struct App
{
	SDL_Renderer*	Renderer;
	SDL_Window*		Window;
} App;

extern App g_App;

bool App_Init(void);
int32 App_Run(void);