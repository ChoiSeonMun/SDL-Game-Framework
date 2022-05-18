#include "stdafx.h"
#include "Common.h"
#include "Input.h"

#define IS_KEY_DOWN(vkey) (0x8000 & GetAsyncKeyState(vkey))


bool s_isKeyDownOnPrevFrame[256];
bool s_isKeyDownOnCurrentFrame[256];


void Input_Update(void)
{
	memcpy(s_isKeyDownOnPrevFrame, s_isKeyDownOnCurrentFrame, sizeof(s_isKeyDownOnCurrentFrame));

	for (int32 vkey = 0; vkey < 256; ++vkey)
	{
		if (IS_KEY_DOWN(vkey))
		{
			s_isKeyDownOnCurrentFrame[vkey] = true;
		}
		else
		{
			s_isKeyDownOnCurrentFrame[vkey] = false;
		}
	}
}

bool Input_GetKeyDown(uint8 vkey)
{
	if (false == s_isKeyDownOnPrevFrame[vkey] && true == s_isKeyDownOnCurrentFrame[vkey])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Input_GetKeyUp(uint8 vkey)
{
	if (true == s_isKeyDownOnPrevFrame[vkey] && false == s_isKeyDownOnCurrentFrame[vkey])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Input_GetKey(uint8 vkey)
{
	if (true == s_isKeyDownOnPrevFrame[vkey] && true == s_isKeyDownOnCurrentFrame[vkey])
	{
		return true;
	}
	else
	{
		return false;
	}
}

int32 Count = 0;

void Input_Choice(uint8 vkey, uint8 vkey2)
{
	if (Input_GetKeyDown(vkey) && Count >= 1)
	{
		return Count--;
	}
	if (Input_GetKeyDown(vkey2) && Count < 2)
	{
		return Count++;
	}

}