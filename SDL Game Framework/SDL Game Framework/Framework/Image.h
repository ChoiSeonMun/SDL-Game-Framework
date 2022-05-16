#pragma once

#include "Type.h"

typedef struct Image
{
	struct SDL_Texture* Texture;
	int32				Width;
	int32				Height;
	float				ScaleX;
	float				ScaleY;
} Image;

bool Image_Init(void);
void Image_Cleanup(void);
void Image_LoadImage(Image* image, const char* filename);
void Image_SetAlphaValue(Image* image, uint8 alpha);
