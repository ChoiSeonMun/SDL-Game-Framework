#pragma once

#include "Framework.h"
#include "PageIndex.h"
#include "Config.h"

typedef struct Option
{
	int32		PosX;
	int32		PosY;
	Text		Text[TEXT_MAX_LINE];
	EPageIndex	NextPage;
	SDL_Color	Color;
} Option;

void Option_Init(Option* option, int32 posX, int32 posY);
void Option_Update(Option* option);
void Option_Render(Option* option);
void Option_Release(Option* option);