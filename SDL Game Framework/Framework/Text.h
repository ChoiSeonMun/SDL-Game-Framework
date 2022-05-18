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
/// 텍스트 관련 라이브러리를 초기화한다.
/// </summary>
/// <returns>성공했다면 true, 아니면 false</returns>
bool Text_Init(void);

/// <summary>
/// 텍스트 관련 라이브러리를 정리한다.
/// </summary>
void Text_Cleanup(void);

/// <summary>
/// 텍스트를 만든다.
/// </summary>
/// <param name="text">텍스트 객체</param>
/// <param name="fontFile">폰트 파일 이름(.ttf만 가능)</param>
/// <param name="fontSize">폰트 크기</param>
/// <param name="str">유니코드 문자열</param>
/// <param name="length">문자열의 길이</param>
void Text_CreateText(Text* text, const char* fontFile, int32 fontSize, const wchar_t* str, int32 length);

/// <summary>
/// 한글자씩 출력되는 텍스트
/// </summary>
/// <param name="text">텍스트 객체</param>
/// <param name="fontFile">폰트 파일</param>
/// <param name="fontSize">글자 크기</param>
/// <param name="str">유니코드 문자열</param>
/// <param name="length">텍스트 길이</param>
/// <param name="timer">출력 시간</param>
void Text_CreateMoveText(Text* text, const char* fontFile, int32 fontSize, const wchar_t* str, int32 length, static float timer);

/// <summary>
/// 텍스트와 관련된 자원을 반납한다. Release()에서 반드시 호출해주자.
/// </summary>
/// <param name="text">텍스트 객체</param>
void Text_FreeText(Text* text);

/// <summary>
/// 폰트를 설정한다.
/// </summary>
/// <param name="text">텍스트 객체</param>
/// <param name="fontFile">폰트 파일 이름(.ttf만 가능)</param>
/// <param name="fontSize">폰트 크기</param>
void Text_SetFont(Text* text, const char* fontFile, int32 fontSize);

/// <summary>
/// 폰트 스타일을 변경한다. | 연산자로 여러 스타일을 한 번에 지정할 수 있다.
/// </summary>
/// <param name="text">텍스트 객체</param>
/// <param name="style">폰트 스타일</param>
void Text_SetFontStyle(Text* text, EFontStyle style);

/// <summary>
/// 폰트 스타일을 가져온다.
/// </summary>
/// <param name="text">텍스트 객체</param>
/// <returns>폰트 스타일</returns>
EFontStyle Text_GetFontStyle(const Text* text);

void Text_TextChoice(const Text* text, int32 Count);