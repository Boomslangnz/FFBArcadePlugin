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
#include "HummerExtreme.h"

static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;

extern int EnableDamper;
extern int DamperStrength;

bool init = false;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int ViosityStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("ViosityStrength"), 100, settingsFilename);
static int SpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("SpringStrength"), 100, settingsFilename);


static void(__cdecl* clSteerDualDeviceSetTRQCurveHalfPointOrig)(void* thisParam, int param_1, float param_2, float param_3);
static void __cdecl clSteerDualDeviceSetTRQCurveHalfPoint(void* thisParam, int param_1, float param_2, float param_3) {
	return clSteerDualDeviceSetTRQCurveHalfPointOrig(thisParam, param_1, param_2, param_3);
}

static void(__cdecl* clSteerDualDeviceSetVibrateOrig)(void* thisParam, int param_1, float param_2, float param_3);
static void __cdecl clSteerDualDeviceSetVibrate(void* thisParam, int param_1, float param_2, float param_3) {
	myTriggers->Sine(param_3 * 100, 1, param_2 * 60);
	myTriggers->Rumble(param_2 * 60,0,param_3 * 100);
	return clSteerDualDeviceSetVibrateOrig(thisParam, param_1, param_2, param_3);
}

static void(__cdecl* clSteerDualDeviceSetViscosityOrig)(void* thisParam, int param_1, float param_2, float param_3);
static void __cdecl clSteerDualDeviceSetViscosity(void* thisParam, int param_1, float param_2, float param_3) {
	double percentForce = (double)param_2 * (ViosityStrength / 100.0);
	myTriggers->Friction(percentForce);
	return clSteerDualDeviceSetViscosityOrig(thisParam, param_1, param_2, param_3);
}

static void(__cdecl* clSteerDualDeviceInitCenterOrig)(void* thisParam, int param_1, unsigned char param_2);
static void __cdecl clSteerDualDeviceInitCenter(void* thisParam, int param_1, unsigned char param_2) {
	double percentForce = (double)param_2 * (SpringStrength / 100.0);
	myTriggers->Springi(percentForce);
	return clSteerDualDeviceInitCenterOrig(thisParam, param_1, param_2);
}

static int(__cdecl* clSteerDualDeviceWaitOrig)(int param_1);
static int __cdecl clSteerDualDeviceWait(int param_1) {
	return 0;
}
void HummerExtreme::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (!init)
	{
		init = true;
		myTriggers = triggers;
		myConstants = constants;
		myHelpers = helpers;
		MH_Initialize();
		//checking wheel is cool for an update
		MH_CreateHook((LPVOID)0x80cffb4, clSteerDualDeviceWait, (LPVOID*)&clSteerDualDeviceWaitOrig);
		//Ingame effects
		MH_CreateHook((LPVOID)0x80d01aa, clSteerDualDeviceSetTRQCurveHalfPoint, (LPVOID*)&clSteerDualDeviceSetTRQCurveHalfPointOrig);
		MH_CreateHook((LPVOID)0x80d004a, clSteerDualDeviceSetVibrate, (LPVOID*)&clSteerDualDeviceSetVibrateOrig);
		MH_CreateHook((LPVOID)0x80d00fa, clSteerDualDeviceSetViscosity, (LPVOID*)&clSteerDualDeviceSetViscosityOrig);
		MH_CreateHook((LPVOID)0x80d0302, clSteerDualDeviceInitCenter, (LPVOID*)&clSteerDualDeviceInitCenterOrig);
		MH_EnableHook(MH_ALL_HOOKS);
	}
}
