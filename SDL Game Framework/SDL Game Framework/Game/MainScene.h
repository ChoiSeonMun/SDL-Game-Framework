//#pragma once
//
//#include "Framework.h"
//
//typedef struct tagScene {
//    int32        Number;                    //씬 넘버
//    wchar_t*    Name;                    //씬 이름
//    Image        BGImage;                //배경화면
//    Music        BGM;                    //배경 음악
//    Image        AdditionImage;            //추가 이미지
//    int32        AddImage_X;                //추가 이미지 위치
//    int32        AddImage_Y;                //추가 이미지 위치
//    SoundEffect     EffectSound;            //효과음
//    int32        EffectSoundTiming;        //효과음 표현 타이밍
//    int32        DialogCount;            //텍스트 갯수
//    Text*           DialogList[1024];            //텍스트 배열
//    int32        OptionCount;            //옵션 갯수
//    Image        OptionImagesList[6];        //옵션 이미지 배열
//    int32        NextSceneNumberList[6];        //옵션 선택시 넘어가는 씬 넘버
//    int32        NextEndingSceneNumberList[6];//다음 씬이 엔딩씬일 경우
//} SceneStruct;
//
//typedef struct tagMainScene {
//    SceneStruct   Scene;
//    bool        isEndScene;
//} MainScene;
//
//void MainScene_Init(MainScene* scene, SceneStruct* sceneList);
//void MainScene_Update(MainScene* scene);
//void MainScene_Render(MainScene* scene);
//void MainScene_Release(MainScene* scene);