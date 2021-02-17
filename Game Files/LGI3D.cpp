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
#include "LGI3D.h"
#include "SDL.h"
#include <Windows.h>
extern int joystick_index1;
extern int joystick_index2;
extern SDL_Haptic* haptic2;
extern SDL_Joystick* GameController2;
extern SDL_Haptic* ControllerHaptic2;
static bool init = false;

void LGI3D::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	
	int ff = helpers->ReadIntPtr(0x0065DA20, /* isRelativeOffset */ true);
	UINT8 ff1 = helpers->ReadByte(ff + 0x44, /* isRelativeOffset */ false);
	INT_PTR health1p1 = helpers->ReadIntPtr(0x008429F4, /* isRelativeOffset*/ true);
	INT_PTR health1p2 = helpers->ReadIntPtr(health1p1 + 0x4, /* isRelativeOffset */ false);
	INT_PTR health1p3 = helpers->ReadIntPtr(health1p2 + 0x74, /* isRelativeOffset */ false);
	INT_PTR health2p3 = helpers->ReadIntPtr(health1p2 + 0x78, /* isRelativeOffset */ false);
	float health1p = helpers->ReadFloat32(health1p3 + 0x14, /* isRelativeOffset */ false); //1p health
	float health2p = helpers->ReadFloat32(health2p3 + 0x14, /* isRelativeOffset */ false); //2p health
	helpers->log("got value: ");
	std::string ffs = std::to_string(ff1);
	helpers->log((char *)ffs.c_str());
	float static oldFloat1 = 0.0;
	float static oldFloat2 = 0.0;
	float newFloat1 = health1p;
	float newFloat2 = health2p;

	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int configFeedbackLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLength"), 120, settingsFilename);
	int HowtoRumbleKnockEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleKnockEffect"), 0, settingsFilename);
	int HowtoRumbleMotorEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleMotorEffect"), 0, settingsFilename);
	int HowtoRumbleHealthEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleHealthEffect"), 0, settingsFilename);
	int Knock1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Knock1pStrength"), 0, settingsFilename);
	int Motor1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Motor1pStrength"), 0, settingsFilename);
	int Health1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Health1pStrength"), 0, settingsFilename);
	int Knock2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Knock2pStrength"), 0, settingsFilename);
	int Motor2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Motor2pStrength"), 0, settingsFilename);
	int Health2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Health2pStrength"), 0, settingsFilename);

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

	if ((oldFloat1 != newFloat1) && (health1p != 0x01))
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

	if ((oldFloat2 != newFloat2) && (health2p != 0x01))
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

	if (ff1 & 0x20)
	{
		if (HowtoRumbleKnockEffect == 0)
		{
			double percentForce = ((Knock1pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (HowtoRumbleKnockEffect == 1)
		{
			double percentForce = ((Knock1pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->Rumble(0, percentForce, percentLength);
		}
		else if (HowtoRumbleKnockEffect == 2)
		{
			double percentForce = ((Knock1pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->Rumble(percentForce, 0, percentLength);
		}
	}

	if (ff1 & 0x40)
	{
		if (HowtoRumbleMotorEffect == 0)
		{
			double percentForce = ((Motor1pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (HowtoRumbleMotorEffect == 1)
		{
			double percentForce = ((Motor1pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->Rumble(0, percentForce, percentLength);
		}
		else if (HowtoRumbleMotorEffect == 2)
		{
			double percentForce = ((Motor1pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->Rumble(percentForce, 0, percentLength);
		}
	}

	if (ff1 & 0x04)
	{
		if (HowtoRumbleKnockEffect == 0)
		{
			double percentForce = ((Knock2pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->RumbleDevice2(percentForce, percentForce, percentLength);
		}
		else if (HowtoRumbleKnockEffect == 1)
		{
			double percentForce = ((Knock2pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->RumbleDevice2(0, percentForce, percentLength);
		}
		else if (HowtoRumbleKnockEffect == 2)
		{
			double percentForce = ((Knock2pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->RumbleDevice2(percentForce, 0, percentLength);
		}
	}

	if (ff1 & 0x08)
	{
		if (HowtoRumbleMotorEffect == 0)
		{
			double percentForce = ((Motor2pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->RumbleDevice2(percentForce, percentForce, percentLength);
		}
		else if (HowtoRumbleMotorEffect == 1)
		{
			double percentForce = ((Motor2pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->RumbleDevice2(0, percentForce, percentLength);
		}
		else if (HowtoRumbleMotorEffect == 2)
		{
			double percentForce = ((Motor2pStrength) / 100.0);
			double percentLength = configFeedbackLength;
			triggers->RumbleDevice2(percentForce, 0, percentLength);
		}
	}
	oldFloat1 = newFloat1;
	oldFloat2 = newFloat2;
}