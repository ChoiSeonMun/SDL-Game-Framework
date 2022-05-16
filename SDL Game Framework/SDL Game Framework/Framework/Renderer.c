#include "stdafx.h"

static SDL_Renderer* s_Renderer;

bool Renderer_Init(SDL_Window* window)
{
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	s_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (NULL == s_Renderer)
	{
		return false;
	}

	return true;
}

void Renderer_Cleanup(void)
{
	SDL_DestroyRenderer(s_Renderer);
}

void Renderer_Prepare(void)
{
	SDL_SetRenderDrawColor(s_Renderer, 255, 255, 255, 255);
	SDL_RenderClear(s_Renderer);
}

void Renderer_Flip(void)
{
	SDL_RenderPresent(s_Renderer);
	//SDL_SetRenderDrawColor(s_Renderer, 255, 255, 255, 255);
	//SDL_RenderClear(s_Renderer);
}
