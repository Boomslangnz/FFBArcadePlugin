/*This file is part of FFB Arcade Plugin.
FFB Arcade Plugin is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
FFB Arcade Plugin is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with FFB Arcade Plugin.If not, see < https://www.gnu.org/licenses/>.
*/

#include <string>
#include "FordRacingOther.h"
static EffectTriggers *myTriggers;
static EffectConstants *myConstants;
static Helpers *myHelpers;
extern int EnableDamper;
extern int DamperStrength;

static bool init = false;

static int __stdcall Out32(DWORD device, DWORD data)
{
	if (device == 0x378)
	{
		if (data > 0xFFFF0013 && data < 0xFFFF001F)
		{
			double percentForce = (4294901791 - data) / 10.0;
			double percentLength = 100;
			myTriggers->Rumble(0, percentForce, percentLength);
			myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if (data > 5 && data < 16)
		{
			double percentForce = (16 - data) / 10.0;
			double percentLength = 100;
			myTriggers->Rumble(percentForce, 0, percentLength);
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

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);
		
	myTriggers = triggers;
	myConstants = constants;
	myHelpers = helpers;
}