
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
#include "FnFDrift.h"


static bool init;
static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;
extern int EnableDamper;
extern int DamperStrength;

static int(__cdecl* FnFSendToLptOrig)(uint16_t addr, uint8_t FFB);
static int __cdecl FnFSendToLpt(uint16_t addr, uint8_t FFB)
{
	if (addr == 0x378)
	{
		bool isLeft = FFB < 0x80;
		float percentForce;
		if (isLeft) {

			percentForce = static_cast<float>(FFB) / 0x7F;
			myTriggers->Rumble(0, percentForce, 100.0);
			myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else {

			percentForce = static_cast<float>(FFB - 0x80) / 0x7F;
			myTriggers->Rumble(0, percentForce, 100.0);
			myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
		}
	}

	return 0;

}


static void(__cdecl* FnFIgnoreLPTOrig)();
static void __cdecl FnFignoreLPT() {
	return;
}

void FnFDrift::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {
	if (!init)
	{
		//enable IO calls
		myHelpers->WriteIntPtr(0x05a3ca4, 1, false);
		MH_Initialize();
		MH_CreateHook((LPVOID)0x048a410, FnFSendToLpt, (LPVOID*)&FnFSendToLptOrig);

		MH_CreateHook((LPVOID)0x048a760, FnFignoreLPT, (LPVOID*)&FnFIgnoreLPTOrig);
		MH_CreateHook((LPVOID)0x048a7b0, FnFignoreLPT, (LPVOID*)&FnFIgnoreLPTOrig);
		MH_CreateHook((LPVOID)0x048a8f0, FnFignoreLPT, (LPVOID*)&FnFIgnoreLPTOrig);
		MH_CreateHook((LPVOID)0x048aa20, FnFignoreLPT, (LPVOID*)&FnFIgnoreLPTOrig);
		MH_EnableHook(MH_ALL_HOOKS);
		init = true;
	}

	if (EnableDamper)
		triggers->Damper(DamperStrength / 100.0);

	myTriggers = triggers;
	myConstants = constants;
	myHelpers = helpers;
}