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
#include "WackyRaces.h"
#include "SDL.h"
static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;
static SDL_Event e;

int ttx2wr(int ffRaw) {
	switch (ffRaw) {
		// moving left, from weakest to strongest (30 => 16).
	case 4096:
		return 30;
	case 64:
		return 29;
	case 4160:
		return 28;
	case 2048:
		return 27;
	case 6144:
		return 26;
	case 2112:
		return 25;
	case 6208:
		return 24;
	case 32:
		return 23;
	case 4128:
		return 22;
	case 96:
		return 21;
	case 4192:
		return 20;
	case 2080:
		return 19;
	case 6176:
		return 18;
	case 2144:
		return 17;
	case 6240:
		return 16;
		// moving right, from weakest to strongest (15 => 1)
	case 12288:
		return 15;
	case 8256:
		return 14;
	case 12352:
		return 13;
	case 10240:
		return 12;
	case 14336:
		return 11;
	case 10304:
		return 10;
	case 14400:
		return 9;
	case 8224:
		return 8;
	case 12320:
		return 7;
	case 8288:
		return 6;
	case 12384:
		return 5;
	case 10272:
		return 4;
	case 14368:
		return 3;
	case 10336:
		return 2;
	case 14432:
		return 1;
	default:
		return 0;
	}
}

static int RunningThread(void* ptr)
{
	int cnt;
	for (cnt = 0; cnt >= 0; ++cnt)
	{
		int ff = 0;

		{
			long ffAddress = myHelpers->ReadInt32(0x7E00590, /* isRelativeOffset*/ true);
			int ffRaw = myHelpers->ReadInt32(ffAddress + 0x45, /* isRelativeOffset */ false);
			int lampArray[7] = { 16, 1024, 512, 128, 8, 256, 16384 };
			for (int i = 0; i < 7; i++) {
				if ((ffRaw & lampArray[i]) == lampArray[i]) {
					ffRaw -= lampArray[i];
				}
			};
			ff = ttx2wr(ffRaw);
		}

		if (ff > 15)
		{
			myHelpers->log("moving wheel left");
			double percentForce = (31 - ff) / 15.0;
			double percentLength = 100;
			myTriggers->Rumble(0, percentForce, percentLength);
			myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if (ff > 0)
		{
			myHelpers->log("moving wheel right");
			double percentForce = (16 - ff) / 15.0;
			double percentLength = 100;
			myTriggers->Rumble(percentForce, 0, percentLength);
			myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
		}
	}
	return 0;
}

void WackyRaces::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

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