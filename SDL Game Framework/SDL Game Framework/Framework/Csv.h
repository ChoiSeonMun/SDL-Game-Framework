#pragma once

#include <wchar.h>
#include <stdint.h>

#define MAXIMUM_ROW 200

//
//
struct Parsing_Data {
    int16   ID;
    int16   SENCE_NUMBER;
    char    MAIN_IMAGE[128];

    int16   IMG_OUTPUT_STYLE;
    char    SOUND_NAME[128];

    char    EFFECT_SOUND_NAME[128];
    int16   EFFECT_COUNT;
    wchar_t TEXT[2000];

    int16   CHOOSE_1_NEXT_SCENE;
    wchar_t CHOOSE_TEXT_1[128];

    int16   CHOOSE_2_NEXT_SCENE;
    wchar_t CHOOSE_TEXT_2[128];

    int16   CHOOSE_3_NEXT_SCENE;
    wchar_t CHOOSE_TEXT_3[128];
};

//

typedef struct Parsing {
    struct Parsing_Data sceneData[200]; //200Àº µ¥ÀÌÅÍ 200ÁÙ ¹ÞÀ½
}Parsing;

extern Parsing parsing_dt;


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