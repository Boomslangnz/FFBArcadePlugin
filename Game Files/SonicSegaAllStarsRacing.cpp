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
#include "SonicSegaAllStarsRacing.h"
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
		INT_PTR FFBEnable = myHelpers->ReadByte(0x5CD858, /* isRelativeOffset*/ true);
		INT_PTR FFB = myHelpers->ReadByte(0x5CD864, /* isRelativeOffset*/ true);

		{
			//Enable FFB
			myHelpers->WriteByte(0x5CD858, 0x03, true);
		}

		{
			//Trigger friction to stop any oscillation
			double percentForce = 0.2;
			myTriggers->Friction(percentForce);
		}

		if ((FFB > 0)& (FFB < 19))
		{
			myHelpers->log("moving wheel right");
			double percentForce = (FFB) / 18.0;
			double percentLength = 100;
			myTriggers->Rumble(0, percentForce, percentLength);
			myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((FFB > 237)& (FFB < 256))
		{
			myHelpers->log("moving wheel right");
			double percentForce = (256 - FFB) / 18.0;
			double percentLength = 100;
			myTriggers->Rumble(percentForce, 0, percentLength);
			myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
		}
	}
	return 0;
}

void SonicSegaAllStarsRacing::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

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
