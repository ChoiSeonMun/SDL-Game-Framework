#pragma once

typedef struct Text
{
	struct TTF_Font*	Font;
	const wchar_t*		String;
	int32				Length;
} Text;

typedef enum FontStyle
{
	FS_NORMAL = 0x00,
	FS_BOLD = 0x01,
	FS_ITALIC = 0x02,
	FS_UNDERLINE = 0x04,
	FS_STRIKETHROUGH = 0x08
} EFontStyle;

bool Text_Init(void);
void Text_Cleanup(void);
void Text_CreateText(Text* text, const char* fontFile, int32 fontSize, const wchar_t* str, int32 length);
void Text_FreeText(Text* text);
void Text_SetFont(Text* text, const char* fontFile, int32 fontSize);
void Text_SetFontStyle(Text* text, EFontStyle style);
EFontStyle Text_GetFontStyle(const Text* text);