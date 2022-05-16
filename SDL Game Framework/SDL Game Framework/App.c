#include "stdafx.h"
#include "App.h"

#include "Framework/Window.h"
#include "Framework/Renderer.h"

bool App_Init(void)
{
	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LOG_WITH_ERRORCODE("Fail to initialize SDL");

		return false;
	}

	if (false == Window_Init())
	{
		SDL_LOG_WITH_ERRORCODE("Fail to intialize window");

		return false;
	}

	SDL_Window* window = Window_GetWindow();
	if (false == Renderer_Init(window))
	{
		SDL_LOG_WITH_ERRORCODE("Fail to initialize renderer");

		return false;
	}

	return true;
}

void cleanup(void)
{
	Renderer_Cleanup();
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
	Renderer_Flip();
}

int32 App_Run(void)
{
	atexit(cleanup);

	while (true)
	{
		Renderer_Prepare();
		processInput();
		update();
		render();
	}


	return 0;
}