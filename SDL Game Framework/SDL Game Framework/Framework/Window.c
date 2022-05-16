#include "stdafx.h"

static SDL_Window* s_Window;
static const char* s_Title = "Hello SDL";
static int32 s_Width = 1280;
static int32 s_Height = 720;
static uint32 s_flags = 0;

bool Window_Init(void)
{
	s_Window = SDL_CreateWindow(s_Title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		s_Width, s_Height, s_flags);

	if (NULL == s_Window)
	{
		return false;
	}

	return true;
}

void Window_Cleanup(void)
{
	SDL_DestroyWindow(s_Window);
}