#include "stdafx.h"
#include "App.h"

#include "Framework/Window.h"
#include "Framework/Renderer.h"
#include "Framework/Image.h"

App g_App;

bool App_Init(void)
{
	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		LogWithErrorCode("Fail to initialize SDL", SDL_GetError());

		return false;
	}

	Window_Init();
	if (NULL == g_App.Window)
	{
		LogWithErrorCode("Fail to intialize window", SDL_GetError());

		return false;
	}

	Renderer_Init();
	if (NULL == g_App.Renderer)
	{
		LogWithErrorCode("Fail to initialize renderer", SDL_GetError());

		return false;
	}

	if (false == Image_Init())
	{
		LogWithErrorCode("Fail to initalize image library", IMG_GetError());
	}

	return true;
}

void cleanup(void)
{
	Image_Cleanup();
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

Image image;
void render(void)
{
	Renderer_DrawImage(&image, 100, 100);
	Renderer_Flip();
}

void processEvent(SDL_Event event)
{
	
}

int32 App_Run(void)
{
	atexit(cleanup);

	Image_LoadImage(&image, "Background.jfif");

	SDL_Event event;
	while (true)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				break;
			}

			processEvent(event);
		}
		else
		{
			Renderer_Prepare();
			processInput();
			update();
			render();
		}
	}


	return 0;
}