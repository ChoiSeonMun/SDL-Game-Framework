#include "stdafx.h"
#include "Option.h"

void Option_Init(Option* option, int32 posX, int32 posY)
{
	option->PosX = posX;
	option->PosY = posY;
}

void Option_Update(Option* option)
{
}

void Option_Render(Option* option)
{
	Renderer_DrawTextBlended(&option->Text, option->PosX, option->PosY, option->Color);
}

void Option_Release(Option* option)
{
	Text_FreeText(&option->Text);
}