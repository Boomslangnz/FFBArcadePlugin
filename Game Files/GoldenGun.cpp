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
#include "GoldenGun.h"
#include "SDL.h"
extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;
extern SDL_Haptic* ControllerHaptic2;
extern SDL_Haptic* haptic2;
static bool init = false;
static bool health1pbool = false;
static bool health2pbool = false;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int configFeedbackLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLength"), 120, settingsFilename);
static int HowtoRumbleGunEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleGunEffect"), 0, settingsFilename);
static int HowtoRumbleRageEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleRageEffect"), 0, settingsFilename);
static int HowtoRumbleHealthEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleHealthEffect"), 0, settingsFilename);
static int Gun1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gun1pStrength"), 0, settingsFilename);
static int Rage1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Rage1pStrength"), 0, settingsFilename);
static int Health1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Health1pStrength"), 0, settingsFilename);
static int Gun2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gun2pStrength"), 0, settingsFilename);
static int Rage2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Rage2pStrength"), 0, settingsFilename);
static int Health2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Health2pStrength"), 0, settingsFilename);

void GoldenGun::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	INT_PTR Base1p = helpers->ReadIntPtr(0x27034A0, true);
	INT_PTR Base11p = helpers->ReadIntPtr(Base1p + 0x24, false);
	INT_PTR Base21p = helpers->ReadIntPtr(Base11p + 0x34, false);
	UINT8 Health1p = helpers->ReadByte(Base21p + 0x3C, false);
	UINT8 Ammo1p = helpers->ReadByte(Base21p + 0x6C, false);
	UINT8 Ingame1p = helpers->ReadByte(Base21p + 0x38, false);
	UINT8 StartButton1p = helpers->ReadByte(0x478F8C, true);

	INT_PTR Base2p = helpers->ReadIntPtr(0x2703388, true);
	INT_PTR Base12p = helpers->ReadIntPtr(Base2p + 0x28, false);
	INT_PTR Base22p = helpers->ReadIntPtr(Base12p + 0x38, false);
	UINT8 Health2p = helpers->ReadByte(Base22p + 0x3C, false);
	UINT8 Ammo2p = helpers->ReadByte(Base22p + 0x6C, false);
	UINT8 Ingame2p = helpers->ReadByte(Base22p + 0x38, false);
	UINT8 StartButton2p = helpers->ReadByte(0x478F94, true);

	static UINT8 oldHealth1p = 0;
	static UINT8 oldAmmo1p = 0;
	static UINT8 oldHealth2p = 0;
	static UINT8 oldAmmo2p = 0;

	UINT8 newHealth1p = Health1p;
	UINT8 newAmmo1p = Ammo1p;
	UINT8 newHealth2p = Health2p;
	UINT8 newAmmo2p = Ammo2p;

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

	if (!health1pbool)
	{
		if ((Health1p == 0) && (Ingame1p == 12 || Ingame1p == 14))
		{
			if (HowtoRumbleHealthEffect == 0)
			{
				double percentForce = ((Health1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				triggers->Rumble(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 1)
			{
				double percentForce = ((Health1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				triggers->Rumble(0, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 2)
			{
				double percentForce = ((Health1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				triggers->Rumble(percentForce, 0, percentLength);
			}
			health1pbool = true;
		}
	}

	if (Ingame1p == 3)
	{
		if (StartButton1p != 0x80)
		{
			if (oldHealth1p != newHealth1p)
			{
				if (HowtoRumbleHealthEffect == 0)
				{
					double percentForce = ((Health1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					triggers->Rumble(percentForce, percentForce, percentLength);
				}
				else if (HowtoRumbleHealthEffect == 1)
				{
					double percentForce = ((Health1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					triggers->Rumble(0, percentForce, percentLength);
				}
				else if (HowtoRumbleHealthEffect == 2)
				{
					double percentForce = ((Health1pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					triggers->Rumble(percentForce, 0, percentLength);
				}
				health1pbool = false;
			}
		}
		
		if (oldAmmo1p != newAmmo1p)
		{
			if (HowtoRumbleGunEffect == 0)
			{
				double percentForce = ((Gun1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				triggers->Rumble(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleGunEffect == 1)
			{
				double percentForce = ((Gun1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				triggers->Rumble(0, percentForce, percentLength);
			}
			else if (HowtoRumbleGunEffect == 2)
			{
				double percentForce = ((Gun1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				triggers->Rumble(percentForce, 0, percentLength);
			}
		}
	}

	if (!health2pbool)
	{
		if ((Health2p == 0) && (Ingame2p == 12 || Ingame2p == 14))
		{
			if (HowtoRumbleHealthEffect == 0)
			{
				double percentForce = ((Health2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				triggers->RumbleDevice2(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 1)
			{
				double percentForce = ((Health2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				triggers->RumbleDevice2(0, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 2)
			{
				double percentForce = ((Health2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				triggers->RumbleDevice2(percentForce, 0, percentLength);
			}
			health2pbool = true;
		}
	}

	if (Ingame2p == 3)
	{
		if (StartButton2p != 0x80)
		{
			if (oldHealth2p != newHealth2p)
			{
				if (HowtoRumbleHealthEffect == 0)
				{
					double percentForce = ((Health2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					triggers->RumbleDevice2(percentForce, percentForce, percentLength);
				}
				else if (HowtoRumbleHealthEffect == 1)
				{
					double percentForce = ((Health2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					triggers->RumbleDevice2(0, percentForce, percentLength);
				}
				else if (HowtoRumbleHealthEffect == 2)
				{
					double percentForce = ((Health2pStrength) / 100.0);
					double percentLength = configFeedbackLength;
					triggers->RumbleDevice2(percentForce, 0, percentLength);
				}
			}
		}
		
		if (oldAmmo2p != newAmmo2p)
		{
			if (HowtoRumbleGunEffect == 0)
			{
				double percentForce = ((Gun2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				triggers->RumbleDevice2(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleGunEffect == 1)
			{
				double percentForce = ((Gun2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				triggers->RumbleDevice2(0, percentForce, percentLength);
			}
			else if (HowtoRumbleGunEffect == 2)
			{
				double percentForce = ((Gun2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				triggers->RumbleDevice2(percentForce, 0, percentLength);
			}
		}
	}

	oldHealth1p = newHealth1p;
	oldAmmo1p = newAmmo1p;
	oldHealth2p = newHealth2p;
	oldAmmo2p = newAmmo2p;
}