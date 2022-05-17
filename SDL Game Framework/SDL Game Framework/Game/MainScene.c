//#include "MainScene.h"
//#include "stdafx.h"
//#include "Framework/Scene.h"
//
//SceneStruct* s_SceneList;
//SceneStruct* s_EndSceneList;
//
//static int32 s_prevScene;
//static int32 s_CurrentOptionNumber;
//static int32 s_CurrentDialogNumber;
//
//void MainScene_Init(MainScene* scene, SceneStruct* sceneList, SceneStruct* endSceneList) {
//	s_SceneList = sceneList;
//	scene->Scene = s_SceneList[0];
//	s_CurrentDialogNumber = 0;
//	s_CurrentOptionNumber = 0;
//}
//
//void MainScene_Update(MainScene* scene) {
//
//	if(Input_
//
//	if (Input_GetKeyDown(VK_RETURN)) {
//		int32 nextScene = scene->Scene.NextSceneNumberList[s_CurrentOptionNumber];
//		if (nextScene == NULL) {
//			scene->Scene = s_SceneList[nextScene];
//		}
//		else {
//			nextScene = scene->Scene.NextEndingSceneNumberList[s_CurrentOptionNumber];
//		}
//	}
//}
//
//void MainScene_Render(MainScene* scene) {
//
//}
//
//void MainScene_Release(MainScene* scene) {
//
//}