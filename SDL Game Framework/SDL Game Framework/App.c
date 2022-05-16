#include "stdafx.h"
#include "App.h"

App g_App;

bool App_Init(void)
{
	if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_LOG_WITH_ERRORCODE("Fail to initialize");

		return false;
	}

	int32 windowFlags = 0;
	if (0 != SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags, &g_App.Window, &g_App.Renderer))
	{
		SDL_LOG_WITH_ERRORCODE("Fail to create window");

		return false;
	}

	return true;
}

void cleanup(void)
{
	SDL_Quit();
}

int32 App_Run(void)
{
	atexit(cleanup);

	return 0;
}