#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "csv.h"
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
#include "Csvparser.h"

//

Parsing parsing_dt;

void csvParser(void)
{
	CsvFile csvFile;
	memset(&csvFile, 0, sizeof(CsvFile));
	CreateCsvFile(&csvFile, "obt.csv");

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
				case 0:
					parsing_dt.sceneData[r - 1].ID = atoi(&strt[0]);
					break;
				case 1:
					parsing_dt.sceneData[r - 1].SENCE_NUMBER = atoi(&strt[0]);
					break;
				case 2:
					strcpy_s(parsing_dt.sceneData[r - 1].MAIN_IMAGE, sizeof(parsing_dt.sceneData[r - 1].MAIN_IMAGE), strt);
					break;
				case 3:
					parsing_dt.sceneData[r - 1].IMG_OUTPUT_STYLE = atoi(&strt[0]);
					break;
				case 4:
					strcpy_s(parsing_dt.sceneData[r - 1].SOUND_NAME, sizeof(parsing_dt.sceneData[r - 1].SOUND_NAME), strt);
					break;
				case 5:
					strcpy_s(parsing_dt.sceneData[r - 1].EFFECT_SOUND_NAME, sizeof(parsing_dt.sceneData[r - 1].EFFECT_SOUND_NAME), strt);
					break;
				case 6:
					parsing_dt.sceneData[r - 1].EFFECT_COUNT = atoi(&strt[0]);
					break;
				case 7:
					wcscpy_s(parsing_dt.sceneData[r - 1].TEXT, sizeof(parsing_dt.sceneData[r - 1].TEXT), str);
					break;
				case 8:
					parsing_dt.sceneData[r - 1].CHOOSE_1_NEXT_SCENE = atoi(&strt[0]);
					break;
				case 9:
					wcscpy_s(parsing_dt.sceneData[r - 1].CHOOSE_TEXT_1, sizeof(parsing_dt.sceneData[r - 1].CHOOSE_TEXT_1), str);
					break;
				case 10:
					parsing_dt.sceneData[r - 1].CHOOSE_2_NEXT_SCENE = atoi(&strt[0]);
					break;
				case 11:
					wcscpy_s(parsing_dt.sceneData[r - 1].CHOOSE_TEXT_2, sizeof(parsing_dt.sceneData[r - 1].CHOOSE_TEXT_2), str);
					break;
				case 12:
					parsing_dt.sceneData[r - 1].CHOOSE_3_NEXT_SCENE = atoi(&strt[0]);
					break;
				case 13:
					wcscpy_s(parsing_dt.sceneData[r - 1].CHOOSE_TEXT_3, sizeof(parsing_dt.sceneData[r - 1].CHOOSE_TEXT_3), str);
					break;
				}
			}
		}
	}


}
