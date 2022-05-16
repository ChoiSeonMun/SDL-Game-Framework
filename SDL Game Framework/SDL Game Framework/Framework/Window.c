#include "stdafx.h"
#include "App.h"

static const char* s_Title = "Hello SDL";
static int32 s_Width = 1280;
static int32 s_Height = 720;
static uint32 s_flags = 0;

void Window_Init(void)
{
	g_App.Window = SDL_CreateWindow(s_Title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		s_Width, s_Height, s_flags);
}

void Window_Cleanup(void)
{
	SDL_DestroyWindow(g_App.Window);
}