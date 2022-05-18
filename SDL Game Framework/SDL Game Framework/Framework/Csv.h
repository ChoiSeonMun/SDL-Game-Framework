#pragma once

#include <wchar.h>
#include <stdint.h>

#define MAXIMUM_ROW 200

//
struct Parsing_Data {
    uint8_t ID;
    uint8_t SENCE_NUMBER;
    uint8_t SCREEN_SIZE_X;
    uint8_t SCREEN_SIZE_Y;
    wchar_t IMG_1[128];

    wchar_t IMG_POSITION[10];
    uint8_t IMG_DELAY_TIME;
    wchar_t IMG_OUTPUT_STYLE[128];
    wchar_t SOUND_1[128];
    uint8_t SOUND_DELAY_TIME;

    //x줄 y길이
    wchar_t TEXT[2000];
    wchar_t TEXT_POSITION[10];
    uint8_t TEXT_DELAY_TIME;
    wchar_t TEXT_OUTPUT_STYLE[10];
    wchar_t CHOOSE_POSITION[10];

    uint8_t CHOOSE_NUM_1;
    uint8_t CHOOSE_NUM_2;
    uint8_t CHOOSE_NUM_3;
    wchar_t CHOOSE_TEXT_1[128];
    wchar_t CHOOSE_TEXT_2[128];

    wchar_t CHOOSE_TEXT_3[128];
    wchar_t CHOOSE_STYLE[10];

};

//

typedef struct Parsing {
    struct Parsing_Data sceneData[200]; //200은 데이터 200줄 받음
}parsing;

extern parsing parsing_dt;


typedef struct CsvItem
{
    char* RawData;
} CsvItem;

typedef struct CsvFile
{
    int			ColumnCount;
    int			RowCount;
    CsvItem* Items[MAXIMUM_ROW];
} CsvFile;

void CreateCsvFile(CsvFile* csvFile, const char* filename);
int			ParseToInt(const CsvItem item);
char* ParseToAscii(const CsvItem item);
wchar_t* ParseToUnicode(char* str);