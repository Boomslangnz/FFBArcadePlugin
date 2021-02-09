#include <string>
#include "StormRacerG.h"
static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;

static bool init = false;

static void __cdecl UsbIO_SetSeatShakeImpluse(int a1, int a2, float a3, bool a4)
{
	double percentForce = a1 / 1200.0;
	myTriggers->Rumble(percentForce, percentForce, 150);
	return;
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

void StormRacerG::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (!init)
	{
		uintptr_t ImageBaseSRG = (uintptr_t)GetModuleHandle((L"racing.exe"));

		int hookLength = 6;
		DWORD hookAddress = ImageBaseSRG + 0x12C5DE;

		jmpBackAddy = hookAddress + hookLength;
		Hook((void*)hookAddress, UsbIO_SetSeatShakeImpluse, hookLength);
		helpers->WriteNop(ImageBaseSRG + 0x12C5DE + 5, 1, false);

		init = true;
	}

	UINT8 FFB = helpers->ReadByte(0x46F429C, false);
	UINT8 Enable = helpers->ReadByte(0x4710214, false);
	float speedo = helpers->ReadFloat32(0x114A22D8, false);

	if (Enable == 0x01)
	{
		if (speedo < 0)
		{
			speedo = -speedo;
		}

		double percentForce = speedo / 320.0;

		//4 == Slipstring

		if (FFB & 0x01)
		{
			myTriggers->Rumble(percentForce, percentForce, 150);
		}

		if (FFB & 0x02)
		{
			myTriggers->Rumble(percentForce, percentForce, 150);
		}

		if (FFB & 0x08)
		{
			myTriggers->Rumble(percentForce, percentForce, 150);
		}
	}

	myTriggers = triggers;
	myConstants = constants;
	myHelpers = helpers;
}