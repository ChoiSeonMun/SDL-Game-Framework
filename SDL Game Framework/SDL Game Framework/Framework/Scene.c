#include "stdafx.h"
#include "Scene.h"

#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

typedef struct tagScene {
	int32        Number;                    //�� �ѹ�
	const wchar_t* Name;                    //�� �̸�
	Image        BGImage;                //���ȭ��
	Music        BGM;                    //��� ����
	Image        AdditionImage;            //�߰� �̹���
	int32        AddImage_X;                //�߰� �̹��� ��ġ
	int32        AddImage_Y;                //�߰� �̹��� ��ġ
	SoundEffect     EffectSound;            //ȿ����
	int32        EffectSoundTiming;        //ȿ���� ǥ�� Ÿ�̹�
	int32        DialogCount;            //�ؽ�Ʈ ����
	Text		 DialogList[10][10];            //�ؽ�Ʈ �迭
	float		DialogSpeed;
	int32        OptionCount;            //�ɼ� ����
	Image        OptionImagesList[6];        //�ɼ� �̹��� �迭
	int32        NextSceneNumberList[6];        //�ɼ� ���ý� �Ѿ�� �� �ѹ�
	int32        NextEndingSceneNumberList[6];//���� ���� �������� ���

	int32		CurrentOptionNumber;
	int32		CurrentTextNumber;
} SceneStruct;

#define SCENE_COUNT	2
SceneStruct Scenes[SCENE_COUNT];

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
	L"�����̽� Ű�� ������ ���� ������ �Ѿ�ϴ�."
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

void setScenes(void) {
	Scenes[0].Number = 0;
	Scenes[0].Name = L"1-1";
	Image_LoadImage(&Scenes[0].BGImage, "bg.jpg");
	Scenes[0].BGImage.ScaleY -= 0.07f;
	Scenes[0].BGImage.ScaleX -= 0.07f;
	Audio_LoadMusic(&Scenes[0].BGM, "powerful.mp3");
	Image_LoadImage(&Scenes[0].AdditionImage, "NULL");
	Scenes[0].AddImage_X = 0;
	Scenes[0].AddImage_Y = 0;
	Audio_LoadMusic(&Scenes[0].EffectSound, "NULL");
	Scenes[0].EffectSoundTiming = NULL;

	Scenes[0].DialogCount = 3;
	Text_CreateText(&Scenes[0].DialogList[0][0], "d2coding.ttf", 50, L"���� �� �� �ִ�!!", wcslen(L"���� �� �� �ִ�!!"));
	Text_CreateText(&Scenes[0].DialogList[0][1], "d2coding.ttf", 50, L"�Ƹ���...", wcslen(L"�Ƹ���..."));
	Text_CreateText(&Scenes[0].DialogList[0][2], "d2coding.ttf", 50, L"", wcslen(L""));
	Text_CreateText(&Scenes[0].DialogList[1][0], "d2coding.ttf", 50, L"������...", wcslen(L"������..."));
	Text_CreateText(&Scenes[0].DialogList[1][1], "d2coding.ttf", 50, L"", wcslen(L""));
	Text_CreateText(&Scenes[0].DialogList[2][0], "d2coding.ttf", 50, L"���� ����?", wcslen(L"���� ����?"));
	Text_CreateText(&Scenes[0].DialogList[2][1], "d2coding.ttf", 50, L"", wcslen(L""));
	Scenes[0].DialogSpeed = 3.0f;

	Scenes[0].OptionCount = 4;
	for (int i = 0; i < Scenes[0].OptionCount;i++) {
		Image_LoadImage(&Scenes[0].OptionImagesList[i], "option.png");
		Scenes[0].OptionImagesList[i].ScaleY -= 0.45f;
		Scenes[0].OptionImagesList[i].ScaleX -= 0.45f;
		Image_SetAlphaValue(&Scenes[0].OptionImagesList[i], 125);
	}

	for (int i = 0; i < Scenes[0].OptionCount; i++) {
		Scenes[0].NextSceneNumberList[i] = 0;
	}

	Scenes[0].CurrentOptionNumber = 0;
	Scenes[0].CurrentTextNumber = 0;

	Scenes[1].Number = 1;
	Scenes[1].Name = L"1-2";
	Image_LoadImage(&Scenes[1].BGImage, "bg.jpg");
	Scenes[1].BGImage.ScaleY -= 0.07f;
	Scenes[1].BGImage.ScaleX -= 0.07f;
	Audio_LoadMusic(&Scenes[1].BGM, "powerful.mp3");
	Image_LoadImage(&Scenes[1].AdditionImage, "NULL");
	Scenes[1].AddImage_X = 0;
	Scenes[1].AddImage_Y = 0;
	Audio_LoadMusic(&Scenes[1].EffectSound, "NULL");
	Scenes[1].EffectSoundTiming = NULL;

	Scenes[1].DialogCount = 3;
	Text_CreateText(&Scenes[1].DialogList[0][0], "d2coding.ttf", 50, L"�̰��� 2��° ��!", wcslen(L"�̰��� 2��° ��!"));
	Text_CreateText(&Scenes[1].DialogList[0][1], "d2coding.ttf", 50, L"�Ƹ���...", wcslen(L"�Ƹ���..."));
	Text_CreateText(&Scenes[1].DialogList[0][2], "d2coding.ttf", 50, L"", wcslen(L""));
	Text_CreateText(&Scenes[1].DialogList[1][0], "d2coding.ttf", 50, L"������...", wcslen(L"������..."));
	Text_CreateText(&Scenes[1].DialogList[1][1], "d2coding.ttf", 50, L"", wcslen(L""));
	Text_CreateText(&Scenes[1].DialogList[2][0], "d2coding.ttf", 50, L"���� ����?", wcslen(L"���� ����?"));
	Text_CreateText(&Scenes[1].DialogList[2][1], "d2coding.ttf", 50, L"", wcslen(L""));
	Scenes[1].DialogSpeed = 3.0f;

	Scenes[1].OptionCount = 4;
	for (int i = 0; i < Scenes[0].OptionCount;i++) {
		Image_LoadImage(&Scenes[0].OptionImagesList[i], "option.png");
		Scenes[0].OptionImagesList[i].ScaleY -= 0.45f;
		Scenes[0].OptionImagesList[i].ScaleX -= 0.45f;
		Image_SetAlphaValue(&Scenes[0].OptionImagesList[i], 125);
	}

	for (int i = 0; i < Scenes[0].OptionCount; i++) {
		Scenes[0].NextSceneNumberList[i] = 0;
	}

	Scenes[0].CurrentOptionNumber = 0;
	Scenes[0].CurrentTextNumber = 0;
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
	SceneStruct   Scene;
	bool        isEndScene;
} MainScene;

bool isSceneChanging = false;
bool showOptions = false;
Text* ShowText;
int32 s_CurrentScene = 0;
void init_temp(void)
{
	g_Scene.Data = malloc(sizeof(MainScene));
	memset(g_Scene.Data, 0, sizeof(MainScene));

	MainScene* data = (MainScene*)g_Scene.Data;

	isSceneChanging = false;
	showOptions = false;
}

void update_temp(void)
{
	MainScene* data = (MainScene*) g_Scene.Data;

	//���� ���� ���
	if (!isSceneChanging) {

		//�ؽ�Ʈ ǥ�ð� �ʿ��� ���
		if (data->Scene.CurrentTextNumber < data->Scene.DialogCount) {
			int32 i = 0;
			ShowText = data->Scene.DialogList[data->Scene.CurrentTextNumber];
		}
		//�ɼ��� ���;��ϴ� ���
		else {
			showOptions = true;

			//������ ����
			int32 optionCount = data->Scene.OptionCount;

			Image_SetAlphaValue(&data->Scene.OptionImagesList[data->Scene.CurrentOptionNumber], 125);
			if (Input_GetKeyDown('1')) {
				if (optionCount >= 1) {
					data->Scene.CurrentOptionNumber = 0;
				}
			}
			if (Input_GetKeyDown('2')) {
				if (optionCount >= 2) {
					data->Scene.CurrentOptionNumber = 1;
				}
			}
			if (Input_GetKeyDown('3')) {
				if (optionCount >= 3) {
					data->Scene.CurrentOptionNumber = 2;
				}
			}
			if (Input_GetKeyDown('4')) {
				if (optionCount >= 4) {
					data->Scene.CurrentOptionNumber = 3;
				}
			}

			//�¿�Ű�� ����
			if (Input_GetKeyDown(VK_LEFT)) {
				if (data->Scene.CurrentOptionNumber > 0) {
					data->Scene.CurrentOptionNumber--;
				}
				else {
					data->Scene.CurrentOptionNumber = data->Scene.OptionCount - 1;
				}
			}

			if (Input_GetKeyDown(VK_RIGHT)) {
				if (data->Scene.CurrentOptionNumber < data->Scene.OptionCount - 1) {
					data->Scene.CurrentOptionNumber++;
				}
				else {
					data->Scene.CurrentOptionNumber = 0;
				}
			}

			//�� �Ʒ� Ű��(dksehlasdu)glglglg
			if (Input_GetKeyDown(VK_UP)) {
				if (data->Scene.OptionCount >= 3) {
					if (data->Scene.CurrentOptionNumber >= data->Scene.OptionCount / 2) {
						data->Scene.CurrentOptionNumber -= 2;
					}
				}
			}

			if (Input_GetKeyDown(VK_DOWN)) {
				if (data->Scene.OptionCount >= 3) {
					if (data->Scene.CurrentOptionNumber < data->Scene.OptionCount / 2) {
						data->Scene.CurrentOptionNumber += 2;
					}
				}
			}

			Image_SetAlphaValue(&data->Scene.OptionImagesList[data->Scene.CurrentOptionNumber], 255);

			//������ ����
			if (Input_GetKeyDown(VK_RETURN)) {
				isSceneChanging = true;
				s_CurrentScene = data->Scene.NextSceneNumberList[data->Scene.CurrentOptionNumber];
				Scene_SetNextScene(SCENE_TEMP);
			}
		}

		//Ű���� �� �Է�
		if (Input_GetKeyDown(VK_SPACE)) {
			if (data->Scene.CurrentTextNumber < data->Scene.DialogCount) {
				ShowText = &data->Scene.DialogList[data->Scene.CurrentTextNumber];
				data->Scene.CurrentTextNumber++;
			}
		}
	}
	
}

void render_temp(void)
{
	MainScene* data = (MainScene*)g_Scene.Data;

	//��� �̹��� ���
	Renderer_DrawImage(&data->Scene.BGImage, 0, 0);
	//Renderer_DrawImage(&TextBGImage, 30, 30);
	
	//�ؽ�Ʈ ���
	SDL_Color color = { 0,0,0,255 };
	int32 i = 0;
	while (ShowText[i].Length != 0) {
		Renderer_DrawTextSolid(&ShowText[i], 400, 300 + i * 100, color);
		i++;
	}

	//������ ���
	if (showOptions) {
		for (int i = 0; i < data->Scene.OptionCount;i++) {
			Renderer_DrawImage(&data->Scene.OptionImagesList[i], 250 + i % 2 * 700, 600 + (i/2) * 200);
		}
	}
}

void release_temp(void)
{
	MainScene* data = (MainScene*)g_Scene.Data;

	Audio_FreeMusic(&data->Scene.BGM);
	Audio_FreeMusic(&data->Scene.EffectSound);
	for (int32 i = 0; i < data->Scene.DialogCount;i++) {
		Text_FreeText(&data->Scene.DialogList[i]);
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