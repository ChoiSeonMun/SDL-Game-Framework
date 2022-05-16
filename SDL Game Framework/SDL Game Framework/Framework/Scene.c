#include "stdafx.h"
#include "Scene.h"

#include "Image.h"
#include "Timer.h"
#include "Renderer.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene

Image image;
int x, y;
float speed;

void init_title(void)
{
	Image_LoadImage(&image, "Background.jfif");
	x = 100;
	y = 100;
	speed = 100.0f;
}

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
}

void render_title(void)
{
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