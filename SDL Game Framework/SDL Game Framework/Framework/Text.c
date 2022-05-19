#include "stdafx.h"
#include "Text.h"

static char s_path[MAX_PATH];

bool Text_Init(void)
{
	if (0 != TTF_Init())
	{
		return false;
	}

	return true;
}

void Text_Cleanup(void)
{
	TTF_Quit();
}

void Text_CreateText(Text* text, const char* fontFile, int32 fontSize, const wchar_t* str, int32 length)
{
	LogInfo("Loading Font : %s", fontFile);
	sprintf_s(s_path, sizeof(s_path), "%s/%s", FONT_DIRECTORY, fontFile);
	text->Font = TTF_OpenFont(s_path, fontSize);
	
	text->String = malloc(sizeof(wchar_t) * (length + 1));
	for (int32 i = 0; i < length; ++i)
	{
		(text->String)[i] = str[i];
	}
	(text->String)[length] = L'\0';
	
	text->Length = length;
}

void Text_FreeText(Text* text)
{
	TTF_CloseFont(text->Font);
	text->Font = NULL;

	SafeFree(text->String);
	
	text->Length = 0;
}

void Text_SetFont(Text* text, const char* fontFile, int32 fontSize)
{
	if (text->Font)
	{
		TTF_CloseFont(text->Font);
	}

	LogInfo("Loading Font : %s", fontFile);
	sprintf_s(s_path, sizeof(s_path), "%s/%s", FONT_DIRECTORY, fontFile);
	text->Font = TTF_OpenFont(s_path, fontSize);
}

void Text_SetFontStyle(Text* text, EFontStyle style)
{
	TTF_SetFontStyle(text->Font, style);
}

EFontStyle Text_GetFontStyle(const Text* text)
{
	return (EFontStyle)TTF_GetFontStyle(text->Font);
}
