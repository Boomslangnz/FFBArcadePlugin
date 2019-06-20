#include <string>
#include "FordRacingOther.h"
static EffectTriggers *myTriggers;
static EffectConstants *myConstants;
static Helpers *myHelpers;

static bool init = false;

static int __stdcall Out32(DWORD device, DWORD data)
{
	if (device == 0x378)
	{
		if (data > 0xFFFF0013 && data < 0xFFFF001F)
		{
			double percentForce = (4294901791 - data) / 10.0;
			double percentLength = 100;
			myTriggers->LeftRight(0, percentForce, percentLength);
			myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if (data > 5 && data < 16)
		{
			double percentForce = (16 - data) / 10.0;
			double percentLength = 100;
			myTriggers->LeftRight(percentForce, 0, percentLength);
			myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
		}
	}
	return 0;
}

static bool Hook(void * toHook, void * ourFunct, int len) {
	if (len < 5) {
		return false;
	}

	DWORD curProtection;
	VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);

	memset(toHook, 0x90, len);

	DWORD relativeAddress = ((DWORD)ourFunct - (DWORD)toHook) - 5;

	*(BYTE*)toHook = 0xE9;
	*(DWORD*)((DWORD)toHook + 1) = relativeAddress;

	DWORD temp;
	VirtualProtect(toHook, len, curProtection, &temp);

	return true;
}

static DWORD jmpBackAddy;

void FordRacingOther::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	HMODULE hMod = GetModuleHandleA("inpout32.dll");
	if (hMod)
	{
		if (!init)
		{
			int hookLength = 6;
			DWORD hookAddress = (DWORD)GetProcAddress(GetModuleHandle(L"inpout32.dll"), "Out32");
			if (hookAddress)
			{	
				jmpBackAddy = hookAddress + hookLength;
				Hook((void*)hookAddress, Out32, hookLength);
				init = true;
			}

		}
	}
	myTriggers = triggers;
	myConstants = constants;
	myHelpers = helpers;
}