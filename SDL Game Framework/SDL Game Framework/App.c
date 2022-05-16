#include "stdafx.h"
#include "App.h"

#include "Framework/Window.h"
#include "Framework/Renderer.h"
#include "Framework/Image.h"
#include "Framework/Input.h"
#include "Framework/Timer.h"

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
	Input_Update();
}

int x = 100;
int y = 100;
void update(void)
{
	if (Input_GetKeyDown(VK_DOWN))
	{
		y += 4;
	}
	
	if (Input_GetKeyDown(VK_UP))
	{
		y -= 4;
	}

	if (Input_GetKeyDown(VK_LEFT))
	{
		x -= 4;
	}

	if (Input_GetKeyDown(VK_RIGHT))
	{
		x += 4;
	}
}

Image image;
void render(void)
{
	Renderer_DrawImage(&image, x, y);
	Renderer_Flip();
}

int32 App_Run(void)
{
	atexit(cleanup);

	Timer_Init(60);

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
		}
		else
		{
			if (Timer_Update())
			{
				Renderer_Prepare();
				processInput();
				update();
				render();
			}
		}
	}


	return 0;
}