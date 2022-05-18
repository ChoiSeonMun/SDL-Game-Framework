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
	L"여기는 타이틀씬입니다. 텍스트와 관련된 여러가지를 테스트해봅시다.",
	L"B키를 누르면 폰트가 굵게 변합니다.",
	L"I키를 누르면 폰트가 이탤릭체로 변합니다.",
	L"U키를 누르면 텍스트에 밑줄이 생깁니다.",
	L"S키를 누르면 텍스트에 취소선이 생깁니다.",
	L"N키를 누르면 다시 원래대로 돌아옵니다.",
	L"C키를 누르면 렌더 모드가 바뀝니다. (Solid -> Shaded -> Blended)",
	L"1키를 누르면 텍스트가 작아집니다.",
	L"2키를 누르면 텍스트가 커집니다.",
	L"스페이스 키를 누르면 다음 씬으로 넘어갑니다.",
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

	Text_CreateText(&data->RoadingText[0], "12LotteMartHappyLight.ttf", 18, L"바이오 칩셋 로딩중.", wcslen(L"바이오 칩셋 로딩중."));
	Text_CreateText(&data->RoadingText[1], "12LotteMartHappyLight.ttf", 18, L"바이오 칩셋 로딩중..", wcslen(L"바이오 칩셋 로딩중.."));
	Text_CreateText(&data->RoadingText[2], "12LotteMartHappyLight.ttf", 18, L"바이오 칩셋 로딩중...", wcslen(L"바이오 칩셋 로딩중..."));
	Text_CreateText(&data->Recording, "12LotteMartHappyLight.ttf", 18, L"기록자 - [타카네 준]", wcslen(L"기록자 - [타카네 준]"));
	Text_CreateText(&data->Date, "12LotteMartHappyLight.ttf", 18, L"2067년 8 월 12 일", wcslen(L"2067년 8 월 12 일"));
	Text_CreateText(&data->Rocation, "12LotteMartHappyLight.ttf", 18, L"위치 좌표 - [東京 , 日本]", wcslen(L"위치 좌표 - [동경 , 일본]"));
	Text_CreateText(&data->Infomation, "12LotteMartHappyLight.ttf", 18, L"본 칩셋은 내각관방 직할 내각정보조사실 존치기록물 입니다-", wcslen(L"본 칩셋은 내각관방 직할 내각정보조사실 존치기록물 입니다-"));
	Text_CreateText(&data->RoadConform[0], "12LotteMartHappyLight.ttf", 18, L"로드 컨펌중 -", wcslen(L"로드 컨펌중 -"));
	Text_CreateText(&data->RoadConform[1], "12LotteMartHappyLight.ttf", 18, L"로드 컨펌중 --", wcslen(L"로드 컨펌중 --"));
	Text_CreateText(&data->RoadConform[2], "12LotteMartHappyLight.ttf", 18, L"로드 컨펌중 ---", wcslen(L"로드 컨펌중 ---"));
	Text_CreateText(&data->RoadConform[3], "12LotteMartHappyLight.ttf", 18, L"로드 컨펌중 ----", wcslen(L"로드 컨펌중 ----"));
	Text_CreateText(&data->BioLink[0], "12LotteMartHappyLight.ttf", 18, L"바이오 링크 완료.", wcslen(L"바이오 링크 완료."));
	Text_CreateText(&data->BioLink[1], "12LotteMartHappyLight.ttf", 18, L"바이오 링크 완료..", wcslen(L"바이오 링크 완료.."));
	Text_CreateText(&data->BioLink[2], "12LotteMartHappyLight.ttf", 18, L"바이오 링크 완료...", wcslen(L"바이오 링크 완료..."));
	Text_CreateText(&data->BrainLink, "12LotteMartHappyLight.ttf", 18, L"대뇌 감정 링크 확인", wcslen(L"대뇌 감정 링크 확인"));
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
	L"「오늘도 수고했어.」",
	L"히나노, 여자친구의 목소리다-",
	L"또 승진 못한 남자친구를 두고 무슨 이야기인지.",
	L"재무성 관료가 된지 어연 10년, 말이 관료지 그냥 말단 공무원이다.",
	L"만년 계장이 무슨 관료인가, 입 아픈 이야기다.",
	L"\"오늘은 아무것도 하기싫네.\"",
	L"「언제는 뭘 하고 싶었고?」",
	L"\"내일은 뭘 하고 싶을 수도..\"",
	L"「당신 내일은 금융청 일 때문에 바쁘다며.」",
	L"\"그럼 내일도 하기 싫겠네.\"",
	L"의미없는 이야기의 반복, 머리아픈 이야기들.."
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
	L"『수도하이퍼루프 닛포리선, 2번 리니어 승강장에 진입합니다.』",
	L"띠링띠링띠링띠링-",
	L"\"내일부터 며칠간 못 볼 수도 있으니까 오늘 많이 봐둬\"",
	L"졸려하는 히나노를 툭툭 건들며 얼굴을 들이댄다.",
	L"「금융청에 무슨 일이길래.」",
	L"\"요즘 미즈호 은행의 움직임이 수상해서 말이야. 당분간은 못들어갈 거 같아.\"",
	L"「검찰은 뭐하고?」",
	L"\"그 놈들은 믿을게 못 돼. 이미 은행과 짜고 치고 했을 수도 있겠지.\"",
	L"「그렇구나...」",
	L"\"열차 떠나겠다. 이만 가볼게. 나 없이 잘 지낼 수 있지?\"",
	L"「응.」",
	L"뚱한 표정의 그녀를 달래듯 잠시 끌어안고 신속히 열차에 올라탔다.",
	L"창문 너머 서 있는 그녀에게 손을 흔들다 피곤으로 찌는 몸을 푹신한 시트에 파묻었다.",
	L"이 끝에 무슨 일이 기다리고 있을지 꿈에도 모른 채 난 깊은 잠에 빠졌다."
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
	L"『똑똑똑.』",
	L"\"하아... 들어와라\"",
	L"여유롭게 따뜻한 커피를 마시려고 했건만,",
	L"부하인 사카이 사무로가 눈치도 없이 상황보고를 시작했다.",
	L"「미즈호 은행에서 비자금을 유통하는 정황이 포착되었습니다.」",
	L"그 놈의 비자금.",
	L"난 이미 10년 넘도록 지긋지긋하게 반복해온 일에 진절머리가 날 지경이였다.",
	L"기업의 비리는 어디서나 있었고 늘 내가 해결해왔지만 끝끝내 내게 떨어진 콩고물은 없었다.",
	L"\"비자금이라.. 규모는 얼마정도지?\"",
	L"「현재 추정으론 50억엔 정도입니다.」",
	L"다만 이번엔 상대가 미즈호 은행이였다는 것.",
	L"미즈호 은행은 우리나라 최대 금융그룹이 아니던가,",
	L"오랜만에 구미가 확 당기는 기분이였다."
};

const wchar_t* twoment1 = L"\"그런 거물이 어디서 꼬리가 잡혔길래?\"";
const wchar_t* twoment2 = L"\"수령인은 포착 되었고?\"";

const wchar_t* twochoicement1 = L"\"그런 거물이 어디서 꼬리가 잡혔길래?\"<";
const wchar_t* twochoicement2 = L"\"수령인은 포착 되었고?\"<";

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
	L"\"그런 거물이 어디서 꼬리가 잡혔길래?\"",
	L"「며칠 전 미즈호의 대규모 구조조정으로 생계를 잃은 자가 앙심을 품고",
	L"관련 지출 전표를 브로커에게 보냈다고 합니다.」",
	L"\"멍청한 자식들이 결국 제 발등을 찍었군.. 그래 수령인도 알아냈고?\"",
	L"「네. 정치인 타이라 켄타로에게 건넸다고 합니다.」",
	L"「미즈호 은행이 수출 대금 50억엔을 수표로 바꿔 자체적으로 돈세탁 과정을 거쳤습니다.」.",
	L"\"...잠깐\""
};

const wchar_t* threeforechoicement = L"\"방금 타이라 켄타로 라고 했나?\"<";

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
	L"\"수령인은 포착 되었고?\"",
	L"「정치인 타이라 켄타로에게 건넸습니다.」",
	L"「미즈호 은행이 수출 대금 50억엔을 수표로 바꿔 자체적으로 돈세탁 과정을 거쳤습니다.」",
	L"\"...잠깐\""
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
	L"\"방금 타이라 켄타로라고 했나?\"",
	L"「네. 틀림 없습니다.」",
	L"중의원 타이라 켄타로. 일본 차기 총리로 지목되는 유력 후보다.",
	L"총재선거 지지율이 압도적으로 높은 정치계의 거물.",
	L" ",
	L"그런 타이라 켄타로가 미즈호 은행과 결탁이라니...",
	L"이들을 이 손으로 일망타진 할 수 있는 일생일대의 기회 아니겠는가!",
	L"잘만 진행된다면 분명 이전 잡일과는 비교도 안될만큼 큰 공로를 세울 수 있을 것이다."
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