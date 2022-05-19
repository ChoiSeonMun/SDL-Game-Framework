#include "stdafx.h"
#include "PageManager.h"
#include "PageIndex.h"

void PageManager_Init(PageManager* pageManager)
{
	CsvFile csvFile = { 0 };
	CreateCsvFile(&csvFile, "CsvTest.csv");

	for (int32 page = 1; page < csvFile.RowCount; ++page)
	{
		pageManager->Pages[page].ID = ParseToInt(csvFile.Items[page][COL_PAGE_INDEX]);

		const char* backgroundImageFileName = ParseToAscii(csvFile.Items[page][COL_BACKGROUND_IMAGE]);
		Image_LoadImage(&pageManager->Pages[page].Background, backgroundImageFileName);

		const char* backgroundMusicFileName = ParseToAscii(csvFile.Items[page][COL_BACKGROUND_MUSIC]);
		Audio_LoadMusic(&pageManager->Pages[page].Bgm, backgroundMusicFileName);

		int32 diff = COL_OPTION2 - COL_OPTION1;
		for (int32 i = 0; i < 2; ++i)
		{
			Page_SetOption(&pageManager->Pages[page], i, csvFile.Items[page], COL_OPTION1 + i * diff);
		}

		SafeFree(backgroundImageFileName);
		SafeFree(backgroundMusicFileName);

		Page_Init(&pageManager->Pages[page]);
	}

	FreeCsvFile(&csvFile);

	pageManager->CurrentPage = &pageManager->Pages[PAGE_1];
	pageManager->NextPage = NULL;
}

void PageManager_Update(PageManager* pageManager)
{
	if (pageManager->NextPage != NULL)
	{
		pageManager->CurrentPage = pageManager->NextPage;
		pageManager->NextPage = NULL;
	}

	Page_Update(pageManager->CurrentPage);

	if (Input_GetKeyDown(VK_SPACE))
	{
		int32 nextPageIndex = pageManager->CurrentPage->Options->NextPage;
		pageManager->NextPage = &pageManager->Pages[nextPageIndex];
	}
}

void PageManager_Render(PageManager* pageManager)
{
	Page_Render(pageManager->CurrentPage);
}

void PageManager_Release(PageManager* pageManager)
{
	for (int32 i = 0; i < MAX_PAGE_COUNT; ++i)
	{
		Page_Release(&pageManager->Pages[i]);
	}
}
