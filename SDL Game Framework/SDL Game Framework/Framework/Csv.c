#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>   


#include "Csv.h"

static char* s_Buffer;
static char* s_BufferPointer;

void readFileToBuffer(const char* filename)
{
    FILE* fp;
    if (0 != fopen_s(&fp, filename, "r"))
    {
        return;
    }
    //
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);

    s_Buffer = malloc(sizeof(char) * (fileSize + 1));
    memset(s_Buffer, 0, sizeof(char) * (fileSize + 1));

    fseek(fp, 0, SEEK_SET);
    fread(s_Buffer, fileSize, 1, fp);

    fclose(fp);
}


int countCategory(const char* firstLine)
{
    int result = 1;
    while (*firstLine != '\n')
    {
        if (*firstLine == ',')
        {
            ++result;

        }

        ++firstLine;
    }

    return result;
}

void CreateCsvFile(CsvFile* csvFile, const char* filename)
{
    readFileToBuffer(filename);

    //칼럼수
    csvFile->ColumnCount = countCategory(s_Buffer);
    for (int i = 0; i < MAXIMUM_ROW; ++i)
    {
        csvFile->Items[i] = (CsvItem*)malloc(sizeof(CsvItem) * csvFile->ColumnCount);
    }

    //
    s_BufferPointer = s_Buffer;
    while (*s_BufferPointer != '\0')
    {
        int row = csvFile->RowCount;

        // 한 줄을 읽어들인다.
        int commaCount = 0;
        int quotesCount = 0;
        const char* lineStart = s_BufferPointer;
        const char* lineEnd = lineStart;
        while (true)
        {
            if (csvFile->ColumnCount - 1 == commaCount && '\n' == *lineEnd)
            {
                break;
            }

            if (*lineEnd == ',')
            {
                ++commaCount;
            }

            ++lineEnd;
        }

        // 콤마 분류
        const char* recordStart = lineStart;
        const char* recordEnd = recordStart;
        for (int i = 0; i < csvFile->ColumnCount; ++i)
        {
            while (*recordEnd != '@' && recordEnd != lineEnd)//null이 아닐때임
            {
                ++recordEnd;
            }

            int size = recordEnd - recordStart;
            csvFile->Items[row][i].RawData = (char*)malloc(sizeof(char) * (size + 1));
            //레코드 사이즈 별로 데이터 담기
            memcpy(csvFile->Items[row][i].RawData, recordStart, size);
            csvFile->Items[row][i].RawData[size] = '\0';

            recordStart = recordEnd + 1;
            recordEnd = recordStart;
        }

        ++csvFile->RowCount;

        s_BufferPointer = lineEnd + 1;
    }

}

int ParseToInt(const CsvItem item)
{
    char* end;
    return strtol(item.RawData, &end, 10);
}

char* ParseToAscii(const CsvItem item)
{
    int size = strlen(item.RawData);
    char* result = malloc(size + 1);
    memset(result, 0, size + 1);
    if (item.RawData[0] == '"' && item.RawData[1] == '"' && item.RawData[size - 1] == '"' && item.RawData[size - 2] == '"') {
        memcpy(result, &item.RawData[2], size - 4);
    }
    else if (item.RawData[0] == '"' && item.RawData[size - 1] == '"')
    {
        memcpy(result, &item.RawData[1], size - 2);
    }
    else
    {
        memcpy(result, item.RawData, size);
    }
    return result;
}

wchar_t* ParseToUnicode(char* str)
{

    int size = MultiByteToWideChar(CP_ACP, NULL, str, -1, NULL, NULL);
    wchar_t* result = (wchar_t*)malloc(sizeof(wchar_t) * (size + 1));
    MultiByteToWideChar(CP_ACP, NULL, str, -1, result, size);

    return result;
}