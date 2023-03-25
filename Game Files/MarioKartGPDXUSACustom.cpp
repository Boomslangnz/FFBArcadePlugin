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
#include "MarioKartGPDXUSACustom.h"

extern int EnableDamper;
extern int DamperStrength;

void MarioKartGPDXUSACustom::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int ConstantEffectForSteering = GetPrivateProfileInt(TEXT("Settings"), TEXT("ConstantEffectForSteering"), 0, settingsFilename);
	int ConstantEffectForSteeringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("ConstantEffectForSteeringStrength"), 0, settingsFilename);
	int WeaponRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("WeaponRumble"), 0, settingsFilename);
	int WeaponRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("WeaponRumbleStrength"), 0, settingsFilename);
	int CoinRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("CoinRumble"), 0, settingsFilename);
	int CoinRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("CoinRumbleStrength"), 0, settingsFilename);
	int DriftRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("DriftRumble"), 0, settingsFilename);
	int DriftRumbleControllerStrengthMultiplier = GetPrivateProfileInt(TEXT("Settings"), TEXT("DriftRumbleControllerStrengthMultiplier"), 0, settingsFilename);
	int HitGroundRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("HitGroundRumble"), 0, settingsFilename);
	int HitGroundRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("HitGroundRumbleStrength"), 0, settingsFilename);
	int BoostRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("BoostRumble"), 0, settingsFilename);
	int BoostRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("BoostRumbleStrength"), 0, settingsFilename);
	int MainShakeRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("MainShakeRumble"), 0, settingsFilename);
	int MainShakeRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("MainShakeRumbleStrength"), 0, settingsFilename);
	int DirtRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("DirtRumble"), 0, settingsFilename);
	int DirtRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("DirtRumbleStrength"), 0, settingsFilename);
	int GrassRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("GrassRumble"), 0, settingsFilename);
	int GrassRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("GrassRumbleStrength"), 0, settingsFilename);
	int SandRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("SandRumble"), 0, settingsFilename);
	int SandRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("SandRumbleStrength"), 0, settingsFilename);
	int WaterRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("WaterRumble"), 0, settingsFilename);
	int WaterRumbleWheelStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("WaterRumbleWheelStrength"), 0, settingsFilename);
	int WaterRumbleControllerStrengthMultiplier = GetPrivateProfileInt(TEXT("Settings"), TEXT("WaterRumbleControllerStrengthMultiplier"), 0, settingsFilename);
	int TileRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("TileRumble"), 0, settingsFilename);
	int TileRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("TileRumbleStrength"), 0, settingsFilename);
	int CarpetRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("CarpetRumble"), 0, settingsFilename);
	int CarpetRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("CarpetRumbleStrength"), 0, settingsFilename);
	int SpeedBumpRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("SmallBumpRumble"), 0, settingsFilename);
	int SpeedBumpRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("SmallBumpRumbleStrength"), 0, settingsFilename);
	int RoughTrackRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("RoughTrackRumble"), 0, settingsFilename);
	int RoughTrackRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("RoughTrackRumbleStrength"), 0, settingsFilename);
	int BridgeRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("BridgeRumble"), 0, settingsFilename);
	int BridgeRumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("BridgeRumbleStrength"), 0, settingsFilename);

	INT_PTR ff1 = helpers->ReadIntPtr(0xB96B74, /* isRelativeOffset */ true); //shake
	INT_PTR ff2 = helpers->ReadIntPtr(0xB4F324,/* isRelativeOffset */ true);
	UINT8 ff3 = helpers->ReadInt32(ff2 + 0x628, /* isRelativeOffset */ false); // terrain data
	UINT8 ff5 = helpers->ReadInt32(ff2 + 0x658, /* isRelativeOffset */ false); //kart flying or on ground
	INT_PTR ff6 = helpers->ReadIntPtr(0xB486BC,/* isRelativeOffset */ true);
	INT_PTR ff7 = helpers->ReadIntPtr(ff6 + 0x2E0, /* isRelativeOffset */ false);
	INT_PTR ff8 = helpers->ReadIntPtr(ff7 + 0xAC, /* isRelativeOffset */ false);
	INT_PTR ff9 = helpers->ReadIntPtr(ff8 + 0xC, /* isRelativeOffset */ false);
	INT_PTR ff10 = helpers->ReadIntPtr(ff9 + 0xC, /* isRelativeOffset */ false);
	UINT8 ff11 = helpers->ReadByte(ff10 + 0x330, /* isRelativeOffset */ false); // 1 during race only
	float Speed = helpers->ReadFloat32(ff2 + 0x558, /* isRelativeOffset */ false); //Speed of Kart
	UINT8 ff13 = helpers->ReadByte(0xB4E330, /* isRelativeOffset */ true); //picking up coins
	UINT8 ff14 = helpers->ReadByte(0xB9548D, /* isRelativeOffset */ true); //picking up weapon box
	INT_PTR Wheelbase = helpers->ReadIntPtr(0xB4F2E0, /* isRelativeOffset */ true);
	UINT8 Wheel = helpers->ReadByte(Wheelbase + 0x125, /* isRelativeOffset */ false); //0-255 steering
	INT_PTR ff16 = helpers->ReadIntPtr(0xB441C8, /* isRelativeOffset*/ true);
	UINT8 ff17 = helpers->ReadByte(ff2 + 0x674, /* isRelativeOffset */ false); // Drift
	UINT8 ff18 = helpers->ReadByte(ff16 + 0x3A4, /* isRelativeOffset */ false); // Boost

	int static oldcoins = 0;
	int newcoins = ff13;
	int static oldweapon = 0;
	int newweapon = ff14;
	int static oldhitground = 0;
	int newhitground = ff5;

	if (EnableDamper == 1)
	{
		triggers->Damper(DamperStrength / 100.0);
	}

	if ((ConstantEffectForSteering == 1) && (ff11 == 1))
	{
		if ((Wheel >= 0) && (Wheel < 128))
		{
			double percentForce = ((128 - Wheel) / (ConstantEffectForSteeringStrength / 1.0));
			double percentLength = 100;
			triggers->LeftRight(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((Wheel > 127) && (Wheel < 256))
		{
			double percentForce = ((Wheel - 127) / (ConstantEffectForSteeringStrength / 1.0));
			double percentLength = 100;
			triggers->LeftRight(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}
	if ((MainShakeRumble == 1) && (4194308 == ff1) && (ff11 == 1))
	{
		// Large Shake when hitting walls, other karts or getting hit by items
		double percentForce = ((MainShakeRumbleStrength) / 100.0);
		double percentLength = (500);
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(200, 200, percentForce);
	}
	else if ((BoostRumble == 1) && (ff18 == 1) && (ff11 == 1))
	{
		// Shake when Boost
		double percentForce = ((BoostRumbleStrength) / 100.0);
		double percentLength = (100);
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(60, 60, percentForce);
	}
	else if ((DriftRumble == 1) && (ff17 == 1) && (Wheel >= 0) && (Wheel < 128) && (ff11 == 1))
	{
		// Drift Effect including steering left
		double percentForce = (((128 - Wheel) / 128.0) * (DriftRumbleControllerStrengthMultiplier / 100.0));
		double percentLength = (100);
		triggers->LeftRight(percentForce, 0, percentLength);
		triggers->Friction(percentForce);
	}
	else if ((DriftRumble == 1) && (ff17 == 1) && (Wheel > 127) && (Wheel < 256) && (ff11 == 1))
	{
		// Drift Effect including steering right
		double percentForce = (((Wheel - 127) / 128.0) * (DriftRumbleControllerStrengthMultiplier / 100.0));
		double percentLength = (100);
		triggers->LeftRight(0, percentForce, percentLength);
		triggers->Friction(percentForce);
	}
	else if ((HitGroundRumble == 1) && (oldhitground != newhitground) && (ff5 == 1) && (ff11 == 1))
	{
		// Shake when hitting ground
		double percentForce = ((HitGroundRumbleStrength) / 100.0);
		double percentLength = (100);
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		Sleep(50);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
	}
	else if ((WeaponRumble == 1) && (oldweapon != newweapon) && (ff11 == 1))
	{
		// Shake when picking up new weapons or using them
		double percentForce = ((WeaponRumbleStrength) / 100.0);
		double percentLength = (300);
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(80, 50, percentForce);
	}
	else if ((CoinRumble == 1) && (oldcoins != newcoins) && (ff11 == 1))
	{
		// Shake when picking up coins
		double percentForce = ((CoinRumbleStrength) / 100.0);
		double percentLength = (200);
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(50, 50, percentForce);
	}
	else if ((DirtRumble == 1) && (3 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		// small friction when driving on dirt while moving
		double percentForce = ((DirtRumbleStrength) / 100.0);
		double percentLength = (100);
		triggers->LeftRight(percentForce, 0, percentLength);
		triggers->Friction(percentForce);
	}
	else if ((SpeedBumpRumble == 1) && (10 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		//	Small constant when hitting bumps
		double percentForce = ((SpeedBumpRumbleStrength) / 100.0);
		double percentLength = (50);
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, 0);
	}
	else if ((GrassRumble == 1) && (4 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		// Wheel rumbles while driving on grass
		double percentForce = ((GrassRumbleStrength) / 100.0);
		double percentLength = (50);
		triggers->LeftRight(0, percentForce, percentLength);
		triggers->Sine(50, 50, percentForce);
	}
	else if ((CarpetRumble == 1) && (9 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		// Wheel rumbles while driving on carpet
		double percentForce = ((CarpetRumbleStrength) / 100.0);
		double percentLength = (50);
		triggers->LeftRight(0, percentForce, percentLength);
		triggers->Sine(50, 50, percentForce);
	}
	else if ((WaterRumble == 1) && (7 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1) && (Wheel >= 0) && (Wheel < 128))
	{
		//wheel hard to turn while driving through water
		double percentForce = ((WaterRumbleWheelStrength) / 100.0);
		double percentForce1 = ((128 - Wheel / 128.0) * (WaterRumbleControllerStrengthMultiplier / 100.0));
		double percentLength = (100);
		triggers->LeftRight(percentForce1, 0, percentLength);
		triggers->Friction(percentForce);
	}
	else if ((WaterRumble == 1) && (7 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1) && (Wheel > 127))
	{
		double percentForce = ((WaterRumbleWheelStrength) / 100.0);
		double percentForce1 = ((Wheel - 127 / 128.0) * (WaterRumbleControllerStrengthMultiplier / 100.0));
		double percentLength = (100);
		triggers->LeftRight(0, percentForce1, percentLength);
		triggers->Friction(percentForce);
	}
	else if ((TileRumble == 1) && (12 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		//Wheel rumbles lightly when driving over tiles
		double percentForce = ((TileRumbleStrength) / 100.0);
		double percentLength = (150);
		triggers->LeftRight(0, percentForce, percentLength);
		triggers->Friction(percentForce);
	}
	else if ((SandRumble == 1) && (14 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		//Wheel rumbles lightly when driving over sand
		double percentForce = ((SandRumbleStrength) / 100.0);
		double percentLength = (50);
		triggers->LeftRight(percentForce, 0, percentLength);
		triggers->Sine(70, 70, percentForce);
	}
	else if ((RoughTrackRumble == 1) && (11 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		//Wheel rumbles lightly when driving over rough part of track
		double percentForce = ((RoughTrackRumbleStrength) / 100.0);
		double percentLength = (100);
		triggers->LeftRight(0, percentForce, percentLength);
		triggers->Sine(40, 50, percentForce);
	}
	else if ((BridgeRumble == 1) && (8 == ff3) && (ff11 == 1) && (ff5 == 1) && (Speed > 0.1))
	{
		//Wheel rumbles moderately when driving over wooden bridges
		double percentForce = ((BridgeRumbleStrength) / 100.0);
		double percentLength = (100);
		triggers->LeftRight(percentForce, percentForce, percentLength);
		triggers->Sine(180, 150, percentForce);
	}
	oldcoins = newcoins;
	oldweapon = newweapon;
	oldhitground = newhitground;
}