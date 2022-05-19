#pragma once

#include "Config.h"
#include "Page.h"

typedef struct PageManager
{
	Page	Pages[MAX_PAGE_COUNT];
	Page*	CurrentPage;
	Page*	NextPage;
} PageManager;

void PageManager_Init(PageManager* pageManager);
void PageManager_Update(PageManager* pageManager);
void PageManager_Render(PageManager* pageManager);
void PageManager_Release(PageManager* pageManager);