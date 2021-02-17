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
static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;
extern SDL_Haptic* ControllerHaptic2;
extern SDL_Haptic* haptic2;
static EffectTriggers *myTriggers;
static EffectConstants *myConstants;
static Helpers *myHelpers;
extern HINSTANCE gl_cgGLDll;
static bool HealthA = false;
static bool HealthB = false;
static bool init = false;

static int ThreadLoop()
{
	INT_PTR Base1p = myHelpers->ReadIntPtr((INT_PTR)gl_cgGLDll + 0x9164, false);
	INT_PTR Base11p = myHelpers->ReadIntPtr(Base1p + 0x11C, false);
	INT_PTR Base21p = myHelpers->ReadIntPtr(Base11p + 0x50, false);
	INT_PTR Base31p = myHelpers->ReadIntPtr(Base21p + 0x20, false);
	UINT8 Health1p = myHelpers->ReadByte(Base31p + 0x3C, false);
	UINT8 Bullet1p = myHelpers->ReadByte(Base31p + 0x274, false);
	UINT8 GrenadeExplode1p = myHelpers->ReadByte(Base31p + 0x2B3, false);
	INT_PTR Base2p = myHelpers->ReadIntPtr((INT_PTR)gl_cgGLDll + 0x9164, false);
	INT_PTR Base12p = myHelpers->ReadIntPtr(Base2p + 0x11C, false);
	INT_PTR Base22p = myHelpers->ReadIntPtr(Base12p + 0x50, false);
	INT_PTR Base32p = myHelpers->ReadIntPtr(Base22p + 0x38, false);
	UINT8 Health2p = myHelpers->ReadByte(Base32p + 0x3C, false);
	UINT8 Bullet2p = myHelpers->ReadByte(Base32p + 0x274, false);
	UINT8 GrenadeExplode2p = myHelpers->ReadByte(Base32p + 0x2B3, false);
	UINT8 IngameValue1p = myHelpers->ReadByte(Base31p + 0x38, false);
	UINT8 IngameValue2p = myHelpers->ReadByte(Base32p + 0x38, false);
	INT_PTR StartBase = myHelpers->ReadIntPtr((INT_PTR)gl_cgGLDll + 0x3C40, false);
	INT_PTR StartBase1 = myHelpers->ReadIntPtr(StartBase + 0x130, false);
	INT_PTR StartBase2 = myHelpers->ReadIntPtr(StartBase1 + 0x234, false);
	UINT8 StartButton1p = myHelpers->ReadByte(StartBase2 + 0x530, false);
	UINT8 StartButton2p = myHelpers->ReadByte(StartBase2 + 0x538, false);

	UINT8 static oldHealth1p = 0;
	UINT8 static oldBullet1p = 0;
	UINT8 static oldHealth2p = 0;
	UINT8 static oldBullet2p = 0;
	UINT8 newHealth1p = Health1p;
	UINT8 newBullet1p = Bullet1p;
	UINT8 newHealth2p = Health2p;
	UINT8 newBullet2p = Bullet2p;

	wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
	int configFeedbackLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLength"), 120, settingsFilename);
	int HowtoRumbleBulletEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleBulletEffect"), 0, settingsFilename);
	int HowtoRumbleGrenadeEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleGrenadeEffect"), 0, settingsFilename);
	int HowtoRumbleHealthEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumbleHealthEffect"), 0, settingsFilename);
	int Bullet1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Bullet1pStrength"), 0, settingsFilename);
	int Grenade1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Grenade1pStrength"), 0, settingsFilename);
	int Health1pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Health1pStrength"), 0, settingsFilename);
	int Bullet2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Bullet2pStrength"), 0, settingsFilename);
	int Grenade2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Grenade2pStrength"), 0, settingsFilename);
	int Health2pStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Health2pStrength"), 0, settingsFilename);

	if ((Health1p == 0) && (IngameValue1p == 11))
	{
		if (!HealthA)
		{
			if (HowtoRumbleHealthEffect == 0)
			{
				double percentForce = ((Health1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->Rumble(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 1)
			{
				double percentForce = ((Health1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->Rumble(0, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 2)
			{
				double percentForce = ((Health1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->Rumble(percentForce, 0, percentLength);
			}
			HealthA = true;
		}
	}

	if ((Health2p == 0) && (IngameValue2p == 11))
	{
		if (!HealthB)
		{
			if (HowtoRumbleHealthEffect == 0)
			{
				double percentForce = ((Health2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->RumbleDevice2(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 1)
			{
				double percentForce = ((Health2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->RumbleDevice2(0, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 2)
			{
				double percentForce = ((Health2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->RumbleDevice2(percentForce, 0, percentLength);
			}
			HealthB = true;
		}
	}

	if ((IngameValue1p == 3) && (StartButton1p != 0x80))
	{
		if (oldHealth1p != newHealth1p)
		{
			if (HowtoRumbleHealthEffect == 0)
			{
				double percentForce = ((Health1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->Rumble(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 1)
			{
				double percentForce = ((Health1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->Rumble(0, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 2)
			{
				double percentForce = ((Health1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->Rumble(percentForce, 0, percentLength);
			}
		}
		if (oldBullet1p != newBullet1p)
		{
			if (HowtoRumbleBulletEffect == 0)
			{
				double percentForce = ((Bullet1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->Rumble(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleBulletEffect == 1)
			{
				double percentForce = ((Bullet1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->Rumble(0, percentForce, percentLength);
			}
			else if (HowtoRumbleBulletEffect == 2)
			{
				double percentForce = ((Bullet1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->Rumble(percentForce, 0, percentLength);
			}
		}
		if (GrenadeExplode1p == 0x42)
		{
			if (HowtoRumbleGrenadeEffect == 0)
			{
				double percentForce = ((Grenade1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->Rumble(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleGrenadeEffect == 1)
			{
				double percentForce = ((Grenade1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->Rumble(0, percentForce, percentLength);
			}
			else if (HowtoRumbleGrenadeEffect == 2)
			{
				double percentForce = ((Grenade1pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->Rumble(percentForce, 0, percentLength);
			}
		}
		HealthA = false;
	}

	if ((IngameValue2p == 3) && (StartButton2p != 0x80))
	{
		if (oldHealth2p != newHealth2p)
		{
			if (HowtoRumbleHealthEffect == 0)
			{
				double percentForce = ((Health2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->RumbleDevice2(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 1)
			{
				double percentForce = ((Health2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->RumbleDevice2(0, percentForce, percentLength);
			}
			else if (HowtoRumbleHealthEffect == 2)
			{
				double percentForce = ((Health2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->RumbleDevice2(percentForce, 0, percentLength);
			}
		}
		if (oldBullet2p != newBullet2p)
		{
			if (HowtoRumbleBulletEffect == 0)
			{
				double percentForce = ((Bullet2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->RumbleDevice2(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleBulletEffect == 1)
			{
				double percentForce = ((Bullet2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->RumbleDevice2(0, percentForce, percentLength);
			}
			else if (HowtoRumbleBulletEffect == 2)
			{
				double percentForce = ((Bullet2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->RumbleDevice2(percentForce, 0, percentLength);
			}
		}
		if (GrenadeExplode2p == 0x42)
		{
			if (HowtoRumbleGrenadeEffect == 0)
			{
				double percentForce = ((Grenade2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->RumbleDevice2(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumbleGrenadeEffect == 1)
			{
				double percentForce = ((Grenade2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->RumbleDevice2(0, percentForce, percentLength);
			}
			else if (HowtoRumbleGrenadeEffect == 2)
			{
				double percentForce = ((Grenade2pStrength) / 100.0);
				double percentLength = configFeedbackLength;
				myTriggers->RumbleDevice2(percentForce, 0, percentLength);
			}
		}
		HealthB = false;
	}
	oldHealth1p = newHealth1p;
	oldBullet1p = newBullet1p;
	oldHealth2p = newHealth2p;
	oldBullet2p = newBullet2p;

	return 0;
}

static DWORD WINAPI RunningLoop(LPVOID lpParam)
{
	while (true)
	{
		ThreadLoop();
		Sleep(16);
	}
}

void HOTD4::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	if (!init)
	{
		myTriggers = triggers;
		myConstants = constants;
		myHelpers = helpers;
		CreateThread(NULL, 0, RunningLoop, NULL, 0, NULL);

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
	
	myTriggers = triggers;
	myConstants = constants;
	myHelpers = helpers;
}