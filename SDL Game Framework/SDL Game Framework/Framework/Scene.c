#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

typedef struct tagScene {
	int32			Number;							//씬 넘버
	const wchar_t*	Name;							//씬 이름
	Image			BGImage;						//배경화면
	Music			BGM;							//배경 음악
	Image			AdditionImage;					//추가 이미지
	int32			AddImage_X;						//추가 이미지 위치
	int32			AddImage_Y;						//추가 이미지 위치
	SoundEffect		EffectSound;					//효과음
	int32			EffectSoundTiming;				//효과음 표현 타이밍
	int32			DialogCount;					//텍스트 갯수
	Text			DialogList[10][10];				//텍스트 배열
	int32			OptionCount;					//옵션 갯수
	Image			OptionImagesList[6];			//옵션 이미지 배열
	int32			NextSceneNumberList[6];			//옵션 선택시 넘어가는 씬 넘버
	int32			NextEndingSceneNumberList[6];	//다음 씬이 엔딩씬일 경우
	bool			isEndingScene;					//엔딩인지
} SceneStruct;

#define SCENE_COUNT	118
SceneStruct Scenes[SCENE_COUNT];

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

/*
void setScene(int32 indexNum, wchar_t* name, char* bgImageName,
	char* musicName, char* additionImageName, char* additionImagePos, 
	char* effectSoundName, int32 effectSoundTime, int32 dialogCount,
	wchar_t** dialog, int32 optionCount, char* optionName,
	int32* nextSceneNumber, bool isEndingScene) {

	Scenes[indexNum-1].Number = indexNum-1;
	Scenes[indexNum-1].Name = name;
	Image_LoadImage(&Scenes[indexNum - 1].BGImage, bgImageName);
	Scenes[indexNum - 1].BGImage.ScaleY -= 0.065f;
	Scenes[indexNum - 1].BGImage.ScaleX -= 0.065f;
	Audio_LoadMusic(&Scenes[indexNum - 1].BGM, musicName);
	Image_LoadImage(&Scenes[indexNum - 1].AdditionImage, additionImageName);
	//수정 필용
	Scenes[indexNum - 1].AddImage_X = 0;
	Scenes[indexNum - 1].AddImage_Y = 0;
	Audio_LoadMusic(&Scenes[indexNum - 1].EffectSound, effectSoundName);
	Scenes[indexNum - 1].EffectSoundTiming = effectSoundTime;

	Scenes[indexNum - 1].DialogCount = dialogCount;
	int32 i = 0, j = 0;
	for (int32 i = 0; i < dialogCount;i++) {
		while (wcslen(&dialog[i][j]) != 0) {
			Text_CreateText(&Scenes[indexNum-1].DialogList[i][j], )
		}
	}
	
	Text_CreateText(&Scenes[indexNum-1].DialogList[0][0], "d2coding.ttf", 50, L"2031년 5월 13일 오랜만에 여동생을 만나 ", wcslen(L"2031년 5월 13일 오랜만에 여동생을 만나 "));
	Text_CreateText(&Scenes[indexNum-1].DialogList[0][1], "d2coding.ttf", 50, L"용산 아이파크 몰에 왔다.", wcslen(L"용산 아이파크 몰에 왔다."));
	Text_CreateText(&Scenes[indexNum-1].DialogList[0][2], "d2coding.ttf", 50, L"", wcslen(L""));
	Text_CreateText(&Scenes[indexNum-1].DialogList[1][0], "d2coding.ttf", 50, L"이곳엔 여동생이 가장 좋아하는 ", wcslen(L"이곳엔 여동생이 가장 좋아하는 "));
	Text_CreateText(&Scenes[indexNum-1].DialogList[1][1], "d2coding.ttf", 50, L"키즈카페가 있기 때문이다.", wcslen(L"키즈카페가 있기 때문이다."));
	Text_CreateText(&Scenes[indexNum-1].DialogList[1][2], "d2coding.ttf", 50, L"", wcslen(L""));

	Scenes[indexNum-1].OptionCount = 0;
	Scenes[indexNum-1].NextSceneNumberList[0] = 1;
}
*/
void setScenes(void) {
	//Scene 1
	Scenes[0].Number = 0;
	Scenes[0].Name = L"";
	Image_LoadImage(&Scenes[0].BGImage, "csv/roof/S#0.start.jpg");
	Scenes[0].BGImage.ScaleY -= 0.065f;
	Scenes[0].BGImage.ScaleX -= 0.065f;
	Audio_LoadMusic(&Scenes[0].BGM, "csv/roof/powerful.mp3");
	Image_LoadImage(&Scenes[0].AdditionImage, "NULL");
	Scenes[0].AddImage_X = 0;
	Scenes[0].AddImage_Y = 0;
	Audio_LoadMusic(&Scenes[0].EffectSound, "NULL");
	Scenes[0].EffectSoundTiming = NULL;

	Scenes[0].DialogCount = 2;
	Text_CreateText(&Scenes[0].DialogList[0][0], "d2coding.ttf", 50, L"2031년 5월 13일 오랜만에 여동생을 만나 ", wcslen(L"2031년 5월 13일 오랜만에 여동생을 만나 "));
	Text_CreateText(&Scenes[0].DialogList[0][1], "d2coding.ttf", 50, L"용산 아이파크 몰에 왔다.", wcslen(L"용산 아이파크 몰에 왔다."));
	Text_CreateText(&Scenes[0].DialogList[0][2], "d2coding.ttf", 50, L"", wcslen(L""));
	Text_CreateText(&Scenes[0].DialogList[1][0], "d2coding.ttf", 50, L"이곳엔 여동생이 가장 좋아하는 ", wcslen(L"이곳엔 여동생이 가장 좋아하는 "));
	Text_CreateText(&Scenes[0].DialogList[1][1], "d2coding.ttf", 50, L"키즈카페가 있기 때문이다.", wcslen(L"키즈카페가 있기 때문이다."));
	Text_CreateText(&Scenes[0].DialogList[1][2], "d2coding.ttf", 50, L"", wcslen(L""));
	
	Scenes[0].OptionCount = 0;
	Scenes[0].NextSceneNumberList[0] = 1;


	//Scene 2
	Scenes[1].Number = 1;
	Scenes[1].Name = L"";
	Image_LoadImage(&Scenes[1].BGImage, "csv/roof/S#1.roof.jpg");
	Scenes[1].BGImage.ScaleY -= 0.065f;
	Scenes[1].BGImage.ScaleX -= 0.065f;
	Audio_LoadMusic(&Scenes[1].BGM, "powerful.mp3");
	Image_LoadImage(&Scenes[1].AdditionImage, "NULL");
	Scenes[1].AddImage_X = 0;
	Scenes[1].AddImage_Y = 0;
	Audio_LoadMusic(&Scenes[1].EffectSound, "NULL");
	Scenes[1].EffectSoundTiming = NULL;

	Scenes[1].DialogCount = 2;
	Text_CreateText(&Scenes[1].DialogList[0][0], "d2coding.ttf", 50, L"동생이 키즈카페에서 만난 친구들과 노는 것을 확인한 후,", wcslen(L"동생이 키즈카페에서 만난 친구들과 노는 것을 확인한 후,"));
	Text_CreateText(&Scenes[1].DialogList[0][1], "d2coding.ttf", 50, L"", wcslen(L""));
	Text_CreateText(&Scenes[1].DialogList[1][0], "d2coding.ttf", 50, L"담배를 피러", wcslen(L"담배를 피러"));
	Text_CreateText(&Scenes[1].DialogList[1][1], "d2coding.ttf", 50, L"용산 아이파크 몰 옥상으로 올라갔다.", wcslen(L"용산 아이파크 몰 옥상으로 올라갔다."));
	Text_CreateText(&Scenes[1].DialogList[1][2], "d2coding.ttf", 50, L"", wcslen(L""));
	
	Scenes[1].OptionCount = 0;
	Scenes[1].NextSceneNumberList[0] = 0;

	//Scene 3
	Scenes[2].Number = 2;
	Scenes[2].Name = L"";
	Image_LoadImage(&Scenes[2].BGImage, "csv/roof/S#1-2.jpg");
	Scenes[2].BGImage.ScaleY -= 0.065f;
	Scenes[2].BGImage.ScaleX -= 0.065f;
	Audio_LoadMusic(&Scenes[2].BGM, "powerful.mp3");
	Image_LoadImage(&Scenes[2].AdditionImage, "csv/roof/S#2.jpg");
	Scenes[2].AddImage_X = 800;
	Scenes[2].AddImage_Y = 600;
	Audio_LoadMusic(&Scenes[2].EffectSound, "NULL");
	Scenes[2].EffectSoundTiming = NULL;

	Scenes[2].DialogCount = 6;
	Text_CreateText(&Scenes[1].DialogList[0][0], "d2coding.ttf", 50, L"동생이 키즈카페에서 만난 친구들과 노는 것을 확인한 후,", wcslen(L"동생이 키즈카페에서 만난 친구들과 노는 것을 확인한 후,"));
	Text_CreateText(&Scenes[1].DialogList[0][1], "d2coding.ttf", 50, L"", wcslen(L""));
	Text_CreateText(&Scenes[1].DialogList[1][0], "d2coding.ttf", 50, L"담배를 피러", wcslen(L"담배를 피러"));
	Text_CreateText(&Scenes[1].DialogList[1][1], "d2coding.ttf", 50, L"용산 아이파크 몰 옥상으로 올라갔다.", wcslen(L"용산 아이파크 몰 옥상으로 올라갔다."));
	Text_CreateText(&Scenes[1].DialogList[1][2], "d2coding.ttf", 50, L"", wcslen(L""));
	
	Scenes[2].OptionCount = 0;
	Scenes[2].NextSceneNumberList[0] = 2;
}

void init_main(void)
{
	setScenes();

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

	if (Input_GetKeyDown(VK_RETURN)) {
		Scene_SetNextScene(SCENE_TEMP);
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

#pragma region TempScene
typedef struct tagMainScene {
	SceneStruct*   Scene;
	bool        isEndScene;
	int32		CurrentOptionNumber;
	int32		CurrentTextNumber;
	Image		BlackOutImage;
	int32		BlackOutAlpha;
} MainScene;

bool isSceneChanging = false;
bool showOptions = false;
Text* ShowText;
int32 s_CurrentScene = 0;
SDL_Color color = { 0,0,0,0 };
void init_temp(void)
{
	g_Scene.Data = malloc(sizeof(MainScene));
	memset(g_Scene.Data, 0, sizeof(MainScene));

	MainScene* data = (MainScene*)g_Scene.Data;

	data->Scene = &Scenes[s_CurrentScene];
	data->isEndScene = false;
	data->CurrentOptionNumber = 0;
	data->CurrentTextNumber = 0;
	data->BlackOutAlpha = 255;
	Image_LoadImage(&data->BlackOutImage, "black.png");
	Image_SetAlphaValue(&data->BlackOutImage, data->BlackOutAlpha);
	Audio_PlayFadeIn(&data->Scene->BGM, INFINITY_LOOP, 2000);

	isSceneChanging = false;
	showOptions = false;
	ShowText = NULL;
}

void update_temp(void)
{
	MainScene* data = (MainScene*) g_Scene.Data;

	//보통 씬일 경우
	if (!isSceneChanging) {
		if (data->BlackOutAlpha > 0) {
			data->BlackOutAlpha -= 5;
		}
		else {
			//키보드 값 입력
			if (Input_GetKeyDown(VK_SPACE)) {

				if (data->CurrentTextNumber < data->Scene->DialogCount) {
					ShowText = &data->Scene->DialogList[data->CurrentTextNumber];
					data->CurrentTextNumber++;
					color.a = 0;
				}
				else if (data->Scene->OptionCount <= 0) {
					isSceneChanging = true;
					Audio_FadeOut(1800);
				}
			}
		}

		//텍스트 표시가 필요한 경우
		if (data->CurrentTextNumber < data->Scene->DialogCount) {
			int32 i = 0;
			ShowText = data->Scene->DialogList[data->CurrentTextNumber];
			if (color.a < 255) {
				color.a += 5;
			}
		}
		//옵션이 나와야하는 경우
		else {
			showOptions = true;

			//선택지 선택
			int32 optionCount = data->Scene->OptionCount;

			Image_SetAlphaValue(&data->Scene->OptionImagesList[data->CurrentOptionNumber], 125);
			if (Input_GetKeyDown('1') || Input_GetKeyDown(VK_NUMPAD1)) {
				if (optionCount >= 1) {
					data->CurrentOptionNumber = 0;
				}
			}
			if (Input_GetKeyDown('2') || Input_GetKeyDown(VK_NUMPAD2)) {
				if (optionCount >= 2) {
					data->CurrentOptionNumber = 1;
				}
			}
			if (Input_GetKeyDown('3') || Input_GetKeyDown(VK_NUMPAD3)) {
				if (optionCount >= 3) {
					data->CurrentOptionNumber = 2;
				}
			}
			if (Input_GetKeyDown('4') || Input_GetKeyDown(VK_NUMPAD4)) {
				if (optionCount >= 4) {
					data->CurrentOptionNumber = 3;
				}
			}

			//좌우키로 설정
			if (Input_GetKeyDown(VK_LEFT)) {
				if (data->CurrentOptionNumber > 0) {
					data->CurrentOptionNumber--;
				}
				else {
					data->CurrentOptionNumber = data->Scene->OptionCount - 1;
				}
			}

			if (Input_GetKeyDown(VK_RIGHT)) {
				if (data->CurrentOptionNumber < data->Scene->OptionCount - 1) {
					data->CurrentOptionNumber++;
				}
				else {
					data->CurrentOptionNumber = 0;
				}
			}

			//위 아래 키로
			if (Input_GetKeyDown(VK_UP)) {
				if (data->Scene->OptionCount >= 3) {
					if (data->CurrentOptionNumber >= 2) {
						data->CurrentOptionNumber -= 2;
					}
				}
			}

			if (Input_GetKeyDown(VK_DOWN)) {
				if (data->Scene->OptionCount >= 3) {
					if (data->CurrentOptionNumber < data->Scene->OptionCount / 2) {
						data->CurrentOptionNumber += 2;
					}
				}
			}

			Image_SetAlphaValue(&data->Scene->OptionImagesList[data->CurrentOptionNumber], 255);

			//선택지 선택
			if (Input_GetKeyDown(VK_RETURN)) {
				isSceneChanging = true;
				Audio_FadeOut(1800);
			}
		}
	}

	else {
		if (data->BlackOutAlpha < 255) {
			data->BlackOutAlpha += 5;
		}
		else {
			isSceneChanging = false;
			s_CurrentScene = data->Scene->NextSceneNumberList[data->CurrentOptionNumber];
			Scene_SetNextScene(SCENE_TEMP);
		}
	}
	Image_SetAlphaValue(&data->BlackOutImage, data->BlackOutAlpha);
}

void render_temp(void)
{
	MainScene* data = (MainScene*)g_Scene.Data;

	//배경 이미지 출력
	Renderer_DrawImage(&data->Scene->BGImage, 0, 0);
	//Renderer_DrawImage(&TextBGImage, 30, 30);
	
	//텍스트 출력
	int32 i = 0;
	while (ShowText[i].Length != 0) {
		Renderer_DrawTextSolid(&ShowText[i], 400, 300 + i * 80, color);
		i++;
	}

	//선택지 출력
	if (showOptions) {
		if (data->Scene->OptionCount > 2) {
			for (int i = 0; i < data->Scene->OptionCount; i++) {
				Renderer_DrawImage(&data->Scene->OptionImagesList[i], 250 + i % 2 * 700, 600 + (i / 2) * 200);
			}
		}
		else {
			for (int i = 0; i < data->Scene->OptionCount; i++) {
				Renderer_DrawImage(&data->Scene->OptionImagesList[i], 250 + i % 2 * 700, 700 + (i / 2) * 200);
			}
		}
	}

	//페이드 인 페이드 아웃 효과를 위한 검은색 배경
	Renderer_DrawImage(&data->BlackOutImage, 0, 0);
}

void release_temp(void)
{
	MainScene* data = (MainScene*)g_Scene.Data;

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
	case SCENE_TEMP:
 		g_Scene.Init = init_temp;
		g_Scene.Update = update_temp;
		g_Scene.Render = render_temp;
		g_Scene.Release = release_temp;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}