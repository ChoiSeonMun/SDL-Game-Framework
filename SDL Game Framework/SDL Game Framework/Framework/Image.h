#pragma once

#include "Type.h"

typedef struct Image
{
	struct SDL_Texture* Texture;
	int32				Width;
	int32				Height;
} Image;

bool Image_Init(void);
void Image_Cleanup(void);
void Image_LoadImage(Image* image, const char* filename);