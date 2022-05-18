#include "stdafx.h"
#include "App.h"

#include <crtdbg.h>


int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(93);

	if (false == App_Init())
	{
		return 1;
	}

	int32 appResult = App_Run();

	return appResult;
}