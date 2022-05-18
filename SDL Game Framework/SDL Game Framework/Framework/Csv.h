#pragma once

#include "Common.h"
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
	CsvItem* Items[MAXIMUM_ROW];
} CsvFile;

/// <summary>
/// CSV ������ �м��� CsvFile ��ü�� �����.
/// </summary>
/// <param name="csvFile">CsvFile ��ü</param>
/// <param name="filename">���� �̸�</param>
void		CreateCsvFile(CsvFile* csvFile, const char* filename);

/// <summary>
/// CSV ��ü�� �ڿ��� �ݳ��Ѵ�.
/// </summary>
/// <param name="csvFile">CsvFile ��ü</param>
void		FreeCsvFile(CsvFile* csvFile);

/// <summary>
/// ���ڵ带 ������ �����´�.
/// </summary>
/// <param name="item">���ڵ�</param>
/// <returns></returns>
int32		ParseToInt(const CsvItem item);

/// <summary>
/// ���ڵ带 ���ڿ��� �����´�.
/// </summary>
/// <param name="item">���ڵ�</param>
/// <returns></returns>
char* ParseToAscii(const CsvItem item);

/// <summary>
/// ���ڵ带 �����ڵ� ���ڿ��� �����´�.
/// </summary>
/// <param name="item">���ڵ�</param>
/// <returns></returns>
wchar_t* ParseToUnicode(const CsvItem item);