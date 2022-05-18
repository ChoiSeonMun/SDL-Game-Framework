#pragma once

#include <wchar.h>

#define MAXIMUM_ROW 200

typedef struct CsvItem
{
	byte* RawData;
} CsvItem;

typedef struct CsvFile
{
	int32		ColumnCount;
	int32		RowCount;
	CsvItem*	Items[MAXIMUM_ROW];
} CsvFile;

/// <summary>
/// CSV 파일을 분석해 CsvFile 객체를 만든다.
/// </summary>
/// <param name="csvFile">CsvFile 객체</param>
/// <param name="filename">파일 이름</param>
void		CreateCsvFile(CsvFile* csvFile, const char* filename);

/// <summary>
/// CSV 객체의 자원을 반납한다.
/// </summary>
/// <param name="csvFile">CsvFile 객체</param>
void		FreeCsvFile(CsvFile* csvFile);

/// <summary>
/// 레코드를 정수로 가져온다.
/// </summary>
/// <param name="item">레코드</param>
/// <returns></returns>
int32		ParseToInt(const CsvItem item);

/// <summary>
/// 레코드를 문자열로 가져온다.
/// </summary>
/// <param name="item">레코드</param>
/// <returns></returns>
char*		ParseToAscii(const CsvItem item);

/// <summary>
/// 레코드를 유니코드 문자열로 가져온다.
/// </summary>
/// <param name="item">레코드</param>
/// <returns></returns>
wchar_t*	ParseToUnicode(const CsvItem item);