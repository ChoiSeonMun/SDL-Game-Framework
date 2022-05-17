#pragma once

typedef struct Text
{
	struct TTF_Font*	Font;
	wchar_t*			String;
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

/// <summary>
/// �ؽ�Ʈ ���� ���̺귯���� �ʱ�ȭ�Ѵ�.
/// </summary>
/// <returns>�����ߴٸ� true, �ƴϸ� false</returns>
bool Text_Init(void);

/// <summary>
/// �ؽ�Ʈ ���� ���̺귯���� �����Ѵ�.
/// </summary>
void Text_Cleanup(void);

/// <summary>
/// �ؽ�Ʈ�� �����.
/// </summary>
/// <param name="text">�ؽ�Ʈ ��ü</param>
/// <param name="fontFile">��Ʈ ���� �̸�(.ttf�� ����)</param>
/// <param name="fontSize">��Ʈ ũ��</param>
/// <param name="str">�����ڵ� ���ڿ�</param>
/// <param name="length">���ڿ��� ����</param>
void Text_CreateText(Text* text, const char* fontFile, int32 fontSize, const wchar_t* str, int32 length);

/// <summary>
/// �ؽ�Ʈ�� ���õ� �ڿ��� �ݳ��Ѵ�. Release()���� �ݵ�� ȣ��������.
/// </summary>
/// <param name="text">�ؽ�Ʈ ��ü</param>
void Text_FreeText(Text* text);

/// <summary>
/// ��Ʈ�� �����Ѵ�.
/// </summary>
/// <param name="text">�ؽ�Ʈ ��ü</param>
/// <param name="fontFile">��Ʈ ���� �̸�(.ttf�� ����)</param>
/// <param name="fontSize">��Ʈ ũ��</param>
void Text_SetFont(Text* text, const char* fontFile, int32 fontSize);

/// <summary>
/// ��Ʈ ��Ÿ���� �����Ѵ�. | �����ڷ� ���� ��Ÿ���� �� ���� ������ �� �ִ�.
/// </summary>
/// <param name="text">�ؽ�Ʈ ��ü</param>
/// <param name="style">��Ʈ ��Ÿ��</param>
void Text_SetFontStyle(Text* text, EFontStyle style);

/// <summary>
/// ��Ʈ ��Ÿ���� �����´�.
/// </summary>
/// <param name="text">�ؽ�Ʈ ��ü</param>
/// <returns>��Ʈ ��Ÿ��</returns>
EFontStyle Text_GetFontStyle(const Text* text);

void Text_LoadText(Text* text, const char* filename);