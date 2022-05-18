#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;
/*
#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

const wchar_t* str[] = {
	L"����� Ÿ��Ʋ���Դϴ�. �ؽ�Ʈ�� ���õ� ���������� �׽�Ʈ�غ��ô�.",
	L"BŰ�� ������ ��Ʈ�� ���� ���մϴ�.",
	L"IŰ�� ������ ��Ʈ�� ���Ÿ�ü�� ���մϴ�.",
	L"UŰ�� ������ �ؽ�Ʈ�� ������ ����ϴ�.",
	L"SŰ�� ������ �ؽ�Ʈ�� ��Ҽ��� ����ϴ�.",
	L"NŰ�� ������ �ٽ� ������� ���ƿɴϴ�.",
	L"CŰ�� ������ ���� ��尡 �ٲ�ϴ�. (Solid -> Shaded -> Blended)",
	L"1Ű�� ������ �ؽ�Ʈ�� �۾����ϴ�.",
	L"2Ű�� ������ �ؽ�Ʈ�� Ŀ���ϴ�.",
	L"�����̽� Ű�� ������ ���� ������ �Ѿ�ϴ�.",
};

typedef struct TitleSceneData
{
	Text	GuideLine[10];
	Text	TestText;
	int32	FontSize;
	int32	RenderMode;
	Image	TestImage;
} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	for (int32 i = 0; i < 10; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 16, str[i], wcslen(str[i]));
	}

	data->FontSize = 24;
	Text_CreateText(&data->TestText, "d2coding.ttf", data->FontSize, L"�� �ؽ�Ʈ�� ���մϴ�.", 13);

	data->RenderMode = SOLID;

	Image_LoadImage(&data->TestImage, "Background.jfif");
}

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	if (Input_GetKeyDown('B'))
	{
		Text_SetFontStyle(&data->TestText, FS_BOLD);
	}

	if (Input_GetKeyDown('I'))
	{
		Text_SetFontStyle(&data->TestText, FS_ITALIC);
	}

	if (Input_GetKeyDown('U'))
	{
		Text_SetFontStyle(&data->TestText, FS_UNDERLINE);
	}

	if (Input_GetKeyDown('S'))
	{
		Text_SetFontStyle(&data->TestText, FS_STRIKETHROUGH);
	}

	if (Input_GetKeyDown('N'))
	{
		Text_SetFontStyle(&data->TestText, FS_NORMAL);
	}

	if (Input_GetKeyDown('C'))
	{
		data->RenderMode = (data->RenderMode + 1) % 3;
	}

	if (Input_GetKey('1'))
	{
		--data->FontSize;
		Text_SetFont(&data->TestText, "d2coding.ttf", data->FontSize);
	}

	if (Input_GetKey('2'))
	{
		++data->FontSize;
		Text_SetFont(&data->TestText, "d2coding.ttf", data->FontSize);
	}

	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_MAIN);
	}
}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	for (int32 i = 0; i < 10; ++i)
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 10, 20 * i, color);
	}
	
	switch (data->RenderMode)
	{
	case SOLID:
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->TestText, 400, 400, color);
	}
	break;
	case SHADED:
	{
		SDL_Color bg = { .a = 255 };
		SDL_Color fg = { .r = 255, .g = 255, .a = 255 };
		Renderer_DrawTextShaded(&data->TestText, 400, 400, fg, bg);
	}
	break;
	case BLENDED:
	{
		Renderer_DrawImage(&data->TestImage, 400, 400);
		SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
		Renderer_DrawTextBlended(&data->TestText, 400, 400, color);
	}
	break;
	}
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	for (int32 i = 0; i < 10; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Text_FreeText(&data->TestText);

	Image_FreeImage(&data->TestImage);

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

	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_START);
	}
}

void render_main(void)
{

	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		SDL_Color color = { .a = 0 };
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

	Image_FreeImage(&data->BackGround);

	SafeFree(g_Scene.Data);
}
#pragma endregion
*/

#pragma region MainScreen
typedef struct MainScreenData
{
	Text	RoadingText[3];
	Text	Recording;
	Text	Date;
	Text	Rocation;
	Text	Infomation;
	Text	RoadConform[4];
	Text	BioLink[3];
	Text	BrainLink;
	int32	RoadingCheck;
	int32	ConformCheck;
	int32	BioLinkCheck;
	int32	NextText;
	bool	isNext;
} MainScreenData;

void init_MainScreen(void)
{
	g_Scene.Data = malloc(sizeof(MainScreenData));
	memset(g_Scene.Data, 0, sizeof(MainScreenData));
	MainScreenData* data = (MainScreenData*)g_Scene.Data;

	Text_CreateText(&data->RoadingText[0], "12LotteMartHappyLight.ttf", 18, L"���̿� Ĩ�� �ε���.", wcslen(L"���̿� Ĩ�� �ε���."));
	Text_CreateText(&data->RoadingText[1], "12LotteMartHappyLight.ttf", 18, L"���̿� Ĩ�� �ε���..", wcslen(L"���̿� Ĩ�� �ε���.."));
	Text_CreateText(&data->RoadingText[2], "12LotteMartHappyLight.ttf", 18, L"���̿� Ĩ�� �ε���...", wcslen(L"���̿� Ĩ�� �ε���..."));
	Text_CreateText(&data->Recording, "12LotteMartHappyLight.ttf", 18, L"����� - [Ÿī�� ��]", wcslen(L"����� - [Ÿī�� ��]"));
	Text_CreateText(&data->Date, "12LotteMartHappyLight.ttf", 18, L"2067�� 8 �� 12 ��", wcslen(L"2067�� 8 �� 12 ��"));
	Text_CreateText(&data->Rocation, "12LotteMartHappyLight.ttf", 18, L"��ġ ��ǥ - [���� , ����]", wcslen(L"��ġ ��ǥ - [���� , �Ϻ�]"));
	Text_CreateText(&data->Infomation, "12LotteMartHappyLight.ttf", 18, L"�� Ĩ���� �������� ���� ������������� ��ġ��Ϲ� �Դϴ�-", wcslen(L"�� Ĩ���� �������� ���� ������������� ��ġ��Ϲ� �Դϴ�-"));
	Text_CreateText(&data->RoadConform[0], "12LotteMartHappyLight.ttf", 18, L"�ε� ������ -", wcslen(L"�ε� ������ -"));
	Text_CreateText(&data->RoadConform[1], "12LotteMartHappyLight.ttf", 18, L"�ε� ������ --", wcslen(L"�ε� ������ --"));
	Text_CreateText(&data->RoadConform[2], "12LotteMartHappyLight.ttf", 18, L"�ε� ������ ---", wcslen(L"�ε� ������ ---"));
	Text_CreateText(&data->RoadConform[3], "12LotteMartHappyLight.ttf", 18, L"�ε� ������ ----", wcslen(L"�ε� ������ ----"));
	Text_CreateText(&data->BioLink[0], "12LotteMartHappyLight.ttf", 18, L"���̿� ��ũ �Ϸ�.", wcslen(L"���̿� ��ũ �Ϸ�."));
	Text_CreateText(&data->BioLink[1], "12LotteMartHappyLight.ttf", 18, L"���̿� ��ũ �Ϸ�..", wcslen(L"���̿� ��ũ �Ϸ�.."));
	Text_CreateText(&data->BioLink[2], "12LotteMartHappyLight.ttf", 18, L"���̿� ��ũ �Ϸ�...", wcslen(L"���̿� ��ũ �Ϸ�..."));
	Text_CreateText(&data->BrainLink, "12LotteMartHappyLight.ttf", 18, L"��� ���� ��ũ Ȯ��", wcslen(L"��� ���� ��ũ Ȯ��"));
	data->BioLinkCheck = 0;
	data->ConformCheck = 1;
	data->RoadingCheck = 1;
	data->NextText = 0;
	data->isNext = false;
}

void update_MainScreen(void)
{
	MainScreenData* data = (MainScreenData*)g_Scene.Data;

	static float elapsedTime;
	static float gotoNextScene;
	elapsedTime += Timer_GetDeltaTime();

	if (elapsedTime >= 0.65f)
	{
		if (data->RoadingCheck < 3)
		{
			data->RoadingCheck++;
		}
		else if (data->NextText == 5 && data->RoadingCheck == 3 && data->ConformCheck < 4)
		{
			data->ConformCheck++;
		}
		else if (data->NextText == 6 && data->ConformCheck == 4 && data->BioLinkCheck < 3)
		{
			data->BioLinkCheck++;
		}
		if (data->isNext)
		{
			data->NextText++;
			data->isNext = false;
		}
		elapsedTime = 0;
	}
	if (data->NextText == 8)
	{
		gotoNextScene += Timer_GetDeltaTime();
		if (gotoNextScene >= 3.0f)
		{
			Scene_SetNextScene(SCENE_START);
		}
	}
}

void render_MainScreen(void)
{
	SDL_Color color = { .r = 255,.b = 255,.g = 255 };
	MainScreenData* data = (MainScreenData*)g_Scene.Data;
	for (int32 i = 0; i < data->RoadingCheck; i++)
	{
		Renderer_DrawTextSolid(&data->RoadingText[i], 30, 30, color);
	}
	if (data->RoadingCheck == 3)
	{
		data->isNext = true;
	}
	if (data->NextText > 0)
	{
		Renderer_DrawTextSolid(&data->Recording, 30, 70, color);
		if (data->NextText == 1)
		{
			data->isNext = true;
		}
	}
	if (data->NextText > 1)
	{
		Renderer_DrawTextSolid(&data->Date, 700, 340, color);
		if (data->NextText == 2)
		{
			data->isNext = true;
		}
	}
	if (data->NextText > 2)
	{
		Renderer_DrawTextSolid(&data->Rocation, 660, 370, color);
		if (data->NextText == 3)
		{
			data->isNext = true;
		}
	}
	if (data->NextText > 3)
	{
		Renderer_DrawTextSolid(&data->Infomation, 50, 400, color);
		if (data->NextText == 4)
		{
			data->isNext = true;
		}
	}
	if (data->NextText > 4)
	{
		for (int32 i = 0; i < data->ConformCheck; i++)
		{
			Renderer_DrawTextSolid(&data->RoadConform[i], 60, 520, color);
			
		}
		if (data->NextText == 5 && data->ConformCheck == 4)
		{
			data->isNext = true;
		}
	}
	if (data->NextText > 5)
	{
		for (int32 i = 0; i < data->BioLinkCheck; i++)
		{
			Renderer_DrawTextSolid(&data->BioLink[i], 800, 600, color);
		}
		if (data->NextText == 6 && data->ConformCheck == 3)
		{
			data->isNext = true;
		}
	}
	if (data->NextText > 6)
	{
		Renderer_DrawTextSolid(&data->BrainLink, 1020, 600, color);
		if (data->NextText == 7)
		{
			data->isNext = true;
		}
	}
}

void release_MainScreen(void)
{
	MainScreenData* data = (MainScreenData*)g_Scene.Data;

	for (int32 i = 0; i < 3; i++)
	{
		Text_FreeText(&data->RoadingText[i]);
		Text_FreeText(&data->BioLink[i]);
		Text_FreeText(&data->RoadConform[i]);
	}
	Text_FreeText(&data->RoadConform[3]);
	Text_FreeText(&data->Recording);
	Text_FreeText(&data->Date);
	Text_FreeText(&data->Rocation);
	Text_FreeText(&data->Infomation);
	Text_FreeText(&data->BrainLink);

	SafeFree(g_Scene.Data);
}

#pragma endregion

#pragma region StartScene
const wchar_t* starttext[] = {
	L"�����õ� �����߾�.��",
	L"������, ����ģ���� ��Ҹ���-",
	L"�� ���� ���� ����ģ���� �ΰ� ���� �̾߱�����.",
	L"�繫�� ���ᰡ ���� � 10��, ���� ������ �׳� ���� �������̴�.",
	L"���� ������ ���� �����ΰ�, �� ���� �̾߱��.",
	L"\"������ �ƹ��͵� �ϱ�ȳ�.\"",
	L"�������� �� �ϰ� �;���?��",
	L"\"������ �� �ϰ� ���� ����..\"",
	L"����� ������ ����û �� ������ �ٻڴٸ�.��",
	L"\"�׷� ���ϵ� �ϱ� �Ȱڳ�.\"",
	L"�ǹ̾��� �̾߱��� �ݺ�, �Ӹ����� �̾߱��.."
};

typedef struct StartSceneData
{
	Text		GuideLine[11];
	Image		BackGround;
	int32		check;
} StartSceneData;

void init_Start(void)
{
	g_Scene.Data = malloc(sizeof(StartSceneData));
	memset(g_Scene.Data, 0, sizeof(StartSceneData));
	StartSceneData* data = (StartSceneData*)g_Scene.Data;

	for (int32 i = 0; i < 11; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "GmarketSansTTFLight.ttf", 18, starttext[i], wcslen(starttext[i]));
	}
	Image_LoadImage(&data->BackGround, "S_01.png");
	data->check = 0;
}

void update_Start(void)
{
	StartSceneData* data = (StartSceneData*)g_Scene.Data;

	static float elapsedTime;
	elapsedTime += Timer_GetDeltaTime();

	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_SCENEONE);
	}

	if (elapsedTime >= 0.85f)
	{
		if (data->check < 11)
		{
			data->check++;
		}
		elapsedTime = 0;
	}
}

void render_Start(void)
{
	StartSceneData* data = (StartSceneData*)g_Scene.Data;
	Renderer_DrawImage(&data->BackGround, 0, 0);

	for (int32 i = 0; i < data->check; i++)
	{
		SDL_Color color = { .r = 255,.b = 255,.g = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 725, 15 + (42 * i), color);
	}
}

void release_Start(void)
{
	StartSceneData* data = (StartSceneData*)g_Scene.Data;

	for (int32 i = 0; i < 11; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region SceneOne
const wchar_t* onetext[] = {
	L"�����������۷��� ��������, 2�� ���Ͼ� �°��忡 �����մϴ�.��",
	L"�층�층�층�층-",
	L"\"���Ϻ��� ��ĥ�� �� �� ���� �����ϱ� ���� ���� ����\"",
	L"�����ϴ� �����븦 ���� �ǵ�� ���� ���̴��.",
	L"������û�� ���� ���̱淡.��",
	L"\"���� ����ȣ ������ �������� �����ؼ� ���̾�. ��а��� ���� �� ����.\"",
	L"�������� ���ϰ�?��",
	L"\"�� ����� ������ �� ��. �̹� ����� ¥�� ġ�� ���� ���� �ְ���.\"",
	L"���׷�����...��",
	L"\"���� �����ڴ�. �̸� ������. �� ���� �� ���� �� ����?\"",
	L"����.��",
	L"���� ǥ���� �׳ฦ �޷��� ��� ����Ȱ� �ż��� ������ �ö�����.",
	L"â�� �ʸ� �� �ִ� �׳࿡�� ���� ���� �ǰ����� ��� ���� ǫ���� ��Ʈ�� �Ĺ�����.",
	L"�� ���� ���� ���� ��ٸ��� ������ �޿��� �� ä �� ���� �ῡ ������."
};

typedef struct SceneOneData
{
	Text	GuideLine[14];
	Image	BackGround;
	int32	check;
} SceneOneData;
void init_SceneOne(void)
{
	g_Scene.Data = malloc(sizeof(SceneOneData));
	memset(g_Scene.Data, 0, sizeof(SceneOneData));
	SceneOneData* data = (SceneOneData*)g_Scene.Data;

	for (int32 i = 0; i < 14; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "GmarketSansTTFLight.ttf", 18, onetext[i], wcslen(onetext[i]));
	}
	Image_LoadImage(&data->BackGround, "S_02.png");
}

void update_SceneOne(void)
{
	SceneOneData* data = (SceneOneData*)g_Scene.Data;

	static float elapsedTime;
	elapsedTime += Timer_GetDeltaTime();

	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_SCENETWO);
	}

	if (elapsedTime >= 0.85f)
	{
		if (data->check < 14)
		{
			data->check++;
		}
		elapsedTime = 0;
	}
}

void render_SceneOne(void)
{
	SceneOneData* data = (SceneOneData*)g_Scene.Data;
	Renderer_DrawImage(&data->BackGround, 0, 0);
	SDL_Color color = { .r = 255,.b = 255,.g = 255 };
	for (int32 i = 0; i < data->check; i++)
	{
		Renderer_DrawTextSolid(&data->GuideLine[i], 725, 15 + (42 * i), color);
	}
}

void release_SceneOne(void)
{
	SceneOneData* data = (SceneOneData*)g_Scene.Data;

	for (int32 i = 0; i < 14; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region SceneTwo
const wchar_t* twotext[] = {
	L"���ȶȶ�.��",
	L"\"�Ͼ�... ���Ͷ�\"",
	L"�����Ӱ� ������ Ŀ�Ǹ� ���÷��� �߰Ǹ�,",
	L"������ ��ī�� �繫�ΰ� ��ġ�� ���� ��Ȳ���� �����ߴ�.",
	L"������ȣ ���࿡�� ���ڱ��� �����ϴ� ��Ȳ�� �����Ǿ����ϴ�.��",
	L"�� ���� ���ڱ�.",
	L"�� �̹� 10�� �ѵ��� ���������ϰ� �ݺ��ؿ� �Ͽ� �����Ӹ��� �� �����̿���.",
	L"����� �񸮴� ��𼭳� �־��� �� ���� �ذ��ؿ����� ������ ���� ������ ����� ������.",
	L"\"���ڱ��̶�.. �Ը�� ��������?\"",
	L"������ �������� 50�￣ �����Դϴ�.��",
	L"�ٸ� �̹��� ��밡 ����ȣ �����̿��ٴ� ��.",
	L"����ȣ ������ �츮���� �ִ� �����׷��� �ƴϴ���,",
	L"�������� ���̰� Ȯ ���� ����̿���."
};

const wchar_t* twoment1 = L"\"�׷� �Ź��� ��� ������ �����淡?\"";
const wchar_t* twoment2 = L"\"�������� ���� �Ǿ���?\"";

const wchar_t* twochoicement1 = L"\"�׷� �Ź��� ��� ������ �����淡?\"<";
const wchar_t* twochoicement2 = L"\"�������� ���� �Ǿ���?\"<";

typedef struct SceneTwoData
{
	Text	GuideLine[13];
	Text	Choice1;
	Text	Choice2;
	Image	BackGround;
	bool	isChoice1;
	int32	selectNum;
	bool	canShow;
	int32	check;
} SceneTwoData;

void init_SceneTwo(void)
{
	g_Scene.Data = malloc(sizeof(SceneTwoData));
	memset(g_Scene.Data, 0, sizeof(SceneTwoData));
	SceneTwoData* data = (SceneTwoData*)g_Scene.Data;

	for (int32 i = 0; i < 13; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "GmarketSansTTFLight.ttf", 18, twotext[i], wcslen(twotext[i]));
	}
	Text_CreateText(&data->Choice1, "GmarketSansTTFLight.ttf", 24, twochoicement1, wcslen(twochoicement1));
	Text_CreateText(&data->Choice2, "GmarketSansTTFLight.ttf", 24, twoment2, wcslen(twoment2));
	Image_LoadImage(&data->BackGround, "S_03.png");
	data->isChoice1 = true;
	data->canShow = false;
	data->selectNum = 0;
}

void update_SceneTwo(void)
{
	SceneTwoData* data = (SceneTwoData*)g_Scene.Data;

	static float elapsedTime;
	elapsedTime += Timer_GetDeltaTime();

	if (elapsedTime >= 0.85f)
	{
		if (data->check < 13)
		{
			data->check++;
		}
		if (data->check == 13)
		{
			data->canShow = true;
		}
		elapsedTime = 0;
	}

	if (Input_GetKey(VK_UP))
	{
		if (data->selectNum > 0)
		{
			Text_CreateText(&data->Choice1, "GmarketSansTTFLight.ttf", 24, twochoicement1, wcslen(twochoicement1));
			Text_CreateText(&data->Choice2, "GmarketSansTTFLight.ttf", 24, twoment2, wcslen(twoment2));
			data->selectNum--;
		}
	}

	if (Input_GetKey(VK_DOWN))
	{
		if (data->selectNum < 1)
		{
			Text_CreateText(&data->Choice1, "GmarketSansTTFLight.ttf", 24, twoment1, wcslen(twoment1));
			Text_CreateText(&data->Choice2, "GmarketSansTTFLight.ttf", 24, twochoicement2, wcslen(twochoicement2));
			data->selectNum++;
		}
	}

	if (Input_GetKeyDown(VK_RETURN))
	{
		if (data->selectNum % 2 == 0)
		{
			if (!(data->isChoice1))
			{
				data->isChoice1 = true;
			}
			Scene_SetNextScene(SCENE_SCENETHREE);
		}
		else
		{
			if (data->isChoice1)
			{
				data->isChoice1 = false;
			}
			Scene_SetNextScene(SCENE_SCENEFORE);
		}
	}
}

void render_SceneTwo(void)
{
	SceneTwoData* data = (SceneTwoData*)g_Scene.Data;
	Renderer_DrawImage(&data->BackGround, 0, 0);


	for (int32 i = 0; i < data->check; i++)
	{
		SDL_Color color = { .r = 255,.b = 255,.g = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 725, 15 + (42 * i), color);
	}

	if (data->canShow)
	{
		SDL_Color color = { .r = 255,.b = 255,.g = 255 };
		Renderer_DrawTextSolid(&data->Choice1, 5, 580, color);
		Renderer_DrawTextSolid(&data->Choice2, 5, 640, color);
	}
		
}

void release_SceneTwo(void)
{
	SceneTwoData* data = (SceneTwoData*)g_Scene.Data;

	for (int32 i = 0; i < 13; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Text_FreeText(&data->Choice1);
	Text_FreeText(&data->Choice2);
	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region SceneThree
const wchar_t* threetext[] = {
	L"\"�׷� �Ź��� ��� ������ �����淡?\"",
	L"����ĥ �� ����ȣ�� ��Ը� ������������ ���踦 ���� �ڰ� �ӽ��� ǰ��",
	L"���� ���� ��ǥ�� ���Ŀ���� ���´ٰ� �մϴ�.��",
	L"\"��û�� �ڽĵ��� �ᱹ �� �ߵ��� �����.. �׷� �����ε� �˾Ƴ°�?\"",
	L"����. ��ġ�� Ÿ�̶� ��Ÿ�ο��� �ǳ޴ٰ� �մϴ�.��",
	L"������ȣ ������ ���� ��� 50�￣�� ��ǥ�� �ٲ� ��ü������ ����Ź ������ ���ƽ��ϴ�.��.",
	L"\"...���\""
};

const wchar_t* threeforechoicement = L"\"��� Ÿ�̶� ��Ÿ�� ��� �߳�?\"<";

typedef struct SceneThreeData
{
	Text	GuideLine[7];
	Text	Choice1;
	Image	BackGround;
	bool	canShow;
	int32	check;
} SceneThreeData;

void init_SceneThree(void)
{
	g_Scene.Data = malloc(sizeof(SceneThreeData));
	memset(g_Scene.Data, 0, sizeof(SceneThreeData));
	SceneThreeData* data = (SceneThreeData*)g_Scene.Data;

	for (int32 i = 0; i < 7; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "GmarketSansTTFLight.ttf", 18, threetext[i], wcslen(threetext[i]));
	}
	Text_CreateText(&data->Choice1, "GmarketSansTTFLight.ttf", 24, threeforechoicement, wcslen(threeforechoicement));
	Image_LoadImage(&data->BackGround, "S_03.png");
	data->canShow = false;
	data->check = 0;
}

void update_SceneThree(void)
{
	SceneThreeData* data = (SceneThreeData*)g_Scene.Data;

	static float elapsedTime;
	elapsedTime += Timer_GetDeltaTime();

	if (elapsedTime >= 0.85f)
	{
		if (data->check < 7)
		{
			data->check++;
		}
		if (data->check == 7)
		{
			data->canShow = true;
		}
		elapsedTime = 0;
	}

	if (Input_GetKeyDown(VK_RETURN))
	{
		Scene_SetNextScene(SCENE_SCENEFIVE);
	}
}

void render_SceneThree(void)
{
	SceneThreeData* data = (SceneThreeData*)g_Scene.Data;
	Renderer_DrawImage(&data->BackGround, 0, 0);
	for (int32 i = 0; i < data->check; i++)
	{
		SDL_Color color = { .r = 255,.b = 255,.g = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 725, 15 + (42 * i), color);
	}
	if (data->canShow)
	{
		SDL_Color color = { .r = 255,.b = 255,.g = 255 };
		Renderer_DrawTextSolid(&data->Choice1, 5, 610, color);
	}
}

void release_SceneThree(void)
{
	SceneThreeData* data = (SceneThreeData*)g_Scene.Data;

	for (int32 i = 0; i < 7; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Text_FreeText(&data->Choice1);
	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region SceneFore
const wchar_t* foretext[] = {
	L"\"�������� ���� �Ǿ���?\"",
	L"����ġ�� Ÿ�̶� ��Ÿ�ο��� �ǳ޽��ϴ�.��",
	L"������ȣ ������ ���� ��� 50�￣�� ��ǥ�� �ٲ� ��ü������ ����Ź ������ ���ƽ��ϴ�.��",
	L"\"...���\""
};

typedef struct SceneForeData
{
	Text	GuideLine[4];
	Text	Choice1;
	Image	BackGround;
	int32	check;
	bool	canShow;
} SceneForeData;

void init_SceneFore(void)
{
	g_Scene.Data = malloc(sizeof(SceneForeData));
	memset(g_Scene.Data, 0, sizeof(SceneForeData));
	SceneForeData* data = (SceneForeData*)g_Scene.Data;

	for (int32 i = 0; i < 4; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "GmarketSansTTFLight.ttf", 18, foretext[i], wcslen(foretext[i]));
	}
	Text_CreateText(&data->Choice1, "GmarketSansTTFLight.ttf", 24, threeforechoicement, wcslen(threeforechoicement));
	Image_LoadImage(&data->BackGround, "S_03.png");
	data->canShow = false;
	data->check = 0;
}

void update_SceneFore(void)
{
	SceneForeData* data = (SceneForeData*)g_Scene.Data;

	static float elapsedTime;
	elapsedTime += Timer_GetDeltaTime();

	if (elapsedTime >= 0.85f)
	{
		if (data->check < 4)
		{
			data->check++;
		}
		if (data->check == 4)
		{
			data->canShow = true;
		}
		elapsedTime = 0;
	}

	if (Input_GetKeyDown(VK_RETURN))
	{
		Scene_SetNextScene(SCENE_SCENEFIVE);
	}
}

void render_SceneFore(void)
{
	SceneForeData* data = (SceneForeData*)g_Scene.Data;
	Renderer_DrawImage(&data->BackGround, 0, 0);
	for (int32 i = 0; i < data->check; i++)
	{
		SDL_Color color = { .r = 255,.b = 255,.g = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 725, 15 + (42 * i), color);
	}
	if (data->canShow)
	{
		SDL_Color color = { .r = 255,.b = 255,.g = 255 };
		Renderer_DrawTextSolid(&data->Choice1, 5, 610, color);
	}
}

void release_SceneFore(void)
{
	SceneForeData* data = (SceneForeData*)g_Scene.Data;

	for (int32 i = 0; i < 4; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Text_FreeText(&data->Choice1);
	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region SceneFive
const wchar_t* fivetext[] = {
	L"\"��� Ÿ�̶� ��Ÿ�ζ�� �߳�?\"",
	L"����. Ʋ�� �����ϴ�.��",
	L"���ǿ� Ÿ�̶� ��Ÿ��. �Ϻ� ���� �Ѹ��� ����Ǵ� ���� �ĺ���.",
	L"���缱�� �������� �е������� ���� ��ġ���� �Ź�.",
	L" ",
	L"�׷� Ÿ�̶� ��Ÿ�ΰ� ����ȣ ����� ��Ź�̶��...",
	L"�̵��� �� ������ �ϸ�Ÿ�� �� �� �ִ� �ϻ��ϴ��� ��ȸ �ƴϰڴ°�!",
	L"�߸� ����ȴٸ� �и� ���� ���ϰ��� �񱳵� �ȵɸ�ŭ ū ���θ� ���� �� ���� ���̴�."
};

typedef struct SceneFiveData
{
	Text	GuideLine[8];
	Image	BackGround;
	int32	check;
} SceneFiveData;

void init_SceneFive(void)
{
	g_Scene.Data = malloc(sizeof(SceneFiveData));
	memset(g_Scene.Data, 0, sizeof(SceneFiveData));
	SceneFiveData* data = (SceneFiveData*)g_Scene.Data;

	for (int32 i = 0; i < 8; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "GmarketSansTTFLight.ttf", 18, fivetext[i], wcslen(fivetext[i]));
	}
	Image_LoadImage(&data->BackGround, "S_03.png");
	data->check = 0;
}

void update_SceneFive(void)
{
	SceneFiveData* data = (SceneFiveData*)g_Scene.Data;

	static float elapsedTime;
	elapsedTime += Timer_GetDeltaTime();

	if (elapsedTime >= 0.85f)
	{
		if (data->check < 8)
		{
			data->check++;
		}
		elapsedTime = 0;
	}

	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_SCENESIX);
	}
}

void render_SceneFive(void)
{
	SceneFiveData* data = (SceneFiveData*)g_Scene.Data;
	Renderer_DrawImage(&data->BackGround, 0, 0);
	for (int32 i = 0; i < data->check; i++)
	{
		SDL_Color color = { .r = 255,.b = 255,.g = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 725, 15 + (42 * i), color);
	}
}

void release_SceneFive(void)
{
	SceneFiveData* data = (SceneFiveData*)g_Scene.Data;

	for (int32 i = 0; i < 8; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
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
		/*
	case SCENE_TITLE:
		g_Scene.Init = init_title;
		g_Scene.Update = update_title;
		g_Scene.Render = render_title;
		g_Scene.Release = release_title;
		break;
	case SCENE_MAIN:
		g_Scene.Init = init_main;
		g_Scene.Update = update_main;
		g_Scene.Render = render_main;
		g_Scene.Release = release_main;
		break;
		*/
	case SCENE_MAINSCREEN:
		g_Scene.Init = init_MainScreen;
		g_Scene.Update = update_MainScreen;
		g_Scene.Render = render_MainScreen;
		g_Scene.Release = release_MainScreen;
		break;
	case SCENE_START:
		g_Scene.Init = init_Start;
		g_Scene.Update = update_Start;
		g_Scene.Render = render_Start;
		g_Scene.Release = release_Start;
		break;
	case SCENE_SCENEONE:
		g_Scene.Init = init_SceneOne;
		g_Scene.Update = update_SceneOne;
		g_Scene.Render = render_SceneOne;
		g_Scene.Release = release_SceneOne;
		break;
	case SCENE_SCENETWO:
		g_Scene.Init = init_SceneTwo;
		g_Scene.Update = update_SceneTwo;
		g_Scene.Render = render_SceneTwo;
		g_Scene.Release = release_SceneTwo;
		break;
	case SCENE_SCENETHREE:
		g_Scene.Init = init_SceneThree;
		g_Scene.Update = update_SceneThree;
		g_Scene.Render = render_SceneThree;
		g_Scene.Release = release_SceneThree;
		break;
	case SCENE_SCENEFORE:
		g_Scene.Init = init_SceneFore;
		g_Scene.Update = update_SceneFore;
		g_Scene.Render = render_SceneFore;
		g_Scene.Release = release_SceneFore;
		break;
	case SCENE_SCENEFIVE:
		g_Scene.Init = init_SceneFive;
		g_Scene.Update = update_SceneFive;
		g_Scene.Render = render_SceneFive;
		g_Scene.Release = release_SceneFive;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}