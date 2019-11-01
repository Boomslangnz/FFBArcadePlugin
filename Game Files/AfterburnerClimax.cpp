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
#include "AfterburnerClimax.h"
#include "SDL.h"
static SDL_Event e;
static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int Rumble1Strength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Rumble1Strength"), 0, settingsFilename);
static int Rumble2Strength = GetPrivateProfileInt(TEXT("Settings"), TEXT("Rumble2Strength"), 0, settingsFilename);
static int Rumble1Length = GetPrivateProfileInt(TEXT("Settings"), TEXT("Rumble1Length"), 0, settingsFilename);
static int Rumble2Length = GetPrivateProfileInt(TEXT("Settings"), TEXT("Rumble2Length"), 0, settingsFilename);

static int RunningThread(void* ptr)
{
	int cnt;
	for (cnt = 0; cnt >= 0; ++cnt)
	{
		UINT8 ff = myHelpers->ReadByte(0x08347A5E, /* isRelativeOffset */ false);

		myHelpers->log("got value: ");
		std::string ffs = std::to_string(ff);
		myHelpers->log((char*)ffs.c_str());

		if (ff == 64)
		{
			double percentForce = ((Rumble1Strength) / 100.0);
			double percentLength = (Rumble1Length);
			myTriggers->Rumble(percentForce, percentForce, percentLength);
		}
		else if (ff == 80)
		{
			double percentForce = ((Rumble2Strength) / 100.0);
			double percentLength = (Rumble2Length);
			myTriggers->Rumble(percentForce, percentForce, percentLength);
		}
	}
	return 0;
}

void AfterburnerClimax::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

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