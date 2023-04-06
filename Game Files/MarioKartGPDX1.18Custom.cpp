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
#include "MarioKartGPDX1.18Custom.h"

static bool init;

extern int EnableDamper;
extern int DamperStrength;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int ConstantEffectForSteering = GetPrivateProfileInt(TEXT("Settings"), TEXT("ConstantEffectForSteering"), 0, settingsFilename);
static int ConstantEffectForSteeringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("ConstantEffectForSteeringStrength"), 0, settingsFilename);
static int WeaponRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("WeaponRumble"), 0, settingsFilename);
static int WeaponRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("WeaponRumbleStrength"), 0, settingsFilename);
static int CoinRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("CoinRumble"), 0, settingsFilename);
static int CoinRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("CoinRumbleStrength"), 0, settingsFilename);
static int DriftRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("DriftRumble"), 0, settingsFilename);
static int DriftRumbleControllerStrengthMultiplier = GetPrivateProfileInt(TEXT("Settings"), TEXT("DriftRumbleControllerStrengthMultiplier"), 0, settingsFilename);
static int HitGroundRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("HitGroundRumble"), 0, settingsFilename);
static int HitGroundRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("HitGroundRumbleStrength"), 0, settingsFilename);
static int BoostRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("BoostRumble"), 0, settingsFilename);
static int BoostRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("BoostRumbleStrength"), 0, settingsFilename);
static int MainShakeRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("MainShakeRumble"), 0, settingsFilename);
static int MainShakeRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("MainShakeRumbleStrength"), 0, settingsFilename);
static int DirtRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("DirtRumble"), 0, settingsFilename);
static int DirtRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("DirtRumbleStrength"), 0, settingsFilename);
static int GrassRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("GrassRumble"), 0, settingsFilename);
static int GrassRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("GrassRumbleStrength"), 0, settingsFilename);
static int SandRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("SandRumble"), 0, settingsFilename);
static int SandRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("SandRumbleStrength"), 0, settingsFilename);
static int WaterRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("WaterRumble"), 0, settingsFilename);
static int WaterRumbleWheelStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("WaterRumbleWheelStrength"), 0, settingsFilename);
static int WaterRumbleControllerStrengthMultiplier = GetPrivateProfileInt(TEXT("Settings"), TEXT("WaterRumbleControllerStrengthMultiplier"), 0, settingsFilename);
static int TileRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("TileRumble"), 0, settingsFilename);
static int TileRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("TileRumbleStrength"), 0, settingsFilename);
static int CarpetRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("CarpetRumble"), 0, settingsFilename);
static int CarpetRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("CarpetRumbleStrength"), 0, settingsFilename);
static int SpeedBumpRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("SmallBumpRumble"), 0, settingsFilename);
static int SpeedBumpRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("SmallBumpRumbleStrength"), 0, settingsFilename);
static int RoughTrackRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("RoughTrackRumble"), 0, settingsFilename);
static int RoughTrackRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("RoughTrackRumbleStrength"), 0, settingsFilename);
static int BridgeRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("BridgeRumble"), 0, settingsFilename);
static int BridgeRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("BridgeRumbleStrength"), 0, settingsFilename);
static int MenuRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("MenuRumble"), 0, settingsFilename);
static int MenuRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("MenuRumbleStrength"), 0, settingsFilename);

static UINT8 MenuPosition;
static UINT8 oldMenuPosition;
static UINT8 oldGameState;
static bool MenuEffect;

static int oldCoins;
static int oldWeapon;
static int oldHitGround;

static int(__stdcall* PlayerCostumeSelectionRightOri)(DWORD* a1);
static int __stdcall PlayerCostumeSelectionRightHook(DWORD* a1)
{
	MenuEffect = true;
	return PlayerCostumeSelectionRightOri(a1);
}

static int(__stdcall* PlayerCostumeSelectionLeftOri)(DWORD* a1);
static int __stdcall PlayerCostumeSelectionLeftHook(DWORD* a1)
{
	MenuEffect = true;
	return PlayerCostumeSelectionLeftOri(a1);
}

static int(__stdcall* KartCostumeSelectionOri)(int a1, int a2, int a3);
static int __stdcall KartCostumeSelectionHook(int a1, int a2, int a3)
{
	MenuEffect = true;
	return KartCostumeSelectionOri(a1, a2, a3);
}

static DWORD*(__stdcall* PlayerSelectionRightOri)(int a1);
static DWORD* __stdcall PlayerSelectionRightHook(int a1)
{
	MenuEffect = true;
	return PlayerSelectionRightOri(a1);
}

static DWORD* (__stdcall* PlayerSelectionLeftOri)(int a1);
static DWORD* __stdcall PlayerSelectionLeftHook(int a1)
{
	MenuEffect = true;
	return PlayerSelectionLeftOri(a1);
}

static DWORD* (__stdcall* ModeSelectionRightOri)(int a1);
static DWORD* __stdcall ModeSelectionRightHook(int a1)
{
	MenuEffect = true;
	return ModeSelectionRightOri(a1);
}

static DWORD* (__stdcall* ModeSelectionLeftOri)(int a1);
static DWORD* __stdcall ModeSelectionLeftHook(int a1)
{
	MenuEffect = true;
	return ModeSelectionLeftOri(a1);
}

static int(__stdcall* SpeedSelectionRightOri)(int a1);
static int __stdcall SpeedSelectionRightHook(int a1)
{
	MenuEffect = true;
	return SpeedSelectionRightOri(a1);
}

static int(__stdcall* SpeedSelectionLeftOri)(int a1);
static int __stdcall SpeedSelectionLeftHook(int a1)
{
	MenuEffect = true;
	return SpeedSelectionLeftOri(a1);
}

static int(__stdcall* CupSelectionRightOri)(int a1, int a2, int a3);
static int __stdcall CupSelectionRightHook(int a1, int a2, int a3)
{
	MenuEffect = true;
	return CupSelectionRightOri(a1, a2, a3);
}

static int(__stdcall* CupSelectionLeftOri)(int a1, int a2, int a3);
static int __stdcall CupSelectionLeftHook(int a1, int a2, int a3)
{
	MenuEffect = true;
	return CupSelectionLeftOri(a1, a2, a3);
}

static int(__stdcall* RoundSelectionRightOri)(int a1);
static int __stdcall RoundSelectionRightHook(int a1)
{
	MenuEffect = true;
	return RoundSelectionRightOri(a1);
}

static int(__stdcall* RoundSelectionLeftOri)(int a1);
static int __stdcall RoundSelectionLeftHook(int a1)
{
	MenuEffect = true;
	return RoundSelectionLeftOri(a1);
}

static int(__stdcall* ItemSelectionRightOri)(int a1);
static int __stdcall ItemSelectionRightHook(int a1)
{
	MenuEffect = true;
	return ItemSelectionRightOri(a1);
}

static int(__stdcall* ItemSelectionLeftOri)(int a1);
static int __stdcall ItemSelectionLeftHook(int a1)
{
	MenuEffect = true;
	return ItemSelectionLeftOri(a1);
}

static int(__stdcall* Item2SelectionRightOri)(int a1);
static int __stdcall Item2SelectionRightHook(int a1)
{
	MenuEffect = true;
	return Item2SelectionRightOri(a1);
}

static int(__stdcall* Item2SelectionLeftOri)(int a1);
static int __stdcall Item2SelectionLeftHook(int a1)
{
	MenuEffect = true;
	return Item2SelectionLeftOri(a1);
}

static int(__stdcall* Item3SelectionRightOri)(int a1);
static int __stdcall Item3SelectionRightHook(int a1)
{
	MenuEffect = true;
	return Item3SelectionRightOri(a1);
}

static int(__stdcall* Item3SelectionLeftOri)(int a1);
static int __stdcall Item3SelectionLeftHook(int a1)
{
	MenuEffect = true;
	return Item3SelectionLeftOri(a1);
}

void MarioKartGPDX118Custom::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	INT_PTR ff1 = helpers->ReadIntPtr(0xAC72F4, true); //shake
	INT_PTR ff2 = helpers->ReadIntPtr(0xAC2A30, true);//??
	UINT8 ff3 = helpers->ReadByte(ff2 + 0x66C, false); // terrain data
	UINT8 ff5 = helpers->ReadByte(ff2 + 0x69C, false); //kart flying or on ground
	INT_PTR ff6 = helpers->ReadIntPtr(0xAAFAB8, true);
	INT_PTR ff7 = helpers->ReadIntPtr(ff6 + 0x44,false);
	INT_PTR ff8 = helpers->ReadIntPtr(ff7 + 0x70, false);
	INT_PTR ff9 = helpers->ReadIntPtr(ff8 + 0x108, false);
	INT_PTR ff10 = helpers->ReadIntPtr(ff9 + 0x98, false);
	UINT8 ff11 = helpers->ReadByte(ff10 + 0x4C4, false); // 1 during race only
	float Speed = helpers->ReadFloat32(ff2 + 0x580, false); //Speed of Kart
	UINT8 ff13 = helpers->ReadByte(0xAB9110, true); //picking up coins
	UINT8 ff14 = helpers->ReadByte(0xAC5C0D, true); //picking up weapon box
	UINT8 Wheel = helpers->ReadByte(0xAC6EAD, true); //0-255 steering
	INT_PTR ff16 = helpers->ReadIntPtr(0xAAD0BC, true);
	UINT8 ff17 = helpers->ReadByte(ff2 + 0x6B8, false); // Drift
	UINT8 ff18 = helpers->ReadByte(ff16 + 0x3A4, false); // Boost

	DWORD GameStateBase = helpers->ReadInt32(0xAAEE58, true);
	UINT8 GameState = helpers->ReadByte(GameStateBase + 0x44, false);

	helpers->log("got value: ");
	std::string ffs = std::to_string(ff1);
	helpers->log((char*)ffs.c_str()); helpers->log("got value: ");

	if (!init && MenuRumble)
	{
		init = true;

		DWORD ImageBase = (DWORD)GetModuleHandleA(0);

		MH_Initialize(); 
		MH_CreateHook((void*)(ImageBase + 0x386940), PlayerCostumeSelectionRightHook, (void**)&PlayerCostumeSelectionRightOri);
		MH_CreateHook((void*)(ImageBase + 0x3867E0), PlayerCostumeSelectionLeftHook, (void**)&PlayerCostumeSelectionLeftOri);
		MH_CreateHook((void*)(ImageBase + 0x3D1250), KartCostumeSelectionHook, (void**)&KartCostumeSelectionOri);
		MH_CreateHook((void*)(ImageBase + 0x379650), PlayerSelectionRightHook, (void**)&PlayerSelectionRightOri);
		MH_CreateHook((void*)(ImageBase + 0x379540), PlayerSelectionLeftHook, (void**)&PlayerSelectionLeftOri);
		MH_CreateHook((void*)(ImageBase + 0x3A7A50), ModeSelectionRightHook, (void**)&ModeSelectionRightOri);
		MH_CreateHook((void*)(ImageBase + 0x3A79D0), ModeSelectionLeftHook, (void**)&ModeSelectionLeftOri);
		MH_CreateHook((void*)(ImageBase + 0x377B30), SpeedSelectionRightHook, (void**)&SpeedSelectionRightOri);
		MH_CreateHook((void*)(ImageBase + 0x377AD0), SpeedSelectionLeftHook, (void**)&SpeedSelectionLeftOri);
		MH_CreateHook((void*)(ImageBase + 0x3908D0), CupSelectionRightHook, (void**)&CupSelectionRightOri);
		MH_CreateHook((void*)(ImageBase + 0x390800), CupSelectionLeftHook, (void**)&CupSelectionLeftOri);
		MH_CreateHook((void*)(ImageBase + 0x3B0160), RoundSelectionRightHook, (void**)&RoundSelectionRightOri);
		MH_CreateHook((void*)(ImageBase + 0x3B00D0), RoundSelectionLeftHook, (void**)&RoundSelectionLeftOri);
		MH_CreateHook((void*)(ImageBase + 0x39D460), ItemSelectionRightHook, (void**)&ItemSelectionRightOri);
		MH_CreateHook((void*)(ImageBase + 0x39D3C0), ItemSelectionLeftHook, (void**)&ItemSelectionLeftOri);
		MH_CreateHook((void*)(ImageBase + 0x39C640), Item2SelectionRightHook, (void**)&Item2SelectionRightOri);
		MH_CreateHook((void*)(ImageBase + 0x39C550), Item2SelectionLeftHook, (void**)&Item2SelectionLeftOri);
		MH_CreateHook((void*)(ImageBase + 0x39EF70), Item3SelectionRightHook, (void**)&Item3SelectionRightOri);
		MH_CreateHook((void*)(ImageBase + 0x39EEA0), Item3SelectionLeftHook, (void**)&Item3SelectionLeftOri);
		MH_EnableHook(MH_ALL_HOOKS);
	}

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	if (MenuRumble && !ff11)
	{
		DWORD MenuBase = helpers->ReadInt32(0xAAEEB0, true);
		DWORD MenuOff0 = helpers->ReadInt32(MenuBase + 0x10, false);

		DWORD BanapassOff0 = helpers->ReadInt32(GameStateBase + 0x38, false);

		if (GameState != oldGameState)
			MenuPosition = 0;

		switch (GameState)
		{
		case 0x09: // Banapass Selection Screen
			MenuPosition = helpers->ReadByte(BanapassOff0 + 0x30, false);
			break;
		case 0x13: // Camera Costume Selection Screen
			MenuPosition = helpers->ReadByte(MenuOff0 + 0x294, false);
			break;
		case 0x2D: // After Race Change Selection Screen
			MenuPosition = helpers->ReadByte(MenuOff0 + 0xE0, false);
			break;
		case 0x2F: // After Race Continue Selection Screen
			MenuPosition = helpers->ReadByte(MenuOff0 + 0xE8, false);
			break;
		}

		if (MenuPosition != oldMenuPosition && GameState == oldGameState)
		{
			double percentForce = MenuRumbleStrength / 100.0;
			triggers->Sine(60, 0, percentForce);
			triggers->Rumble(percentForce, percentForce, 100);
		}

		if (MenuEffect)
		{
			MenuEffect = false;
			double percentForce = MenuRumbleStrength / 100.0;
			triggers->Sine(60, 0, percentForce);
			triggers->Rumble(percentForce, percentForce, 100);
		}
	}

	if (ConstantEffectForSteering && ff11 == 1)
	{
		if (Wheel >= 0 && Wheel < 128)
		{
			double percentForce = ((128 - Wheel) / (ConstantEffectForSteeringStrength / 1.0));
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if (Wheel > 127 && Wheel < 256)
		{
			double percentForce = ((Wheel - 127) / (ConstantEffectForSteeringStrength / 1.0));
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}

	if ((MainShakeRumble) && (4194308 == ff1) && (ff11 == 1))
	{
		// Large Shake when hitting walls, other karts or getting hit by items
		double percentForce = ((MainShakeRumbleStrength) / 100.0);
		double percentLength = (500);
		triggers->Rumble(percentForce, percentForce, percentLength);
		triggers->Sine(200, 200, percentForce);
	}

	if ((BoostRumble == 1) && (ff18 == 1) && (ff11 == 1))
	{
		// Shake when Boost
		double percentForce = ((BoostRumbleStrength) / 100.0);
		double percentLength = (100);
		triggers->Rumble(percentForce, percentForce, percentLength);
		triggers->Sine(60, 60, percentForce);
	}

	if ((DriftRumble == 1) && (ff17 == 1) && (Wheel >= 0) && (Wheel < 128) && (ff11 == 1))
	{
		// Drift Effect including steering left
		double percentForce = (((128 - Wheel) / 128.0) * (DriftRumbleControllerStrengthMultiplier / 100.0));
		double percentLength = (100);
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Friction(percentForce);
	}

	if ((DriftRumble == 1) && (ff17 == 1) && (Wheel > 127) && (Wheel < 256) && (ff11 == 1))
	{
		// Drift Effect including steering right
		double percentForce = (((Wheel - 127) / 128.0) * (DriftRumbleControllerStrengthMultiplier / 100.0));
		double percentLength = (100);
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Friction(percentForce);
	}

	if ((HitGroundRumble == 1) && (oldHitGround != ff5) && (ff5 == 1) && (ff11 == 1))
	{
		// Shake when hitting ground
		double percentForce = ((HitGroundRumbleStrength) / 100.0);
		double percentLength = (100);
		triggers->Rumble(percentForce, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		Sleep(50);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}

	if ((WeaponRumble == 1) && (oldWeapon != ff14) && (ff11 == 1))
	{
		// Shake when picking up new weapons or using them
		double percentForce = ((WeaponRumbleStrength) / 100.0);
		double percentLength = (300);
		triggers->Rumble(percentForce, percentForce, percentLength);
		triggers->Sine(80, 50, percentForce);
	}

	if ((CoinRumble == 1) && (oldCoins != ff13) && (ff11 == 1))
	{
		// Shake when picking up coins
		double percentForce = ((CoinRumbleStrength) / 100.0);
		double percentLength = (200);
		triggers->Rumble(percentForce, percentForce, percentLength);
		triggers->Sine(50, 50, percentForce);
	}

	if ((DirtRumble == 1) && (3 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		// small friction when driving on dirt while moving
		double percentForce = ((DirtRumbleStrength) / 100.0);
		double percentLength = (100);
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Friction(percentForce);
	}

	if ((SpeedBumpRumble == 1) && (10 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		//	Small constant when hitting bumps
		double percentForce = ((SpeedBumpRumbleStrength) / 100.0);
		double percentLength = (50);
		triggers->Rumble(percentForce, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, 0);
	}

	if ((GrassRumble == 1) && (4 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		// Wheel rumbles while driving on grass
		double percentForce = ((GrassRumbleStrength) / 100.0);
		double percentLength = (50);
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Sine(50, 50, percentForce);
	}

	if ((CarpetRumble == 1) && (9 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		// Wheel rumbles while driving on carpet
		double percentForce = ((CarpetRumbleStrength) / 100.0);
		double percentLength = (50);
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Sine(50, 50, percentForce);
	}

	if ((WaterRumble == 1) && (7 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1) && (Wheel >= 0) && (Wheel < 128))
	{
		//wheel hard to turn while driving through water
		double percentForce = ((WaterRumbleWheelStrength) / 100.0);
		double percentForce1 = ((128 - Wheel / 128.0) * (WaterRumbleControllerStrengthMultiplier / 100.0));
		double percentLength = (100);
		triggers->Rumble(percentForce1, 0, percentLength);
		triggers->Friction(percentForce);
	}

	if ((WaterRumble == 1) && (7 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1) && (Wheel > 127))
	{
		double percentForce = ((WaterRumbleWheelStrength) / 100.0);
		double percentForce1 = ((Wheel - 127 / 128.0) * (WaterRumbleControllerStrengthMultiplier / 100.0));
		double percentLength = (100);
		triggers->Rumble(0, percentForce1, percentLength);
		triggers->Friction(percentForce);
	}

	if ((TileRumble == 1) && (12 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		//Wheel rumbles lightly when driving over tiles
		double percentForce = ((TileRumbleStrength) / 100.0);
		double percentLength = (150);
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Friction(percentForce);
	}

	if ((SandRumble == 1) && (14 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		//Wheel rumbles lightly when driving over sand
		double percentForce = ((SandRumbleStrength) / 100.0);
		double percentLength = (50);
		triggers->Rumble(percentForce, 0, percentLength);
		triggers->Sine(70, 70, percentForce);
	}

	if ((RoughTrackRumble == 1) && (11 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		//Wheel rumbles lightly when driving over rough part of track
		double percentForce = ((RoughTrackRumbleStrength) / 100.0);
		double percentLength = (100);
		triggers->Rumble(0, percentForce, percentLength);
		triggers->Sine(40, 50, percentForce);
	}

	if ((BridgeRumble == 1) && (8 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		//Wheel rumbles moderately when driving over wooden bridges
		double percentForce = ((BridgeRumbleStrength) / 100.0);
		double percentLength = (100);
		triggers->Rumble(percentForce, percentForce, percentLength);
		triggers->Sine(120, 120, percentForce);
	}

	oldCoins = ff13;
	oldWeapon = ff14;
	oldHitGround = ff5;
	oldMenuPosition = MenuPosition;
	oldGameState = GameState;
}