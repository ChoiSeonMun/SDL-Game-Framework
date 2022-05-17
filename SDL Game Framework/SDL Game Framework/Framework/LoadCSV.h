#pragma once
#include "stdafx.h"
#include "common.h"
#include "Text.h"
#include "Audio.h"
#include "Image.h"



typedef struct SceneData
{
	int32		index;
	char		BGMFileName[128];
	char		BackGroundFileName[128];
	int32		imageTime;
	int32		imageEffect;
	int32		textTime;
	int32		textSpeed;
	int32		textpos;
	int32		textEffect;
	char		textFileName1[128];
	char		textFileName2[128];
	char		textFileName3[128];
	char		select1[128];
	int32		select1Value;
	char		select2[128];
	int32		select2Value;
	char		select3[128];
	int32		select3Value;
} SceneData;



bool CSVInit(const char* ap_file_name, SceneData* data);
char* GetNextString(char* ap_src_str, char a_delimiter, char* ap_buffer);
