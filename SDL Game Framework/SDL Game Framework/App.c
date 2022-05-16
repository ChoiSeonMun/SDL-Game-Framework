#include "stdafx.h"
#include "App.h"

#include "Framework/Window.h"

bool App_Init(void)
{
	if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_LOG_WITH_ERRORCODE("Fail to initialize SDL");

		return false;
	}

	if (false == Window_Init())
	{
		SDL_LOG_WITH_ERRORCODE("Fail to intialize window");

		return false;
	}

	return true;
}

void cleanup(void)
{
	Window_Cleanup();
	SDL_Quit();
}

void processInput(void)
{

}

void update(void)
{

}

void render(void)
{
}

int32 App_Run(void)
{
	atexit(cleanup);


	return 0;
}