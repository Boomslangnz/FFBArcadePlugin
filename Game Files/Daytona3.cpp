#include <string>
#include "Daytona3.h"
#include "SDL.h"
#include <Windows.h>

void Daytona3::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	int ff = helpers->ReadInt32(0x15AFC46, /* isRelativeOffset */ false);
	int gamestate = helpers->ReadInt32(0x19B5744, /* isRelativeOffset */ false);
	UINT8 gear = helpers->ReadByte(0x019B468C, /* isRelativeOffset */ false);
	UINT8 steering = helpers->ReadByte(0x019B4678, /* isRelativeOffset */ false);
	helpers->log("got value: ");
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());
	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int ShowButtonNumbersForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowButtonNumbersForSetup"), 0, settingsFilename);
	int ChangeGearsViaPlugin = GetPrivateProfileInt(TEXT("Settings"), TEXT("ChangeGearsViaPlugin"), 0, settingsFilename);
	int EscapeKeyExitViaPlugin = GetPrivateProfileInt(TEXT("Settings"), TEXT("EscapeKeyExitViaPlugin"), 0, settingsFilename);
	int MenuMovementViaPlugin = GetPrivateProfileInt(TEXT("Settings"), TEXT("MenuMovementViaPlugin"), 0, settingsFilename);
	int Gear1 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear1"), 0, settingsFilename);
	int Gear2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear2"), 0, settingsFilename);
	int Gear3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear3"), 0, settingsFilename);
	int Gear4 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear4"), 0, settingsFilename);
	int GearUp = GetPrivateProfileInt(TEXT("Settings"), TEXT("GearUp"), 0, settingsFilename);
	int GearDown = GetPrivateProfileInt(TEXT("Settings"), TEXT("GearDown"), 0, settingsFilename);
	int HideCursor = GetPrivateProfileInt(TEXT("Settings"), TEXT("HideCursor"), 0, settingsFilename);

	if (HideCursor == 1)
	{
		SetCursorPos(2000, 2000);
	}

	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		/*	if (e.type == SDL_KEYDOWN)
		{
		if (e.key.keysym.sym == SDLK_ESCAPE)
		{
		MessageBoxA(NULL, "test", "", 0);
		}
		} */
		if (ShowButtonNumbersForSetup == 1)
		{
			if (e.type == SDL_JOYBUTTONDOWN)
			{
				if (e.jbutton.button == 0)
				{
					MessageBoxA(NULL, "Button 0 Pressed", "", 0);
				}
				else if (e.jbutton.button == 1)
				{
					MessageBoxA(NULL, "Button 1 Pressed", "", 0);
				}
				else if (e.jbutton.button == 2)
				{
					MessageBoxA(NULL, "Button 2 Pressed", "", 0);
				}
				else if (e.jbutton.button == 3)
				{
					MessageBoxA(NULL, "Button 3 Pressed", "", 0);
				}
				else if (e.jbutton.button == 4)
				{
					MessageBoxA(NULL, "Button 4 Pressed", "", 0);
				}
				else if (e.jbutton.button == 5)
				{
					MessageBoxA(NULL, "Button 5 Pressed", "", 0);
				}
				else if (e.jbutton.button == 6)
				{
					MessageBoxA(NULL, "Button 6 Pressed", "", 0);
				}
				else if (e.jbutton.button == 7)
				{
					MessageBoxA(NULL, "Button 7 Pressed", "", 0);
				}
				else if (e.jbutton.button == 8)
				{
					MessageBoxA(NULL, "Button 8 Pressed", "", 0);
				}
				else if (e.jbutton.button == 9)
				{
					MessageBoxA(NULL, "Button 9 Pressed", "", 0);
				}
				else if (e.jbutton.button == 10)
				{
					MessageBoxA(NULL, "Button 10 Pressed", "", 0);
				}
				else if (e.jbutton.button == 11)
				{
					MessageBoxA(NULL, "Button 11 Pressed", "", 0);
				}
				else if (e.jbutton.button == 12)
				{
					MessageBoxA(NULL, "Button 12 Pressed", "", 0);
				}
				else if (e.jbutton.button == 13)
				{
					MessageBoxA(NULL, "Button 13 Pressed", "", 0);
				}
				else if (e.jbutton.button == 14)
				{
					MessageBoxA(NULL, "Button 14 Pressed", "", 0);
				}
				else if (e.jbutton.button == 15)
				{
					MessageBoxA(NULL, "Button 15 Pressed", "", 0);
				}
				else if (e.jbutton.button == 16)
				{
					MessageBoxA(NULL, "Button 16 Pressed", "", 0);
				}
				else if (e.jbutton.button == 17)
				{
					MessageBoxA(NULL, "Button 17 Pressed", "", 0);
				}
				else if (e.jbutton.button == 18)
				{
					MessageBoxA(NULL, "Button 18 Pressed", "", 0);
				}
				else if (e.jbutton.button == 19)
				{
					MessageBoxA(NULL, "Button 19 Pressed", "", 0);
				}
				else if (e.jbutton.button == 20)
				{
					MessageBoxA(NULL, "Button 20 Pressed", "", 0);
				}
				else if (e.jbutton.button == 21)
				{
					MessageBoxA(NULL, "Button 21 Pressed", "", 0);
				}
				else if (e.jbutton.button == 22)
				{
					MessageBoxA(NULL, "Button 22 Pressed", "", 0);
				}
				else if (e.jbutton.button == 23)
				{
					MessageBoxA(NULL, "Button 23 Pressed", "", 0);
				}
				else if (e.jbutton.button == 24)
				{
					MessageBoxA(NULL, "Button 24 Pressed", "", 0);
				}
				else if (e.jbutton.button == 25)
				{
					MessageBoxA(NULL, "Button 25 Pressed", "", 0);
				}
				else if (e.jbutton.button == 26)
				{
					MessageBoxA(NULL, "Button 26 Pressed", "", 0);
				}
				else if (e.jbutton.button == 27)
				{
					MessageBoxA(NULL, "Button 27 Pressed", "", 0);
				}
				else if (e.jbutton.button == 28)
				{
					MessageBoxA(NULL, "Button 28 Pressed", "", 0);
				}
				else if (e.jbutton.button == 29)
				{
					MessageBoxA(NULL, "Button 29 Pressed", "", 0);
				}
				else if (e.jbutton.button == 30)
				{
					MessageBoxA(NULL, "Button 30 Pressed", "", 0);
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
	if (GetAsyncKeyState((VK_ESCAPE)) && (EscapeKeyExitViaPlugin == 1))
	{
		system("taskkill /f /im Daytona.exe");
		system("taskkill /f /im InpWrapper.exe");
	}

	if ((steering > 137) & (gamestate == 18) && (MenuMovementViaPlugin == 1))
	{	
		keybd_event(VK_RIGHT, 0x25, 0, 0);
		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
	}
	else if ((steering > 117 & steering < 138) & (gamestate == 18) && (MenuMovementViaPlugin == 1))
	{
		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
	}
	else if ((steering < 118) & (gamestate == 18) && (MenuMovementViaPlugin == 1))
	{
		keybd_event(VK_LEFT, 0x25, 0, 0);
		keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
	}
	if ((steering > 137) & (gamestate == 30) && (MenuMovementViaPlugin == 1))
	{
		keybd_event(VK_RIGHT, 0x25, 0, 0);
		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
	}
	else if ((steering > 117 & steering < 138) & (gamestate == 30) && (MenuMovementViaPlugin == 1))
	{
		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
	}
	else if ((steering < 118) & (gamestate == 30) && (MenuMovementViaPlugin == 1))
	{
		keybd_event(VK_LEFT, 0x25, 0, 0);
		keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
		Sleep(100);
		keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
	}

		if (ff > 15)
		{
			helpers->log("moving wheel right");
			// assume that 30 is the weakest and 16 is the strongest
			double percentForce = (31 - ff) / 15.0;
			double percentLength = 100;
			// direction from left => makes wheel turn right
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce); // old logic: 31 - ff
			lastWasStop = 0;
		}
		else if (ff > 0)
		{
			helpers->log("moving wheel left");
			// assume that 1 is the strongest and 15 is the weakest
			double percentForce = (16 - ff) / 15.0;
			double percentLength = 100;
			// direction from right => makes wheel turn left
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce); // old logic: 15 - ff
			lastWasStop = 0;
		}
		else
		{
			if (lastWasStop == 0) {
				triggers->Constant(constants->DIRECTION_FROM_LEFT, 0); // just pass the hash of 0 strength so we update lastEffectHash & lastEffectTime
				lastWasStop = 1;
			}
		}
	}