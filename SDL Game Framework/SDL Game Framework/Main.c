#include "stdafx.h"
#include "App.h"

int main(int argc, char* argv[])
{
	if (false == App_Init())
	{
		return 1;
	}

	int32 appResult = App_Run();

	return appResult;
}