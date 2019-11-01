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
#include "Daytona3.h"
#include "SDL.h"
#include <Windows.h>
static bool keybdleft = false;
static bool keybdright = false;
static bool keybdup = false;
static EffectTriggers *myTriggers;
static EffectConstants *myConstants;
static Helpers *myHelpers;
static SDL_Event e;
static wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
static int ShowButtonNumbersForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowButtonNumbersForSetup"), 0, settingsFilename);
static int ChangeGearsViaPlugin = GetPrivateProfileInt(TEXT("Settings"), TEXT("ChangeGearsViaPlugin"), 0, settingsFilename);
static int EscapeKeyExitViaPlugin = GetPrivateProfileInt(TEXT("Settings"), TEXT("EscapeKeyExitViaPlugin"), 0, settingsFilename);
static int MenuMovementViaPlugin = GetPrivateProfileInt(TEXT("Settings"), TEXT("MenuMovementViaPlugin"), 0, settingsFilename);
static int Gear1 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear1"), 0, settingsFilename);
static int Gear2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear2"), 0, settingsFilename);
static int Gear3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear3"), 0, settingsFilename);
static int Gear4 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear4"), 0, settingsFilename);
static int GearUp = GetPrivateProfileInt(TEXT("Settings"), TEXT("GearUp"), 0, settingsFilename);
static int GearDown = GetPrivateProfileInt(TEXT("Settings"), TEXT("GearDown"), 0, settingsFilename);
static int HideCursor = GetPrivateProfileInt(TEXT("Settings"), TEXT("HideCursor"), 0, settingsFilename);

static int RunningThread(void *ptr)
{
	int cnt;
	for (cnt = 0; cnt >= 0; ++cnt)
	{
		UINT8 steering = myHelpers->ReadByte(0x019B4678, false);
		UINT8 gamestate = myHelpers->ReadByte(0x19B5744, false);
		UINT8 ff = myHelpers->ReadByte(0x15AFC46, false);
		HWND hWnd = FindWindowA(0, ("Daytona Championship USA"));

		if (HideCursor == 1)
		{
			SetCursorPos(2000, 2000);
		}

		if (GetAsyncKeyState((VK_ESCAPE)) && (EscapeKeyExitViaPlugin == 1))
		{
			if (hWnd > NULL)
			{
				//SendMessage(hWnd, WM_CLOSE, NULL, NULL);
				system("taskkill /f /im InpWrapper.exe");
				TerminateProcess(GetCurrentProcess(), 0);
			}
		}

		if (MenuMovementViaPlugin == 1)
		{
			//Menu Movement & Game Initial Screen
			if (gamestate == 18 || gamestate == 30)
			{
				if ((steering <= 0x75) && (steering > 0x50))
				{
					//Menu Left
					if (!keybdleft)
					{
						keybdleft = true;
						SendMessage(hWnd, WM_KEYDOWN, VK_LEFT, 0);
					}
					else
					{
						SendMessage(hWnd, WM_KEYUP, VK_LEFT, 0);
					}
				}
				else if (steering <= 0x50)
				{
					SendMessage(hWnd, WM_KEYDOWN, VK_LEFT, 0);
				}
				else if ((steering >= 0x89) && (steering < 0xAE))
				{
					//Menu Right
					if (!keybdright)
					{
						keybdright = true;
						SendMessage(hWnd, WM_KEYDOWN, VK_RIGHT, 0);
					}
					else
					{
						SendMessage(hWnd, WM_KEYUP, VK_RIGHT, 0);
					}
				}
				else if (steering >= 0xAE)
				{
					SendMessage(hWnd, WM_KEYDOWN, VK_RIGHT, 0);
				}
				else
				{
					keybdleft = false;
					keybdright = false;
					SendMessage(hWnd, WM_KEYUP, VK_RIGHT, 0);
					SendMessage(hWnd, WM_KEYUP, VK_LEFT, 0);
				}
				keybdup = false;
			}
			else
			{
				if (!keybdup)
				{
					keybdup = true;
					keybdleft = false;
					keybdright = false;
					SendMessage(hWnd, WM_KEYUP, VK_RIGHT, 0);
					SendMessage(hWnd, WM_KEYUP, VK_LEFT, 0);
				}
			}
		}
		
		if (ff > 15)
		{
			double percentForce = (31 - ff) / 15.0;
			double percentLength = 100;
			myTriggers->Rumble(percentForce, 0, percentLength);
			myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if (ff > 0)
		{
			double percentForce = (16 - ff) / 15.0;
			double percentLength = 100;
			myTriggers->Rumble(0, percentForce, percentLength);
			myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}
	return 0;
}

void Daytona3::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	myTriggers = triggers;
	myConstants = constants;
	myHelpers = helpers;

	SDL_Thread *thread;
	thread = SDL_CreateThread(RunningThread, "RunningThread", (void *)NULL);

	UINT8 gear = helpers->ReadByte(0x019B468C, /* isRelativeOffset */ false);
	int ff = helpers->ReadInt32(0x15AFC46, /* isRelativeOffset */ false);
	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());
	while (SDL_WaitEvent(&e) != 0)
	{		
		myTriggers = triggers;
		myConstants = constants;
		myHelpers = helpers;

		if (ShowButtonNumbersForSetup == 1)
		{
			if (e.type == SDL_JOYBUTTONDOWN)
			{
				if (e.jbutton.button >= 0)
				{
					char buff[100];
					sprintf_s(buff, "Button %d Pressed", e.jbutton.button);
					MessageBoxA(NULL, buff, "", NULL);
				}
			}
		}		

		if (e.type == SDL_JOYBUTTONDOWN)
		{
			if (ChangeGearsViaPlugin == 1)
			{
				if (e.jbutton.button == Gear1)
				{
					helpers->WriteByte(0x019B468C, 0x00, false);
				}
				else if (e.jbutton.button == Gear2)
				{
					helpers->WriteByte(0x019B468C, 0x02, false);
				}
				else if (e.jbutton.button == Gear3)
				{
					helpers->WriteByte(0x019B468C, 0x01, false);
				}
				else if (e.jbutton.button == Gear4)
				{
					helpers->WriteByte(0x019B468C, 0x03, false);
				}
				else if ((e.jbutton.button == GearDown) && (gear > 0x00))
				{
					helpers->WriteByte(0x019B468C, --gear, false);
				}
				else if ((e.jbutton.button == GearUp) && (gear < 0x03))
				{
					helpers->WriteByte(0x019B468C, ++gear, false);
				}
			}
		}
	}
}