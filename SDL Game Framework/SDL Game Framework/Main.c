#include "stdafx.h"
#include "App.h"

#include <crtdbg.h>
#include "Framework/Csv.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	/*CsvFile csv;
	CreateCsvFile(&csv, "test.csv");

	int32 temp = ParseToInt(csv.Items[1][0]);
	printf("%d", temp);*/

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	if (false == App_Init())
	{
		return 1;
	}
	
	int32 appResult = App_Run();
	
	return appResult;
}