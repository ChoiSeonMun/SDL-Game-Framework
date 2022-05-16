#include "stdafx.h"
#include "App.h"
#include "Image.h"
#include "Text.h"

void Renderer_Init(void)
{
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	g_App.Renderer = SDL_CreateRenderer(g_App.Window, -1, SDL_RENDERER_ACCELERATED);
}

void Renderer_Cleanup(void)
{
	SDL_DestroyRenderer(g_App.Renderer);
}

void Renderer_Prepare(void)
{
	SDL_SetRenderDrawColor(g_App.Renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_App.Renderer);
}

void Renderer_Flip(void)
{
	SDL_RenderPresent(g_App.Renderer);
	//SDL_SetRenderDrawColor(s_Renderer, 255, 255, 255, 255);
	//SDL_RenderClear(s_Renderer);
}

void Renderer_DrawImage(const Image* image, int x, int y)
{
	SDL_Rect rect = { .x = x, .y = y,
		.w = image->Width * image->ScaleX,
		.h = image->Height * image->ScaleY };
	
	SDL_RenderCopy(g_App.Renderer, image->Texture, NULL, &rect);
}

void Renderer_DrawTextSolid(const Text* text, int x, int y, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderUNICODE_Solid(text->Font, text->String, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_App.Renderer, surface);
	SDL_Rect rect = { .x = x, .y = y };
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(g_App.Renderer, texture, NULL, &rect);

	SDL_FreeSurface(surface);
}

void Renderer_DrawTextShaded(const Text* text, int x, int y, SDL_Color foreground, SDL_Color background)
{
	SDL_Surface* surface = TTF_RenderUNICODE_Shaded(text->Font, text->String, foreground, background);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_App.Renderer, surface);
	SDL_Rect rect = { .x = x, .y = y };
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(g_App.Renderer, texture, NULL, &rect);

	SDL_FreeSurface(surface);
}

void Renderer_DrawTextBlended(const Text* text, int x, int y, SDL_Color foreground)
{
	SDL_Surface* surface = TTF_RenderUNICODE_Blended(text->Font, text->String, foreground);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_App.Renderer, surface);
	SDL_Rect rect = { .x = x, .y = y };
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(g_App.Renderer, texture, NULL, &rect);

	SDL_FreeSurface(surface);
}