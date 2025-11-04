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
#include "Cars.h"
extern int EnableDamper;
extern int DamperStrength;
static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");

static int ffbEnabled = 0;
static bool init = false;

static EffectTriggers* myTriggers;
static EffectConstants* myConstants;

static void(__thiscall* testMenuFFB)(int param_1, float ffbAmt, char param_3);
static void __fastcall testMenuFFBHook(int param_1, float ffbAmt, char param_3) {
	if (ffbEnabled)
	{
		if (ffbAmt >= 0)
		{
			myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, ffbAmt);
		}
		else
		{
			myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, ffbAmt * -1);

		}
	}
	testMenuFFB(param_1, ffbAmt, param_3);
}

static void(__thiscall* gameFFB)(int param_1, float ffbAmt, char param_3);
static void __fastcall gameFFBHook(int param_1, float ffbAmt, char param_3) {
	if (ffbEnabled)
	{
		if (ffbAmt >= 0)
		{
			myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, ffbAmt);
		}
		else
		{
			myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, ffbAmt * -1);

		}
	}
	gameFFB(param_1, ffbAmt, param_3);
}


static void(__thiscall* enableRumbleEffectOrig)(int param_1_00, int rumbleEffect);
static void __fastcall enableRumbleEffect(int param_1_00, int rumbleEffect) {
	if (ffbEnabled)
	{
		if (rumbleEffect == 0)
		{
			//in the air
			myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, 0);
		}
		if (rumbleEffect > 0)
		{
			//rumbling after collision
			myTriggers->Rumble(0, 1, rumbleEffect);
			myTriggers->Sine(rumbleEffect, 0, 50);
		}
	}
	enableRumbleEffectOrig(param_1_00, rumbleEffect);
}


void Cars::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (!init) {

		myTriggers = triggers;
		myConstants = constants;

		MH_Initialize();
		MH_CreateHook((void*)(0x0451ba0), testMenuFFBHook, (void**)&testMenuFFB);
		MH_CreateHook((void*)(0x0821d40), gameFFBHook, (void**)&gameFFB);
		MH_CreateHook((void*)(0x00455550), enableRumbleEffect, (void**)&enableRumbleEffectOrig);

		MH_EnableHook(MH_ALL_HOOKS);
		init = true;
	}


	int ffbStatus = helpers->ReadByte(0x18d32a2, false);
	if (ffbStatus == 1 && !ffbEnabled)
	{
		ffbEnabled = true;
	}
	else if (ffbStatus == 0 && ffbEnabled)
	{
		ffbEnabled = false;
	}


}