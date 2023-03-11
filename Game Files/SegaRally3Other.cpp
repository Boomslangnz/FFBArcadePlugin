#include <string>
#include "SegaRally3Other.h"

static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;
extern int EnableDamper;
extern int DamperStrength;

static bool init = false;

static int __stdcall Out32(DWORD device, DWORD data)
{
	if (EnableDamper == 1)
	{
		myTriggers->Damper(DamperStrength / 100.0);
	}

	if (data > 15)
	{
		double percentForce = (31 - data) / 15.0;
		double percentLength = 100;
		myTriggers->Rumble(percentForce, 0, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
	}
	else if (data > 0)
	{
		double percentForce = (16 - data) / 15.0;
		double percentLength = 100;
		myTriggers->Rumble(0, percentForce, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
	}
	return 0;
}

static bool Hook(void* toHook, void* ourFunct, int len) {
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

void SegaRally3Other::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {
	if (!init)
	{
		HMODULE hMod = GetModuleHandleA("inpout32.dll");
		if (hMod)
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