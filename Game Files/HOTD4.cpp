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
#include "HOTD4.h"
#include "SDL.h"
#include <Windows.h>
extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;
extern SDL_Haptic* ControllerHaptic2;
extern SDL_Haptic* haptic2;
static EffectTriggers *myTriggers;
static EffectConstants *myConstants;
static Helpers *myHelpers;
SDL_Event e;

static int RunningThread(void *ptr)
{
	int cnt;
	for (cnt = 0; cnt >= 0; ++cnt)
	{
		INT_PTR Base = myHelpers->ReadIntPtr(0x1CCEC0, true);
		INT_PTR Base1 = myHelpers->ReadIntPtr(Base + 0xF8, false);
		INT_PTR Base2 = myHelpers->ReadIntPtr(Base1 + 0x38, false);
		INT_PTR Base3 = myHelpers->ReadIntPtr(Base2 + 0x20, false);
		UINT8 Health = myHelpers->ReadByte(Base3 + 0x3C, false);
		UINT8 Bullet = myHelpers->ReadByte(Base3 + 0x274, false);
		UINT8 Grenade = myHelpers->ReadByte(Base3 + 0x2A0, false);

		UINT8 static oldHealth = 0;
		UINT8 static oldBullet = 0;
		UINT8 static oldGrenade = 0;
		UINT8 newHealth = Health;
		UINT8 newBullet = Bullet;
		UINT8 newGrenade = Grenade;

		wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
		int HowtoRumbleBulletEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleBulletEffect"), 0, settingsFilename);
		int HowtoRumbleGrenadeEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleGrenadeEffect"), 0, settingsFilename);
		int HowtoRumbleHealthEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleHealthEffect"), 0, settingsFilename);
		int Bullet1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Bullet1pStrength"), 0, settingsFilename);
		int Grenade1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Grenade1pStrength"), 0, settingsFilename);
		int Health1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Health1pStrength"), 0, settingsFilename);
		int Bullet2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Bullet2pStrength"), 0, settingsFilename);
		int Grenade2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Grenade2pStrength"), 0, settingsFilename);
		int Health2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Health2pStrength"), 0, settingsFilename);

		if (oldHealth != newHealth)
		{
			if (HowtoRumbleHealthEffect == 0)
			{
				double percentForce = ((Health1pStrength) / 100.0);
				double percentLength = (400);
				myTriggers->LeftRight(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 1)
			{
				double percentForce = ((Health1pStrength) / 100.0);
				double percentLength = (400);
				myTriggers->LeftRight(0, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 2)
			{
				double percentForce = ((Health1pStrength) / 100.0);
				double percentLength = (400);
				myTriggers->LeftRight(percentForce, 0, percentLength);
			}
		}
		if (oldBullet != newBullet)
		{
			if (HowtoRumbleBulletEffect == 0)
			{
				double percentForce = ((Bullet1pStrength) / 100.0);
				double percentLength = (400);
				myTriggers->LeftRight(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleBulletEffect == 1)
			{
				double percentForce = ((Bullet1pStrength) / 100.0);
				double percentLength = (400);
				myTriggers->LeftRight(0, percentForce, percentLength);
			}
			else if (HowtoRumbleBulletEffect == 2)
			{
				double percentForce = ((Bullet1pStrength) / 100.0);
				double percentLength = (400);
				myTriggers->LeftRight(percentForce, 0, percentLength);
			}
		}
		if (oldGrenade != newGrenade)
		{
			if (HowtoRumbleGrenadeEffect == 0)
			{
				double percentForce = ((Grenade1pStrength) / 100.0);
				double percentLength = (400);
				myTriggers->LeftRight(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleGrenadeEffect == 1)
			{
				double percentForce = ((Grenade1pStrength) / 100.0);
				double percentLength = (400);
				myTriggers->LeftRight(0, percentForce, percentLength);
			}
			else if (HowtoRumbleGrenadeEffect == 2)
			{
				double percentForce = ((Grenade1pStrength) / 100.0);
				double percentLength = (400);
				myTriggers->LeftRight(percentForce, 0, percentLength);
			}
		}
		oldHealth = newHealth;
		oldBullet = newBullet;
		oldGrenade = newGrenade;
	}
	return 0;
}

void HOTD4::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	SDL_Thread *thread;
	thread = SDL_CreateThread(RunningThread, "RunningThread", (void *)NULL);

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
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

	while (SDL_WaitEvent(&e) != 0)
	{
		myTriggers = triggers;
		myConstants = constants;
		myHelpers = helpers;
	}

	myTriggers = triggers;
	myConstants = constants;
	myHelpers = helpers;
}