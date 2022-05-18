#include "stdafx.h"
#include "Image.h"
#include "App.h"
#include "Input.h"
bool Image_Init(void)
{
	int32 imageFlag = IMG_INIT_PNG | IMG_INIT_JPG;
	int32 imageLibResult = IMG_Init(imageFlag);
	if (imageFlag != (imageFlag & imageLibResult))
	{
		return false;
	}

	return true;
}

void Image_Cleanup(void)
{
	IMG_Quit();
}

void Image_LoadImage(Image* image, const char* filename)
{
	LogInfo("Image Loading... %s", filename);
	
	static char path[MAX_PATH];

	sprintf_s(path, sizeof(path), "%s/%s", IMAGE_DIRECTORY, filename);
	image->Texture = IMG_LoadTexture(g_App.Renderer, path);
	SDL_QueryTexture(image->Texture, NULL, NULL, &image->Width, &image->Height);
	image->ScaleX = image->ScaleY = 1.0f;

	SDL_SetTextureBlendMode(image->Texture, SDL_BLENDMODE_BLEND);
}

void Image_SetAlphaValue(Image* image, uint8 alpha)
{
	SDL_SetTextureAlphaMod(image->Texture, alpha);
}



void Image_Choice(Image* image, int32 Count)
{
	for (int32 i = 0; i < 3; i++)
	{
		
		Image_SetAlphaValue(image, 50);
		if (Count == i)
		{
			Image_SetAlphaValue(image, 200);
		}

		Renderer_DrawImage(image[i], (i * 350) + 50, 300);
		
	}

}


Renderer_DrawImage(&data->choice[i], (i * 350) + 50, 300);