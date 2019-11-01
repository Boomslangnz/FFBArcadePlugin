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
#include "InitialD4.h"
#include "math.h"
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
		wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
		int FFBMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBMode"), 0, settingsFilename);
		UINT8 ff = myHelpers->ReadByte(0x089AE89A, /* isRelativeOffset */ false);
		UINT8 ff1 = myHelpers->ReadByte(0x089AE899, /* isRelativeOffset */ false);
		UINT8 ff2 = myHelpers->ReadByte(0x089AE898, /* isRelativeOffset */ false);
		myHelpers->log("got value: ");
		std::string ffs = std::to_string(ff);
		myHelpers->log((char*)ffs.c_str());

		if (ff2 == 0x86)
		{
			myTriggers->Spring(0.8);
		}
		if (ff2 == 0x85) //cars colliding or rubbing against wall etc
		{
			if (ff1 > 0)
			{
				double percentLength = 200;
				double percentForce = (0.6);
				myTriggers->Friction(percentForce);
				myTriggers->Rumble(percentForce, percentForce, percentLength);
			}
		}
		if (FFBMode == 1)
		{
			if (ff2 == 0x84)
			{
				if ((ff > 0x37) && (ff < 0x80) && (ff1 == 0))
				{
					myHelpers->log("moving wheel right");
					double percentForce = (128 - ff) / 72.0;
					double percentLength = 100;
					double powforce = (ff - 55) / 72.0;
					myTriggers->Rumble(pow(percentForce, powforce), 0, percentLength);
					myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, (pow(percentForce, powforce)));
				}
				else if ((ff > 0x00) && (ff < 0x49) && (ff1 == 1))
				{
					myHelpers->log("moving wheel left");
					double percentForce = (ff) / 72.0;
					double percentLength = 100;
					double powforce = (73 - ff) / 72.0;
					myTriggers->Rumble(0, pow(percentForce, powforce), percentLength);
					myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, (pow(percentForce, powforce)));
				}
			}
		}
		else
		{
			if (ff2 == 0x84)
			{
				if ((ff > 0x37) && (ff < 0x80) && (ff1 == 0))
				{
					myHelpers->log("moving wheel right");
					double percentForce = (128 - ff) / 72.0;
					double percentLength = 100;
					myTriggers->Rumble(percentForce, 0, percentLength);
					myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((ff > 0x00) && (ff < 0x49) && (ff1 == 1))
				{
					myHelpers->log("moving wheel left");
					double percentForce = (ff) / 72.0;
					double percentLength = 100;
					myTriggers->Rumble(0, percentForce, percentLength);
					myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
				}
			}
		}
	}
}

void InitialD4::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers){

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