#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

//const wchar_t* str[] = {
//	L"PRESS THE ENTER",
//	//L"B키를 누르면 폰트가 굵게 변합니다.",
//	//L"I키를 누르면 폰트가 이탤릭체로 변합니다.",
//	//L"U키를 누르면 텍스트에 밑줄이 생깁니다.",
//	//L"S키를 누르면 텍스트에 취소선이 생깁니다.",
//	//L"N키를 누르면 다시 원래대로 돌아옵니다.",
//	//L"C키를 누르면 렌더 모드가 바뀝니다. (Solid -> Shaded -> Blended)",
//	//L"1키를 누르면 텍스트가 작아집니다.",
//	//L"2키를 누르면 텍스트가 커집니다.",
//	//L"스페이스 키를 누르면 다음 씬으로 넘어갑니다."
//};

typedef struct TitleSceneData
{
	Text	GuideLine[1];
	Music	TitleBGM;
	float	Volume;
	Text	EnterText;
	int32	FontSize;
	int32	RenderMode;
	Image	TitleImage;
	int32	X;
	int32	Y;
	Image	StartImage;
	int32	SX;
	int32	SY;
} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	//for (int32 i = 0; i < 1; ++i)
	//{
	//	Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 16, str[i], wcslen(str[i]));
	//}

	data->FontSize = 48;
	Text_CreateText(&data->EnterText, "chosun.ttf", data->FontSize, L"--- PRESS THE ENTER ---", 24);

	data->RenderMode = SOLID;

	Image_LoadImage(&data->TitleImage, "title_2.jpg");
	data->X = 0;
	data->Y = 0;
	Image_LoadImage(&data->StartImage, "start.png");
	data->SX = (WINDOW_WIDTH / 2) - (data->StartImage.Width / 2);
	data->SY = 650;

	Audio_LoadMusic(&data->TitleBGM, "title.mp3");
	
	Audio_PlayFadeIn(&data->TitleBGM, INFINITY_LOOP, 3000);

	data->Volume = 1.0f;
}

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	if (Input_GetKeyDown(VK_RETURN))
	{
		Scene_SetNextScene(SCENE_CREDIT);
	}
}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	//for (int32 i = 0; i < 10; ++i)
	//{
	//	SDL_Color color = { .a = 255 };
	//	Renderer_DrawTextSolid(&data->GuideLine[i], 10, 20 * i, color);
	//}
	
	//switch (data->RenderMode)
	//{
	//case SOLID:
	//{
	//	SDL_Color color = { .a = 255 };
	//	Renderer_DrawTextSolid(&data->EnterText, 400, 400, color);
	//}
	//break;
	//case SHADED:
	//{
	//	SDL_Color bg = { .a = 255 };
	//	SDL_Color fg = { .r = 255, .g = 255, .a = 255 };
	//	Renderer_DrawTextShaded(&data->EnterText, 400, 400, fg, bg);
	//}
	//break;
	//case BLENDED:
	//{
	//	Renderer_DrawImage(&data->TestImage, 400, 400);
	//	SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
	//	Renderer_DrawTextBlended(&data->EnterText, 400, 400, color);
	//}
	//break;
	//}
	Renderer_DrawImage(&data->TitleImage, data->X, data->Y);
	static float elapsedTime = 0;

	static bool isShow = true;
	elapsedTime += Timer_GetDeltaTime();
	if (elapsedTime >= 1.0f)
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawImage(&data->StartImage, data->SX, data->SY);
		Renderer_DrawTextSolid(&data->EnterText, WINDOW_WIDTH / 2 - (data->EnterText.Length * data->FontSize) / 4, 950, color);
		
		if (elapsedTime >= 1.5f)
		{ 
			elapsedTime = 0.0f;
		}
	}
	
	
	
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	//for (int32 i = 0; i < 10; ++i)
	//{
	//	Text_FreeText(&data->GuideLine[i]);
	//}
	Text_FreeText(&data->EnterText);
	SafeFree(g_Scene.Data);
}
#pragma endregion


#pragma region CreditScene
typedef struct CreditSceneData
{
	Text	EnterText;
	int32	FontSize;
	int32	RenderMode;
	TitleSceneData TitleBGM;
	Image	CreditImage;
	int32	X;
	int32	Y;
} CreditSceneData;

void init_credit(void)
{
	g_Scene.Data = malloc(sizeof(CreditSceneData));
	memset(g_Scene.Data, 0, sizeof(CreditSceneData));

	CreditSceneData* data = (CreditSceneData*)g_Scene.Data;

	data->FontSize = 48;
	Text_CreateText(&data->EnterText, "chosun.ttf", data->FontSize, L"--- PRESS THE ENTER ---", 24);

	data->RenderMode = SOLID;

	Image_LoadImage(&data->CreditImage, "credit.jpg");
	data->X = 0;
	data->Y = 0;

}


void update_credit(void)
{
	CreditSceneData* data = (CreditSceneData*)g_Scene.Data;

	if (Input_GetKeyDown(VK_RETURN))
	{
		Scene_SetNextScene(SCENE_INTRO);
		Audio_Stop();
	}
}

void render_credit(void)
{
	CreditSceneData* data = (CreditSceneData*)g_Scene.Data;
	Renderer_DrawImage(&data->CreditImage, data->X, data->Y);
	static float elapsedTime = 0;

	static bool isShow = true;
	elapsedTime += Timer_GetDeltaTime();
	if (elapsedTime >= 1.0f)
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->EnterText, WINDOW_WIDTH / 2 - (data->EnterText.Length * data->FontSize) / 4, 900, color);

		if (elapsedTime >= 2.0f)
		{
			elapsedTime = 0.0f;
		}
	}

}

void release_credit(void)
{
	CreditSceneData* data = (CreditSceneData*)g_Scene.Data;

	Text_FreeText(&data->EnterText);
	Audio_FreeMusic(&data->TitleBGM);

	
	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region Intro

const wchar_t* intro1str[] = {
	L"한차례 퍼진 '좀비 병'의 유행으로 국가 멸망위기 까지 갔던 대한민국은, ",
	L"선진국들의 도움으로 '좀비 바이러스'를 퇴치하고 국가 정상화에 돌입했다.",
	L" ",
	L"더 이상의 '좀비병'으로 인한 나라의 멸망을 두고 볼 수 없던 대통령은",
	L" 대통령 산하 TF팀 <행복 연구소> 를 설립했다.",
};
const wchar_t* intro2str[] = {
	L"대통령 산하 TF팀 <행복 연구소> 에서는 ",
	L"국민 여러분의 행복과 안보를 책임질 여러 연구를 하고 있습니다.",
	L" ",
	L"여러분들의 건강과 행복을",
	L"질병과 바이러스로부터지켜드리기 위하여",
	L" ",
	L"<행복 연구소> 는 정부 기관 아래 최첨단 연구 장비와 지식을 겸비하여",
	L"꾸준한 연구 및 개발을 진행하고 있습니다.",
};
const wchar_t* intro3str[] = {
	L"하지만 사실, 이 <행복 연구소> 는",
	L"<좀비 바이러스를 이용한 대량 살상 무기>를 개발하는 곳이었고,  ",
	L"거기서 과학계에서 금지된 인간의 염색체를 ",
	L"이용한 지능 쥐 실험을 하고 있었다. 물론, 극비 사항이었다.",
	L" ",
	L"인간의 염색체와 뇌세포를 이식하여 지능을 높이고 ",
	L"최첨단 연구 장비와 지식을 겸비하여 ",
	L"꾸준한 연구 및 개발을 진행하고 있습니다. ",
};
const wchar_t* intro4str[] = {
	L"이 사실이 밝혀지면 안되는 정부는, \"좀비 바이러스\" 라고  ",
	L"질병 코드 000 제로 로 명명하고 전파 주의보를 내렸다.",
	L" ",
	L"<행복 연구소>에 '좀비 바이러스 의심자'를 신고하면,",
	L"포상금도 주기로 하였다. ",
	L"'좀비 바이러스 의심자'는 좀비화가 진행되는 상태이며 ",
	L"완전한 좀비는 아니기 때문에 ",
	L"<행복 연구소>로 가서 치료를 하면",
	L"'완전한 인간화'로 완치가 가능하다고 선전 하였다.",
	L" ",
	L"그렇기 때문에 모든 시민들은 \"좀비 바이러스\"  증상을 보이는 사람들을",
	L"국가에 신고하여 포상금을 받았다.",
};
const wchar_t* intro5str[] = {
	L"하지만 '좀비 바이러스 의심자' 괴담은 ",
	L"유투버 렉카 등을 통해 유투브에 퍼졌고, 그 내용은 이러했다.",
	L" ",
	L"1) '좀비 바이러스 의심자' 들이",
	L"<행복 연구소>를 들어가 나온 것을 본 사람이 없다. ",
	L"2) 실제 '좀비 바이러스 의심자'들은 연구에 쓰인다.",
	L"3) 가족들에게 이 사실을 발설 시 금액을 다시 회수한다는 조건으로",
	L"몇 십억 대의 금액을 주며동의서는 받아간다.",
	L" ",
	L"는 괴담이었다.",
};
const wchar_t* intro6str[] = {
	L"이 '지능 쥐'는 큰 부작용이 있었는데,",
	L"연구소 직원들이 '지능 쥐' 실험을 할 때마다 ",
	L" ",
	L"뇌파 반응을 보기 위하여 연구실에 ",
	L"K-POP 노래를 계속 틀고 연구를 진행했고,",
	L"그 영향으로 이 '지능 쥐'는 때때로",
	L"K-POP 노래에 맞춰 춤을 추는 것이다.",
	L" ",
	L"이 쥐에 물리면, 물린 사람도 좀비화가 진행되며",
	L"가끔 춤을 추고 싶은 욕구에 휘말리게 될 가능성도 있다고 한다.",
};


typedef struct IntroSceneData
{
	Text	Inro1Line[5];
	Text	Inro2Line[8];
	Text	Inro3Line[8];
	Text	Inro4Line[12];
	Text	Inro5Line[10];
	Text	Inro6Line[10];
	int32	FontSize;
	int32	RenderMode;
	Image	Intro1Image;
	int32	X;
	int32	Y;
	Image	Intro2Image;
	Music	IntroBGM;
	float   Volume;

} IntroSceneData;
#define TextFont "GmarketSansTTFBold.ttf"
void init_intro(void)
{
	g_Scene.Data = malloc(sizeof(IntroSceneData));
	memset(g_Scene.Data, 0, sizeof(IntroSceneData));

	IntroSceneData* data = (IntroSceneData*)g_Scene.Data;
	
	for (int32 i = 0; i < 5; ++i)
	{
		
		Text_CreateText(&data->Inro1Line[i], TextFont, 25, intro1str[i], wcslen(intro1str[i]));
	}
	for (int32 i = 0; i < 8; ++i)
	{
		Text_CreateText(&data->Inro2Line[i], TextFont, 25, intro2str[i], wcslen(intro2str[i]));
	}
	for (int32 i = 0; i < 8; ++i)
	{
		Text_CreateText(&data->Inro3Line[i], TextFont, 25, intro3str[i], wcslen(intro3str[i]));
	}
	for (int32 i = 0; i < 12; ++i)
	{
		Text_CreateText(&data->Inro4Line[i], TextFont, 25, intro4str[i], wcslen(intro4str[i]));
	}
	for (int32 i = 0; i < 10; ++i)
	{
		Text_CreateText(&data->Inro5Line[i], TextFont, 25, intro5str[i], wcslen(intro5str[i]));
	}
	for (int32 i = 0; i < 10; ++i)
	{
		Text_CreateText(&data->Inro6Line[i], TextFont, 25, intro6str[i], wcslen(intro6str[i]));
	}
	
	
	data->RenderMode = SOLID;

	Image_LoadImage(&data->Intro1Image, "Intro-1.jpg");
	Image_LoadImage(&data->Intro2Image, "Intro-2.jpg");
	data->X = 0;
	data->Y = 0;

	Audio_LoadMusic(&data->IntroBGM, "HappyLab.mp3");

	Audio_PlayFadeIn(&data->IntroBGM, INFINITY_LOOP, 3000);

	data->Volume = 1.0f;

}
int count = 1;
void update_intro(void)
{
	if (Input_GetKeyDown(VK_RETURN))
	{
		count++;
		if (count == 7)
		{
			Scene_SetNextScene(SCENE_MAIN);
		}
	}
	
}
#define INTRO_X 430
void render_intro(void)
{
	IntroSceneData* data = (IntroSceneData*)g_Scene.Data;
	Renderer_DrawImage(&data->Intro1Image, data->X, data->Y);
	if (count >= 4)
	{
		Renderer_DrawImage(&data->Intro2Image, data->X, data->Y);
	}
	SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
	
	if (count == 1)
	{
		for (int32 i = 0; i < 5; ++i)
		{
			//Text_SetFontStyle(&data->Inro1Line[i], FS_BOLD);
			Renderer_DrawTextSolid(&data->Inro1Line[i], INTRO_X, 220 + (50 * i), color);
		}
	}
	if (count == 2)
	{
		for (int32 i = 0; i < 8; ++i)
		{
			//Text_SetFontStyle(&data->Inro2Line[i], FS_BOLD);
			Renderer_DrawTextSolid(&data->Inro2Line[i], INTRO_X, 220 + (50 * i), color);
		}
	}
	if (count == 3)
	{
		for (int32 i = 0; i < 8; ++i)
		{
			//Text_SetFontStyle(&data->Inro3Line[i], FS_BOLD);
			Renderer_DrawTextSolid(&data->Inro3Line[i], INTRO_X, 220 + (50 * i), color);
		}
	}
	if (count == 4)
	{
		for (int32 i = 0; i < 12; ++i)
		{
			//Text_SetFontStyle(&data->Inro4Line[i], FS_BOLD);
			Renderer_DrawTextSolid(&data->Inro4Line[i], INTRO_X, 220 + (50 * i), color);
		}
	}
	if (count == 5)
	{
		for (int32 i = 0; i < 10; ++i)
		{
			//Text_SetFontStyle(&data->Inro5Line[i], FS_BOLD);
			Renderer_DrawTextSolid(&data->Inro5Line[i], INTRO_X, 220 + (50 * i), color);
		}
	}
	if (count == 6)
	{
		for (int32 i = 0; i < 10; ++i)
		{
			//Text_SetFontStyle(&data->Inro6Line[i], FS_BOLD);
			Renderer_DrawTextSolid(&data->Inro6Line[i], INTRO_X, 220 + (50 * i), color);
		}
	}


	
}

void release_intro(void)
{
	IntroSceneData* data = (IntroSceneData*)g_Scene.Data;
	for (int32 i = 0; i < 5; ++i)
	{
		Text_FreeText(&data->Inro1Line[i]);
	}
	for (int32 i = 0; i < 8; ++i)
	{
		Text_FreeText(&data->Inro2Line[i]);
	}
	for (int32 i = 0; i < 8; ++i)
	{
		Text_FreeText(&data->Inro3Line[i]);
	}
	for (int32 i = 0; i < 12; ++i)
	{
		Text_FreeText(&data->Inro4Line[i]);
	}
	for (int32 i = 0; i < 10; ++i)
	{
		Text_FreeText(&data->Inro5Line[i]);
	}
	for (int32 i = 0; i < 10; ++i)
	{
		Text_FreeText(&data->Inro6Line[i]);
	}

	Audio_FreeMusic(&data->IntroBGM);
	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region MainScene
const wchar_t* str2[] = {
	L"여기서는 사운드와 이미지 블렌딩에 대해서 알아봅시다.",
	L"화살표키로 이미지를 이동시킬 수 있습니다.",
	L"E키를 누르면 이펙트를 재생시킬 수 있습니다. 이펙트 소리가 작으니 볼륨을 낮춘 후 진행하세요.",
	L"M키로 음악을 끄거나 켤 수 있습니다.",
	L"P키로 음악을 멈추거나 재개할 수 있습니다.",
	L"1번과 2번으로 볼륨을 조절할 수 있습니다.",
	L"WASD로 이미지의 스케일을 조정할 수 있습니다.",
	L"KL키로 이미지의 투명도를 조절할 수 있습니다."
};

#define GUIDELINE_COUNT 8

typedef struct MainSceneData
{
	Text		GuideLine[GUIDELINE_COUNT];
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

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 16, str2[i], wcslen(str2[i]));
	}
	
	Image_LoadImage(&data->BackGround, "background.jfif");

	Audio_LoadMusic(&data->BGM, "powerful.mp3");
	Audio_HookMusicFinished(logOnFinished);
	Audio_LoadSoundEffect(&data->Effect, "effect2.wav");
	Audio_HookSoundEffectFinished(log2OnFinished);
	Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);

	data->Volume = 1.0f;

	data->Speed = 400.0f;
	data->X = 400;
	data->Y = 400;
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

	if (Input_GetKeyDown('P'))
	{
		if (Audio_IsMusicPaused())
		{
			Audio_Resume();
		}
		else
		{
			Audio_Pause();
		}
	}

	if (Input_GetKey('1'))
	{
		data->Volume -= 0.01f;
		Audio_SetVolume(data->Volume);
	}

	if (Input_GetKey('2'))
	{
		data->Volume += 0.01f;
		Audio_SetVolume(data->Volume);
	}

	if (Input_GetKey(VK_DOWN))
	{
		data->Y += data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_UP))
	{
		data->Y -= data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_LEFT))
	{
		data->X -= data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_RIGHT))
	{
		data->X += data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey('W'))
	{
		data->BackGround.ScaleY -= 0.05f;
	}

	if (Input_GetKey('S'))
	{
		data->BackGround.ScaleY += 0.05f;
	}

	if (Input_GetKey('A'))
	{
		data->BackGround.ScaleX -= 0.05f;
	}

	if (Input_GetKey('D'))
	{
		data->BackGround.ScaleX += 0.05f;
	}

	if (Input_GetKey('K'))
	{
		data->Alpha = Clamp(0, data->Alpha - 1, 255);
		Image_SetAlphaValue(&data->BackGround, data->Alpha);
	}

	if (Input_GetKey('L'))
	{
		data->Alpha = Clamp(0, data->Alpha + 1, 255);
		Image_SetAlphaValue(&data->BackGround, data->Alpha);
	}
}

void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 10, 20 * i, color);
	}

	Renderer_DrawImage(&data->BackGround, data->X, data->Y);
}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Audio_FreeMusic(&data->BGM);
	Audio_FreeSoundEffect(&data->Effect);

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
	case SCENE_CREDIT:
		g_Scene.Init = init_credit;
		g_Scene.Update = update_credit;
		g_Scene.Render = render_credit;
		g_Scene.Release = release_credit;
		break;
	case SCENE_INTRO:
		g_Scene.Init = init_intro;
		g_Scene.Update = update_intro;
		g_Scene.Render = render_intro;
		g_Scene.Release = release_intro;
		break;
	case SCENE_MAIN:
		g_Scene.Init = init_main;
		g_Scene.Update = update_main;
		g_Scene.Render = render_main;
		g_Scene.Release = release_main;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;




}