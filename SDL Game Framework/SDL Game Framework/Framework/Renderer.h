#pragma once

/// <summary>
/// �������� �ʱ�ȭ�Ѵ�.
/// </summary>
/// <return>�ʱ�ȭ�� �����ϸ� true, �ƴϸ� false</return>
bool Renderer_Init(void);

/// <summary>
/// �������� �����Ѵ�.
/// </summary>
void Renderer_Cleanup(void);

/// <summary>
/// ����ۿ� �ø��Ѵ�.
/// </summary>
void Renderer_Flip(void);

/// <summary>
/// �̹����� �׸���.
/// </summary>
/// <param name="image">�̹��� ��ü</param>
/// <param name="x">��ǥ</param>
/// <param name="y">��ǥ</param>
void Renderer_DrawImage(const struct Image* image, int32 x, int32 y);

/// <summary>
/// �ؽ�Ʈ�� ����Ѵ�. (������ ����)
/// </summary>
/// <param name="text">�ؽ�Ʈ ��ü</param>
/// <param name="x">��ǥ</param>
/// <param name="y">��ǥ</param>
/// <param name="color">������ ����</param>
void Renderer_DrawTextSolid(const struct Text* text, int32 x, int32 y, SDL_Color color);

/// <summary>
/// �ؽ�Ʈ�� ����Ѵ�. ������ �ʿ��� �� ����Ѵ�.
/// </summary>
/// <param name="text">�ؽ�Ʈ ��ü</param>
/// <param name="x">��ǥ</param>
/// <param name="y">��ǥ</param>
/// <param name="foreground">������ ����</param>
/// <param name="background">������ ����</param>
void Renderer_DrawTextShaded(const struct Text* text, int32 x, int32 y, SDL_Color foreground, SDL_Color background);

/// <summary>
/// �ؽ�Ʈ�� ����Ѵ�. �̹��� ���� ����� �� ����Ѵ�.
/// </summary>
/// <param name="text">�ؽ�Ʈ ��ü</param>
/// <param name="x">��ǥ</param>
/// <param name="y">��ǥ</param>
/// <param name="foreground">������ ����</param>
void Renderer_DrawTextBlended(const struct Text* text, int32 x, int32 y, SDL_Color foreground);