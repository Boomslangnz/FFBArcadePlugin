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
#include "KODrive.h"
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
		UINT8 ff = myHelpers->ReadByte(0x00B261F6, /* isRelativeOffset */ false);
		UINT8 ff1 = myHelpers->ReadByte(0x00B261F5, /* isRelativeOffset */ false);
		wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
		int FFBMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBMode"), 0, settingsFilename);
		myHelpers->log("got value: ");
		std::string ffs = std::to_string(ff);
		myHelpers->log((char*)ffs.c_str());

		if ((ff == 10) & (ff1 == 30))
		{
			double percentForce = 0.4;
			double percentForce1 = 1.0;
			double percentLength = 100;
			myTriggers->Rumble(percentForce1, percentForce1, percentLength);
			myTriggers->Sine(80, 80, percentForce);
		}
		if (FFBMode == 1)
		{
			if ((ff > 0x66)& (ff < 0x80)& (ff1 == 0))
			{
				myHelpers->log("moving wheel right");
				double percentForce = (128 - ff) / 24.0;
				double percentLength = 100;
				myTriggers->Rumble(pow(percentForce, 0.5), 0, percentLength);
				myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ff > 0x00)& (ff < 0x19)& (ff1 == 1))
			{
				myHelpers->log("moving wheel left");
				double percentForce = (ff) / 24.0;
				double percentLength = 100;
				myTriggers->Rumble(0, pow(percentForce, 0.5), percentLength);
				myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
		}
		else
		{
			if ((ff > 0x66)& (ff < 0x80)& (ff1 == 0))
			{
				myHelpers->log("moving wheel right");
				double percentForce = (128 - ff) / 24.0;
				double percentLength = 100;
				myTriggers->Rumble(percentForce, 0, percentLength);
				myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ff > 0x00)& (ff < 0x19)& (ff1 == 1))
			{
				myHelpers->log("moving wheel left");
				double percentForce = (ff) / 24.0;
				double percentLength = 100;
				myTriggers->Rumble(0, percentForce, percentLength);
				myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}
	}
}

void KODrive::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers) {

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