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
#include <tchar.h>
#include "M2Emulator.h"
#include "math.h"
#include "SDL.h"

//M2 Emulator Games
std::string SegaRallyChampionship("Sega Rally Championship");
std::string SegaRallyChampionshipRevB("Sega Rally Championship (Rev B)");
std::string SegaRallyProDrivin("Sega Rally Pro Drivin'");
std::string DaytonaUSA("Daytona USA");
std::string DaytonaUSA93Edition("Daytona USA '93 Edition");
std::string DaytonaUSASaturnAds("Daytona USA (Saturn Ads)");
std::string DaytonaUSASpecialEdition("Daytona USA Special Edition");
std::string DaytonaUSATurbo("Daytona USA Turbo");
std::string DaytonaUSATurboRevA("Daytona USA Turbo (Rev A)");
std::string DaytonaUSAGTX2004("Daytona USA: GTX 2004");
std::string DaytonaUSAToTheMaxx("Daytona USA: To The Maxx");
std::string Indianapolis500RevADeluxe("Indianapolis 500 (Rev A, Deluxe)");
std::string Indianapolis500RevATwinNewerrev("Indianapolis 500 (Rev A, Twin, Newer rev)");
std::string Indianapolis500RevATwinOlderrev("Indianapolis 500 (Rev A, Twin, Older rev)");
std::string OverRev("Over Rev");
std::string OverRevModel2B("Over Rev (Model 2B)");
std::string SuperGT24h("Super GT 24h");
std::string SegaTouringCarChampionship("Sega Touring Car Championship");
std::string SegaTouringCarChampionshipRevA("Sega Touring Car Championship (Rev A)");
std::string SegaTouringCarChampionshipRevB("Sega Touring Car Championship (Rev B)");

//Config Settings
extern wchar_t* settingsFilename;
extern int DeviceGUID;
extern int configFeedbackLength;
extern int configGameId;
extern int configMinForce;
extern int configMaxForce;
extern int PowerMode;
extern int EnableRumble;
extern int ReverseRumble;
extern int configFeedbackLength;
extern int configAlternativeMinForceLeft;
extern int configAlternativeMaxForceLeft;
extern int configAlternativeMinForceRight;
extern int configAlternativeMaxForceRight;
extern int EnableForceSpringEffect;
extern int ForceSpringStrength;

static int DaytonaAIMultiplayerHack = GetPrivateProfileInt(TEXT("Settings"), TEXT("DaytonaAIMultiplayerHack"), 0, settingsFilename);
static int DaytonaForcePanoramicAttract = GetPrivateProfileInt(TEXT("Settings"), TEXT("DaytonaForcePanoramicAttract"), 0, settingsFilename);
static int EnableOutputs = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableOutputs"), 0, settingsFilename);

static int configMinForceDaytona = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceDaytona"), 0, settingsFilename);
static int configMaxForceDaytona = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceDaytona"), 100, settingsFilename);
static int configAlternativeMinForceLeftDaytona = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftDaytona"), 0, settingsFilename);
static int configAlternativeMaxForceLeftDaytona = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftDaytona"), 100, settingsFilename);
static int configAlternativeMinForceRightDaytona = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightDaytona"), 0, settingsFilename);
static int configAlternativeMaxForceRightDaytona = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightDaytona"), 100, settingsFilename);
static int configFeedbackLengthDaytona = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthDaytona"), 120, settingsFilename);
static int PowerModeDaytona = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeDaytona"), 0, settingsFilename);
static int EnableForceSpringEffectDaytona = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectDaytona"), 0, settingsFilename);
static int ForceSpringStrengthDaytona = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthDaytona"), 0, settingsFilename);

static int configMinForceSRally = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSRally"), 0, settingsFilename);
static int configMaxForceSRally = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSRally"), 100, settingsFilename);
static int configAlternativeMinForceLeftSRally = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftSRally"), 0, settingsFilename);
static int configAlternativeMaxForceLeftSRally = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftSRally"), 100, settingsFilename);
static int configAlternativeMinForceRightSRally = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightSRally"), 0, settingsFilename);
static int configAlternativeMaxForceRightSRally = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightSRally"), 100, settingsFilename);
static int configFeedbackLengthSRally = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthSRally"), 120, settingsFilename);
static int PowerModeSRally = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeSRally"), 0, settingsFilename);
static int EnableForceSpringEffectSRally = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectSRally"), 0, settingsFilename);
static int ForceSpringStrengthSRally = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthSRally"), 0, settingsFilename);

static int configMinForceIndy500 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceIndy500"), 0, settingsFilename);
static int configMaxForceIndy500 = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceIndy500"), 100, settingsFilename);
static int configAlternativeMinForceLeftIndy500 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftIndy500"), 0, settingsFilename);
static int configAlternativeMaxForceLeftIndy500 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftIndy500"), 100, settingsFilename);
static int configAlternativeMinForceRightIndy500 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightIndy500"), 0, settingsFilename);
static int configAlternativeMaxForceRightIndy500 = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightIndy500"), 100, settingsFilename);
static int configFeedbackLengthIndy500 = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthIndy500"), 120, settingsFilename);
static int PowerModeIndy500 = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeIndy500"), 0, settingsFilename);
static int EnableForceSpringEffectIndy500 = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectIndy500"), 0, settingsFilename);
static int ForceSpringStrengthIndy500 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthIndy500"), 0, settingsFilename);

static int configMinForceSTCC = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSTCC"), 0, settingsFilename);
static int configMaxForceSTCC = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSTCC"), 100, settingsFilename);
static int configAlternativeMinForceLeftSTCC = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftSTCC"), 0, settingsFilename);
static int configAlternativeMaxForceLeftSTCC = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftSTCC"), 100, settingsFilename);
static int configAlternativeMinForceRightSTCC = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightSTCC"), 0, settingsFilename);
static int configAlternativeMaxForceRightSTCC = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightSTCC"), 100, settingsFilename);
static int configFeedbackLengthSTCC = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthSTCC"), 120, settingsFilename);
static int PowerModeSTCC = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeSTCC"), 0, settingsFilename);
static int EnableForceSpringEffectSTCC = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectSTCC"), 0, settingsFilename);
static int ForceSpringStrengthSTCC = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthSTCC"), 0, settingsFilename);

static int configMinForceOverRev = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceOverRev"), 0, settingsFilename);
static int configMaxForceOverRev = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceOverRev"), 100, settingsFilename);
static int configAlternativeMinForceLeftOverRev = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftOverRev"), 0, settingsFilename);
static int configAlternativeMaxForceLeftOverRev = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftOverRev"), 100, settingsFilename);
static int configAlternativeMinForceRightOverRev = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightOverRev"), 0, settingsFilename);
static int configAlternativeMaxForceRightOverRev = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightOverRev"), 100, settingsFilename);
static int configFeedbackLengthOverRev = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthOverRev"), 120, settingsFilename);
static int PowerModeOverRev = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeOverRev"), 0, settingsFilename);
static int EnableForceSpringEffectOverRev = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectOverRev"), 0, settingsFilename);
static int ForceSpringStrengthOverRev = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthOverRev"), 0, settingsFilename);

static int configMinForceSuperGT = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceSuperGT"), 0, settingsFilename);
static int configMaxForceSuperGT = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceSuperGT"), 100, settingsFilename);
static int configAlternativeMinForceLeftSuperGT = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceLeftSuperGT"), 0, settingsFilename);
static int configAlternativeMaxForceLeftSuperGT = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceLeftSuperGT"), 100, settingsFilename);
static int configAlternativeMinForceRightSuperGT = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMinForceRightSuperGT"), 0, settingsFilename);
static int configAlternativeMaxForceRightSuperGT = GetPrivateProfileInt(TEXT("Settings"), TEXT("AlternativeMaxForceRightSuperGT"), 100, settingsFilename);
static int configFeedbackLengthSuperGT = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthSuperGT"), 120, settingsFilename);
static int PowerModeSuperGT = GetPrivateProfileInt(TEXT("Settings"), TEXT("PowerModeSuperGT"), 0, settingsFilename);
static int EnableForceSpringEffectSuperGT = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectSuperGT"), 0, settingsFilename);
static int ForceSpringStrengthSuperGT = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthSuperGT"), 0, settingsFilename);

static bool init = false;
static bool CustomStrengthInit = false;
static bool outputinit = false;

static UINT8 ff;

static bool __stdcall ExitHook(UINT uExitCode)
{
	ExitProcess(0);
	return 0;
}

static bool Hook(void * toHook, void * ourFunct, int len) {
	if (len < 5) {
		return false;
	}

	DWORD curProtection;
	VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);

	memset(toHook, 0x90, len);

	DWORD relativeAddress = ((DWORD)ourFunct - (DWORD)toHook) - 5;

	*(BYTE*)toHook = 0xE9;
	*(DWORD*)((DWORD)toHook + 1) = relativeAddress;

	DWORD temp;
	VirtualProtect(toHook, len, curProtection, &temp);

	return true;
}

static DWORD jmpBackAddy;

char* romnameM2;

void M2Emulator::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers) {

	HWND hWnd1 = FindWindowA(0, SegaRallyChampionship.c_str());
	HWND hWnd2 = FindWindowA(0, DaytonaUSA.c_str());
	HWND hWnd3 = FindWindowA(0, Indianapolis500RevADeluxe.c_str());
	HWND hWnd4 = FindWindowA(0, SegaTouringCarChampionshipRevA.c_str());
	HWND hWnd5 = FindWindowA(0, OverRev.c_str());
	HWND hWnd6 = FindWindowA(0, SuperGT24h.c_str());
	HWND hWnd7 = FindWindowA(0, DaytonaUSA93Edition.c_str());
	HWND hWnd8 = FindWindowA(0, DaytonaUSASaturnAds.c_str());
	HWND hWnd9 = FindWindowA(0, DaytonaUSASpecialEdition.c_str());
	HWND hWnd10 = FindWindowA(0, DaytonaUSATurbo.c_str());
	HWND hWnd11 = FindWindowA(0, DaytonaUSATurboRevA.c_str());
	HWND hWnd12 = FindWindowA(0, DaytonaUSAGTX2004.c_str());
	HWND hWnd13 = FindWindowA(0, DaytonaUSAToTheMaxx.c_str());
	HWND hWnd14 = FindWindowA(0, SegaRallyChampionshipRevB.c_str());
	HWND hWnd15 = FindWindowA(0, SegaRallyProDrivin.c_str());
	HWND hWnd16 = FindWindowA(0, Indianapolis500RevATwinNewerrev.c_str());
	HWND hWnd17 = FindWindowA(0, Indianapolis500RevATwinOlderrev.c_str());
	HWND hWnd18 = FindWindowA(0, SegaTouringCarChampionship.c_str());
	HWND hWnd19 = FindWindowA(0, SegaTouringCarChampionshipRevB.c_str());
	HWND hWnd20 = FindWindowA(0, OverRevModel2B.c_str());

	romnameM2 = new char[256];

	// TODO: would be better to dump all the game names in an array and loop instead with a single hWnd
	if (hWnd1 > NULL)
	{
		sprintf(romnameM2, "%s", SegaRallyChampionship);
	}
	else if(hWnd2 > NULL)
	{
		sprintf(romnameM2, "%s", DaytonaUSA);
	}
	else if (hWnd3 > NULL)
	{
		sprintf(romnameM2, "%s", Indianapolis500RevADeluxe);
	}
	else if (hWnd4 > NULL)
	{
		sprintf(romnameM2, "%s", SegaTouringCarChampionshipRevA);
	}
	else if (hWnd5 > NULL)
	{
		sprintf(romnameM2, "%s", OverRev);
	}
	else if (hWnd6 > NULL)
	{
		sprintf(romnameM2, "%s", SuperGT24h);
	}
	else if (hWnd7 > NULL)
	{
		sprintf(romnameM2, "%s", DaytonaUSA93Edition);
	}
	else if (hWnd8 > NULL)
	{
		sprintf(romnameM2, "%s", DaytonaUSASaturnAds);
	}
	else if (hWnd9 > NULL)
	{
		sprintf(romnameM2, "%s", DaytonaUSASpecialEdition);
	}
	else if (hWnd10 > NULL)
	{
		sprintf(romnameM2, "%s", DaytonaUSATurbo);
	}
	else if (hWnd11 > NULL)
	{
		sprintf(romnameM2, "%s", DaytonaUSATurboRevA);
	}
	else if (hWnd12 > NULL)
	{
		sprintf(romnameM2, "%s", DaytonaUSAGTX2004);
	}
	else if (hWnd13 > NULL)
	{
		sprintf(romnameM2, "%s", DaytonaUSAToTheMaxx);
	}
	else if (hWnd14 > NULL)
	{
		sprintf(romnameM2, "%s", SegaRallyChampionshipRevB);
	}
	else if (hWnd15 > NULL)
	{
		sprintf(romnameM2, "%s", SegaRallyProDrivin);
	}
	else if (hWnd16 > NULL)
	{
		sprintf(romnameM2, "%s", Indianapolis500RevATwinNewerrev);
	}
	else if (hWnd17 > NULL)
	{
		sprintf(romnameM2, "%s", Indianapolis500RevATwinOlderrev);
	}
	else if (hWnd18 > NULL)
	{
		sprintf(romnameM2, "%s", SegaTouringCarChampionship);
	}
	else if (hWnd19 > NULL)
	{
		sprintf(romnameM2, "%s", SegaTouringCarChampionshipRevB);
	}
	else if (hWnd20 > NULL)
	{
		sprintf(romnameM2, "%s", OverRevModel2B);
	}

	if (EnableForceSpringEffect == 1)
	{
		triggers->Springi(ForceSpringStrength / 100.0);
	}

	if (!outputinit)
	{
		if (EnableOutputs == 1)
		{
			HMODULE lib = LoadLibraryA("OutputBlaster.dll");
			outputinit = true;
		}		
	}

	HMODULE hMod = GetModuleHandleA("KERNEL32.dll");
	if (hMod)
	{
		if (!init)
		{
			int hookLength = 6;
			DWORD hookAddress = (DWORD)GetProcAddress(GetModuleHandle(L"KERNEL32.dll"), "ExitProcess");
			if (hookAddress)
			{
				jmpBackAddy = hookAddress + hookLength;
				Hook((void*)hookAddress, ExitHook, hookLength);
				init = true;
			}
		}
	}

	if ((hWnd2 > NULL) || (hWnd3 > NULL) || (hWnd4 > NULL) || (hWnd5 > NULL) || (hWnd6 > NULL) || (hWnd7 > NULL) || (hWnd8 > NULL) || (hWnd9 > NULL) || (hWnd10 > NULL) || (hWnd11 > NULL) || (hWnd12 > NULL) || (hWnd13 > NULL) ||(hWnd16 > NULL) || (hWnd17 > NULL) || (hWnd18 > NULL) || (hWnd19 > NULL) || (hWnd20 > NULL))
	{
		std::string ffs = std::to_string(ff);
		helpers->log((char*)ffs.c_str());
		helpers->log("got value: ");

		if ((ff > 0x09) && (ff < 0x18))
		{
			//Spring
			double percentForce = (ff - 15) / 8.0;
			double percentLength = 100;
			triggers->Spring(percentForce);
		}

		if ((ff > 0x1F) && (ff < 0x28))
		{
			//Clutch
			double percentForce = (ff - 31) / 8.0;
			double percentLength = 100;
			triggers->Friction(percentForce);
		}

		if ((ff > 0x2F) && (ff < 0x3D))
		{
			//Centering
			double percentForce = (ff - 47) / 13.0;
			double percentLength = 100;
			triggers->Spring(percentForce);
		}

		if ((ff > 0x3F) && (ff < 0x48))
		{
			//Uncentering
			double percentForce = (ff - 63) / 8.0;
			double percentLength = 100;
			triggers->Sine(40, 0, percentForce);
			triggers->Rumble(percentForce, percentForce, percentLength);
		}

		if ((ff > 0x4F) && (ff < 0x58))
		{
			//Roll Left
			double percentForce = (ff - 79) / 8.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((ff > 0x5F) && (ff < 0x68))
		{
			//Roll Right
			double percentForce = (ff - 95) / 8.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
	}

	if ((hWnd1 > NULL) || (hWnd14 > NULL) || (hWnd15 > NULL))
	{
		if (!CustomStrengthInit)
		{
			CustomStrengthInit = true;
			configMinForce = configMinForceSRally;
			configMaxForce = configMaxForceSRally;
			configAlternativeMinForceLeft = configAlternativeMinForceLeftSRally;
			configAlternativeMaxForceLeft = configAlternativeMaxForceLeftSRally;
			configAlternativeMinForceRight = configAlternativeMinForceRightSRally;
			configAlternativeMaxForceRight = configAlternativeMaxForceRightSRally;
			configFeedbackLength = configFeedbackLengthSRally;
			PowerMode = PowerModeSRally;
			EnableForceSpringEffect = EnableForceSpringEffectSRally;
			ForceSpringStrength = ForceSpringStrengthSRally;
		}

		UINT8 ff1 = helpers->ReadByte(0x174CF4, /* isRelativeOffset*/ true); //SegaRallyChampionship
		std::string ffs = std::to_string(ff1);
		helpers->log((char*)ffs.c_str());
		helpers->log("got value: ");

		if ((ff1 > 0xBF) && (ff1 < 0xDF))
		{
			helpers->log("moving wheel left");
			double percentForce = (ff1 - 191) / 31.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((ff1 > 0x7F) && (ff1 < 0x9F))
		{
			helpers->log("moving wheel right");
			double percentForce = (ff1 - 127) / 31.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
	}

	if ((hWnd2 > NULL) || (hWnd7 > NULL) || (hWnd8 > NULL) || (hWnd9 > NULL) || (hWnd10 > NULL) || (hWnd11 > NULL) || (hWnd12 > NULL) || (hWnd13 > NULL))
	{
		if (!CustomStrengthInit)
		{
			CustomStrengthInit = true;
			configMinForce = configMinForceDaytona;
			configMaxForce = configMaxForceDaytona;
			configAlternativeMinForceLeft = configAlternativeMinForceLeftDaytona;
			configAlternativeMaxForceLeft = configAlternativeMaxForceLeftDaytona;
			configAlternativeMinForceRight = configAlternativeMinForceRightDaytona;
			configAlternativeMaxForceRight = configAlternativeMaxForceRightDaytona;
			configFeedbackLength = configFeedbackLengthDaytona;
			PowerMode = PowerModeDaytona;
			EnableForceSpringEffect = EnableForceSpringEffectDaytona;
			ForceSpringStrength = ForceSpringStrengthDaytona;
		}

		if (DaytonaForcePanoramicAttract == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			helpers->WriteByte(Rambase1 + 0x1070, 0x00, /* isRelativeOffset*/ false);
		}

		if (DaytonaAIMultiplayerHack == 1)
		{
			INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, /* isRelativeOffset*/ true);
			INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, /* isRelativeOffset */ false);
			UINT8 gamestate = helpers->ReadByte(Rambase1 + 0x10A4, /* isRelativeOffset*/ false);
			UINT8 track = helpers->ReadByte(Rambase1 + 0x1460, /* isRelativeOffset*/ false);
			UINT8 trackselect = helpers->ReadByte(Rambase1 + 0x1468, /* isRelativeOffset*/ false);
			UINT8 countdown = helpers->ReadByte(Rambase1 + 0x1850, /* isRelativeOffset*/ false);
			UINT8 linksize = helpers->ReadByte(Rambase1 + 0x40001, /* isRelativeOffset*/ false);
			UINT8 linkID = helpers->ReadByte(Rambase1 + 0x40002, /* isRelativeOffset*/ false);
			INT_PTR gamestatetimer = helpers->ReadIntPtr(Rambase1 + 0x10A8, /* isRelativeOffset*/ false);
			UINT8 camhack = helpers->ReadByte(Rambase1 + 0x14A4, /* isRelativeOffset*/ false);
			UINT8 carsinfront = helpers->ReadByte(Rambase1 + 0x51EC, /* isRelativeOffset*/ false);
			UINT8 mpposition = helpers->ReadByte(Rambase1 + 0x51ED, /* isRelativeOffset*/ false);
			float cary = helpers->ReadFloat32(Rambase1 + 0x519C, /* isRelativeOffset */ false);
			float carx = helpers->ReadFloat32(Rambase1 + 0x51A4, /* isRelativeOffset */ false);
			UINT8 nop1 = helpers->ReadByte(0xC2130, /* isRelativeOffset*/ true);
			UINT8 nop2 = helpers->ReadByte(0xC2131, /* isRelativeOffset*/ true);
			UINT8 nop3 = helpers->ReadByte(0xC2132, /* isRelativeOffset*/ true);


			if (gamestate == 0x1A)
			{
				helpers->WriteByte(Rambase1 + 0x51ED, carsinfront, /* isRelativeOffset*/ false);
			}

			if (trackselect == 0x01)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x02, /* isRelativeOffset*/ false);
			}
			else if (trackselect == 0x02)
			{
				helpers->WriteByte(Rambase1 + 0x1460, 0x01, /* isRelativeOffset*/ false);
			}

			if (linksize == 0x02)
			{
				if (linkID == 0x02)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, 3, true);
					}

					if ((gamestate > 0x1A)& (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133)& (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 0.0, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x03)
			{
				if (linkID == 0x03)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133)& (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, 3, true);
					}

					if ((gamestate > 0x1A)& (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133)& (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, 3, true);
					}

					if ((gamestate > 0x1A)& (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133)& (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
			else if (linksize == 0x04)
			{
				if (linkID == 0x04)
				{
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(250);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC302CAF4, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37C0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133)& (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				if (linkID == 0x03)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, 3, true);
					}

					if ((gamestate > 0x1A)& (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C40, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(350);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37CF3D0, /* isRelativeOffset */ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteFloat32(Rambase1 + 0x519C, 450.0, /* isRelativeOffset */ false);
					}
					if ((gamestatetimer > 4294964133)& (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x02)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, 3, true);
					}

					if ((gamestate > 0x1A)& (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540C80, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x01, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						Sleep(150);
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02 || track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133)& (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
				}
				else if (linkID == 0x01)
				{
					if ((gamestate == 0x1A) & (gamestatetimer < 100))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}
					else if ((gamestate == 0x1A) & (gamestatetimer > 100))
					{
						Sleep(100);
						helpers->WriteNop(0xC2130, 3, true);
					}

					if ((gamestate > 0x1A)& (gamestate < 0x1A))
					{
						helpers->WriteByte(0xC2130, 0x88, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2131, 0x14, /* isRelativeOffset*/ true);
						helpers->WriteByte(0xC2132, 0x01, /* isRelativeOffset*/ true);
					}

					if (gamestate > 0x07)
					{
						helpers->WriteIntPtr(Rambase1 + 0x40004, 0x00540D00, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x40008, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteIntPtr(Rambase1 + 0x4000C, 0x00540CC0, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5484, 0x00, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5784, 0x02, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5A84, 0x03, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x5D84, 0x04, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6084, 0x05, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6384, 0x06, /* isRelativeOffset*/ false);
						helpers->WriteByte(Rambase1 + 0x6684, 0x07, /* isRelativeOffset*/ false);
					}
					if ((gamestatetimer > 4294964133)& (gamestate == 0x12))
					{
						helpers->WriteIntPtr(Rambase1 + 0x10A8, 0x3B6, /* isRelativeOffset*/ false);
					}
					if ((gamestate == 0x16) & (countdown == 0x00) & (track == 0x00))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						helpers->WriteByte(Rambase1 + 0x1850, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x01))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC2F195E8, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
					else if ((gamestate == 0x14) & (trackselect == 0x00) & (track == 0x02))
					{
						helpers->WriteByte(Rambase1 + 0x40000, 0x99, /* isRelativeOffset*/ false); // change to 99
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x10A4, 0x13, /* isRelativeOffset*/ false); // restart race
						Sleep(50);
						helpers->WriteByte(Rambase1 + 0x40000, 0x01, /* isRelativeOffset*/ false); // change back to 1
						Sleep(50);
						helpers->WriteIntPtr(Rambase1 + 0x51A4, 0xC37E0001, /* isRelativeOffset */ false);
						helpers->WriteByte(Rambase1 + 0x1468, 0x01, /* isRelativeOffset*/ false);
					}
				}
			}
		}

		ff = helpers->ReadByte(0x0057285B, /* isRelativeOffset*/ false); //DaytonaUSA		
	}

	if ((hWnd3 > NULL) || (hWnd16 > NULL) || (hWnd17 > NULL))
	{
		if (!CustomStrengthInit)
		{
			CustomStrengthInit = true;
			configMinForce = configMinForceIndy500;
			configMaxForce = configMaxForceIndy500;
			configAlternativeMinForceLeft = configAlternativeMinForceLeftIndy500;
			configAlternativeMaxForceLeft = configAlternativeMaxForceLeftIndy500;
			configAlternativeMinForceRight = configAlternativeMinForceRightIndy500;
			configAlternativeMaxForceRight = configAlternativeMaxForceRightIndy500;
			configFeedbackLength = configFeedbackLengthIndy500;
			PowerMode = PowerModeIndy500;
			EnableForceSpringEffect = EnableForceSpringEffectIndy500;
			ForceSpringStrength = ForceSpringStrengthIndy500;
		}

		ff = helpers->ReadByte(0x17285B, /* isRelativeOffset*/ true); //Indy500
	}	

	if ((hWnd4 > NULL) || (hWnd18 > NULL) || (hWnd19 > NULL))
	{
		if (!CustomStrengthInit)
		{
			CustomStrengthInit = true;
			configMinForce = configMinForceSTCC;
			configMaxForce = configMaxForceSTCC;
			configAlternativeMinForceLeft = configAlternativeMinForceLeftSTCC;
			configAlternativeMaxForceLeft = configAlternativeMaxForceLeftSTCC;
			configAlternativeMinForceRight = configAlternativeMinForceRightSTCC;
			configAlternativeMaxForceRight = configAlternativeMaxForceRightSTCC;
			configFeedbackLength = configFeedbackLengthSTCC;
			PowerMode = PowerModeSTCC;
			EnableForceSpringEffect = EnableForceSpringEffectSTCC;
			ForceSpringStrength = ForceSpringStrengthSTCC;
		}

		ff = helpers->ReadByte(0x17285B, /* isRelativeOffset*/ true); //Sega Touring Car Championship
	}		

	if ((hWnd5 > NULL) || (hWnd20 > NULL))
	{
		if (!CustomStrengthInit)
		{
			CustomStrengthInit = true;
			configMinForce = configMinForceOverRev;
			configMaxForce = configMaxForceOverRev;
			configAlternativeMinForceLeft = configAlternativeMinForceLeftOverRev;
			configAlternativeMaxForceLeft = configAlternativeMaxForceLeftOverRev;
			configAlternativeMinForceRight = configAlternativeMinForceRightOverRev;
			configAlternativeMaxForceRight = configAlternativeMaxForceRightOverRev;
			configFeedbackLength = configFeedbackLengthOverRev;
			PowerMode = PowerModeOverRev;
			EnableForceSpringEffect = EnableForceSpringEffectOverRev;
			ForceSpringStrength = ForceSpringStrengthOverRev;
		}

		ff = helpers->ReadByte(0x17285B, /* isRelativeOffset*/ true); //OverRev
	}	

	if (hWnd6 > NULL)
	{
		if (!CustomStrengthInit)
		{
			CustomStrengthInit = true;
			configMinForce = configMinForceSuperGT;
			configMaxForce = configMaxForceSuperGT;
			configAlternativeMinForceLeft = configAlternativeMinForceLeftSuperGT;
			configAlternativeMaxForceLeft = configAlternativeMaxForceLeftSuperGT;
			configAlternativeMinForceRight = configAlternativeMinForceRightSuperGT;
			configAlternativeMaxForceRight = configAlternativeMaxForceRightSuperGT;
			configFeedbackLength = configFeedbackLengthSuperGT;
			PowerMode = PowerModeSuperGT;
			EnableForceSpringEffect = EnableForceSpringEffectSuperGT;
			ForceSpringStrength = ForceSpringStrengthSuperGT;
		}

		ff = helpers->ReadByte(0x17285B, /* isRelativeOffset*/ true); //Super GT 24h
	}		
}