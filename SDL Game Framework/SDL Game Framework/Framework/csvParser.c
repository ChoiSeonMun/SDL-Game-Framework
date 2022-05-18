#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "csv.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
#include "csvparser.h"

parsing parsing_dt;

void csvParser(void)
{
	CsvFile csvFile;
	memset(&csvFile, 0, sizeof(CsvFile));
	CreateCsvFile(&csvFile, "game.csv");

	// CSV 파일 파싱한 후 텍스트 그려본 다음 제대로 출력 안되면
	// App_Init()에 아래 구문 추가
	setlocale(LC_ALL, "kr_KR.utf8");


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
				case 2: parsing_dt.sceneData[r - 1].SCREEN_SIZE_X = atoi(str); break;
				case 3: parsing_dt.sceneData[r - 1].SCREEN_SIZE_Y = atoi(str); break;//여기 부터
				case 4: wcscpy_s(parsing_dt.sceneData[r - 1].IMG_1,sizeof(parsing_dt.sceneData[r - 1].IMG_1), str); break;
				case 5: wcscpy_s(parsing_dt.sceneData[r - 1].IMG_POSITION,sizeof(parsing_dt.sceneData[r - 1].IMG_POSITION), str); break;
				case 6: parsing_dt.sceneData[r - 1].IMG_DELAY_TIME = atoi(str); break;
				case 7: wcscpy_s(parsing_dt.sceneData[r - 1].IMG_OUTPUT_STYLE,sizeof(parsing_dt.sceneData[r - 1].IMG_OUTPUT_STYLE), str); break;
				case 8: wcscpy_s(parsing_dt.sceneData[r - 1].SOUND_1,sizeof(parsing_dt.sceneData[r - 1].SOUND_1), str); break;
				case 9: parsing_dt.sceneData[r - 1].SOUND_DELAY_TIME = atoi(str); break;
				case 10: wcscpy_s(parsing_dt.sceneData[r - 1].TEXT,sizeof(parsing_dt.sceneData[r - 1].TEXT), str); break;
				case 11: wcscpy_s(parsing_dt.sceneData[r - 1].TEXT_POSITION,sizeof(parsing_dt.sceneData[r - 1].TEXT_POSITION), str); break;
				case 12: parsing_dt.sceneData[r - 1].TEXT_DELAY_TIME = atoi(str); break;
				case 13: wcscpy_s(parsing_dt.sceneData[r - 1].TEXT_OUTPUT_STYLE,sizeof(parsing_dt.sceneData[r - 1].TEXT_OUTPUT_STYLE), str); break;
				case 14: wcscpy_s(parsing_dt.sceneData[r - 1].CHOOSE_POSITION,sizeof(parsing_dt.sceneData[r - 1].CHOOSE_POSITION), str); break;
				case 15: parsing_dt.sceneData[r - 1].CHOOSE_NUM_1 = atoi(str); break;
				case 16: parsing_dt.sceneData[r - 1].CHOOSE_NUM_2 = atoi(str); break;
				case 17: parsing_dt.sceneData[r - 1].CHOOSE_NUM_3 = atoi(str); break;
				case 18: wcscpy_s(parsing_dt.sceneData[r - 1].CHOOSE_TEXT_1,sizeof(parsing_dt.sceneData[r - 1].CHOOSE_TEXT_1), str); break;
				case 19: wcscpy_s(parsing_dt.sceneData[r - 1].CHOOSE_TEXT_2,sizeof(parsing_dt.sceneData[r - 1].CHOOSE_TEXT_2), str); break;
				case 20: wcscpy_s(parsing_dt.sceneData[r - 1].CHOOSE_TEXT_3, sizeof(parsing_dt.sceneData[r - 1].CHOOSE_TEXT_3), str); break;
				case 21: wcscpy_s(parsing_dt.sceneData[r - 1].CHOOSE_STYLE,sizeof(parsing_dt.sceneData[r - 1].CHOOSE_STYLE), str); break;
				}
			}
		}
	}


}