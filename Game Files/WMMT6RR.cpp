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
#include "WMMT6RR.h"
#include "SDL.h"

extern int EnableDamper;
extern int DamperStrength;
static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;
extern SDL_Event e;
static UINT8 oldgear = 0;
static bool init = false;
// static bool gameFfbStarted = false;
static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int SpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("SpringStrength"), 100, settingsFilename);
static int FrictionStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("FrictionStrength"), 0, settingsFilename);
static int JointsAndStripesStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("JointsAndStripesStrength"), 100, settingsFilename);
static int CollisionsStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("CollisionsStrength"), 100, settingsFilename);
static int TiresSlipStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("TiresSlipStrength"), 100, settingsFilename);
static int HighSpeedVibrationsStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("HighSpeedVibrationsStrength"), 100, settingsFilename);
static int LimitBetweenHighSpeedVibrationsAndTiresSlip = GetPrivateProfileInt(TEXT("Settings"), TEXT("LimitBetweenHighSpeedVibrationsAndTiresSlip"), 75, settingsFilename);

static int ReverseCollision = GetPrivateProfileInt(TEXT("Settings"), TEXT("ReverseCollision"), 0, settingsFilename);
static int ReverseTiresSlip = GetPrivateProfileInt(TEXT("Settings"), TEXT("ReverseTiresSlip"), 0, settingsFilename);
// static int GearChangeStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("GearChangeStrength"), 20, settingsFilename);
// static int GearChangeDelay = GetPrivateProfileInt(TEXT("Settings"), TEXT("GearChangeDelay"), 250, settingsFilename);
// static int GearChangeLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("GearChangeLength"), 200, settingsFilename);
// static int WheelSpinStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("WheelSpinStrength"), 100, settingsFilename);
static int ShowButtonNumbersForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowButtonNumbersForSetup"), 0, settingsFilename);
//static int ForceFullTune = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceFullTune"), 0, settingsFilename);
//static int DisableRaceTimer = GetPrivateProfileInt(TEXT("Settings"), TEXT("DisableRaceTimer"), 0, settingsFilename);
//static int EnableForceFinish = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceFinish"), 0, settingsFilename);
//static int EnableForceTimeUp = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceTimeUp"), 0, settingsFilename);
//static int ForceFinishButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceFinishButton"), 99, settingsFilename);
//static int ForceTimeUpButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceTimeUpButton"), 99, settingsFilename);

//static int InputThread(void* ptr)
//{
//	if (1 != EnableForceFinish && 1 != EnableForceTimeUp)
//	{
//		return 0;
//	}
//
//	myHelpers->log("starting input thread");
//	while (SDL_WaitEvent(&e) != 0)
//	{
//		if (e.type == SDL_JOYBUTTONDOWN)
//		{
//			myHelpers->log("button pressed");
//			if (1 == EnableForceFinish && e.jbutton.button == ForceFinishButton)
//			{
//				INT_PTR ptr1 = myHelpers->ReadIntPtr(0x199A468, true);
//				myHelpers->WriteByte(ptr1 + 0x28, 8, false);
//			}
//			else if (1 == EnableForceTimeUp && e.jbutton.button == ForceTimeUpButton)
//			{
//				int tempDisableRaceTimer = DisableRaceTimer;
//				DisableRaceTimer = 0;
//				myHelpers->WriteFloat32(0x199AE18, 0, true);
//				if (1 == tempDisableRaceTimer)
//				{
//					Sleep(10000);
//					DisableRaceTimer = tempDisableRaceTimer;
//				}
//			}
//		}
//	}
//	myHelpers->log("input thread stopped");
//	return 0;
//}
//
//static int SpamThread(void* ptr)
//{
//	if (1 != ForceFullTune && 1 != DisableRaceTimer)
//	{
//		return 0;
//	}
//
//	Sleep(5000); // To avoid crashes
//	myHelpers->log("starting spam thread");
//	while (1)
//	{
//		if (1 == ForceFullTune)
//		{
//			INT_PTR ptr1 = myHelpers->ReadIntPtr(0x1948F10, true);
//			INT_PTR ptr2 = myHelpers->ReadIntPtr(ptr1 + 0x180 + 0xa8 + 0x18, false);
//			UINT8 car = myHelpers->ReadByte(ptr2 + 0x2C, false);
//			std::string msg = "car: " + std::to_string(car);
//			myHelpers->log((char*)msg.c_str());
//
//			if (0x00 < car)
//			{
//				UINT8 power = myHelpers->ReadByte(ptr2 + 0x98, false);
//				UINT8 handling = myHelpers->ReadByte(ptr2 + 0x9C, false);
//				msg = "power: " + std::to_string(power) + " | handling: " + std::to_string(handling);
//				myHelpers->log((char*)msg.c_str());
//
//				if (0x20 != (power + handling))
//				{
//					myHelpers->log("forcing full tune");
//					myHelpers->WriteByte(ptr2 + 0x98, 0x10, false);
//					myHelpers->WriteByte(ptr2 + 0x9C, 0x10, false);
//				}
//			}
//		}
//
//		if (1 == DisableRaceTimer)
//		{
//			myHelpers->WriteFloat32(0x199AE18, 999.99, true);
//		}
//
//		Sleep(500); // We don't need to spam too much
//	}
//	myHelpers->log("spam thread stopped");
//	return 0;
//}

// static int GearChangeThread(void* ptr)
// {
// 	if (GearChangeDelay > 0)
// 	{
// 		Sleep(GearChangeDelay);
// 	}
// 	myHelpers->log("gear change");
// 	double percentForce = GearChangeStrength / 100.0;
// 	myTriggers->Sine(GearChangeLength, GearChangeLength, percentForce);
// 	myTriggers->Rumble(0, percentForce, 150);
// 	return 0;
// }

void WMMT6RR::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers)
{
	if (!init)
	{
		init = true;
		myTriggers = triggers;
		myConstants = constants;
		myHelpers = helpers;
		//SDL_CreateThread(InputThread, "InputThread", (void*)NULL);
		//SDL_CreateThread(SpamThread, "SpamThread", (void*)NULL);
	}

	float spring = helpers->ReadFloat32(0x1F25264, true);
	float friction = helpers->ReadFloat32(0x1F25268, true);
	float collisions = helpers->ReadFloat32(0x1F2526C, true);
	float tiresSlip = helpers->ReadFloat32(0x1F25260, true);
	int speed = helpers->ReadInt32(0x1F2612C, true);
	int rpm = helpers->ReadInt32(0x1F2629C, true);
	std::string msg = "spring: " + std::to_string(spring) + " | friction: " + std::to_string(friction)
		+ " | collisions: " + std::to_string(collisions) + " | tires slip: " + std::to_string(tiresSlip)
		+ " | speed: " + std::to_string(speed)+ " | rpm: " +std::to_string(rpm);
	helpers->log((char*)msg.c_str());
	if(ReverseCollision)
	{
		collisions = -collisions;
	}
	if(ReverseTiresSlip)
	{
		tiresSlip = -tiresSlip;
	}

	if (EnableDamper == 1)
	{
		triggers->Damper(DamperStrength / 100.0);
	}

	double percentForce;
	if (!rpm && !speed)
	{
		helpers->log("fake spring+friction until game's FFB starts");
		percentForce = 0.3 * SpringStrength / 100.0;
		triggers->Spring(percentForce);
		percentForce = 0.5 * FrictionStrength / 100.0;
		triggers->Friction(percentForce);
	}
	else
	{
		helpers->log("game's FFB started");
		percentForce = (1.0 * spring) * SpringStrength / 100.0;
		triggers->Spring(percentForce);
		percentForce = (1.0 * friction) * FrictionStrength / 100.0;
		triggers->Friction(percentForce);
		if (0 < collisions)
		{
			if (0.209 <= collisions && 0.311 >= collisions)
			{
				helpers->log("joint/stripe on the right");
				percentForce = (1.0 * collisions) * JointsAndStripesStrength / 100.0;
				triggers->Sine(80, 80, percentForce);
				triggers->Rumble(0, percentForce, 150);
			}
			else
			{
				helpers->log("collision on the right");
				percentForce = (1.0 * collisions) * CollisionsStrength / 100.0;
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				triggers->Rumble(0, percentForce, 150);
			}
		}
		else if (0 > collisions)
		{
			if (-0.209 >= collisions && -0.311 <= collisions)
			{
				helpers->log("joint/stripe on the left");
				percentForce = (1.0 * collisions) * JointsAndStripesStrength / 100.0;
				triggers->Sine(80, 80, percentForce);
				triggers->Rumble(0, -1.0 * percentForce, 150);
			}
			else
			{
				helpers->log("collision on the left");
				percentForce = (-1.0 * collisions) * CollisionsStrength / 100.0;
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				triggers->Rumble(0, percentForce, 150);
			}
		}
		else
		{
			helpers->log("resetting collision");
			triggers->Constant(constants->DIRECTION_FROM_LEFT, 0);
		}
	
		if (0 < tiresSlip)
		{
			helpers->log("tires slip left");
			bool highSpeedVibrations = (294 <= speed) && (1.0 * tiresSlip) < (LimitBetweenHighSpeedVibrationsAndTiresSlip / 1000.0);
			percentForce = (-1.0 * tiresSlip) * (highSpeedVibrations ? HighSpeedVibrationsStrength : TiresSlipStrength) / 100.0;
			triggers->Sine(100, 100, percentForce);
	
			if (!highSpeedVibrations && ((0 == JointsAndStripesStrength && 0 == CollisionsStrength) || (0.001 > collisions && -0.001 < collisions)))
			{
				triggers->Rumble(0, -1.0 * percentForce, 150);
			}
		}
		else if (0 > tiresSlip)
		{
			helpers->log("tires slip right");
			bool highSpeedVibrations = (294 <= speed) && (-1.0 * tiresSlip) < (LimitBetweenHighSpeedVibrationsAndTiresSlip / 1000.0);
			percentForce = (-1.0 * tiresSlip) * (highSpeedVibrations ? HighSpeedVibrationsStrength : TiresSlipStrength) / 100.0;
			triggers->Sine(100, 100, percentForce);
	
			if (!highSpeedVibrations && ((0 == JointsAndStripesStrength && 0 == CollisionsStrength) || (0.001 > collisions && -0.001 < collisions)))
			{
				triggers->Rumble(0, percentForce, 150);
			}
		}
	}

	
/* TODO
	INT_PTR ptr1 = helpers->ReadIntPtr(0x20681C0, true);	//Wg6Enma_Release_IDL0.dll+29B3E0
	UINT8 gear = helpers->ReadByte(ptr1 + 0x3AC, false);	//ptr1 + 0x3A8

	if (0 < WheelSpinStrength)
	{
		//INT_PTR ptr1 = myHelpers->ReadIntPtr(0x1948F10, true);
		//INT_PTR ptr2 = myHelpers->ReadIntPtr(ptr1 + 0x180 + 0xa8 + 0x18, false);
		//UINT8 power = myHelpers->ReadByte(ptr2 + 0x98, false);
		UINT8 power = 16;
		int rpm = helpers->ReadInt32(0x1F2629C, true);	//wmn6r.exe+1F2629C
		int diff = 0x0A <= power ? 0 : 20;

		if (
			1 == gear && 10 < speed && (
				((30 - diff) > speed && 3500 < rpm)
				|| ((55 - diff) > speed && 5500 < rpm)
				|| ((75 - diff) > speed && 7000 < rpm)
				|| ((100 - diff) > speed && 7800 < rpm)
				)
			)
		{
			percentForce = (((100.0 - speed) / 100.0) * ((rpm * 100.0 / 8500.0) / 100.0)) * WheelSpinStrength / 100.0;
			triggers->Sine(120, 120, percentForce);
			triggers->Rumble(0, percentForce, 150);

			msg = "tires spin: gear: " + std::to_string(gear) + " | speed: " + std::to_string(speed)
				+ " | rpm: " + std::to_string(rpm) + " | force: " + std::to_string(percentForce);
			helpers->log((char*)msg.c_str());
		}
		else if (
			2 == gear && 10 < speed && (
				((110 - (2 * diff)) > speed && 5000 < rpm)
				|| ((130 - (2 * diff)) > speed && 6000 < rpm)
				|| ((145 - (2 * diff)) > speed && 6500 < rpm)
				|| ((160 - (2 * diff)) > speed && 7000 < rpm)
				)
			)
		{
			percentForce = (((160.0 - speed) / 150.0) * ((rpm * 100.0 / 8500.0) / 100.0)) * WheelSpinStrength / 100.0;
			triggers->Sine(120, 120, percentForce);
			triggers->Rumble(0, percentForce, 150);

			msg = "tires spin: gear: " + std::to_string(gear) + " | speed: " + std::to_string(speed)
				+ " | rpm: " + std::to_string(rpm) + " | force: " + std::to_string(percentForce);
			helpers->log((char*)msg.c_str());
		}
	}

	if (0 < GearChangeStrength)
	{
		INT_PTR ptrtime = helpers->ReadIntPtr(0x20681D8, true);		//Wg6Enma_Release_IDL0.dll+29B3F8
		float time = helpers->ReadFloat32(ptrtime + 0x18, false);	//ptrtime + 0x18

		if (oldgear != gear && 0 < gear && 0 < time)
		{
			msg = "oldgear: " + std::to_string(oldgear) + " | gear: " + std::to_string(gear)
				+ " | time: " + std::to_string(time) + " | speed: " + std::to_string(speed);
			helpers->log((char*)msg.c_str());
		}

		if (oldgear != gear && 0 < gear && 0.5 < time && 0.1 <= speed)
		{
			SDL_CreateThread(GearChangeThread, "GearChangeThread", (void*)NULL);
		}
		oldgear = gear;
	}
*/
}