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
#include "FordRacing.h"
#include "SDL.h"
static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;
static SDL_Event e;
static HANDLE hSection;
static LPVOID secData;
static int ffbOffset = 0;

static int TeknoParrotGame()
{
	hSection = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, 64, L"TeknoParrot_JvsState");
	secData = MapViewOfFile(hSection, FILE_MAP_ALL_ACCESS, 0, 0, 64);
	ffbOffset = *((int*)secData + 2);
	return 0;
}

static int GetTeknoParrotFFB()
{
	ffbOffset = *((int*)secData + 2);
	return ffbOffset;
}

static int RunningThread(void* ptr)
{
	int cnt;
	for (cnt = 0; cnt >= 0; ++cnt)
	{		
		int const ff = GetTeknoParrotFFB();
		myHelpers->log("in FR Ffbloop");
		std::string ffs = std::to_string(ff);
		myHelpers->log((char*)ffs.c_str());

		if (ff < -65505 && ff > -65515)
		{
			myHelpers->log("moving wheel left");
			double percentForce = (-65505 - ff) / 9.0;
			double percentLength = 100;
			myTriggers->Rumble(0, percentForce, percentLength);
			myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if (ff > 0 && ff < 16)
		{
			myHelpers->log("moving wheel right");
			double percentForce = (16 - ff) / 9.0;
			double percentLength = 100;
			myTriggers->Rumble(percentForce, 0, percentLength);
			myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
		}
	}
}

void FordRacing::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	myTriggers = triggers;
	myConstants = constants;
	myHelpers = helpers;

	TeknoParrotGame();

	SDL_Thread* thread;
	thread = SDL_CreateThread(RunningThread, "RunningThread", (void*)NULL);

	while (SDL_WaitEvent(&e) != 0)
	{
		myTriggers = triggers;
		myConstants = constants;
		myHelpers = helpers;
	}
}