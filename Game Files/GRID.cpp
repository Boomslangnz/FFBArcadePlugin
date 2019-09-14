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

#include "GRID.h"
#include <Windows.h>
#include <string>

static bool __stdcall Out32(int a2, DWORD BytesReturned)
{
	static char test[256];
	memset(test, 0, 256);
	sprintf(test, "hex print: %08X", BytesReturned);
	OutputDebugStringA(test);
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

void GRID::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers)
{
	bool init = false;
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
}