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
	for (int32 i = 0; i < TEXT_MAX_LINE; ++i)
	{
		Renderer_DrawTextBlended(&option->Text[i],
			option->PosX,
			option->PosY + i * SPACE_BETWEEN_LINES,
			option->Color);
	}
}

void Option_Release(Option* option)
{
	for (int32 i = 0; i < TEXT_MAX_LINE; ++i)
	{
		Text_FreeText(&option->Text[i]);
	}
}