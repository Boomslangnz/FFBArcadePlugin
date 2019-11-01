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
#include "MarioKartGPDX.h"
#include "SDL.h"
static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;
static SDL_Event e;

static int RunningThread(void* ptr)
{
	int cnt;
	for (cnt = 0; cnt >= 0; ++cnt)
	{
		int ff1 = myHelpers->ReadInt32(0x564C5F, /* isRelativeOffset */ true); //shake
		int ff2 = myHelpers->ReadInt32(0x559B68,/* isRelativeOffset */ true);
		int ff3 = myHelpers->ReadInt32(ff2 + 0x5F8, /* isRelativeOffset */ false); // terrain data
		int ff4 = myHelpers->ReadInt32(0x563860, /* isRelativeOffset */ true); //0-255 accl
		int ff5 = myHelpers->ReadInt32(ff2 + 0x628, /* isRelativeOffset */ false); //kart flying or on ground
		int ff6 = myHelpers->ReadInt32(0x5532C4,/* isRelativeOffset */ true);
		int ff7 = myHelpers->ReadInt32(ff6 + 0x1F0, /* isRelativeOffset */ false);
		int ff8 = myHelpers->ReadInt32(ff7 + 0x18, /* isRelativeOffset */ false);
		int ff9 = myHelpers->ReadInt32(ff8 + 0x7C, /* isRelativeOffset */ false);
		int ff10 = myHelpers->ReadInt32(ff9 + 0x164, /* isRelativeOffset */ false); // 1 during race only
		int ff11 = myHelpers->ReadInt32(ff2 + 0x520, /* isRelativeOffset */ false); //1065353216 when kart moves
		myHelpers->log("got value: ");
		std::string ffs = std::to_string(ff1);
		myHelpers->log((char*)ffs.c_str()); myHelpers->log("got value: ");


		// Large Shake when hitting walls, other karts or getting hit by items
		if ((4194308 == ff1) & (ff10 == 1))

		{
			double percentForce = 1.0;
			double percentForce1 = 3.5;
			double percentLength = (500);
			myTriggers->Rumble(percentForce1, percentForce1, percentLength);
			myTriggers->Sine(200, 200, percentForce);
		}

		// small friction when driving on dirt while moving
		else  if ((3 == ff3) & (ff10 == 1) & (ff5 == 1) & (ff11 == 1065353216))
		{
			double percentForce = (0.3);
			double percentLength = (100);
			myTriggers->Rumble(percentForce, 0, percentLength);
			myTriggers->Friction(percentForce);
		}
		//	Small constant when hitting bumps
		else  if ((10 == ff3) & (ff10 == 1) & (ff5 == 1) & (ff11 == 1065353216))
		{
			double percentForce = (0.2);
			double percentLength = (50);
			double percentForce1 = 3.0;
			myTriggers->Rumble(percentForce1, percentForce1, percentLength);
			myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
		}
		// Wheel rumbles while driving on grass
		else if ((4 == ff3) & (ff10 == 1) & (ff5 == 1) & (ff11 == 1065353216))

		{
			double percentForce = 0.2;
			double percentLength = (50);
			myTriggers->Rumble(0, percentForce, percentLength);
			myTriggers->Sine(50, 50, percentForce);
		}
		//wheel hard to turn while driving through water
		else  if ((7 == ff3) & (ff10 == 1) & (ff5 == 1) & (ff11 == 1065353216))
		{
			double percentForce = (0.65);
			myTriggers->Friction(percentForce);
		}
		//Wheel rumbles lightly when driving over tiles
		else if ((12 == ff3) & (ff10 == 1) & (ff5 == 1) & (ff11 == 1065353216))

		{
			double percentForce = 0.1;
			double percentForce1 = 0.2;
			double percentLength = (150);
			myTriggers->Rumble(percentForce1, 0, percentLength);
			myTriggers->Sine(70, 70, percentForce);
		}
		//Wheel rumbles lightly when driving over sand
		else if ((14 == ff3) & (ff10 == 1) & (ff5 == 1) & (ff11 == 1065353216))

		{
			double percentForce = 0.1;
			double percentForce1 = 0.2;
			double percentLength = (50);
			myTriggers->Rumble(percentForce1, 0, percentLength);
			myTriggers->Sine(70, 70, percentForce);
		}
		//Wheel rumbles lightly when driving over rough part of track
		else if ((11 == ff3) & (ff10 == 1) & (ff5 == 1) & (ff11 == 1065353216))

		{
			double percentForce = 0.1;
			double percentForce1 = 0.2;
			double percentLength = (250);
			myTriggers->Rumble(0, percentForce1, percentLength);
			myTriggers->Sine(40, 50, percentForce);
		}
		//Wheel rumbles moderately when driving over wooden bridges
		else if ((8 == ff3) & (ff10 == 1) & (ff5 == 1) & (ff11 == 1065353216))

		{
			double percentForce = 0.4;
			double percentLength = (100);
			myTriggers->Rumble(percentForce, percentForce, percentLength);
			myTriggers->Sine(120, 120, percentForce);
		}
	}
	return 0;
}

void MarioKartGPDX100::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	myTriggers = triggers;
	myConstants = constants;
	myHelpers = helpers;

	SDL_Thread* thread;
	thread = SDL_CreateThread(RunningThread, "RunningThread", (void*)NULL);

	while (SDL_WaitEvent(&e) != 0)
	{
		myTriggers = triggers;
		myConstants = constants;
		myHelpers = helpers;
	}	
}