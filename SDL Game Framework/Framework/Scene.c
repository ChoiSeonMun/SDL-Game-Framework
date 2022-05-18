#include "stdafx.h"
#include "Scene.h"
#include <Windows.h>
#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;
int32		Count;//카운트 값
#define TEXT_COUNT 3//문자열 카운트

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2


typedef struct TitleSceneData
{
	Text	Text1;
	Text	Text2;
	Text	Text3;
	int32	FontSize;
	int32	RenderMode;
	Image	index1;

} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	
	data->FontSize = 50;
	Text_CreateText(&data->Text2, "d2coding.ttf", data->FontSize, L"- G A M E S T A R T -", 21);
	data->FontSize = 30;
	Text_CreateText(&data->Text3, "d2coding.ttf", data->FontSize, L"PRESS - SPACE - BUTTON", 22);
	
	data->RenderMode = SOLID;

	Image_LoadImage(&data->index1, "index0.png");
}

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	
	
	data->FontSize = 50;
	Text_CreateMoveText(&data->Text1, "d2coding.ttf", data->FontSize, L"T A K E N", 8, 0.5f);



	Text_SetFontStyle(&data->Text1, FS_BOLD);
	Text_SetFontStyle(&data->Text2, FS_BOLD);
	Text_SetFontStyle(&data->Text3, FS_BOLD);


	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_RULE);
	}
}
bool canShow = 0;

void render_title(void)
{
	
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	static float elapsedTime;
	elapsedTime += Timer_GetDeltaTime();
	Renderer_DrawImage(&data->index1, 0, 0); 

	
		SDL_Color foreColor = { .r = 255, .g = 255, .b = 255 };
		SDL_Color backColor = { .a = 125 };
		Renderer_DrawTextShaded(&data->Text1, 400, 100, foreColor, backColor);
	
		if (elapsedTime >= 0.7f)
		{

			canShow = !canShow;
			elapsedTime = 0.0f;

		}

		if (canShow == true)
		{
			SDL_Color foreColor = { .r = 255 };
			SDL_Color backColor = { .a = 0 };
			Renderer_DrawTextShaded(&data->Text2, 275, 500, foreColor, backColor);
			Renderer_DrawTextShaded(&data->Text3, 375, 600, foreColor, backColor);

		}
		

		
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;


	Text_FreeText(&data->Text1);
	Text_FreeText(&data->Text2);
	Text_FreeText(&data->Text3);

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region ruleScene

const wchar_t* ruleStr[] =
{
	L"게 임 방 법",
	L"- 선택지가 없는 장면은 스페이스바를 누르면 장면이 넘어갑니다.",
	L"- 선택지가 있는 장면은 방향키와 스페이스바를 이용하여 선택할 수 있습니다.",
};



typedef struct RuleSceneData
{
	Text Text[TEXT_COUNT];
	Image image;
	int32 Alpha;

} RuleSceneData;



void init_rule(void)
{
	g_Scene.Data = malloc(sizeof(RuleSceneData));
	memset(g_Scene.Data, 0, sizeof(RuleSceneData));

	RuleSceneData* data = (RuleSceneData*)g_Scene.Data;

	Image_LoadImage(&data->image, "index0.png");
	for (int32 i = 0; i < TEXT_COUNT; ++i)
	{

		Text_CreateText(&data->Text[i], "d2coding.ttf", 25, ruleStr[i], wcslen(ruleStr[i]));

	}
	data->Alpha = 0;
	
}

void update_rule(void)
{
	RuleSceneData* data = (RuleSceneData*)g_Scene.Data;
	
	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_MAIN);
	}
	
}

void render_rule(void)
{

	RuleSceneData* data = (RuleSceneData*)g_Scene.Data;
	Renderer_DrawImage(&data->image, 0, 0);
	
	data->Alpha = Clamp(1, data->Alpha + 1, 255);// 페이드 인
	Renderer_DrawTextFade(&data->Text[0], 10, 30, data->Alpha);
	Renderer_DrawTextFade(&data->Text[1], 10, 600, data->Alpha);
	Renderer_DrawTextFade(&data->Text[2], 10, 630, data->Alpha);
		
	
	
}

void release_rule(void)
{

	RuleSceneData* data = (RuleSceneData*)g_Scene.Data;

	Text_FreeText(&data->Text[0]);
	Text_FreeText(&data->Text[1]);
	Text_FreeText(&data->Text[2]);


}


#pragma region MainScene
const wchar_t* str2[] = 
{
	L"전직 경찰로 다리에 부상을 입고 은퇴 후 보조금을 받으며 평범하게 살아가던 데이빗.",
	L"데이빗의 유일한 가족은 딸 에이미 한 명 뿐이다.",
	L"하나뿐인 딸 에이미는 어릴 때부터 아빠와 단 둘이 자라 유독 각별한 부녀애를 가지고 있다.",

};



typedef struct MainSceneData
{
	Text		Text[TEXT_COUNT];
	Music		BGM;
	float		Volume;
	SoundEffect Effect;
	Image		BackGround;
	float		Speed;
	int32		X;
	int32		Y;
	int32		Alpha;
	
} MainSceneData;

void logOnFinished(void)
{
	LogInfo("You can show this log on stopped the music");
}

void log2OnFinished(int32 channel)
{
	LogInfo("You can show this log on stopped the effect");
}

void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, sizeof(MainSceneData));

	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	for (int32 i = 0; i < TEXT_COUNT; ++i)
	{
		
		Text_CreateText(&data->Text[i], "d2coding.ttf", 25, str2[i], wcslen(str2[i]));
		
	}
	
	Image_LoadImage(&data->BackGround, "index2.png");

	Audio_LoadMusic(&data->BGM, "index1.mp3");


	data->Volume = 1.0f;

	data->Speed = 400.0f;
	data->Alpha = 255;
}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	
	if (Input_GetKeyDown('E'))
	{
		Audio_PlaySoundEffect(&data->Effect, 1);
	}

	if (Input_GetKeyDown('M'))
	{
		if (Audio_IsMusicPlaying())
		{
			Audio_Stop();
		}
		else
		{
			Audio_Play(&data->BGM, INFINITY_LOOP);
		}
	}


	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_3);
	}
}

void render_main(void)
{
	


	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	Renderer_DrawImage(&data->BackGround, 0, 0);
	Input_Choice(VK_UP, VK_DOWN);// Count값 조절
	Text_TextChoice(&data->Text, Count);//텍스트 선택지
	
}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	for (int32 i = 0; i < 3; ++i)
	{
		Text_FreeText(&data->Text[i]);
	}
	Audio_FreeMusic(&data->BGM);
	Audio_FreeSoundEffect(&data->Effect);

	SafeFree(g_Scene.Data);
}
#pragma endregion


#pragma region _3Scene

const wchar_t* str3[] =
{
	L"그래서 데이빗은 아직 20대 초반인 에이미에게",
	L"엄격한 통금과 외박 금지를 시행하며 도가 지나칠 정도로 애지중지 키우지만,",
	L"진주도 걱정하는 아빠의 마음을 헤아려 늘 불평 없이 말을 잘 듣는다.",

};

typedef struct _3SceneData
{
	Text	Text[TEXT_COUNT];
	Text	Text2;
	int32	FontSize;
	int32	RenderMode;
	Image	index3;
	int32	Alpha;
} _3SceneData;

void init_3Scene(void)
{
	g_Scene.Data = malloc(sizeof(_3SceneData));
	memset(g_Scene.Data, 0, sizeof(_3SceneData));

	_3SceneData* data = (_3SceneData*)g_Scene.Data;


	data->FontSize = 50;
	
	data->RenderMode = SOLID;
	
	Image_LoadImage(&data->index3, "index8.png");
}

void update_3Scene(void)
{
	_3SceneData* data = (_3SceneData*)g_Scene.Data;
	
		Text_CreateMoveText(&data->Text[Count], "d2coding.ttf", 25, str3[Count], wcslen(str3[0]), 0.5);
		Text_CreateMoveText(&data->Text[Count], "d2coding.ttf", 25, str3[Count], wcslen(str3[1]), 0.5);
		Text_CreateMoveText(&data->Text[Count], "d2coding.ttf", 25, str3[Count], wcslen(str3[2]), 0.5);
	

	for (int32 i = 0; i < 3; i++)
	{

		Text_SetFontStyle(&data->Text[i], FS_BOLD);
	}

		data->Alpha = Clamp(100, data->Alpha + 1, 255);
		Image_SetAlphaValue(&data->index3, data->Alpha);
		
	if (Input_GetKeyDown(VK_SPACE))
	{
		Count++;
		if(Count == 3)
		Scene_SetNextScene(SCENE_4);
	}
	
}

void render_3Scene(void)
{
	_3SceneData* data = (_3SceneData*)g_Scene.Data;

	SDL_Color foreColor = { .r = 255, .g = 255, .b = 255 };
	SDL_Color backColor = { .a = 125 };
	Renderer_DrawImage(&data->index3, 0, 0);

	for (int32 i = 0; i < TEXT_COUNT; ++i)
	{
		SDL_Color foreColor = { .r = 255, .g = 255, .b = 255 };
		SDL_Color backColor = { .a = 125 };
		Renderer_DrawTextShaded(&data->Text[i], 10, 30 * i, foreColor, backColor);

	}

}

void release_3Scene(void)
{
	_3SceneData* data = (_3SceneData*)g_Scene.Data;

	for (int32 i = 0; i < 3; i++)
	{
		Text_FreeText(&data->Text[i]);
	}

	


	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region _4Scene

const wchar_t* str4[] =
{
	L"전직 경찰로 다리에 부상을 입고 은퇴 후 보조금을 받으며 평범하게 살아가던 데이빗.",
	L"데이빗의 유일한 가족은 딸 에이미 한 명 뿐이다.",
	L"하나뿐인 딸 에이미는 어릴 때부터 아빠와 단 둘이 자라 유독 각별한 부녀애를 가지고 있다.",

};

typedef struct _4SceneData
{
	Text	Text1;
	Text	Text2;
	int32	FontSize;
	int32	RenderMode;
	Image	index4;
	Image	choice[];



} _4SceneData;

void init_4Scene(void)
{
	g_Scene.Data = malloc(sizeof(_4SceneData));
	memset(g_Scene.Data, 0, sizeof(_4SceneData));

	_4SceneData* data = (_4SceneData*)g_Scene.Data;




	Image_LoadImage(&data->index4, "index4.png");
	Image_LoadImage(&data->choice[0], "Choice1.png");
	Image_LoadImage(&data->choice[1], "Choice2.png");
	Image_LoadImage(&data->choice[2], "Choice3.png");


}

void update_4Scene(void)
{
	_4SceneData* data = (_4SceneData*)g_Scene.Data;

}

void render_4Scene(void)
{
	_4SceneData* data = (_4SceneData*)g_Scene.Data;

	
	Renderer_DrawImage(&data->index4, 0, 0);
	Input_Choice(VK_LEFT, VK_RIGHT);
	//이미지 선택지
	for (int i = 0; i < 3; i++)
	{
		Image_SetAlphaValue(&data->choice[i], 50);
		if (Count == i)
		{
			Image_SetAlphaValue(&data->choice[i], 200);
		}

		Renderer_DrawImage(&data->choice[i], (i * 350) + 50, 300);
	}

	




}

void release_4Scene(void)
{
	_4SceneData* data = (_4SceneData*)g_Scene.Data;


	Text_FreeText(&data->Text1);
	Text_FreeText(&data->Text2);

	SafeFree(g_Scene.Data);
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
	case SCENE_RULE:
		g_Scene.Init = init_rule;
		g_Scene.Update = update_rule;
		g_Scene.Render = render_rule;
		g_Scene.Release = release_rule;
		break;
	case SCENE_MAIN:
		g_Scene.Init = init_main;
		g_Scene.Update = update_main;
		g_Scene.Render = render_main;
		g_Scene.Release = release_main;
		break;
	case SCENE_3:
		g_Scene.Init = init_3Scene;
		g_Scene.Update = update_3Scene;
		g_Scene.Render = render_3Scene;
		g_Scene.Release = release_3Scene;
		break;
	case SCENE_4:
		g_Scene.Init = init_4Scene;
		g_Scene.Update = update_4Scene;
		g_Scene.Render = render_4Scene;
		g_Scene.Release = release_4Scene;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}