#pragma once

#include "Type.h"

typedef struct Image
{
	struct SDL_Texture* Texture;
	int32				Width;
	int32				Height;
	float				ScaleX;
	float				ScaleY;
} Image;

/// <summary>
/// �̹��� ���� ���̺귯���� �ʱ�ȭ�Ѵ�.
/// </summary>
/// <returns>�����ߴٸ� true, �ƴϸ� false</returns>
bool Image_Init(void);

/// <summary>
/// �̹��� ���� ���̺귯���� �����Ѵ�.
/// </summary>
void Image_Cleanup(void);

/// <summary>
/// �̹����� �ҷ��´�.
/// </summary>
/// <param name="image">�̹��� ��ü</param>
/// <param name="filename">���� �̸�</param>
void Image_LoadImage(Image* image, const char* filename);


/// <summary>
/// �̹��� ���� �ڿ��� ��ȯ�Ѵ�. Release�� �ݵ�� �������.
/// </summary>
/// <param name="image">Image ��ü</param>
void Image_FreeImage(Image* image);

/// <summary>
/// �̹����� ���İ��� �����Ѵ�.
/// </summary>
/// <param name="image">�̹��� ��ü</param>
/// <param name="alpha">���� �̸�</param>
void Image_SetAlphaValue(Image* image, uint8 alpha);
