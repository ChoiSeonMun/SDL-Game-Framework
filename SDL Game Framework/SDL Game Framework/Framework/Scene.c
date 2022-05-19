#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;
#define _MAX_SINEN_NUM 100
#include "LoadCSV.h"
#include "Csv.h"

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

const wchar_t* str[] = {
	L"여기는 타이틀씬입니다. 텍스트와 관련된 여러가지를 테스트해봅시다.",
	L"B키를 누르면 폰트가 굵게 변합니다.",
	L"I키를 누르면 폰트가 이탤릭체로 변합니다.",
	L"U키를 누르면 텍스트에 밑줄이 생깁니다.",
	L"S키를 누르면 텍스트에 취소선이 생깁니다.",
	L"N키를 누르면 다시 원래대로 돌아옵니다.",
	L"C키를 누르면 렌더 모드가 바뀝니다. (Solid -> Shaded -> Blended)",
	L"1키를 누르면 텍스트가 작아집니다.",
	L"2키를 누르면 텍스트가 커집니다.",
	L"스페이스 키를 누르면 다음 씬으로 넘어갑니다."
};

typedef struct TitleSceneData
{
	Text	GuideLine[10];
	Text	TestText;
	int32	FontSize;
	int32	RenderMode;
	Image	TestImage;
} TitleSceneData;

static SceneData scenedata[_MAX_SINEN_NUM];
const CsvFile csvFile;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));
	memset(&csvFile, 0, sizeof(CsvFile));
	//CSVInit("게임북 CSV - 시트1.csv", scenedata);
	CreateCsvFile(&csvFile,"csv최신_18일_1539.xlsx - 시트1.csv");
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	for (int32 i = 0; i < 10; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 16, str[i], wcslen(str[i]));
	}

	data->FontSize = 24;
	Text_CreateText(&data->TestText, "d2coding.ttf", data->FontSize, L"이 텍스트가 변합니다.", 13);

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

//typedef struct MainSceneData
//{
//	Text		GuideLine[GUIDELINE_COUNT];
//	Music		BGM;
//	float		Volume;
//	SoundEffect Effect;
//	Image		BackGround;
//	float		Speed;
//	int32		X;
//	int32		Y;
//	int32		Alpha;
//} MainSceneData;




void logOnFinished(void)
{
	LogInfo("You can show this log on stopped the music");
}

void log2OnFinished(int32 channel)
{
	LogInfo("You can show this log on stopped the effect");
}
typedef struct MainSceneData
{
	int32		index;
	Music		BGM;
	float		Volume;
	Image		BackGround;
	int32		BackGroundX;
	int32		BackGroundY;
	int32		imageEffect;
	int32		textTime;
	int32		temp;
	int32		text1X;
	int32		text1Y;
	Text		text1;
	int32		text2X;
	int32		text2Y;
	Text		text2[5];
	int32		text3X;
	int32		text3Y;
	Text		text3[5];
	Text		select1;
	int32		select1Value;
	Text		select2;
	int32		select2Value;
	Text		select3;
	int32		select3Value;
	int32		playerSelectValue;
} MainSceneData;

static int32 sceneNum = 3;
static int32 prevSceneNum = 1;

void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, (sizeof(MainSceneData)));
	MainSceneData* data = (MainSceneData*)g_Scene.Data;



	data->index = ParseToInt(csvFile.Items[sceneNum][0]);
	Audio_LoadMusic(&data->BGM, ParseToAscii(csvFile.Items[sceneNum][1]));
	Audio_HookMusicFinished(logOnFinished);
	Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);
	Image_LoadImage(&data->BackGround, ParseToAscii(csvFile.Items[sceneNum][2]));
	data->select1Value = ParseToInt(csvFile.Items[sceneNum][13]);
	data->select2Value = ParseToInt(csvFile.Items[sceneNum][15]);
	data->select3Value = ParseToInt(csvFile.Items[sceneNum][17]);
	Text_LoadText(&data->text1, ParseToAscii(csvFile.Items[sceneNum][9]));
	Text_LoadText(&data->text2, ParseToAscii(csvFile.Items[sceneNum][10]));
	Text_LoadText(&data->text3, ParseToAscii(csvFile.Items[sceneNum][11]));

	data->Volume = 1.0f;
	
	data->BackGroundX = 0;
	data->BackGroundY = 0;
	data->playerSelectValue = 1;
	
}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

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
	
	if (Input_GetKeyDown('1'))
	{
		prevSceneNum = sceneNum;
		sceneNum = data->select1Value;
		Scene_SetNextScene(SCENE_MAIN);
	}

	if (Input_GetKey('W'))
	{
		--data->playerSelectValue;
	}
	
	if (Input_GetKey('S'))
	{
		++data->playerSelectValue;
	}
	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_CREDIT);
	}
}

void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	Renderer_DrawImage(&data->BackGround, data->BackGroundX, data->BackGroundY);

	SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
	Renderer_DrawTextSolid(&data->text1, 0, 0, color);
	for (int i = 0; i < 5; ++i)
	{
		Renderer_DrawTextSolid(&data->text2[i], 0, 30 * (i + 1), color);

	}
	for (int i = 0; i < 5; ++i)
	{
		Renderer_DrawTextSolid(&data->text3[i], 0, 50 + (15 * (i + 1)), color);

	}

}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	
	Text_FreeText(&data->text1); 
	Text_FreeText(&data->text2);
	Text_FreeText(&data->text3);
	Image_FreeImage(&data->BackGround);
	Audio_FreeMusic(&data->BGM);
	
	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region creditscene
const wchar_t* str4[] = {
	L"메타버스 기획반",
	L"    강재훈",
	L"    이혜승",
	L"    오유정",
	L"메타버스 개발반",
	L"    갈민상",
	L"    용준헌",
	L"    최선우"
};
#define GUIDELINE_COUNT 8
typedef struct creditscene
{
	Text		GuideLine[GUIDELINE_COUNT];
	Music		BGM;
	float		Volume;
	SoundEffect Effect;
	Image		BackGround1;
	Image		BackGround2;
	float		Speed;
	int32		X;
	int32		Y;
	int32		Alpha;
} creditscene;

void init_credit(void)
{

	g_Scene.Data = malloc(sizeof(creditscene));
	memset(g_Scene.Data, 0, sizeof(creditscene));

	creditscene* data = (creditscene*)g_Scene.Data;
	Image_LoadImage(&data->BackGround1, "credit1.png");
	Image_LoadImage(&data->BackGround2, "credit2.png");

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 20, str4[i], wcslen(str4[i]));
	}

	/*Audio_LoadMusic(&data->BGM, "index1.mp3");
	Audio_HookMusicFinished(logOnFinished);
	Audio_LoadSoundEffect(&data->Effect, "effect2.wav");
	Audio_HookSoundEffectFinished(log2OnFinished);
	Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);*/

	/*data->Volume = 1.0f;
	data->Speed = 400.0f;*/
	data->X = 0;
	data->Y = 0;
	data->Alpha = 255; // 색상 
}

void update_credit(void)
{
	creditscene* data = (creditscene*)g_Scene.Data;
	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_MAX);
	}
}

static float elaspedtime = 0.0f;
void render_credit(void)
{
	creditscene* data = (creditscene*)g_Scene.Data;
	//(&data->BackGround1, data->X, data->Y);
	//(&data->BackGround2, data->X, data->Y);
	elaspedtime += Timer_GetDeltaTime();

	if (elaspedtime < 1.0f)
	{

		Renderer_DrawImage(&data->BackGround1, data->X, data->Y);
		data->Alpha = Clamp(0, data->Alpha - 1, 220);
		Image_SetAlphaValue(&data->BackGround1, data->Alpha);
		//SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
		//Renderer_DrawTextBlended(&data->BackGround1, 400, 400, color);

	}

	if (elaspedtime > 1.0f)
	{
		data->Alpha = Clamp(10, data->Alpha, 190);
		Image_SetAlphaValue(&data->BackGround2, data->Alpha);
		Renderer_DrawImage(&data->BackGround2, data->X, data->Y);

		for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
		{
			SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255 };
			Renderer_DrawTextSolid(&data->GuideLine[i], 900, 40 * i, color);
		}

	}
}

void release_credit(void)
{
	creditscene* data = (creditscene*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}

	Image_FreeImage(&data->BackGround1);
	Image_FreeImage(&data->BackGround2);
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
	case SCENE_MAIN:
		g_Scene.Init = init_main;
		g_Scene.Update = update_main;
		g_Scene.Render = render_main;
		g_Scene.Release = release_main;
		break;
	case SCENE_CREDIT:
		g_Scene.Init = init_credit;
		g_Scene.Update = update_credit;
		g_Scene.Render = render_credit;
		g_Scene.Release = release_credit;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}