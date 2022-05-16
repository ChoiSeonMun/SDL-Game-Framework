#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene

Image image;
int x, y;
float speed;
Text text;
int32 fontSize = 16;

void init_title(void)
{
	Image_LoadImage(&image, "Background.jfif");
	x = 100;
	y = 100;
	speed = 400.0f;
	image.ScaleX = 1.5f;
	image.ScaleY = 1.6f;

	Text_CreateText(&text, "d2coding.ttf", fontSize, L"안녕하세요, 폰트입니다.", 14);
}

int32 renderMode;
void update_title(void)
{
	if (Input_GetKey(VK_DOWN))
	{
		y += speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_UP))
	{
		y -= speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_LEFT))
	{
		x -= speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_RIGHT))
	{
		x += speed * Timer_GetDeltaTime();
	}

	if (Input_GetKeyDown('C'))
	{
		renderMode = (renderMode + 1) % 3;
	}

	if (Input_GetKeyDown('1'))
	{
		--fontSize;
		Text_SetFont(&text, "d2coding.ttf", fontSize);
	}

	if (Input_GetKeyDown('2'))
	{
		++fontSize;
		Text_SetFont(&text, "d2coding.ttf", fontSize);
	}

	if (Input_GetKey('B'))
	{
		Text_SetFontStyle(&text, FS_BOLD);
	}

	if (Input_GetKeyDown('I'))
	{
		Text_SetFontStyle(&text, FS_ITALIC);
	}

	if (Input_GetKeyDown('U'))
	{
		Text_SetFontStyle(&text, FS_UNDERLINE);
	}

	if (Input_GetKeyDown('S'))
	{
		Text_SetFontStyle(&text, FS_STRIKETHROUGH);
	}
}

void render_title(void)
{
	switch (renderMode)
	{
	case 0:
	{
		SDL_Color color = { 0 };
		color.a = 255;
		Renderer_DrawTextSolid(&text, 100, 100, color);
	}
	break;
	case 1:
	{
		SDL_Color bg = { .a = 255 };
		SDL_Color fg = { .r = 255, .g = 255, .a = 255 };
		Renderer_DrawTextShaded(&text, 100, 100, fg, bg);
	}
	break;
	case 2:
	{
		Renderer_DrawImage(&image, 100, 100);
		SDL_Color fg = { .r = 255, .g = 255, .b = 255, .a = 255 };
		Renderer_DrawTextBlended(&text, 100, 100, fg);
	}
	break;
	}
}

void release_title(void)
{

}
#pragma endregion


bool Scene_IsSetNextScene(void)
{
	if (SCENE_NULL == s_nextScene)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Scene_SetNextScene(ESceneType scene)
{
	assert(s_nextScene == SCENE_NULL);
	assert(SCENE_NULL < scene&& scene < SCENE_MAX);

	s_nextScene = scene;
}

void Scene_Change(void)
{
	assert(s_nextScene != SCENE_NULL);

	if (g_Scene.Release)
	{
		g_Scene.Release();
	}

	switch (s_nextScene)
	{
	case SCENE_TITLE:
		g_Scene.Init = init_title;
		g_Scene.Update = update_title;
		g_Scene.Render = render_title;
		g_Scene.Release = release_title;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}