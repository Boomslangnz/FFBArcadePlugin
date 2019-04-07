#include <string>
#include "ButtonRumble32bit.h"
#include "SDL.h"
#include <Windows.h>
extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;
extern SDL_Haptic* ControllerHaptic2;
extern SDL_Haptic* haptic2;

void ButtonRumble32bit::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	
	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int ShowButtonNumbersForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowButtonNumbersForSetup"), 0, settingsFilename);
	int BothRumbleMotor = GetPrivateProfileInt(TEXT("Settings"), TEXT("BothRumbleMotor"), 0, settingsFilename);
	int LeftRumbleMotor = GetPrivateProfileInt(TEXT("Settings"), TEXT("LeftRumbleMotor"), 0, settingsFilename);
	int RightRumbleMotor = GetPrivateProfileInt(TEXT("Settings"), TEXT("RightRumbleMotor"), 0, settingsFilename);
	int RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrength"), 0, settingsFilename);
	int RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleLength"), 0, settingsFilename);
	int Button1Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button1Rumble"), 0, settingsFilename);
	int Button2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button2Rumble"), 0, settingsFilename);
	int Button3Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button3Rumble"), 0, settingsFilename);
	int Button4Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button4Rumble"), 0, settingsFilename);
	int Button5Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button5Rumble"), 0, settingsFilename);
	int Button6Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button6Rumble"), 0, settingsFilename);
	int Button7Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button7Rumble"), 0, settingsFilename);
	int Button8Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button8Rumble"), 0, settingsFilename);
	int Button9Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button9Rumble"), 0, settingsFilename);
	int Button10Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button10Rumble"), 0, settingsFilename);
	int Button1Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button1Device2Rumble"), 0, settingsFilename);
	int Button2Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button2Device2Rumble"), 0, settingsFilename);
	int Button3Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button3Device2Rumble"), 0, settingsFilename);
	int Button4Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button4Device2Rumble"), 0, settingsFilename);
	int Button5Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button5Device2Rumble"), 0, settingsFilename);
	int Button6Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button6Device2Rumble"), 0, settingsFilename);
	int Button7Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button7Device2Rumble"), 0, settingsFilename);
	int Button8Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button8Device2Rumble"), 0, settingsFilename);
	int Button9Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button9Device2Rumble"), 0, settingsFilename);
	int Button10Device2Rumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("Button10Device2Rumble"), 0, settingsFilename);

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		wchar_t * deviceGUIDString2 = new wchar_t[256];
		int Device2GUID = GetPrivateProfileString(TEXT("Settings"), TEXT("Device2GUID"), NULL, deviceGUIDString2, 256, settingsFilename);
		char joystick_guid[256];
		sprintf(joystick_guid, "%S", deviceGUIDString2);
		SDL_JoystickGUID guid, dev_guid;
		int numJoysticks = SDL_NumJoysticks();
		std::string njs = std::to_string(numJoysticks);
		((char)njs.c_str());
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			extern int joystick1Index;
			if (i == joystick1Index)
			{
				continue;
			}
			SDL_Joystick* js2 = SDL_JoystickOpen(i);
			joystick_index2 = SDL_JoystickInstanceID(js2);
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

	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
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
			if (e.jaxis.which == joystick_index1)
			{
				if ((BothRumbleMotor == 1) & (LeftRumbleMotor == 0) & (RightRumbleMotor == 0))
				{
					if (e.jbutton.button == Button1Rumble || e.jbutton.button == Button2Rumble || e.jbutton.button == Button3Rumble || e.jbutton.button == Button4Rumble || e.jbutton.button == Button5Rumble || e.jbutton.button == Button6Rumble || e.jbutton.button == Button7Rumble || e.jbutton.button == Button8Rumble || e.jbutton.button == Button9Rumble || e.jbutton.button == Button10Rumble)
					{
						{
							double percentForce = ((RumbleStrength) / 100.0);
							double percentLength = (RumbleLength);
							triggers->LeftRight(percentForce, percentForce, percentLength);
						}
					}
				}
				if ((BothRumbleMotor == 0) & (LeftRumbleMotor == 1) & (RightRumbleMotor == 0))
				{
					if (e.jbutton.button == Button1Rumble || e.jbutton.button == Button2Rumble || e.jbutton.button == Button3Rumble || e.jbutton.button == Button4Rumble || e.jbutton.button == Button5Rumble || e.jbutton.button == Button6Rumble || e.jbutton.button == Button7Rumble || e.jbutton.button == Button8Rumble || e.jbutton.button == Button9Rumble || e.jbutton.button == Button10Rumble)
					{
						{
							double percentForce = ((RumbleStrength) / 100.0);
							double percentLength = (RumbleLength);
							triggers->LeftRight(0, percentForce, percentLength);
						}
					}
				}
				if ((BothRumbleMotor == 0) & (LeftRumbleMotor == 0) & (RightRumbleMotor == 1))
				{
					if (e.jbutton.button == Button1Rumble || e.jbutton.button == Button2Rumble || e.jbutton.button == Button3Rumble || e.jbutton.button == Button4Rumble || e.jbutton.button == Button5Rumble || e.jbutton.button == Button6Rumble || e.jbutton.button == Button7Rumble || e.jbutton.button == Button8Rumble || e.jbutton.button == Button9Rumble || e.jbutton.button == Button10Rumble)
					{
						{
							double percentForce = ((RumbleStrength) / 100.0);
							double percentLength = (RumbleLength);
							triggers->LeftRight(percentForce, 0, percentLength);
						}
					}
				}
			}
			if (e.jaxis.which == joystick_index2)
			{
				if ((BothRumbleMotor == 1) & (LeftRumbleMotor == 0) & (RightRumbleMotor == 0))
				{
					if (e.jbutton.button == Button1Device2Rumble || e.jbutton.button == Button2Device2Rumble || e.jbutton.button == Button3Device2Rumble || e.jbutton.button == Button4Device2Rumble || e.jbutton.button == Button5Device2Rumble || e.jbutton.button == Button6Device2Rumble || e.jbutton.button == Button7Device2Rumble || e.jbutton.button == Button8Device2Rumble || e.jbutton.button == Button9Device2Rumble || e.jbutton.button == Button10Device2Rumble)
					{
						{
							double percentForce = ((RumbleStrength) / 100.0);
							double percentLength = (RumbleLength);
							triggers->LeftRightDevice2(percentForce, percentForce, percentLength);
						}
					}
				}
				if ((BothRumbleMotor == 0) & (LeftRumbleMotor == 1) & (RightRumbleMotor == 0))
				{
					if (e.jbutton.button == Button1Device2Rumble || e.jbutton.button == Button2Device2Rumble || e.jbutton.button == Button3Device2Rumble || e.jbutton.button == Button4Device2Rumble || e.jbutton.button == Button5Device2Rumble || e.jbutton.button == Button6Device2Rumble || e.jbutton.button == Button7Device2Rumble || e.jbutton.button == Button8Device2Rumble || e.jbutton.button == Button9Device2Rumble || e.jbutton.button == Button10Device2Rumble)
					{
						{
							double percentForce = ((RumbleStrength) / 100.0);
							double percentLength = (RumbleLength);
							triggers->LeftRightDevice2(0, percentForce, percentLength);
						}
					}
				}
				if ((BothRumbleMotor == 0) & (LeftRumbleMotor == 0) & (RightRumbleMotor == 1))
				{
					if (e.jbutton.button == Button1Device2Rumble || e.jbutton.button == Button2Device2Rumble || e.jbutton.button == Button3Device2Rumble || e.jbutton.button == Button4Device2Rumble || e.jbutton.button == Button5Device2Rumble || e.jbutton.button == Button6Device2Rumble || e.jbutton.button == Button7Device2Rumble || e.jbutton.button == Button8Device2Rumble || e.jbutton.button == Button9Device2Rumble || e.jbutton.button == Button10Device2Rumble)
					{
						{
							double percentForce = ((RumbleStrength) / 100.0);
							double percentLength = (RumbleLength);
							triggers->LeftRightDevice2(percentForce, 0, percentLength);
						}
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
						{
							double percentForce = ((RumbleStrength) / 100.0);
							double percentLength = (RumbleLength);
							triggers->LeftRight(0, 0, percentLength);
						}
					}
				}
				if (e.jaxis.which == joystick_index2)
				{
					if (e.jbutton.button == Button1Device2Rumble || e.jbutton.button == Button2Device2Rumble || e.jbutton.button == Button3Device2Rumble || e.jbutton.button == Button4Device2Rumble || e.jbutton.button == Button5Device2Rumble || e.jbutton.button == Button6Device2Rumble || e.jbutton.button == Button7Device2Rumble || e.jbutton.button == Button8Device2Rumble || e.jbutton.button == Button9Device2Rumble || e.jbutton.button == Button10Device2Rumble)
					{
						{
							double percentForce = ((RumbleStrength) / 100.0);
							double percentLength = (RumbleLength);
							triggers->LeftRightDevice2(0, 0, percentLength);
						}
					}
				}
			}
		}
	}