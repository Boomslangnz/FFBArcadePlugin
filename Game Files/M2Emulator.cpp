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
#include <tchar.h>
#include "M2Emulator.h"
#include "math.h"
#include "SDL.h"

static bool init = false;

static bool __stdcall ExitHook(UINT uExitCode)
{
	TerminateProcess(GetCurrentProcess(), 0);
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

void M2Emulator::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers) {
	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int FFBMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBMode"), 0, settingsFilename);
	int DaytonaAIMultiplayerHack = GetPrivateProfileInt(TEXT("Settings"), TEXT("DaytonaAIMultiplayerHack"), 0, settingsFilename);
	int DaytonaForcePanoramicAttract = GetPrivateProfileInt(TEXT("Settings"), TEXT("DaytonaForcePanoramicAttract"), 0, settingsFilename);

	HWND hWnd1 = FindWindowA(0, ("Sega Rally Championship"));
	HWND hWnd2 = FindWindowA(0, ("Daytona USA"));
	HWND hWnd3 = FindWindowA(0, ("Indianapolis 500 (Rev A, Deluxe)"));
	HWND hWnd4 = FindWindowA(0, ("Sega Touring Car Championship (Rev A)"));
	HWND hWnd5 = FindWindowA(0, ("Over Rev"));
	HWND hWnd6 = FindWindowA(0, ("Super GT 24h"));
	HWND hWnd7 = FindWindowA(0, ("Daytona USA '93 Edition"));
	HWND hWnd8 = FindWindowA(0, ("Daytona USA (Saturn Ads)"));
	HWND hWnd9 = FindWindowA(0, ("Daytona USA Special Edition"));
	HWND hWnd10 = FindWindowA(0, ("Daytona USA Turbo"));
	HWND hWnd11 = FindWindowA(0, ("Daytona USA Turbo (Rev A)"));
	HWND hWnd12 = FindWindowA(0, ("Daytona USA: GTX 2004"));
	HWND hWnd13 = FindWindowA(0, ("Daytona USA: To The Maxx"));
	HWND hWnd14 = FindWindowA(0, ("Sega Rally Championship (Rev B)"));
	HWND hWnd15 = FindWindowA(0, ("Sega Rally Pro Drivin'"));
	HWND hWnd16 = FindWindowA(0, ("Indianapolis 500 (Rev A, Twin, Newer rev)"));
	HWND hWnd17 = FindWindowA(0, ("Indianapolis 500 (Rev A, Twin, Older rev)"));
	HWND hWnd18 = FindWindowA(0, ("Sega Touring Car Championship"));
	HWND hWnd19 = FindWindowA(0, ("Sega Touring Car Championship (Rev B)"));
	HWND hWnd20 = FindWindowA(0, ("Over Rev (Model 2B)"));


	HMODULE hMod = GetModuleHandleA("KERNEL32.dll");
	if (hMod)
	{
		if (!init)
		{
			int hookLength = 6;
			DWORD hookAddress = (DWORD)GetProcAddress(GetModuleHandle(L"KERNEL32.dll"), "ExitProcess");
			if (hookAddress)
			{
				jmpBackAddy = hookAddress + hookLength;
				Hook((void*)hookAddress, ExitHook, hookLength);
				init = true;
			}
		}
	}

	if (hWnd1 > NULL)
	{
		UINT8 ff = helpers->ReadByte(0x174CF4, /* isRelativeOffset*/ true); //SegaRallyChampionship
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0xBF) & (ff < 0xDF))
			{
				helpers->log("moving wheel left");
				double percentForce = (ff - 191) / 31.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x7F) & (ff < 0x9F))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff - 127) / 31.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0xBF) & (ff < 0xDF))
			{
				helpers->log("moving wheel left");
				double percentForce = (ff - 191) / 31.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x7F) & (ff < 0x9F))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff - 127) / 31.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd2 > NULL)
	{
		if (DaytonaForcePanoramicAttract == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			helpers->WriteByte(Rambase1 + 0x1070, 0x00, /* isRelativeOffset*/ false);
		}

		if (DaytonaAIMultiplayerHack == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			UINT8 gamestate = helpers->ReadByte(Rambase1 + 0x10A4, /* isRelativeOffset*/ false);
			UINT8 track = helpers->ReadByte(Rambase1 + 0x1460, /* isRelativeOffset*/ false);
			UINT8 trackselect = helpers->ReadByte(Rambase1 + 0x1468, /* isRelativeOffset*/ false);
			UINT8 countdown = helpers->ReadByte(Rambase1 + 0x1850, /* isRelativeOffset*/ false);
			UINT8 linksize = helpers->ReadByte(Rambase1 + 0x40001, /* isRelativeOffset*/ false);
			UINT8 linkID = helpers->ReadByte(Rambase1 + 0x40002, /* isRelativeOffset*/ false);
			INT_PTR gamestatetimer = helpers->ReadIntPtr(Rambase1 + 0x10A8, /* isRelativeOffset*/ false);
			UINT8 camhack = helpers->ReadByte(Rambase1 + 0x14A4, /* isRelativeOffset*/ false);
			UINT8 carsinfront = helpers->ReadByte(Rambase1 + 0x51EC, /* isRelativeOffset*/ false);
			UINT8 mpposition = helpers->ReadByte(Rambase1 + 0x51ED, /* isRelativeOffset*/ false);
			float cary = helpers->ReadFloat32(Rambase1 + 0x519C, /* isRelativeOffset */ false);
			float carx = helpers->ReadFloat32(Rambase1 + 0x51A4, /* isRelativeOffset */ false);
			UINT8 nop1 = helpers->ReadByte(0xC2130, /* isRelativeOffset*/ true);
			UINT8 nop2 = helpers->ReadByte(0xC2131, /* isRelativeOffset*/ true);
			UINT8 nop3 = helpers->ReadByte(0xC2132, /* isRelativeOffset*/ true);


			if (gamestate == 0x1A)
			{
				helpers->WriteByte(Rambase1 + 0x51ED, carsinfront, /* isRelativeOffset*/ false);
			}

			if (trackselect == 0x01)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x02, /* isRelativeOffset*/ false);
			}
			else if (trackselect == 0x02)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x01, /* isRelativeOffset*/ false);
			}

			if (linksize == 0x02)
			{
				if (linkID == 0x02)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 0.0, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x03)
			{
				if (linkID == 0x03)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x04)
			{
				if (linkID == 0x04)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC302CAF4, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37C0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				if (linkID == 0x03)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(350);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37CF3D0, /* isRelativeOffset */ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
		}



		UINT8 ff = helpers->ReadByte(0x0057285B, /* isRelativeOffset*/ false); //DaytonaUSA
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd3 > NULL)
	{
		UINT8 ff = helpers->ReadByte(0x17285B, /* isRelativeOffset*/ true); //Indy500
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd4 > NULL)
	{
		UINT8 ff = helpers->ReadByte(0x17285B, /* isRelativeOffset*/ true); //Sega Touring Car Championship
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd5 > NULL)
	{
		UINT8 ff = helpers->ReadByte(0x17285B, /* isRelativeOffset*/ true); //OverRev
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd6 > NULL)
	{
		UINT8 ff = helpers->ReadByte(0x17285B, /* isRelativeOffset*/ true); //Super GT 24h
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd7 > NULL)
	{

		if (DaytonaForcePanoramicAttract == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			helpers->WriteByte(Rambase1 + 0x1070, 0x00, /* isRelativeOffset*/ false);
		}

		UINT8 ff = helpers->ReadByte(0x0057285B, /* isRelativeOffset*/ false); //Daytona USA '93 Edition
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd8 > NULL)
	{
		if (DaytonaForcePanoramicAttract == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			helpers->WriteByte(Rambase1 + 0x1070, 0x00, /* isRelativeOffset*/ false);
		}

		if (DaytonaAIMultiplayerHack == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			UINT8 gamestate = helpers->ReadByte(Rambase1 + 0x10A4, /* isRelativeOffset*/ false);
			UINT8 track = helpers->ReadByte(Rambase1 + 0x1460, /* isRelativeOffset*/ false);
			UINT8 trackselect = helpers->ReadByte(Rambase1 + 0x1468, /* isRelativeOffset*/ false);
			UINT8 countdown = helpers->ReadByte(Rambase1 + 0x1850, /* isRelativeOffset*/ false);
			UINT8 linksize = helpers->ReadByte(Rambase1 + 0x40001, /* isRelativeOffset*/ false);
			UINT8 linkID = helpers->ReadByte(Rambase1 + 0x40002, /* isRelativeOffset*/ false);
			INT_PTR gamestatetimer = helpers->ReadIntPtr(Rambase1 + 0x10A8, /* isRelativeOffset*/ false);
			UINT8 camhack = helpers->ReadByte(Rambase1 + 0x14A4, /* isRelativeOffset*/ false);
			UINT8 carsinfront = helpers->ReadByte(Rambase1 + 0x51EC, /* isRelativeOffset*/ false);
			UINT8 mpposition = helpers->ReadByte(Rambase1 + 0x51ED, /* isRelativeOffset*/ false);
			float cary = helpers->ReadFloat32(Rambase1 + 0x519C, /* isRelativeOffset */ false);
			float carx = helpers->ReadFloat32(Rambase1 + 0x51A4, /* isRelativeOffset */ false);
			UINT8 nop1 = helpers->ReadByte(0xC2130, /* isRelativeOffset*/ true);
			UINT8 nop2 = helpers->ReadByte(0xC2131, /* isRelativeOffset*/ true);
			UINT8 nop3 = helpers->ReadByte(0xC2132, /* isRelativeOffset*/ true);


			if (gamestate == 0x1A)
			{
				helpers->WriteByte(Rambase1 + 0x51ED, carsinfront, /* isRelativeOffset*/ false);
			}

			if (trackselect == 0x01)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x02, /* isRelativeOffset*/ false);
			}
			else if (trackselect == 0x02)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x01, /* isRelativeOffset*/ false);
			}

			if (linksize == 0x02)
			{
				if (linkID == 0x02)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 0.0, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x03)
			{
				if (linkID == 0x03)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x04)
			{
				if (linkID == 0x04)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC302CAF4, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37C0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				if (linkID == 0x03)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(350);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37CF3D0, /* isRelativeOffset */ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
		}

		UINT8 ff = helpers->ReadByte(0x0057285B, /* isRelativeOffset*/ false); //Daytona USA (Saturn Ads)
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd9 > NULL)
	{
		if (DaytonaForcePanoramicAttract == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			helpers->WriteByte(Rambase1 + 0x1070, 0x00, /* isRelativeOffset*/ false);
		}

		if (DaytonaAIMultiplayerHack == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			UINT8 gamestate = helpers->ReadByte(Rambase1 + 0x10A4, /* isRelativeOffset*/ false);
			UINT8 track = helpers->ReadByte(Rambase1 + 0x1460, /* isRelativeOffset*/ false);
			UINT8 trackselect = helpers->ReadByte(Rambase1 + 0x1468, /* isRelativeOffset*/ false);
			UINT8 countdown = helpers->ReadByte(Rambase1 + 0x1850, /* isRelativeOffset*/ false);
			UINT8 linksize = helpers->ReadByte(Rambase1 + 0x40001, /* isRelativeOffset*/ false);
			UINT8 linkID = helpers->ReadByte(Rambase1 + 0x40002, /* isRelativeOffset*/ false);
			INT_PTR gamestatetimer = helpers->ReadIntPtr(Rambase1 + 0x10A8, /* isRelativeOffset*/ false);
			UINT8 camhack = helpers->ReadByte(Rambase1 + 0x14A4, /* isRelativeOffset*/ false);
			UINT8 carsinfront = helpers->ReadByte(Rambase1 + 0x51EC, /* isRelativeOffset*/ false);
			UINT8 mpposition = helpers->ReadByte(Rambase1 + 0x51ED, /* isRelativeOffset*/ false);
			float cary = helpers->ReadFloat32(Rambase1 + 0x519C, /* isRelativeOffset */ false);
			float carx = helpers->ReadFloat32(Rambase1 + 0x51A4, /* isRelativeOffset */ false);
			UINT8 nop1 = helpers->ReadByte(0xC2130, /* isRelativeOffset*/ true);
			UINT8 nop2 = helpers->ReadByte(0xC2131, /* isRelativeOffset*/ true);
			UINT8 nop3 = helpers->ReadByte(0xC2132, /* isRelativeOffset*/ true);


			if (gamestate == 0x1A)
			{
				helpers->WriteByte(Rambase1 + 0x51ED, carsinfront, /* isRelativeOffset*/ false);
			}

			if (trackselect == 0x01)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x02, /* isRelativeOffset*/ false);
			}
			else if (trackselect == 0x02)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x01, /* isRelativeOffset*/ false);
			}

			if (linksize == 0x02)
			{
				if (linkID == 0x02)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 0.0, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x03)
			{
				if (linkID == 0x03)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x04)
			{
				if (linkID == 0x04)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC302CAF4, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37C0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				if (linkID == 0x03)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(350);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37CF3D0, /* isRelativeOffset */ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
		}

		UINT8 ff = helpers->ReadByte(0x0057285B, /* isRelativeOffset*/ false); //Daytona USA Special Edition
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd10 > NULL)
	{
		if (DaytonaForcePanoramicAttract == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			helpers->WriteByte(Rambase1 + 0x1070, 0x00, /* isRelativeOffset*/ false);
		}

		if (DaytonaAIMultiplayerHack == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			UINT8 gamestate = helpers->ReadByte(Rambase1 + 0x10A4, /* isRelativeOffset*/ false);
			UINT8 track = helpers->ReadByte(Rambase1 + 0x1460, /* isRelativeOffset*/ false);
			UINT8 trackselect = helpers->ReadByte(Rambase1 + 0x1468, /* isRelativeOffset*/ false);
			UINT8 countdown = helpers->ReadByte(Rambase1 + 0x1850, /* isRelativeOffset*/ false);
			UINT8 linksize = helpers->ReadByte(Rambase1 + 0x40001, /* isRelativeOffset*/ false);
			UINT8 linkID = helpers->ReadByte(Rambase1 + 0x40002, /* isRelativeOffset*/ false);
			INT_PTR gamestatetimer = helpers->ReadIntPtr(Rambase1 + 0x10A8, /* isRelativeOffset*/ false);
			UINT8 camhack = helpers->ReadByte(Rambase1 + 0x14A4, /* isRelativeOffset*/ false);
			UINT8 carsinfront = helpers->ReadByte(Rambase1 + 0x51EC, /* isRelativeOffset*/ false);
			UINT8 mpposition = helpers->ReadByte(Rambase1 + 0x51ED, /* isRelativeOffset*/ false);
			float cary = helpers->ReadFloat32(Rambase1 + 0x519C, /* isRelativeOffset */ false);
			float carx = helpers->ReadFloat32(Rambase1 + 0x51A4, /* isRelativeOffset */ false);
			UINT8 nop1 = helpers->ReadByte(0xC2130, /* isRelativeOffset*/ true);
			UINT8 nop2 = helpers->ReadByte(0xC2131, /* isRelativeOffset*/ true);
			UINT8 nop3 = helpers->ReadByte(0xC2132, /* isRelativeOffset*/ true);


			if (gamestate == 0x1A)
			{
				helpers->WriteByte(Rambase1 + 0x51ED, carsinfront, /* isRelativeOffset*/ false);
			}

			if (trackselect == 0x01)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x02, /* isRelativeOffset*/ false);
			}
			else if (trackselect == 0x02)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x01, /* isRelativeOffset*/ false);
			}

			if (linksize == 0x02)
			{
				if (linkID == 0x02)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 0.0, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x03)
			{
				if (linkID == 0x03)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x04)
			{
				if (linkID == 0x04)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC302CAF4, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37C0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				if (linkID == 0x03)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(350);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37CF3D0, /* isRelativeOffset */ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
		}

		UINT8 ff = helpers->ReadByte(0x0057285B, /* isRelativeOffset*/ false); //Daytona USA Turbo
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd11 > NULL)
	{
		if (DaytonaForcePanoramicAttract == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			helpers->WriteByte(Rambase1 + 0x1070, 0x00, /* isRelativeOffset*/ false);
		}

		if (DaytonaAIMultiplayerHack == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			UINT8 gamestate = helpers->ReadByte(Rambase1 + 0x10A4, /* isRelativeOffset*/ false);
			UINT8 track = helpers->ReadByte(Rambase1 + 0x1460, /* isRelativeOffset*/ false);
			UINT8 trackselect = helpers->ReadByte(Rambase1 + 0x1468, /* isRelativeOffset*/ false);
			UINT8 countdown = helpers->ReadByte(Rambase1 + 0x1850, /* isRelativeOffset*/ false);
			UINT8 linksize = helpers->ReadByte(Rambase1 + 0x40001, /* isRelativeOffset*/ false);
			UINT8 linkID = helpers->ReadByte(Rambase1 + 0x40002, /* isRelativeOffset*/ false);
			INT_PTR gamestatetimer = helpers->ReadIntPtr(Rambase1 + 0x10A8, /* isRelativeOffset*/ false);
			UINT8 camhack = helpers->ReadByte(Rambase1 + 0x14A4, /* isRelativeOffset*/ false);
			UINT8 carsinfront = helpers->ReadByte(Rambase1 + 0x51EC, /* isRelativeOffset*/ false);
			UINT8 mpposition = helpers->ReadByte(Rambase1 + 0x51ED, /* isRelativeOffset*/ false);
			float cary = helpers->ReadFloat32(Rambase1 + 0x519C, /* isRelativeOffset */ false);
			float carx = helpers->ReadFloat32(Rambase1 + 0x51A4, /* isRelativeOffset */ false);
			UINT8 nop1 = helpers->ReadByte(0xC2130, /* isRelativeOffset*/ true);
			UINT8 nop2 = helpers->ReadByte(0xC2131, /* isRelativeOffset*/ true);
			UINT8 nop3 = helpers->ReadByte(0xC2132, /* isRelativeOffset*/ true);


			if (gamestate == 0x1A)
			{
				helpers->WriteByte(Rambase1 + 0x51ED, carsinfront, /* isRelativeOffset*/ false);
			}

			if (trackselect == 0x01)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x02, /* isRelativeOffset*/ false);
			}
			else if (trackselect == 0x02)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x01, /* isRelativeOffset*/ false);
			}

			if (linksize == 0x02)
			{
				if (linkID == 0x02)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 0.0, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x03)
			{
				if (linkID == 0x03)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x04)
			{
				if (linkID == 0x04)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC302CAF4, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37C0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				if (linkID == 0x03)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(350);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37CF3D0, /* isRelativeOffset */ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
		}

		UINT8 ff = helpers->ReadByte(0x0057285B, /* isRelativeOffset*/ false); //Daytona USA Turbo (Rev A)
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd12 > NULL)
	{
		if (DaytonaForcePanoramicAttract == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			helpers->WriteByte(Rambase1 + 0x1070, 0x00, /* isRelativeOffset*/ false);
		}

		if (DaytonaAIMultiplayerHack == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			UINT8 gamestate = helpers->ReadByte(Rambase1 + 0x10A4, /* isRelativeOffset*/ false);
			UINT8 track = helpers->ReadByte(Rambase1 + 0x1460, /* isRelativeOffset*/ false);
			UINT8 trackselect = helpers->ReadByte(Rambase1 + 0x1468, /* isRelativeOffset*/ false);
			UINT8 countdown = helpers->ReadByte(Rambase1 + 0x1850, /* isRelativeOffset*/ false);
			UINT8 linksize = helpers->ReadByte(Rambase1 + 0x40001, /* isRelativeOffset*/ false);
			UINT8 linkID = helpers->ReadByte(Rambase1 + 0x40002, /* isRelativeOffset*/ false);
			INT_PTR gamestatetimer = helpers->ReadIntPtr(Rambase1 + 0x10A8, /* isRelativeOffset*/ false);
			UINT8 camhack = helpers->ReadByte(Rambase1 + 0x14A4, /* isRelativeOffset*/ false);
			UINT8 carsinfront = helpers->ReadByte(Rambase1 + 0x51EC, /* isRelativeOffset*/ false);
			UINT8 mpposition = helpers->ReadByte(Rambase1 + 0x51ED, /* isRelativeOffset*/ false);
			float cary = helpers->ReadFloat32(Rambase1 + 0x519C, /* isRelativeOffset */ false);
			float carx = helpers->ReadFloat32(Rambase1 + 0x51A4, /* isRelativeOffset */ false);
			UINT8 nop1 = helpers->ReadByte(0xC2130, /* isRelativeOffset*/ true);
			UINT8 nop2 = helpers->ReadByte(0xC2131, /* isRelativeOffset*/ true);
			UINT8 nop3 = helpers->ReadByte(0xC2132, /* isRelativeOffset*/ true);


			if (gamestate == 0x1A)
			{
				helpers->WriteByte(Rambase1 + 0x51ED, carsinfront, /* isRelativeOffset*/ false);
			}

			if (trackselect == 0x01)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x02, /* isRelativeOffset*/ false);
			}
			else if (trackselect == 0x02)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x01, /* isRelativeOffset*/ false);
			}

			if (linksize == 0x02)
			{
				if (linkID == 0x02)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 0.0, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x03)
			{
				if (linkID == 0x03)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x04)
			{
				if (linkID == 0x04)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC302CAF4, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37C0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				if (linkID == 0x03)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(350);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37CF3D0, /* isRelativeOffset */ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
		}

		UINT8 ff = helpers->ReadByte(0x0057285B, /* isRelativeOffset*/ false); //Daytona USA: GTX 2004
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd13 > NULL)
	{
		if (DaytonaForcePanoramicAttract == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			helpers->WriteByte(Rambase1 + 0x1070, 0x00, /* isRelativeOffset*/ false);
		}

		if (DaytonaAIMultiplayerHack == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			UINT8 gamestate = helpers->ReadByte(Rambase1 + 0x10A4, /* isRelativeOffset*/ false);
			UINT8 track = helpers->ReadByte(Rambase1 + 0x1460, /* isRelativeOffset*/ false);
			UINT8 trackselect = helpers->ReadByte(Rambase1 + 0x1468, /* isRelativeOffset*/ false);
			UINT8 countdown = helpers->ReadByte(Rambase1 + 0x1850, /* isRelativeOffset*/ false);
			UINT8 linksize = helpers->ReadByte(Rambase1 + 0x40001, /* isRelativeOffset*/ false);
			UINT8 linkID = helpers->ReadByte(Rambase1 + 0x40002, /* isRelativeOffset*/ false);
			INT_PTR gamestatetimer = helpers->ReadIntPtr(Rambase1 + 0x10A8, /* isRelativeOffset*/ false);
			UINT8 camhack = helpers->ReadByte(Rambase1 + 0x14A4, /* isRelativeOffset*/ false);
			UINT8 carsinfront = helpers->ReadByte(Rambase1 + 0x51EC, /* isRelativeOffset*/ false);
			UINT8 mpposition = helpers->ReadByte(Rambase1 + 0x51ED, /* isRelativeOffset*/ false);
			float cary = helpers->ReadFloat32(Rambase1 + 0x519C, /* isRelativeOffset */ false);
			float carx = helpers->ReadFloat32(Rambase1 + 0x51A4, /* isRelativeOffset */ false);
			UINT8 nop1 = helpers->ReadByte(0xC2130, /* isRelativeOffset*/ true);
			UINT8 nop2 = helpers->ReadByte(0xC2131, /* isRelativeOffset*/ true);
			UINT8 nop3 = helpers->ReadByte(0xC2132, /* isRelativeOffset*/ true);


			if (gamestate == 0x1A)
			{
				helpers->WriteByte(Rambase1 + 0x51ED, carsinfront, /* isRelativeOffset*/ false);
			}

			if (trackselect == 0x01)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x02, /* isRelativeOffset*/ false);
			}
			else if (trackselect == 0x02)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x01, /* isRelativeOffset*/ false);
			}

			if (linksize == 0x02)
			{
				if (linkID == 0x02)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 0.0, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x03)
			{
				if (linkID == 0x03)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x04)
			{
				if (linkID == 0x04)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC302CAF4, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37C0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				if (linkID == 0x03)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(350);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37CF3D0, /* isRelativeOffset */ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, true);
						helpers->WriteNop(0xC2131, true);
						helpers->WriteNop(0xC2132, true);
					}

					if ((gamestate > 0x1A) & (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133) & (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
		}

		UINT8 ff = helpers->ReadByte(0x0057285B, /* isRelativeOffset*/ false); //Daytona USA: To The Maxx
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 15) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x3D))
			{
				//Centering
				double percentForce = (ff - 47) / 13.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd14 > NULL)
	{
		UINT8 ff = helpers->ReadByte(0x174CF4, /* isRelativeOffset*/ true); //Sega Rally Championship (Rev B)
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0xBF) & (ff < 0xDF))
			{
				helpers->log("moving wheel left");
				double percentForce = (ff - 191) / 31.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x7F) & (ff < 0x9F))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff - 127) / 31.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0xBF) & (ff < 0xDF))
			{
				helpers->log("moving wheel left");
				double percentForce = (ff - 191) / 31.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x7F) & (ff < 0x9F))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff - 127) / 31.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	if (hWnd15 > NULL)
	{
		UINT8 ff = helpers->ReadByte(0x174CF4, /* isRelativeOffset*/ true); //Sega Rally Pro Drivin'
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0xBF) & (ff < 0xDF))
			{
				helpers->log("moving wheel left");
				double percentForce = (ff - 191) / 31.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x7F) & (ff < 0x9F))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff - 127) / 31.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0xBF) & (ff < 0xDF))
			{
				helpers->log("moving wheel left");
				double percentForce = (ff - 191) / 31.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x7F) & (ff < 0x9F))
			{
				helpers->log("moving wheel right");
				double percentForce = (ff - 127) / 31.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd16 > NULL)
	{
		UINT8 ff = helpers->ReadByte(0x17285B, /* isRelativeOffset*/ true); //Indianapolis 500 (Rev A, Twin, Newer rev)
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd17 > NULL)
	{
		UINT8 ff = helpers->ReadByte(0x17285B, /* isRelativeOffset*/ true); //Indianapolis 500 (Rev A, Twin, Older rev)
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd18 > NULL)
	{
		UINT8 ff = helpers->ReadByte(0x17285B, /* isRelativeOffset*/ true); //Sega Touring Car Championship
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd19 > NULL)
	{
		UINT8 ff = helpers->ReadByte(0x17285B, /* isRelativeOffset*/ true); //Sega Touring Car Championship (Rev B)
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
	else if (hWnd20 > NULL)
	{
		UINT8 ff = helpers->ReadByte(0x17285B, /* isRelativeOffset*/ true); //Over Rev (Model 2B)
		std::string ffs = std::to_string(ff);
		helpers->log((char *)ffs.c_str());
		helpers->log("got value: ");
		if (FFBMode == 0)
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff > 0x09) & (ff < 0x18))
			{
				//Spring
				double percentForce = (ff - 10) / 14.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x1F) & (ff < 0x28))
			{
				//Clutch
				double percentForce = (ff - 31) / 8.0;
				double percentLength = 100;
				triggers->Friction(percentForce);
			}
			else if ((ff > 0x2F) & (ff < 0x38))
			{
				//Centering
				double percentForce = (ff - 47) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x37) & (ff < 0x40))
			{
				//Centeringtestmenu
				double percentForce = (ff - 55) / 8.0;
				double percentLength = 100;
				triggers->Spring(percentForce);
			}
			else if ((ff > 0x3F) & (ff < 0x48))
			{
				//Uncentering
				double percentForce = (ff - 63) / 8.0;
				double percentLength = 100;
				triggers->Sine(70, 80, percentForce);
			}
			else if ((ff > 0x4F) & (ff < 0x58))
			{
				//Roll Left
				double percentForce = (ff - 79) / 8.0;
				double percentLength = 100;
				triggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x5F) & (ff < 0x68))
			{
				//Roll Right
				double percentForce = (ff - 95) / 8.0;
				double percentLength = 100;
				triggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
}
