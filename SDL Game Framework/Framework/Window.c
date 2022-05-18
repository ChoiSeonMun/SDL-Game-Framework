#include "stdafx.h"
#include "App.h"

static const char* s_Title = "Hello SDL";
static int32 s_Width = WINDOW_WIDTH;
static int32 s_Height = WINDOW_HEIGHT;
static uint32 s_flags = 0;

bool Window_Init(void)
{
	g_App.Window = SDL_CreateWindow(s_Title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		s_Width, s_Height, s_flags);

	if (NULL == g_App.Window)
	{
		return false;
	}

	return true;
}

void Window_Cleanup(void)
{
	SDL_DestroyWindow(g_App.Window);
}