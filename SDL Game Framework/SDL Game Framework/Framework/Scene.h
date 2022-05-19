#pragma once

#include "Type.h"

typedef struct Scene
{
	void (*Init)(void);		// ���� �ʱ�ȭ �ϴ� �Լ�
	void (*Update)(void);	// ������Ʈ
	void (*Render)(void);	// ����
	void (*Release)(void);	// ������ ����� �ڿ��� ����
	void* Data;
} Scene;

typedef enum SceneType
{
	SCENE_NULL,
	/*
	SCENE_TITLE,
	SCENE_MAIN,
	*/
	SCENE_EXTRA,
	SCENE_MAINSCREEN,
	SCENE_START,
	SCENE_SCENEONE,
	SCENE_SCENETWO,
	SCENE_SCENETHREE,
	SCENE_SCENEFORE,
	SCENE_SCENEFIVE,
	SCENE_SCENESIX,
	SCENE_MAX
} ESceneType;

extern Scene g_Scene;

/// <summary>
/// ���� ������ ��ȯ�� �����ΰ�?
/// </summary>
/// <returns>���� ������ ��ȯ�� �����̸� true, �ƴϸ� false</returns>
bool Scene_IsSetNextScene(void);

/// <summary>
/// ���� ���� �����Ѵ�.
/// </summary>
/// <param name="scene">��</param>
void Scene_SetNextScene(ESceneType scene);

/// <summary>
/// �� ��ȯ
/// </summary>
/// <param name=""></param>
void Scene_Change(void);
