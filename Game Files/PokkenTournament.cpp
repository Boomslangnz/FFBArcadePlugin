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
#include "PokkenTournament.h"
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
		INT_PTR ffAddress = myHelpers->ReadIntPtr(0x00E97F10, /* isRelativeOffset*/ true);
		INT_PTR ff1 = myHelpers->ReadIntPtr(ffAddress + 0x60, /* isRelativeOffset */ false);
		INT_PTR ff2 = myHelpers->ReadIntPtr(ff1 + 0x8, /* isRelativeOffset */ false);
		float ff3 = myHelpers->ReadFloat32(ff2 + 0xCC, /* isRelativeOffset */ false); //health
		INT_PTR ffAddress4 = myHelpers->ReadIntPtr(0x00EC4C20, /* isRelativeOffset*/ true);
		INT_PTR ff5 = myHelpers->ReadIntPtr(ffAddress4 + 0x60, /* isRelativeOffset */ false);
		INT_PTR ff6 = myHelpers->ReadIntPtr(ff5 + 0x120, /* isRelativeOffset */ false);
		INT_PTR ff7 = myHelpers->ReadIntPtr(ff6 + 0x698, /* isRelativeOffset */ false); //1 during battle except for first startup

		wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
		int RumbleStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrength"), 0, settingsFilename);
		int RumbleLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleLength"), 0, settingsFilename);
		int HowtoRumble = GetPrivateProfileInt(TEXT("Settings"), TEXT("HowtoRumble"), 0, settingsFilename);

		float static oldFloat = 0.0;
		float newFloat = ff3;

		myHelpers->log("got value: ");
		std::string ffs = std::to_string(ff3);
		myHelpers->log((char*)ffs.c_str());


		if ((oldFloat != newFloat))
		{
			if (HowtoRumble == 0)
			{
				double percentForce = ((RumbleStrength) / 100.0);
				double percentLength = (RumbleLength);
				myTriggers->Rumble(percentForce, percentForce, percentLength);
			}
			else if (HowtoRumble == 1)
			{
				double percentForce = ((RumbleStrength) / 100.0);
				double percentLength = (RumbleLength);
				myTriggers->Rumble(0, percentForce, percentLength);
			}
			else if (HowtoRumble == 2)
			{
				double percentForce = ((RumbleStrength) / 100.0);
				double percentLength = (RumbleLength);
				myTriggers->Rumble(percentForce, 0, percentLength);
			}
		}
		oldFloat = newFloat;
	}
	return 0;
}

void PokkenTournament::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

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