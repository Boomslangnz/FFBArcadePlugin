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
#include <thread>
#include "WMMT5.h"
#include "SDL.h"

void WMMT5::InputThread()
{
	if (1 != EnableForceFinish && 1 != EnableForceTimeUp)
	{
		return;
	}

	helpers->log("starting input thread");
	SDL_Event e;
	while (SDL_WaitEvent(&e) != 0)
	{
		if (e.type == SDL_JOYBUTTONDOWN)
		{
			helpers->log("button pressed");
			if (1 == EnableForceFinish && e.jbutton.button == ForceFinishButton)
			{
				INT_PTR ptr1 = helpers->ReadIntPtr(0x199A468, true);
				helpers->WriteByte(ptr1 + 0x28, 8, false);
			}
			else if (1 == EnableForceTimeUp && e.jbutton.button == ForceTimeUpButton)
			{
				int tempDisableRaceTimer = DisableRaceTimer;
				DisableRaceTimer = 0;
				helpers->WriteFloat32(0x199AE18, 0, true);
				if (1 == tempDisableRaceTimer)
				{
					Sleep(10000);
					DisableRaceTimer = tempDisableRaceTimer;
				}
			}
		}
	}
	helpers->log("input thread stopped");
}

void WMMT5::SpamThread()
{
	if (1 != ForceFullTune && 1 != DisableRaceTimer)
	{
		return;
	}

	Sleep(5000); // To avoid crashes
	helpers->log("starting spam thread");
	while (1)
	{
		if (1 == ForceFullTune)
		{
			INT_PTR ptr1 = helpers->ReadIntPtr(0x1948F10, true);
			INT_PTR ptr2 = helpers->ReadIntPtr(ptr1 + 0x180 + 0xa8 + 0x18, false);
			UINT8 car = helpers->ReadByte(ptr2 + 0x2C, false);
			std::string msg = "car: " + std::to_string(car);
			helpers->log((char*)msg.c_str());

			if (0x00 < car)
			{
				UINT8 power = helpers->ReadByte(ptr2 + 0x98, false);
				UINT8 handling = helpers->ReadByte(ptr2 + 0x9C, false);
				msg = "power: " + std::to_string(power) + " | handling: " + std::to_string(handling);
				helpers->log((char*)msg.c_str());

				if (0x20 != (power + handling))
				{
					helpers->log("forcing full tune");
					helpers->WriteByte(ptr2 + 0x98, 0x10, false);
					helpers->WriteByte(ptr2 + 0x9C, 0x10, false);
				}
			}
		}

		if (1 == DisableRaceTimer)
		{
			helpers->WriteFloat32(0x199AE18, 999.99, true);
		}

		Sleep(500); // We don't need to spam too much
	}
	helpers->log("spam thread stopped");
}

void WMMT5::Loop()
{
	float spring = helpers->ReadFloat32(0x196F18C, true);
	float friction = helpers->ReadFloat32(0x196F190, true);
	float collisions = helpers->ReadFloat32(0x196F194, true);
	float tiresSlip = helpers->ReadFloat32(0x196F188, true);
	int speed = helpers->ReadInt32(0x196FEBC, true);
	std::string msg = "spring: " + std::to_string(spring) + " | friction: " + std::to_string(friction)
		+ " | collisions: " + std::to_string(collisions) + " | tires slip: " + std::to_string(tiresSlip)
		+ " | speed: " + std::to_string(speed);
	helpers->log((char*)msg.c_str());

	double percentForce;
	if (0.001 > spring && !gameFfbStarted)
	{
		helpers->log("fake spring+friction until game's FFB starts");
		percentForce = 0.3 * SpringStrength / 100.0;
		triggers->Spring(percentForce);
		percentForce = 0.5 * FrictionStrength / 100.0;
		triggers->Friction(percentForce);
	}
	else
	{
		if (!gameFfbStarted)
		{
			helpers->log("game's FFB started");
			gameFfbStarted = true;
		}
		percentForce = (1.0 * spring) * SpringStrength / 100.0;
		triggers->Spring(percentForce);
		percentForce = (1.0 * friction) * FrictionStrength / 100.0;
		triggers->Friction(percentForce);
	}

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

	INT_PTR ptr1 = helpers->ReadIntPtr(0x199A450, true);
	UINT8 gear = helpers->ReadByte(ptr1 + 0x398, false);

	if (0 < WheelSpinStrength)
	{
		INT_PTR ptr1 = helpers->ReadIntPtr(0x1948F10, true);
		INT_PTR ptr2 = helpers->ReadIntPtr(ptr1 + 0x180 + 0xa8 + 0x18, false);
		UINT8 power = helpers->ReadByte(ptr2 + 0x98, false);
		int rpm = helpers->ReadInt32(0x1970038, true);
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
		ptr1 = helpers->ReadIntPtr(0x199A468, true);
		float time = helpers->ReadFloat32(ptr1 + 0x18, false);

		if (oldgear != gear && 0 < gear && 0 < time)
		{
			msg = "oldgear: " + std::to_string(oldgear) + " | gear: " + std::to_string(gear)
				+ " | time: " + std::to_string(time) + " | speed: " + std::to_string(speed);
			helpers->log((char*)msg.c_str());
		}

		if (oldgear != gear && 0 < gear && 0.5 < time && 0.1 <= speed)
		{
			std::thread GearChangeThread(&WMMT5::GearChangeThread, this);
			GearChangeThread.detach();
		}
		oldgear = gear;
	}
}
