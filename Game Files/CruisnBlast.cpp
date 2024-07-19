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

#include "CruisnBlast.h"
#include <sstream>
static bool init;

static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;
extern int EnableDamper;
extern int DamperStrength;

static float lastFF = 0;
static int currentScreen = 0;

static int(__cdecl* Wheel_SetHookOrig)(float param_1);
static int __cdecl Wheel_SetHook(float param_1)
{
	float puVar1 = myHelpers->ReadFloat32(0x8babbac, false); //menus ffb?! CHECKED COOL
	float puVar2 = myHelpers->ReadByte(0x8babba8, false); //in game ffb?! //CHECKED seems to just go 0 when off the road
	//int puVar3 = myHelpers->ReadFloat32(0x8babbb0, false); //ffb effects FLOAT??
	//int puVar4 = myHelpers->ReadFloat32(0x8babbb4, false);
	//int puVar5 = myHelpers->ReadFloat32(0x8babbbc, false); //ffb effects
	//int puVar6 = myHelpers->ReadFloat32(0x8babbb8, false); //ffb effects are running (1 at the start i think)
	int puVar7 = myHelpers->ReadInt32(0x8babbc0, false); //0 menus, 1 game

	if (puVar7 == 1)
	{
		if (currentScreen == 0)
		{
			//in game - turn on wheel effects
			myHelpers->WriteByte(0x9c28504, 1, false);
			currentScreen = 1;
			lastFF = 0;
		}
		else
		{
			lastFF = param_1;
		}
	}
	else
	{
		if (currentScreen == 1)
		{
			//not in game turn off wheel effects
			myHelpers->WriteByte(0x9c28504, 0, false);
			lastFF = 0;
			currentScreen = 0;
		}
		else
		{
			lastFF = puVar1;
		}
	}
	if (lastFF >= 0) {
		myTriggers->Rumble(0, lastFF, 100.0);
		myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, lastFF);
	}
	if (lastFF <= 0) {
		myTriggers->Rumble(0, lastFF * -1, 100.0);
		myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, lastFF * -1);
	}
	return 0;
}


void CruisnBlast::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {
	if (!init)
	{
		DWORD ImageBase = (DWORD)GetModuleHandleA(0);

		if (EnableDamper)
			triggers->Damper(DamperStrength / 100.0);

		myHelpers = helpers;
		myTriggers = triggers;
		myConstants = constants;

		//set cab type
		myHelpers->WriteByte(0xa0a7808, 4, false);
		//enable wheel found
		//myHelpers->WriteByte(0x8bab744, 1, false);
		
		MH_Initialize();
		MH_CreateHook((LPVOID)(0x8151b50), Wheel_SetHook, (LPVOID*)&Wheel_SetHookOrig);
		//remove wheel check for WHEEL_SET function
		myHelpers->WriteNop(0x8151b61, 2, false);
		//remove outs for WHEEL_SET function just incase we get there
		myHelpers->WriteNop(0x8151b90, 1, false);
		myHelpers->WriteNop(0x8151b96, 1, false);
		myHelpers->WriteNop(0x8151b9c, 1, false);
		myHelpers->WriteNop(0x8151b87, 1, false);

		MH_EnableHook(MH_ALL_HOOKS);
		init = true;
	}



}