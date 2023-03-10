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
#include "ButtonRumble.h"
#include "SDL.h"
#include <Windows.h>
static bool init = false;
extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;
extern SDL_Haptic* ControllerHaptic2;
extern SDL_Haptic* haptic2;
extern SDL_Event e;

static wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
static int ShowButtonNumbersForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowButtonNumbersForSetup"), 0, settingsFilename);
static int BothRumbleMotor = GetPrivateProfileInt(TEXT("Settings"), TEXT("BothRumbleMotor"), 0, settingsFilename);
static int LeftRumbleMotor = GetPrivateProfileInt(TEXT("Settings"), TEXT("LeftRumbleMotor"), 0, settingsFilename);
static int RightRumbleMotor = GetPrivateProfileInt(TEXT("Settings"), TEXT("RightRumbleMotor"), 0, settingsFilename);
static int RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrength"), 0, settingsFilename);
static int RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleLength"), 0, settingsFilename);
static int Button1Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button1Rumble"), 0, settingsFilename);
static int Button2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button2Rumble"), 0, settingsFilename);
static int Button3Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button3Rumble"), 0, settingsFilename);
static int Button4Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button4Rumble"), 0, settingsFilename);
static int Button5Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button5Rumble"), 0, settingsFilename);
static int Button6Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button6Rumble"), 0, settingsFilename);
static int Button7Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button7Rumble"), 0, settingsFilename);
static int Button8Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button8Rumble"), 0, settingsFilename);
static int Button9Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button9Rumble"), 0, settingsFilename);
static int Button10Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button10Rumble"), 0, settingsFilename);
static int Button1Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button1Device2Rumble"), 0, settingsFilename);
static int Button2Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button2Device2Rumble"), 0, settingsFilename);
static int Button3Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button3Device2Rumble"), 0, settingsFilename);
static int Button4Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button4Device2Rumble"), 0, settingsFilename);
static int Button5Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button5Device2Rumble"), 0, settingsFilename);
static int Button6Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button6Device2Rumble"), 0, settingsFilename);
static int Button7Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button7Device2Rumble"), 0, settingsFilename);
static int Button8Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button8Device2Rumble"), 0, settingsFilename);
static int Button9Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button9Device2Rumble"), 0, settingsFilename);
static int Button10Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button10Device2Rumble"), 0, settingsFilename);

void ButtonRumble::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (!init)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			wchar_t* deviceGUIDString2 = new wchar_t[256];
			int Device2GUID = GetPrivateProfileString(TEXT("Settings"), TEXT("Device2GUID"), NULL, deviceGUIDString2, 256, settingsFilename);
			char joystick_guid[256];
			sprintf(joystick_guid, "%S", deviceGUIDString2);
			SDL_JoystickGUID guid, dev_guid;
			int numJoysticks = SDL_NumJoysticks();
			std::string njs = std::to_string(numJoysticks);
			for (int i = 0; i < SDL_NumJoysticks(); i++)
			{
				extern int joystick1Index;
				if (i == joystick1Index)
				{
					continue;
				}
				SDL_Joystick* js2 = SDL_JoystickOpen(i);
				SDL_JoystickGUID guid = SDL_JoystickGetGUID(js2);
				char guid_str[1024];
				SDL_JoystickGetGUIDString(guid, guid_str, sizeof(guid_str));
				const char* name = SDL_JoystickName(js2);
				char text[256];
				sprintf(text, "Joystick: %d / Name: %s / GUID: %s\n", i, name, guid_str);
				guid = SDL_JoystickGetGUIDFromString(joystick_guid);
				dev_guid = SDL_JoystickGetGUID(js2);
				if (!memcmp(&guid, &dev_guid, sizeof(SDL_JoystickGUID)))
				{
					GameController2 = SDL_JoystickOpen(i);
					joystick_index2 = SDL_JoystickInstanceID(GameController2);
					ControllerHaptic2 = SDL_HapticOpenFromJoystick(GameController2);
					break;
				}
				SDL_JoystickClose(js2);
			}
			haptic2 = ControllerHaptic2;
			if ((SDL_HapticRumbleSupported(haptic2) == SDL_TRUE))
			{
				SDL_HapticRumbleInit;
				SDL_HapticRumbleInit(ControllerHaptic2);
			}
		}
		init = true;
	}
	
	while (SDL_WaitEvent(&e) != 0)
	{
		if (ShowButtonNumbersForSetup)
		{
			if (e.type == SDL_JOYBUTTONDOWN)
			{
				if (e.jaxis.which == joystick_index1 || e.jaxis.which == joystick_index2)
				{
					if (e.jbutton.button >= 0)
					{
						char buff[100];
						sprintf_s(buff, "Button %d Pressed", e.jbutton.button);
						MessageBoxA(NULL, buff, "", NULL);
					}
				}
			}
		}

		if (e.type == SDL_JOYBUTTONDOWN)
		{
			if (e.jaxis.which == joystick_index1)
			{
				if (BothRumbleMotor && !LeftRumbleMotor && !RightRumbleMotor)
				{
					if (e.jbutton.button == Button1Rumble || e.jbutton.button == Button2Rumble || e.jbutton.button == Button3Rumble || e.jbutton.button == Button4Rumble || e.jbutton.button == Button5Rumble || e.jbutton.button == Button6Rumble || e.jbutton.button == Button7Rumble || e.jbutton.button == Button8Rumble || e.jbutton.button == Button9Rumble || e.jbutton.button == Button10Rumble)
					{
						double percentForce = RumbleStrength / 100.0;
						double percentLength = RumbleLength * 1.0;
						triggers->Rumble(percentForce, percentForce, percentLength);
					}
				}

				if (!BothRumbleMotor && LeftRumbleMotor && !RightRumbleMotor)
				{
					if (e.jbutton.button == Button1Rumble || e.jbutton.button == Button2Rumble || e.jbutton.button == Button3Rumble || e.jbutton.button == Button4Rumble || e.jbutton.button == Button5Rumble || e.jbutton.button == Button6Rumble || e.jbutton.button == Button7Rumble || e.jbutton.button == Button8Rumble || e.jbutton.button == Button9Rumble || e.jbutton.button == Button10Rumble)
					{
							double percentForce = RumbleStrength / 100.0;
							double percentLength = RumbleLength * 1.0;
							triggers->Rumble(0, percentForce, percentLength);
					}
				}

				if (!BothRumbleMotor && !LeftRumbleMotor && RightRumbleMotor)
				{
					if (e.jbutton.button == Button1Rumble || e.jbutton.button == Button2Rumble || e.jbutton.button == Button3Rumble || e.jbutton.button == Button4Rumble || e.jbutton.button == Button5Rumble || e.jbutton.button == Button6Rumble || e.jbutton.button == Button7Rumble || e.jbutton.button == Button8Rumble || e.jbutton.button == Button9Rumble || e.jbutton.button == Button10Rumble)
					{
						double percentForce = RumbleStrength / 100.0;
						double percentLength = RumbleLength * 1.0;
						triggers->Rumble(percentForce, 0, percentLength);
					}
				}
			}

			if (e.jaxis.which == joystick_index2)
			{
				if (BothRumbleMotor && !LeftRumbleMotor && !RightRumbleMotor)
				{
					if (e.jbutton.button == Button1Device2Rumble || e.jbutton.button == Button2Device2Rumble || e.jbutton.button == Button3Device2Rumble || e.jbutton.button == Button4Device2Rumble || e.jbutton.button == Button5Device2Rumble || e.jbutton.button == Button6Device2Rumble || e.jbutton.button == Button7Device2Rumble || e.jbutton.button == Button8Device2Rumble || e.jbutton.button == Button9Device2Rumble || e.jbutton.button == Button10Device2Rumble)
					{
						double percentForce = RumbleStrength / 100.0;
						double percentLength = RumbleLength * 1.0;
						triggers->RumbleDevice2(percentForce, percentForce, percentLength);
					}
				}

				if (!BothRumbleMotor && LeftRumbleMotor && !RightRumbleMotor)
				{
					if (e.jbutton.button == Button1Device2Rumble || e.jbutton.button == Button2Device2Rumble || e.jbutton.button == Button3Device2Rumble || e.jbutton.button == Button4Device2Rumble || e.jbutton.button == Button5Device2Rumble || e.jbutton.button == Button6Device2Rumble || e.jbutton.button == Button7Device2Rumble || e.jbutton.button == Button8Device2Rumble || e.jbutton.button == Button9Device2Rumble || e.jbutton.button == Button10Device2Rumble)
					{
						double percentForce = RumbleStrength / 100.0;
						double percentLength = RumbleLength * 1.0;
						triggers->RumbleDevice2(0, percentForce, percentLength);
					}
				}

				if (!BothRumbleMotor && !LeftRumbleMotor && RightRumbleMotor)
				{
					if (e.jbutton.button == Button1Device2Rumble || e.jbutton.button == Button2Device2Rumble || e.jbutton.button == Button3Device2Rumble || e.jbutton.button == Button4Device2Rumble || e.jbutton.button == Button5Device2Rumble || e.jbutton.button == Button6Device2Rumble || e.jbutton.button == Button7Device2Rumble || e.jbutton.button == Button8Device2Rumble || e.jbutton.button == Button9Device2Rumble || e.jbutton.button == Button10Device2Rumble)
					{
						double percentForce = RumbleStrength / 100.0;
						double percentLength = RumbleLength * 1.0;
						triggers->RumbleDevice2(percentForce, 0, percentLength);
					}
				}
			}
		}

		if (e.type == SDL_JOYBUTTONUP)
		{
			if (e.jaxis.which == joystick_index1)
			{
				if (e.jbutton.button == Button1Rumble || e.jbutton.button == Button2Rumble || e.jbutton.button == Button3Rumble || e.jbutton.button == Button4Rumble || e.jbutton.button == Button5Rumble || e.jbutton.button == Button6Rumble || e.jbutton.button == Button7Rumble || e.jbutton.button == Button8Rumble || e.jbutton.button == Button9Rumble || e.jbutton.button == Button10Rumble)
				{
					double percentForce = ((RumbleStrength) / 100.0);
					double percentLength = RumbleLength * 1.0;
					triggers->Rumble(0, 0, percentLength);
				}
			}

			if (e.jaxis.which == joystick_index2)
			{
				if (e.jbutton.button == Button1Device2Rumble || e.jbutton.button == Button2Device2Rumble || e.jbutton.button == Button3Device2Rumble || e.jbutton.button == Button4Device2Rumble || e.jbutton.button == Button5Device2Rumble || e.jbutton.button == Button6Device2Rumble || e.jbutton.button == Button7Device2Rumble || e.jbutton.button == Button8Device2Rumble || e.jbutton.button == Button9Device2Rumble || e.jbutton.button == Button10Device2Rumble)
				{
					double percentForce = ((RumbleStrength) / 100.0);
					double percentLength = RumbleLength * 1.0;
					triggers->RumbleDevice2(0, 0, percentLength);
				}
			}
		}
	}
}	