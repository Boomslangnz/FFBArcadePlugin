
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

#include "FnFSuperCars.h"

static bool init;
static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;
extern int EnableDamper;
extern int DamperStrength;

static void(__cdecl* FUN_00402cf0Orig)(float param_1);
static void __cdecl FUN_00402cf0(float param_1) {


	if (param_1 >= 0) {
		
		myTriggers->Rumble(0, param_1, 100.0);
		myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, param_1 );
	}
	 if (param_1 <= 0) {
		myTriggers->Rumble(0, param_1 * -1, 100.0);
		myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, param_1 * -1);
	}
	return;
}



static void(__cdecl* FnFSCIgnoreLPTOrig)();
static void __cdecl FnFSCignoreLPT() {
	return ;
}

void FnFSuperCars::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {
	if (!init)
	{
		OutputDebugStringA("FnFSuperCars::FFBLoop");


		MH_Initialize();
		MH_CreateHook((LPVOID)0x0402cf0, FUN_00402cf0, (LPVOID*)&FUN_00402cf0Orig);

		//remove unwanted instances
		MH_CreateHook((LPVOID)0x0402ca0, FnFSCignoreLPT, (LPVOID*)&FnFSCIgnoreLPTOrig);
		MH_CreateHook((LPVOID)0x0402c50, FnFSCignoreLPT, (LPVOID*)&FnFSCIgnoreLPTOrig);
		MH_CreateHook((LPVOID)0x0402bc0, FnFSCignoreLPT, (LPVOID*)&FnFSCIgnoreLPTOrig);	
		MH_EnableHook(MH_ALL_HOOKS);

		init = true;
	}

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	myTriggers = triggers;
	myConstants = constants;
	myHelpers = helpers;

}