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
//	//L"BŰ�� ������ ��Ʈ�� ���� ���մϴ�.",
//	//L"IŰ�� ������ ��Ʈ�� ���Ÿ�ü�� ���մϴ�.",
//	//L"UŰ�� ������ �ؽ�Ʈ�� ������ ����ϴ�.",
//	//L"SŰ�� ������ �ؽ�Ʈ�� ��Ҽ��� ����ϴ�.",
//	//L"NŰ�� ������ �ٽ� ������� ���ƿɴϴ�.",
//	//L"CŰ�� ������ ���� ��尡 �ٲ�ϴ�. (Solid -> Shaded -> Blended)",
//	//L"1Ű�� ������ �ؽ�Ʈ�� �۾����ϴ�.",
//	//L"2Ű�� ������ �ؽ�Ʈ�� Ŀ���ϴ�.",
//	//L"�����̽� Ű�� ������ ���� ������ �Ѿ�ϴ�."
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
	L"������ ���� '���� ��'�� �������� ���� ������� ���� ���� ���ѹα���, ",
	L"���������� �������� '���� ���̷���'�� ��ġ�ϰ� ���� ����ȭ�� �����ߴ�.",
	L" ",
	L"�� �̻��� '����'���� ���� ������ ����� �ΰ� �� �� ���� �������",
	L" ����� ���� TF�� <�ູ ������> �� �����ߴ�.",
};
const wchar_t* intro2str[] = {
	L"����� ���� TF�� <�ູ ������> ������ ",
	L"���� �������� �ູ�� �Ⱥ��� å���� ���� ������ �ϰ� �ֽ��ϴ�.",
	L" ",
	L"�����е��� �ǰ��� �ູ��",
	L"������ ���̷����κ������ѵ帮�� ���Ͽ�",
	L" ",
	L"<�ູ ������> �� ���� ��� �Ʒ� ��÷�� ���� ���� ������ ����Ͽ�",
	L"������ ���� �� ������ �����ϰ� �ֽ��ϴ�.",
};
const wchar_t* intro3str[] = {
	L"������ ���, �� <�ູ ������> ��",
	L"<���� ���̷����� �̿��� �뷮 ��� ����>�� �����ϴ� ���̾���,  ",
	L"�ű⼭ ���а迡�� ������ �ΰ��� ����ü�� ",
	L"�̿��� ���� �� ������ �ϰ� �־���. ����, �غ� �����̾���.",
	L" ",
	L"�ΰ��� ����ü�� �������� �̽��Ͽ� ������ ���̰� ",
	L"��÷�� ���� ���� ������ ����Ͽ� ",
	L"������ ���� �� ������ �����ϰ� �ֽ��ϴ�. ",
};
const wchar_t* intro4str[] = {
	L"�� ����� �������� �ȵǴ� ���δ�, \"���� ���̷���\" ���  ",
	L"���� �ڵ� 000 ���� �� ����ϰ� ���� ���Ǻ��� ���ȴ�.",
	L" ",
	L"<�ູ ������>�� '���� ���̷��� �ǽ���'�� �Ű��ϸ�,",
	L"����ݵ� �ֱ�� �Ͽ���. ",
	L"'���� ���̷��� �ǽ���'�� ����ȭ�� ����Ǵ� �����̸� ",
	L"������ ����� �ƴϱ� ������ ",
	L"<�ູ ������>�� ���� ġ�Ḧ �ϸ�",
	L"'������ �ΰ�ȭ'�� ��ġ�� �����ϴٰ� ���� �Ͽ���.",
	L" ",
	L"�׷��� ������ ��� �ùε��� \"���� ���̷���\"  ������ ���̴� �������",
	L"������ �Ű��Ͽ� ������� �޾Ҵ�.",
};
const wchar_t* intro5str[] = {
	L"������ '���� ���̷��� �ǽ���' ������ ",
	L"������ ��ī ���� ���� �����꿡 ������, �� ������ �̷��ߴ�.",
	L" ",
	L"1) '���� ���̷��� �ǽ���' ����",
	L"<�ູ ������>�� �� ���� ���� �� ����� ����. ",
	L"2) ���� '���� ���̷��� �ǽ���'���� ������ ���δ�.",
	L"3) �����鿡�� �� ����� �߼� �� �ݾ��� �ٽ� ȸ���Ѵٴ� ��������",
	L"�� �ʾ� ���� �ݾ��� �ָ絿�Ǽ��� �޾ư���.",
	L" ",
	L"�� �����̾���.",
};
const wchar_t* intro6str[] = {
	L"�� '���� ��'�� ū ���ۿ��� �־��µ�,",
	L"������ �������� '���� ��' ������ �� ������ ",
	L" ",
	L"���� ������ ���� ���Ͽ� �����ǿ� ",
	L"K-POP �뷡�� ��� Ʋ�� ������ �����߰�,",
	L"�� �������� �� '���� ��'�� ������",
	L"K-POP �뷡�� ���� ���� �ߴ� ���̴�.",
	L" ",
	L"�� �㿡 ������, ���� ����� ����ȭ�� ����Ǹ�",
	L"���� ���� �߰� ���� �屸�� �ָ����� �� ���ɼ��� �ִٰ� �Ѵ�.",
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
	L"���⼭�� ����� �̹��� ������ ���ؼ� �˾ƺ��ô�.",
	L"ȭ��ǥŰ�� �̹����� �̵���ų �� �ֽ��ϴ�.",
	L"EŰ�� ������ ����Ʈ�� �����ų �� �ֽ��ϴ�. ����Ʈ �Ҹ��� ������ ������ ���� �� �����ϼ���.",
	L"MŰ�� ������ ���ų� �� �� �ֽ��ϴ�.",
	L"PŰ�� ������ ���߰ų� �簳�� �� �ֽ��ϴ�.",
	L"1���� 2������ ������ ������ �� �ֽ��ϴ�.",
	L"WASD�� �̹����� �������� ������ �� �ֽ��ϴ�.",
	L"KLŰ�� �̹����� ������ ������ �� �ֽ��ϴ�."
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