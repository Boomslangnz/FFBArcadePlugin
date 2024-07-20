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

#include "WasteLandRacers2071.h"
#include <string>
#include <sstream>
#include "SDL.h"

static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;

extern int EnableDamper;
extern int DamperStrength;

static bool init;
static double ffb = 1;

static int(__cdecl* SetForceOrig)(int param_1, int param_2, int param_3, int param_4);
static int __cdecl SetForce(int param_1, int param_2, int param_3, int param_4) {

	ffb = (double)param_1 / 32768.0;

	return 0;
}

static int(__cdecl* SetSteeringPosOrig)(int param_1, int param_2, int param_3, int param_4);
static int __cdecl SetSteeringPos(int param_1, int param_2, int param_3, int param_4) {

	double wheelPos = (double)param_1 / 128000.0;

	if (wheelPos >= 0) {
		myTriggers->Rumble(0, param_1, 100.0);
		myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, wheelPos);
	}
	else if (wheelPos <= 0) {
		myTriggers->Rumble(0, param_1 * -1, 100.0);
		myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, wheelPos * -1);
	}
	return 0;
}

static int(__cdecl* SetDigitalOutOrig)(int param_1, int param_2, int param_3, int param_4);
static int __cdecl SetDigitalOut(int param_1, int param_2, int param_3, int param_4) {
	return 0;
}

void WasteLandRacers2071::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	//check a DLL has been loaded
	if (GetModuleHandleA("sdc2.dll") != NULL && !init) {
		init = true;
		MH_Initialize();
		MH_CreateHookApi(L"sdc2.dll", "SetForce", SetForce, (void**)&SetForceOrig);
		MH_CreateHookApi(L"sdc2.dll", "SetSteeringPos", SetSteeringPos, (void**)&SetSteeringPosOrig);
		MH_CreateHookApi(L"sdc2.dll", "SetDigitalOut", SetDigitalOut, (void**)&SetDigitalOutOrig);
		MH_EnableHook(MH_ALL_HOOKS);
	}

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	triggers->Spring(ffb);

	myTriggers = triggers;
	myConstants = constants;
	myHelpers = helpers;
}