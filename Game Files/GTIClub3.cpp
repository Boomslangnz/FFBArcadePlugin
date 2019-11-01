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
#include "GTIClub3.h"
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
		UINT8 ff = myHelpers->ReadByte(0x00918CBC, /* isRelativeOffset */ false);
		UINT8 ff1 = myHelpers->ReadByte(0x00918CBD, /* isRelativeOffset */ false);
		UINT8 ff2 = myHelpers->ReadByte(0x00918CBE, /* isRelativeOffset */ false);
		UINT8 menu = myHelpers->ReadByte(0x518E8E, /* isRelativeOffset */ true);
		myHelpers->log("got value: ");
		std::string ffs = std::to_string(ff2);
		myHelpers->log((char*)ffs.c_str());

		if (FFBMode == 0)
		{
			if ((ff1 > 0x00)& (ff1 < 0x40)& (menu == 0))
			{
				double percentForce = (ff1) / 63.0;
				double percentLength = 100;
				myTriggers->Rumble(percentForce, percentForce, percentLength);
				myTriggers->Sine(120, 120, percentForce);
			}
			if ((ff > 0x80)& (ff < 0x101)& (menu == 0))
			{
				myHelpers->log("moving wheel right");
				double percentForce = (257 - ff) / 128.0;
				double percentLength = 100;
				myTriggers->Rumble(percentForce, 0, percentLength);
				myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
			}
			else if ((ff > 0x00)& (ff < 0x80)& (menu == 0))
			{
				myHelpers->log("moving wheel left");
				double percentForce = (ff) / 127.0;
				double percentLength = 100;
				myTriggers->Rumble(0, percentForce, percentLength);
				myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
			}
		}
		else
		{
			if ((ff1 > 0x00)& (ff1 < 0x40)& (menu == 0))
			{
				double percentForce = (ff1) / 63.0;
				double percentLength = 100;
				myTriggers->Rumble(pow(percentForce, 0.5), pow(percentForce, 0.5), percentLength);
				myTriggers->Sine(120, 120, pow(percentForce, 0.5));
			}
			if ((ff > 0x80)& (ff < 0x101)& (menu == 0))
			{
				myHelpers->log("moving wheel right");
				double percentForce = (257 - ff) / 128.0;
				double percentLength = 100;
				myTriggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x00)& (ff < 0x80)& (menu == 0))
			{
				myHelpers->log("moving wheel left");
				double percentForce = (ff) / 127.0;
				double percentLength = 100;
				myTriggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
		}
	}
}

void GTIClub3::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers) {

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