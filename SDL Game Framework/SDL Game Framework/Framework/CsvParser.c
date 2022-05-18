#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "Csv.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
#include "CsvParser.h"
#include <crtdbg.h>

//

parsing parsing_dt;

void csvParser(void)
{

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	CsvFile csvFile;
	memset(&csvFile, 0, sizeof(CsvFile));
	CreateCsvFile(&csvFile, "game.csv");

	//
	// CSV 파일 파싱한 후 텍스트 그려본 다음 제대로 출력 안되면
	// App_Init()에 아래 구문 추가
	setlocale(LC_ALL, "kr_KR.utf8");

	//
	for (int r = 0; r < csvFile.RowCount; ++r)
	{
		for (int c = 0; c < csvFile.ColumnCount; ++c)
		{

			if (r != 0) {

				char* strt = ParseToAscii(csvFile.Items[r][c]);
				wchar_t* str = ParseToUnicode(strt);



				switch (c) {
				case 0: parsing_dt.sceneData[r - 1].ID = atoi(str); break;
				case 1: parsing_dt.sceneData[r - 1].SENCE_NUMBER = atoi(str); break;
				case 2: strcpy_s(parsing_dt.sceneData[r - 1].MAIN_IMAGE, sizeof(parsing_dt.sceneData[r - 1].MAIN_IMAGE), strt); break;
				case 3: parsing_dt.sceneData[r - 1].IMG_OUTPUT_STYLE = atoi(str); break;
				case 4: strcpy_s(parsing_dt.sceneData[r - 1].SOUND_NAME, sizeof(parsing_dt.sceneData[r - 1].SOUND_NAME), strt); break;
				case 5: strcpy_s(parsing_dt.sceneData[r - 1].EFFECT_SOUND_NAME, sizeof(parsing_dt.sceneData[r - 1].EFFECT_SOUND_NAME), strt); break;
				case 6: parsing_dt.sceneData[r - 1].EFFECT_COUNT = atoi(str); break;
				case 7: wcscpy_s(parsing_dt.sceneData[r - 1].TEXT, sizeof(parsing_dt.sceneData[r - 1].TEXT), str); break;
				case 8: parsing_dt.sceneData[r - 1].CHOOSE_1_NEXT_SCENE = atoi(str); break;
				case 9: wcscpy_s(parsing_dt.sceneData[r - 1].CHOOSE_1_TEXT, sizeof(parsing_dt.sceneData[r - 1].CHOOSE_1_TEXT), str); break;
				case 10: parsing_dt.sceneData[r - 1].CHOOSE_2_NEXT_SCENE = atoi(str); break;
				case 11: wcscpy_s(parsing_dt.sceneData[r - 1].CHOOSE_2_TEXT, sizeof(parsing_dt.sceneData[r - 1].CHOOSE_2_TEXT), str); break;
				case 12: parsing_dt.sceneData[r - 1].CHOOSE_3_NEXT_SCENE = atoi(str); break;
				case 13:  wcscpy_s(parsing_dt.sceneData[r - 1].CHOOSE_3_TEXT, sizeof(parsing_dt.sceneData[r - 1].CHOOSE_3_TEXT), str); break;
				}

			}
		}
	}

	FreeCsvFile(&csvFile);

}


//void multiLineText(Text GuideLine[], const wchar_t* rawString, const char* fontFile, int32 fontSize) {
//	
//	
//	wchar_t* lineStart = rawString;
//	wchar_t* lineEnd = lineStart;
//
//	int count = 1;
//	for (int i = 0; rawString[i] != L'\0'; i++)
//	{
//		count++;
//	}
//
//	//유니코드에 개행이 있을때 카운트해서 반복문 돌리기
//	for (int32 i = 0; i < count; ++i)
//	{
//		while (true)
//		{
//			if (*lineEnd == L'\n' || *lineEnd == L'\0')
//			{
//				break;
//			}
//
//			++lineEnd;
//		}
//
//		int32 len = lineEnd - lineStart;
//		Text_CreateText(&data->GuideLine[i], fontFile, fontSize, lineStart, len);
//
//		lineStart = lineEnd + 1;
//		lineEnd = lineStart;
//	}
//
//}