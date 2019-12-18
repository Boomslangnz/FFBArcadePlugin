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
#include "Transformers.h"
#include "SDL.h"
extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;
extern SDL_Haptic* ControllerHaptic2;
extern SDL_Haptic* haptic2;
static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;
static bool init = false;
static bool Player1Shoot = false;
static bool Player2Shoot = false;

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

void Transformers::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	INT_PTR Base1p = helpers->ReadIntPtr(0x1A3CC1C, true);
	INT_PTR Base11p = helpers->ReadIntPtr(Base1p + 0x34, false);
	INT_PTR Base21p = helpers->ReadIntPtr(Base11p + 0x39C, false);
	UINT8 Health1p = helpers->ReadByte(Base21p + 0x54, false);

	INT_PTR Base12p = helpers->ReadIntPtr(Base1p + 0x20, false);
	INT_PTR Base22p = helpers->ReadIntPtr(Base12p + 0x398, false);
	INT_PTR Base32p = helpers->ReadIntPtr(Base22p + 0x1C, false);
	UINT8 Health2p = helpers->ReadByte(Base32p + 0x310, false);

	UINT8 Gun = helpers->ReadByte(0xD8CE14, false);
	UINT8 Trigger1p = helpers->ReadByte(0xD8D110, false);
	UINT8 Trigger2p = helpers->ReadByte(0xD8D112, false);

	static UINT8 oldHealth1p = 0;
	static UINT8 oldHealth2p = 0;
	UINT8 newHealth1p = Health1p;
	UINT8 newHealth2p = Health2p;
	
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
		init = true;
	}

		if (Gun == 0x4B)
		{
			Player1Shoot = true;
			Player2Shoot = true;
		}
		else if (Gun == 0x42)
		{
			Player1Shoot = true;
			Player2Shoot = false;
		}
		else if (Gun == 0x09)
		{
			Player1Shoot = false;
			Player2Shoot = true;
		}

		if (Player1Shoot)
		{
			if (Trigger1p == 0)
			{
				Player1Shoot = false;
			}

			if ((Gun == 0x3) || (Gun == 0x90) || (Gun == 0x93) || (Gun == 0x02) || (Gun == 0x12))
			{
				Player1Shoot = false;
			}

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

		if (Player2Shoot)
		{
			if (Trigger2p == 0)
			{
				Player2Shoot = false;
			}

			if ((Gun == 0x3) || (Gun == 0x90) || (Gun == 0x93) || (Gun == 0x02) || (Gun == 0x12))
			{
				Player2Shoot = false;
			}

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
		
	if (oldHealth1p != newHealth1p)
	{
		if (Health1p != 100)
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
		}		
	}

	if (oldHealth2p != newHealth2p)
	{
		if (Health2p != 100)
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

	oldHealth1p = newHealth1p;
	oldHealth2p = newHealth2p;
}