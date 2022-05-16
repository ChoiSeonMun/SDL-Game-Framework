#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene

Image image;
int x, y;
float speed;
Music music;
SoundEffect effect;
float volume = 0.5f;

void LogTemp(int32 channel)
{
	LogInfo("Sound Effect End!");
}

void init_title(void)
{
	Image_LoadImage(&image, "Background.jfif");
	x = 100;
	y = 100;
	speed = 400.0f;
	image.ScaleX = 1.5f;
	image.ScaleY = 1.6f;

	Audio_LoadMusic(&music, "powerful.mp3");
	Audio_LoadSoundEffect(&effect, "effect2.wav");
	//Audio_Play(&effect, INFINITY_LOOP);
	Audio_PlayFadeIn(&music, INFINITY_LOOP, 10000);
	Audio_HookSoundEffectFinished(LogTemp);
}

int num;
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
		volume -= 0.01f;
		Audio_SetVolume(volume);
		LogInfo("Current Volume : %f", Audio_GetVolume());
	}

	if (Input_GetKey('2'))
	{
		volume += 0.01f;
		Audio_SetVolume(volume);
		LogInfo("Current Volume : %f", Audio_GetVolume());
	}

	if (Input_GetKeyDown('P'))
	{
		Audio_PauseSoundEffect();
	}

	if (Input_GetKeyDown('R'))
	{
		Audio_ResumeSoundEffect();
	}

	if (Input_GetKeyDown('E'))
	{
		Audio_PlaySoundEffect(&effect, 1);
	}

	if (Input_GetKeyDown('Z'))
	{
		Audio_Rewind();
	}

	if (Input_GetKeyDown('M'))
	{
		Audio_StopSoundEffect();
	}

	if (Input_GetKeyDown('W'))
	{
		Audio_FadeOut(3000);
	}
	//LogInfo("Is paused : %s", (Audio_IsSoundEffectPaused() ? "true" : "false"));
}

void render_title(void)
{
	Renderer_DrawImage(&image, x, y);
}

void release_title(void)
{
	Audio_FreeSoundEffect(&effect);
	Audio_FreeMusic(&music);
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