#pragma once

/// <summary>
/// 렌더러를 초기화한다.
/// </summary>
/// <return>초기화에 성공하면 true, 아니면 false</return>
bool Renderer_Init(void);

/// <summary>
/// 렌더러를 정리한다.
/// </summary>
void Renderer_Cleanup(void);

/// <summary>
/// 백버퍼와 플립한다.
/// </summary>
void Renderer_Flip(void);

/// <summary>
/// 이미지를 그린다.
/// </summary>
/// <param name="image">이미지 객체</param>
/// <param name="x">좌표</param>
/// <param name="y">좌표</param>
void Renderer_DrawImage(const struct Image* image, int32 x, int32 y);

/// <summary>
/// 텍스트를 출력한다. (못생김 주의)
/// </summary>
/// <param name="text">텍스트 객체</param>
/// <param name="x">좌표</param>
/// <param name="y">좌표</param>
/// <param name="color">글자의 색깔</param>
void Renderer_DrawTextSolid(const struct Text* text, int32 x, int32 y, SDL_Color color);

/// <summary>
/// 텍스트를 출력한다. 배경색이 필요할 때 사용한다.
/// </summary>
/// <param name="text">텍스트 객체</param>
/// <param name="x">좌표</param>
/// <param name="y">좌표</param>
/// <param name="foreground">글자의 색깔</param>
/// <param name="background">글자의 배경색</param>
void Renderer_DrawTextShaded(const struct Text* text, int32 x, int32 y, SDL_Color foreground, SDL_Color background);

/// <summary>
/// 텍스트의 알파값을 바꿔준다.
/// </summary>
/// <param name="text">텍스트 객체</param>
/// <param name="x">좌표</param>
/// <param name="y">좌표</param>
/// <param name="Alpha">텍스트 알파값</param>
void Renderer_DrawTextFade(const struct Text* text, int32 x, int32 y, int32 Alpha);

/// <summary>
/// 텍스트를 출력한다. 이미지 위에 출력할 때 사용한다.
/// </summary>
/// <param name="text">텍스트 객체</param>
/// <param name="x">좌표</param>
/// <param name="y">좌표</param>
/// <param name="foreground">글자의 색깔</param>
void Renderer_DrawTextBlended(const struct Text* text, int32 x, int32 y, SDL_Color foreground);