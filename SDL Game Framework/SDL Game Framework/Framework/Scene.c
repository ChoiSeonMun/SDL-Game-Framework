#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene

Image image, image2;
int x, y;
float speed;
uint8 alpha = 255;

void init_title(void)
{
	Image_LoadImage(&image, "Background.jfif");
	speed = 400.0f;
	image.ScaleX = 1.5f;
	image.ScaleY = 1.6f;

	Image_LoadImage(&image2, "Background2.jfif");
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

	if (Input_GetKey('1'))
	{
		alpha = Clamp(0, alpha - 1, 255);
		Image_SetAlphaValue(&image, alpha);
	}

	if (Input_GetKey('2'))
	{
		alpha = Clamp(0, alpha + 1, 255);
		Image_SetAlphaValue(&image, alpha);
	}
}

void render_title(void)
{
	Renderer_DrawImage(&image2, 100, 100);
	Renderer_DrawImage(&image, x, y);
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