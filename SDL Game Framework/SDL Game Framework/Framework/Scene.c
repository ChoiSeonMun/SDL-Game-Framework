#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"
#include "Csv.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

/*
void setScenes(void) {
	//Scene 1
	Scenes[0].Number = 0;
	Scenes[0].Name = L"";
	Image_LoadImage(&Scenes[0].BGImage, "csv/roof/S#0.start.jpg");
	Audio_LoadMusic(&Scenes[0].BGM, "csv/roof/B-play.mp3");
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
	Audio_LoadMusic(&Scenes[1].BGM, "csv/roof/B-play.mp3");
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
	Audio_LoadMusic(&Scenes[2].BGM, "csv/roof/B-play.mp3");
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
*/
//#define SCENE_COUNT	118
//SceneStruct Scenes[SCENE_COUNT];

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

typedef struct TitleSceneData
{
	Text   GuideLine[1];
	Music   TitleBGM;
	float   Volume;
	Text   EnterText;
	Text   LoadingText;
	int32   FontSize;
	int32   RenderMode;
	Image   TitleImage;
	int32   X;
	int32   Y;
	Image   StartImage;
	int32   SX;
	int32   SY;
	Image    BlackOutImage;
	int32    BlackOutAlpha;
} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	data->FontSize = 48;
	Text_CreateText(&data->EnterText, "GmarketSansTTFBold.ttf", data->FontSize, L"--- PRESS THE SPACE ---", 24);
	Text_CreateText(&data->LoadingText, "GmarketSansTTFBold.ttf", data->FontSize, L"----- LOADING -----", 24);

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

	data->BlackOutAlpha = 255;
	Image_LoadImage(&data->BlackOutImage, "black.jpg");
	Image_SetAlphaValue(&data->BlackOutImage, data->BlackOutAlpha);
}

bool Loading = false;
void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	if (data->BlackOutAlpha > 0)
	{
		data->BlackOutAlpha -= 5;
	}
	if (data->BlackOutAlpha <= 0)
	{
		if (Input_GetKeyDown(VK_SPACE))
		{
			Loading = true;
			Scene_SetNextScene(SCENE_CREDIT);
		}
	}
	Image_SetAlphaValue(&data->BlackOutImage, data->BlackOutAlpha);
}
void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	Renderer_DrawImage(&data->TitleImage, data->X, data->Y);
	static float elapsedTime = 1.0f;

	SDL_Color color = { .a = 255 };
	static bool isShow = true;
	elapsedTime += Timer_GetDeltaTime();
	if (!Loading)
	{
		if (elapsedTime >= 1.0f)
		{
			Renderer_DrawImage(&data->StartImage, data->SX, data->SY);
			Renderer_DrawTextSolid(&data->EnterText, WINDOW_WIDTH / 2 - (data->EnterText.Length * data->FontSize) / 4, 950, color);

			if (elapsedTime >= 1.5f)
			{
				elapsedTime = 0.0f;
			}
		}
	}
	else
	{
		color.r = 255;
		color.g = 255;
		color.b = 255;
		isShow = false;
		Renderer_DrawTextSolid(&data->LoadingText, WINDOW_WIDTH / 2 - (data->LoadingText.Length * data->FontSize) / 4 + 20, 820, color);
	}

}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	//for (int32 i = 0; i < 10; ++i)
	//{
	//   Text_FreeText(&data->GuideLine[i]);
	//}
	Text_FreeText(&data->EnterText);
	SafeFree(g_Scene.Data);
}
#pragma endregion

#define SCENE_COUNT	150
#define MAX_TEXT_SET_COUNT 13
#define MAX_TEXT_COUNT 20
#define MAX_OPTION_COUNT 3

#pragma region SceneData

//각 씬의 정보를 담든 structure
typedef struct tagScene {
	int32			Number;							//씬 넘버
	const wchar_t* Name;								//씬 이름
	Image			BGImage;							//배경화면
	Music			BGM;							//배경 음악
	Image			AdditionImage;						//추가 이미지
	int32			AddImageTiming;						//추가 이미지 타이밍
	SoundEffect		EffectSound;						//효과음
	int32			EffectSoundTiming;						//효과음 표현 타이밍
	int32			DialogCount;						//텍스트 갯수
	Text			DialogList[MAX_TEXT_SET_COUNT][MAX_TEXT_COUNT];						//텍스트 배열
	int32			OptionCount;						//옵션 갯수
	//Image			OptionImagesList[MAX_Option_COUNT];					//옵션 이미지 배열
	Text			OptionList[MAX_OPTION_COUNT];
	int32			NextSceneNumberList[MAX_OPTION_COUNT];					//옵션 선택시 넘어가는 씬 넘버
	//int32			NextEndingSceneNumberList[5];				//다음 씬이 엔딩씬일 경우
	bool			isEndingScene;						//엔딩인지
} SceneStruct;

SceneStruct Scenes[SCENE_COUNT];

bool isGotData = false;
void GetSceneData(void) {
	CsvFile csv;
	memset(&csv, 0, sizeof(CsvFile));
	CreateCsvFile(&csv, "temp1.csv");

	isGotData = true;

	for (int32 i = 1; i < csv.RowCount;i++) {

		if (csv.Items[i] == NULL) {
			break;
		}

		int32 columCount = 0;

		//씬 번호
		int32 sceneNum = ParseToInt(csv.Items[i][columCount++]) - 1;
		printf("%d\n", sceneNum);
		Scenes[sceneNum].Number = sceneNum;
		Scenes[sceneNum].Name = ParseToUnicode(csv.Items[i][columCount++]);
		Image_LoadImage(&Scenes[sceneNum].BGImage, ParseToAscii(csv.Items[i][columCount++]));
		Audio_LoadMusic(&Scenes[sceneNum].BGM, ParseToAscii(csv.Items[i][columCount++]));
		//Audio_SetVolume(0.1f);

		//배경 전환 이미지
		int32 additionalImagePoint = ParseToInt(csv.Items[i][columCount + 1]);
		Scenes[sceneNum].AddImageTiming = additionalImagePoint;
		if (additionalImagePoint > -1) {
			Image_LoadImage(&Scenes[sceneNum].AdditionImage, ParseToAscii(csv.Items[i][columCount]));
		}
		columCount += 2;

		//효과음
		//char* effectSound = ParseToAscii(csv.Items[i][columCount++]);
		int32 effectSoundPoint = ParseToInt(csv.Items[i][columCount + 1]);
		Scenes[sceneNum].EffectSoundTiming = effectSoundPoint;
		if (effectSoundPoint > -1) {
			printf("effect: %d\n", effectSoundPoint);
			Audio_LoadSoundEffect(&Scenes[sceneNum].EffectSound, ParseToAscii(csv.Items[i][columCount]));
		}
		columCount+=2;
		//columCount++;
		//columCount++;

		//텍스트 데이터 저장
		int32 dialogCount = ParseToInt(csv.Items[i][columCount++]);
		Scenes[sceneNum].DialogCount = dialogCount;
		for (int32 j = 0; j < MAX_TEXT_SET_COUNT;j++) {
			if (dialogCount > j) {
				wchar_t* originalData = ParseToUnicode(csv.Items[i][columCount]);
				wchar_t lineData[2048];
				int32 originalIndex = 0, lineDataIndex = 0, dialogListIndex = 0;
				wchar_t preChar = '\0';

				//텍스트 줄바꿈 단위로 나눠 저장
				while (true) {
					//그냥 입력일 경우
					if (*(originalData + originalIndex) != '\n' && *(originalData + originalIndex) != '\0') {
						//"가 아닐 경우 그냥 넣어준다.
						if (*(originalData + originalIndex) != '\"') {
							lineData[lineDataIndex++] = *(originalData + originalIndex);
							preChar = *(originalData + originalIndex);
						}
						// "가 연속으로 있을 경우 넣어준다.
						else {
							if (preChar == *(originalData + originalIndex)) {
								lineData[lineDataIndex++] = *(originalData + originalIndex);
								preChar = '\0';
							}
							else {
								preChar = *(originalData + originalIndex);
							}
						}
					}
					//개행이거나 널일 경우 text를 넣어준다.
					else {
						lineData[lineDataIndex++] = '\0';
						Text_CreateText(&Scenes[sceneNum].DialogList[j][dialogListIndex], "GmarketSansTTFBold.ttf", 25, lineData, wcslen(lineData));
						dialogListIndex++;
						lineDataIndex = 0;

						if (*(originalData + originalIndex) == '\0') {
							break;
						}
					}
					originalIndex++;
				}

				Text_CreateText(&Scenes[sceneNum].DialogList[j][dialogListIndex], "GmarketSansTTFBold.ttf", 30, L"", wcslen(L""));
			}
			columCount++;
		}

		//옵션 데이터 저장
		Scenes[sceneNum].OptionCount = ParseToInt(csv.Items[i][columCount++]);
		for (int32 j = 0; j < MAX_OPTION_COUNT;j++) {
			if (Scenes[i - 1].OptionCount > j) {
				wchar_t* temp = ParseToUnicode(csv.Items[i][columCount]);
				Text_CreateText(&Scenes[sceneNum].OptionList[j], "GmarketSansTTFBold.ttf", 20, temp, wcslen(temp));

				columCount++;
				Scenes[sceneNum].NextSceneNumberList[j] = ParseToInt(csv.Items[i][columCount]) - 1;
				columCount++;
			}
		}

		if (Scenes[sceneNum].OptionCount <= 0) {
			Scenes[sceneNum].NextSceneNumberList[0] = ParseToInt(csv.Items[i][++columCount]) - 1;
		}
	}

	FreeCsvFile(&csv);

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
	//씬 데이터를 미리 받아옴
	if (!isGotData) {
		GetSceneData();
	}

	g_Scene.Data = malloc(sizeof(CreditSceneData));
	memset(g_Scene.Data, 0, sizeof(CreditSceneData));

	CreditSceneData* data = (CreditSceneData*)g_Scene.Data;

	data->FontSize = 48;
	Text_CreateText(&data->EnterText, "chosun.ttf", data->FontSize, L"--- PRESS THE SPACE ---", 24);

	data->RenderMode = SOLID;

	Image_LoadImage(&data->CreditImage, "credit.jpg");
	data->X = 0;
	data->Y = 0;

}

void update_credit(void)
{
	CreditSceneData* data = (CreditSceneData*)g_Scene.Data;

	if (Input_GetKeyDown(VK_SPACE))
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
	L"여러분들의 건강과 행복을 ",
	L"질병과 바이러스로부터지켜드리기 위하여 ",
	L" ",
	L"<행복 연구소> 는 정부 기관 아래 최첨단 연구 장비와 지식을 겸비하여",
	L"꾸준한 연구 및 개발을 진행하고 있습니다.",
};
const wchar_t* intro3str[] = {
	L"하지만 사실, 이 <행복 연구소> 는 ",
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
	L"그 영향으로 이 '지능 쥐'는 때때로 ",
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
int count = 1;
void init_intro(void)
{
	count = 1;
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
void update_intro(void)
{
	if (Input_GetKeyDown(VK_SPACE))
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

#pragma region TempScene

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
	//���� �ʿ�
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

	Text_CreateText(&Scenes[indexNum-1].DialogList[0][0], "d2coding.ttf", 50, L"2031�� 5�� 13�� �������� �������� ���� ", wcslen(L"2031�� 5�� 13�� �������� �������� ���� "));
	Text_CreateText(&Scenes[indexNum-1].DialogList[0][1], "d2coding.ttf", 50, L"��� ������ũ ���� �Դ�.", wcslen(L"��� ������ũ ���� �Դ�."));
	Text_CreateText(&Scenes[indexNum-1].DialogList[0][2], "d2coding.ttf", 50, L"", wcslen(L""));
	Text_CreateText(&Scenes[indexNum-1].DialogList[1][0], "d2coding.ttf", 50, L"�̰��� �������� ���� �����ϴ� ", wcslen(L"�̰��� �������� ���� �����ϴ� "));
	Text_CreateText(&Scenes[indexNum-1].DialogList[1][1], "d2coding.ttf", 50, L"Ű��ī�䰡 �ֱ� �����̴�.", wcslen(L"Ű��ī�䰡 �ֱ� �����̴�."));
	Text_CreateText(&Scenes[indexNum-1].DialogList[1][2], "d2coding.ttf", 50, L"", wcslen(L""));

	Scenes[indexNum-1].OptionCount = 0;
	Scenes[indexNum-1].NextSceneNumberList[0] = 1;
}
*/

#pragma endregion

#pragma region MainScene
typedef struct tagMainScene {
	SceneStruct* Scene;
	bool        isEndScene;
	int32		CurrentOptionNumber;
	int32		CurrentTextNumber;
	SDL_Color	OptionColors[MAX_OPTION_COUNT];
	Image		BlackOutImage;
	int32		BlackOutAlpha;
} MainScene;

bool isSceneChanging = false;
bool showOptions = false;
bool isBGChanged = false;
Text* ShowText;
Text NullText;
int32 s_CurrentScene = 0;
SDL_Color TextColor = { 255,255,255,0 };
Image OptionPointImage;
void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainScene));
	memset(g_Scene.Data, 0, sizeof(MainScene));

	MainScene* data = (MainScene*)g_Scene.Data;

	data->Scene = &Scenes[s_CurrentScene];
	data->isEndScene = false;
	data->CurrentOptionNumber = 0;
	data->CurrentTextNumber = 0;
	data->BlackOutAlpha = 255;
	Image_LoadImage(&data->BlackOutImage, "black.jpg");
	Image_SetAlphaValue(&data->BlackOutImage, data->BlackOutAlpha);
	Audio_PlayFadeIn(&data->Scene->BGM, INFINITY_LOOP, 2000);
	Text_CreateText(&NullText, TextFont, 25, L"", 0);
	Image_LoadImage(&OptionPointImage, "point.png");
	OptionPointImage.ScaleX = 0.02f;
	OptionPointImage.ScaleY = 0.02f;

	for (int32 i = 0; i < data->Scene->OptionCount;i++) {
		data->OptionColors[i].a = 125;
		data->OptionColors[i].r = 225;
		data->OptionColors[i].g = 225;
		data->OptionColors[i].b = 225;
	}

	if (data->Scene->EffectSoundTiming > -1) {
		Audio_PlaySoundEffect(&data->Scene->EffectSound, 1);
	}

	isSceneChanging = false;
	showOptions = false;
	isBGChanged = false;
	ShowText = NULL;
}

void update_main(void)
{
	MainScene* data = (MainScene*)g_Scene.Data;

	//보통 씬일 경우
	if (!isSceneChanging) {
		// 배경 변경 중일 경우
		if (isBGChanged) {
			if (data->BlackOutAlpha < 255) {
				data->BlackOutAlpha += 5;
			}
			else {
				isBGChanged = false;
				data->Scene->BGImage = data->Scene->AdditionImage;
				ShowText = &data->Scene->DialogList[data->CurrentTextNumber-1];
				TextColor.a = 0;
			}
		}
		// 씬 최초 불러오기
		else if (data->BlackOutAlpha > 0) {
			data->BlackOutAlpha -= 5;
		}
		//이외 입력 정상 받음
		else {
			//키보드 값 입력
			if (Input_GetKeyDown(VK_SPACE)) {

				//출력 텍스트 조절
				if (data->CurrentTextNumber < data->Scene->DialogCount) {
					ShowText = &data->Scene->DialogList[data->CurrentTextNumber];
					data->CurrentTextNumber++;

					//배경 이미지 변경
					if (data->Scene->AddImageTiming > -1) {
						if (data->CurrentTextNumber == data->Scene->AddImageTiming) {
							isBGChanged = true;
							ShowText = &NullText;
						}
					}

					//이펙트 싸운드 적용
					if (data->Scene->EffectSoundTiming > -1) {
						if (data->CurrentOptionNumber == data->Scene->EffectSoundTiming) {
							Audio_PlaySoundEffect(&data->Scene->EffectSound, 1);
						}
					}

					TextColor.a = 0;
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
			if (TextColor.a < 255) {
				TextColor.a += 5;
			}
		}
		//옵션이 나와야하는 경우
		else {
			if (data->Scene->OptionCount > 0) {
				showOptions = true;
			}

			//선택지 선택
			int32 optionCount = data->Scene->OptionCount;

			//Image_SetAlphaValue(&data->Scene->OptionImagesList[data->CurrentOptionNumber], 125);
			data->OptionColors[data->CurrentOptionNumber].a = 125;
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

			//위 아래 키로
			if (Input_GetKeyDown(VK_UP)) {
				if (data->CurrentOptionNumber > 0) {
					data->CurrentOptionNumber--;
				}
			}

			if (Input_GetKeyDown(VK_DOWN)) {
				if (data->CurrentOptionNumber < data->Scene->OptionCount - 1) {
					data->CurrentOptionNumber++;
				}
			}

			//Image_SetAlphaValue(&data->Scene->OptionImagesList[data->CurrentOptionNumber], 255);
			data->OptionColors[data->CurrentOptionNumber].a = 255;

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
			//다음 씬이 -1, 즉 엔딩일때는 타이틀로 돌아감. 아니면 다음 씬을 구성
			if (s_CurrentScene != -2) {
				Scene_SetNextScene(SCENE_MAIN);
			}
			else {
				s_CurrentScene = 0;
				Scene_SetNextScene(SCENE_TITLE);
			}
		}
	}

	//암전 효과 적용
	Image_SetAlphaValue(&data->BlackOutImage, data->BlackOutAlpha);
}

void render_main(void)
{
	MainScene* data = (MainScene*)g_Scene.Data;

	//배경 이미지 출력
	Renderer_DrawImage(&data->Scene->BGImage, 0, 0);
	//Renderer_DrawImage(&TextBGImage, 30, 30);

	//텍스트 출력
	if (ShowText != NULL && !isBGChanged) {
		int32 i = 0;
		while (ShowText[i].Length != 0) {
			Renderer_DrawTextSolid(&ShowText[i], 250, 830 + i * 40, TextColor);
			i++;
		}
	}

	//선택지 출력
	if (showOptions) {
		for (int32 i = 0; i < data->Scene->OptionCount;i++) {
			Renderer_DrawTextSolid(&data->Scene->OptionList[i], 250, 895 + i * 40, data->OptionColors[i]);
		}
		Renderer_DrawImage(&OptionPointImage, 210, 895 + data->CurrentOptionNumber * 40);
	}

	//페이드 인 페이드 아웃 효과를 위한 검은색 배경
	Renderer_DrawImage(&data->BlackOutImage, 0, 0);
}

void release_main(void)
{
	MainScene* data = (MainScene*)g_Scene.Data;

	Image_FreeImage(&data->BlackOutImage);
	Text_FreeText(&NullText);
	Image_FreeImage(&OptionPointImage);
	ShowText = 0;

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