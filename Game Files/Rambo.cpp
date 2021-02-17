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
#include "Rambo.h"
#include "SDL.h"
extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;
extern SDL_Haptic* ControllerHaptic2;
extern SDL_Haptic* haptic2;
static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;
extern HINSTANCE gl_cgGLDll;
static bool init = false;

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

void Rambo::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	INT_PTR Base1p = helpers->ReadIntPtr((INT_PTR)gl_cgGLDll + 0x1C4E8, false);
	INT_PTR Base11p = helpers->ReadIntPtr(Base1p + 0x5BC, false);
	INT_PTR Base21p = helpers->ReadIntPtr(Base11p + 0x77C, false);
	INT_PTR Base31p = helpers->ReadIntPtr(Base21p + 0x0, false);
	INT_PTR Base41p = helpers->ReadIntPtr(Base31p + 0x20, false);
	UINT8 Health1p = helpers->ReadByte(Base41p + 0x3C, false);
	UINT8 Ammo1p = helpers->ReadByte(Base41p + 0x400, false);
	float Rage1p = helpers->ReadFloat32(Base41p + 0x68, false);

	INT_PTR Base2p = helpers->ReadIntPtr((INT_PTR)gl_cgGLDll + 0x9144, false);
	INT_PTR Base12p = helpers->ReadIntPtr(Base2p + 0x4F4, false);
	INT_PTR Base22p = helpers->ReadIntPtr(Base12p + 0x278, false);
	INT_PTR Base32p = helpers->ReadIntPtr(Base22p + 0x1B0, false);
	INT_PTR Base42p = helpers->ReadIntPtr(Base32p + 0x38, false);
	UINT8 Health2p = helpers->ReadByte(Base42p + 0x3C, false);
	UINT8 Ammo2p = helpers->ReadByte(Base42p + 0x400, false);
	float Rage2p = helpers->ReadFloat32(Base42p + 0x68, false);

	static UINT8 oldHealth1p = 0;
	static UINT8 oldAmmo1p = 0;
	static UINT8 oldHealth2p = 0;
	static UINT8 oldAmmo2p = 0;
	static float oldRage1p = 0;
	static float oldRage2p = 0;
	UINT8 newHealth1p = Health1p;
	UINT8 newAmmo1p = Ammo1p;
	UINT8 newHealth2p = Health2p;
	UINT8 newAmmo2p = Ammo2p;
	float newRage1p = Rage1p;
	float newRage2p = Rage2p;

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
	}

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

	if (oldRage1p != newRage1p)
	{
		if (HowtoRumbleRageEffect == 0)
		{
			double percentForce = ((Rage1pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (HowtoRumbleRageEffect == 1)
		{
			double percentForce = ((Rage1pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->Rumble(0, percentForce, percentLength);
		}
		else if (HowtoRumbleRageEffect == 2)
		{
			double percentForce = ((Rage1pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->Rumble(percentForce, 0, percentLength);
		}
	}

	if (oldRage2p != newRage2p)
	{
		if (HowtoRumbleRageEffect == 0)
		{
			double percentForce = ((Rage2pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->RumbleDevice2(percentForce, percentForce, percentLength);
		}
		else if (HowtoRumbleRageEffect == 1)
		{
			double percentForce = ((Rage2pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->RumbleDevice2(0, percentForce, percentLength);
		}
		else if (HowtoRumbleRageEffect == 2)
		{
			double percentForce = ((Rage2pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->RumbleDevice2(percentForce, 0, percentLength);
		}
	}

	oldHealth1p = newHealth1p;
	oldAmmo1p = newAmmo1p;
	oldRage1p = newRage1p;
	oldHealth2p = newHealth2p;
	oldAmmo2p = newAmmo2p;
	oldRage2p = newRage2p;
}