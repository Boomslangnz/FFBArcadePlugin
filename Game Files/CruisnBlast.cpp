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
#include "CruisnBlast.h"
#include <iostream>s
#include <sstream>
static bool init;

static EffectTriggers* myTriggers;
static EffectConstants* myConstants;
static Helpers* myHelpers;
extern int EnableDamper;
extern int DamperStrength;

static float lastFF;
static int(__fastcall* Wheel_SetHookOrig)(DWORD thisPtr, DWORD *edx);
static int __fastcall Wheel_SetHook(DWORD thisPtr, DWORD *edx)
{
	//OutputDebugStringA("Wheel_SetHook"); 

	float stackValue;
	__asm {
		mov eax, [esp + 4]
		mov stackValue, eax
	}

		//std::stringstream ss;
		//ss << "Wheel_SetHook: " << stackValue;
		//OutputDebugStringA(ss.str().c_str());
	
		std::stringstream ss;
		ss << "Wheel_SetHook: " << thisPtr;
		OutputDebugStringA(ss.str().c_str());

		//float ff = myHelpers->ReadFloat32(*edx, true);
		//output the ff value
		//std::stringstream ss2;
		//ss2 <<  ff;
		//OutputDebugStringA(ss2.str().c_str());

	//output thisPtr
	//std::stringstream ss2;
	//ss2 << "thisPtr: " << thisPtr;
	//OutputDebugStringA(ss2.str().c_str());

	//output edx
	//std::stringstream ss3;
	//ss3 << "edx: " << edx;
	//OutputDebugStringA(ss3.str().c_str());


	return Wheel_SetHookOrig(thisPtr, edx);
}

static int(__fastcall* GameWheel_initOrig)();
static int __fastcall GameWheel_init()
{
	//OutputDebugStringA("GameWheel_init");
	return GameWheel_initOrig();
}

static int(__fastcall* Wheel_InitOrig)();
static int __fastcall Wheel_Init()
{
	OutputDebugStringA("Wheel_Init");
	myHelpers->WriteByte(0x8bab744, 1, false);
	return 1;
}

static int(__fastcall* Game_diaginitOrig)();
static int __fastcall Game_diaginit()
{
	OutputDebugStringA("Game_diaginit");
	return Game_diaginitOrig();
}

static int(__stdcall* Game_adjInitORig)();
static int __stdcall Game_adjInit()
{
	OutputDebugStringA("Game_adjInit");

	//set wheel command line i think
	myHelpers->WriteIntPtr(0x8bdd9e8, 1, false);
	//write assembly here to jmp to a function
	_asm {
		mov eax, 0x8192960
		jmp eax
	}
	

	return 1;
}

static int(__fastcall* DefaultCommandLineArgsOrig)();
static int __fastcall DefaultCommandLineArgs()
{
	OutputDebugStringA("DefaultCommandLineArgs");
	myHelpers->WriteIntPtr(0x8bdd9e8, 1, false);
	return DefaultCommandLineArgsOrig();
}
static int(__fastcall* PlayerDataTblInitOrig)();
static int __fastcall PlayerDataTblInit()
{
	OutputDebugStringA("PlayerDataTblInit");
	return PlayerDataTblInitOrig();
}

static int(__fastcall* GameInitDongleOrig)();
static int __fastcall GameInitDongle()
{
	OutputDebugStringA("GameInitDongle");
	myHelpers->WriteIntPtr(0x8bdd9e8, 1, false);
	return GameInitDongleOrig();
}

//void FUN_08136610(void)
static int(__fastcall* FUN_08136610Orig)();
static int __fastcall FUN_08136610()
{
	OutputDebugStringA("FUN_08136610");
	myHelpers->WriteIntPtr(0x8bdd9e8, 1, false);
	return FUN_08136610Orig();
}
void CruisnBlast::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {
	if (!init)
	{


		DWORD ImageBase = (DWORD)GetModuleHandleA(0);


		myHelpers->WriteNop(0x8151a02, 1, false);
		myHelpers->WriteNop(0x8151a02, 1, false);
		myHelpers->WriteNop(0x8151a0d, 1, false);
		myHelpers->WriteNop(0x8151a15, 1, false);
		myHelpers->WriteNop(0x8151a1d, 1, false);
		myHelpers->WriteNop(0x8151a22, 1, false);
		myHelpers->WriteNop(0x8151a2a, 1, false);
		myHelpers->WriteNop(0x8151a32, 1, false);
		myHelpers->WriteNop(0x8151a3a, 1, false);

		myHelpers->WriteNop(0x8151aa7, 1, false);
		myHelpers->WriteNop(0x8151ab0, 1, false);
		myHelpers->WriteNop(0x8151ab6, 1, false);
		myHelpers->WriteNop(0x8151abc, 1, false);

		myHelpers->WriteNop(0x8151ad7, 1, false);
		myHelpers->WriteNop(0x8151ae0, 1, false);
		myHelpers->WriteNop(0x8151ae6, 1, false);
		myHelpers->WriteNop(0x8151aec, 1, false);

		myHelpers->WriteNop(0x8151b07, 1, false);
		myHelpers->WriteNop(0x8151b12, 1, false);
		myHelpers->WriteNop(0x8151b1a, 1, false);
		myHelpers->WriteNop(0x8151b22, 1, false);
		myHelpers->WriteNop(0x8151b2a, 1, false);
		myHelpers->WriteNop(0x8151b32, 1, false);
		myHelpers->WriteNop(0x8151b3a, 1, false);
		myHelpers->WriteNop(0x8151b42, 1, false);

		myHelpers->WriteNop(0x8151b87, 1, false);
		myHelpers->WriteNop(0x8151b90, 1, false);
		myHelpers->WriteNop(0x8151b96, 1, false);
		myHelpers->WriteNop(0x8151b9c, 1, false);

		myHelpers->WriteNop(0x8151c1a, 1, false);
		myHelpers->WriteNop(0x8151c25, 1, false);
		myHelpers->WriteNop(0x8151c2d, 1, false);
		myHelpers->WriteNop(0x8151c35, 1, false);
		myHelpers->WriteNop(0x8151c3d, 1, false);
		myHelpers->WriteNop(0x8151c45, 1, false);
		myHelpers->WriteNop(0x8151c4d, 1, false);
		myHelpers->WriteNop(0x8151c55, 1, false);
		myHelpers->WriteNop(0x8151c5d, 1, false);
		myHelpers->WriteNop(0x8151c65, 1, false);
		myHelpers->WriteNop(0x8151c6d, 1, false);
		myHelpers->WriteNop(0x8151c75, 1, false);

		myHelpers->WriteNop(0x8151c97, 1, false);
		myHelpers->WriteNop(0x8151ca0, 1, false);
		myHelpers->WriteNop(0x8151ca6, 1, false);
		myHelpers->WriteNop(0x8151cac, 1, false);

		myHelpers->WriteNop(0x8151cca, 1, false);
		myHelpers->WriteNop(0x8151cd5, 1, false);
		myHelpers->WriteNop(0x8151cdd, 1, false);
		myHelpers->WriteNop(0x8151ce5, 1, false);
		myHelpers->WriteNop(0x8151ced, 1, false);
		myHelpers->WriteNop(0x8151cf5, 1, false);
		myHelpers->WriteNop(0x8151cfd, 1, false);
		myHelpers->WriteNop(0x8151d05, 1, false);

		myHelpers->WriteNop(0x8151d25, 1, false);

		myHelpers->WriteNop(0x8151d4b, 1, false);

		myHelpers->WriteNop(0x8151d6f, 1, false);

		//set cab type
		myHelpers->WriteByte(0xa0a7808, 4, false);
		//enable wheel found
		//myHelpers->WriteByte(0x8bab744, 1, false);
		myHelpers->WriteByte(0x8bab748, 1, false);

		//bypass random command line
		myHelpers->WriteIntPtr(0x8bdd9e8, 1, false);
		myHelpers->WriteNop(0x81ae870, 1, false);

		OutputDebugStringA("CruisnBlast FFB Loop");
		init = true; 
		
		
		MH_Initialize();
		MH_CreateHook((LPVOID)(0x8151b50), Wheel_SetHook, (LPVOID*)&Wheel_SetHookOrig);
		MH_CreateHook((LPVOID)(0x81519d0), Wheel_Init, (LPVOID*)&Wheel_InitOrig);
		MH_CreateHook((LPVOID)(0x8192960), GameWheel_init, (LPVOID*)&GameWheel_initOrig);
		MH_CreateHook((LPVOID)(0x8196850), Game_diaginit, (LPVOID*)&Game_diaginitOrig);
		MH_CreateHook((LPVOID)(0x8191e40), Game_adjInit, (LPVOID*)&Game_adjInitORig);
		MH_CreateHook((LPVOID)(0x81ae4c0), DefaultCommandLineArgs, (LPVOID*)&DefaultCommandLineArgsOrig);
		MH_CreateHook((LPVOID)(0x81d8240), PlayerDataTblInit, (LPVOID*)&PlayerDataTblInitOrig);
		MH_CreateHook((LPVOID)(0x81af700), GameInitDongle, (LPVOID*)&GameInitDongleOrig);
		MH_CreateHook((LPVOID)(0x8136610), FUN_08136610, (LPVOID*)&FUN_08136610Orig);
		//MH_CreateHook((LPVOID)(0x8151b87), Wheel_SetOutHook, (LPVOID*)&Wheel_SetOutHookOrig);

		

		MH_EnableHook(MH_ALL_HOOKS);
	}


}