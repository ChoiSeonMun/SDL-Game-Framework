//#pragma once
//
//#include "Framework.h"
//
//typedef struct tagScene {
//    int32        Number;                    //�� �ѹ�
//    wchar_t*    Name;                    //�� �̸�
//    Image        BGImage;                //���ȭ��
//    Music        BGM;                    //��� ����
//    Image        AdditionImage;            //�߰� �̹���
//    int32        AddImage_X;                //�߰� �̹��� ��ġ
//    int32        AddImage_Y;                //�߰� �̹��� ��ġ
//    SoundEffect     EffectSound;            //ȿ����
//    int32        EffectSoundTiming;        //ȿ���� ǥ�� Ÿ�̹�
//    int32        DialogCount;            //�ؽ�Ʈ ����
//    Text*           DialogList[1024];            //�ؽ�Ʈ �迭
//    int32        OptionCount;            //�ɼ� ����
//    Image        OptionImagesList[6];        //�ɼ� �̹��� �迭
//    int32        NextSceneNumberList[6];        //�ɼ� ���ý� �Ѿ�� �� �ѹ�
//    int32        NextEndingSceneNumberList[6];//���� ���� �������� ���
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