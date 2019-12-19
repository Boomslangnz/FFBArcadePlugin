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

#include "OutputReading.h"
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <tchar.h>
#include "SDL.h"
extern int joystick_index1;
extern int joystick_index2;
extern int joystick_index3;
extern SDL_Joystick* GameController2;
extern SDL_Haptic* ControllerHaptic2;
extern SDL_Haptic* haptic2;
extern SDL_Joystick* GameController3;
extern SDL_Haptic* ControllerHaptic3;
extern SDL_Haptic* haptic3;
HINSTANCE ProcDLL = NULL;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int configFeedbackLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLength"), 120, settingsFilename);
static int configGameId = GetPrivateProfileInt(TEXT("Settings"), TEXT("GameId"), 0, settingsFilename);
static int SinePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("SinePeriod"), 0, settingsFilename);
static int SineFadePeriod = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineFadePeriod"), 0, settingsFilename);
static int SineStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("SineStrength"), 0, settingsFilename);
static int RumbleStrengthLeftMotor = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthLeftMotor"), 0, settingsFilename);
static int RumbleStrengthRightMotor = GetPrivateProfileInt(TEXT("Settings"), TEXT("RumbleStrengthRightMotor"), 0, settingsFilename);
static int EnableForceSpringEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffect"), 0, settingsFilename);
static int ForceSpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrength"), 0, settingsFilename);

static bool init = false;
static bool EmuName = false;
static bool RomGameName = false;
static bool Effect1 = false;
static bool Effect2 = false;
static bool Effect3 = false;
static bool DirtDevilSine = false;
static bool ForceSpringEffect = false;
static bool DontSineUntilRaceStart = false;
static bool HardDrivinFrame = false;
static bool Motion = false;
static bool MotionFalse = false;

HINSTANCE hInstance;
HINSTANCE hPrevInstance;
LPSTR lpCmdLine;
int nCmdShow;

const char* nameFFB;
const char* romFFB;
const char* EmulatorName;
char* name;
char* romname;
char* RunningFFB;
char* Emulator;
int vals[8] = { 0 };
int frame = 0;
int HardDrivinFFB;
int StopConstant;
int newstateFFB;
int stateFFB;
int stateFFB2;
int stateFFB3;
int stateFFBDevice2;
int stateFFBDevice3;

std::string wheelA("wheel");

typedef int(__stdcall* MAME_START)(int hWnd);
typedef int(__stdcall* MAME_STOP)(void);
typedef int(__stdcall* MAME_COPYDATA)(int id, const char* name);
typedef int(__stdcall* MAME_UPDATESTATE)(const char* id, int state);
typedef int(__stdcall* MAME_OUTPUT)(const char* name, int value);
typedef int(__stdcall* INIT_MAME)(int clientid, PWCHAR name, MAME_START start, MAME_STOP stop, MAME_COPYDATA copydata, MAME_UPDATESTATE updatestate, MAME_OUTPUT output);

MAME_START mame_start_ptr;
MAME_STOP mame_stop_ptr;
MAME_COPYDATA mame_copydata_ptr;
MAME_UPDATESTATE mame_updatestate_ptr;
MAME_OUTPUT mame_output_ptr;
INIT_MAME dll_init;

int __stdcall mame_start(int hWnd);
int __stdcall mame_stop(void);
int __stdcall mame_copydata(int id, const char* name);
int __stdcall mame_updatestate(const char* id, int state);
int __stdcall mame_output(const char* name, int value);

void CallTheOutputs()
{
#ifdef _WIN64  
	ProcDLL = LoadLibrary(TEXT("MAME64.dll"));
#else  
	ProcDLL = LoadLibrary(TEXT("MAME32.dll"));
#endif
	if (ProcDLL != NULL)
	{
		dll_init = (INIT_MAME)GetProcAddress(ProcDLL, "init_mame");
	}
	else
	{
#ifdef _WIN64
		MessageBoxA(NULL, "MAME64.dll is missing!", "FFBPluginError", NULL);
#else
		MessageBoxA(NULL, "MAME32.dll is missing!", "FFBPluginError", NULL);
#endif
	}
}

typedef struct _id_map_entry id_map_entry;
struct _id_map_entry
{
	id_map_entry* next;
	const char* name;
	WPARAM					id;
};

void AppendTextToEditCtrl(HWND hWnd, LPCTSTR lpString);
void reset_id_to_outname_cache(void);
const char* get_name_from_id(int id);
void add_map_entry(id_map_entry* entry, int id, char* name);

id_map_entry* idmaplist;

HWND hEdit;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void AppendTextToEditCtrl(HWND hWnd, LPCTSTR pszText);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CallTheOutputs();
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"MAMEInterop";
	wcex.hIconSm = NULL;

	RegisterClassEx(&wcex);

	hWnd = CreateWindow(L"MAMEInterop", L"MAMEInterop", WS_OVERLAPPEDWINDOW,
		0, 0, 512, 512, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
		MessageBox(hWnd, L"Could not create window", L"Error", MB_OK | MB_ICONERROR);

	hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
		8, 8, 488, 464, hWnd, NULL, GetModuleHandle(NULL), NULL);

	if (hEdit == NULL)
		MessageBox(hWnd, L"Could not create edit box.", L"Error", MB_OK | MB_ICONERROR);

	if (hWnd != NULL)
	{
		//ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
	}
	
	mame_start_ptr = mame_start;
	mame_stop_ptr = mame_stop;
	mame_copydata_ptr = mame_copydata;
	mame_updatestate_ptr = mame_updatestate;
	mame_output_ptr = mame_output;

	dll_init(1, L"Test", mame_start_ptr, mame_stop_ptr, mame_copydata_ptr, mame_updatestate_ptr, mame_output_ptr);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		reset_id_to_outname_cache();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void AppendTextToEditCtrl(HWND hWnd, LPCTSTR lpString)
{
	int iPrevLen = GetWindowTextLength(hWnd);
	SendMessage(hWnd, EM_SETSEL, iPrevLen, iPrevLen);
	SendMessage(hWnd, EM_REPLACESEL, 0, (LPARAM)lpString);
}

void reset_id_to_outname_cache(void)
{
	while (idmaplist != NULL)
	{
		id_map_entry* temp = idmaplist;
		idmaplist = temp->next;
		free(temp);
	}
}

const char* get_name_from_id(int id)
{
	while (idmaplist != NULL)
	{
		id_map_entry* temp = idmaplist;

		if (temp->id == (WPARAM)id)
			return temp->name;

		idmaplist = temp->next;
	}

	return NULL;
}

void add_map_entry(id_map_entry* entry, int id, char* name)
{
	char* string;

	entry = (id_map_entry*)malloc(sizeof(entry));
	string = (char*)malloc(strlen(name) + 1);

	if (entry != NULL && string != NULL)
	{
		entry->next = idmaplist;
		entry->name = string;
		entry->id = id;

		strcpy(string, name);
		idmaplist = entry;
	}
}


int __stdcall mame_start(int hWnd)
{
	WCHAR buf[256];

	wsprintf(buf, L"mame_start hwnd = 0x%08x\r\n", hWnd);

	AppendTextToEditCtrl(hEdit, buf);

	return 1;
}

int __stdcall mame_stop(void)
{
	reset_id_to_outname_cache();

	AppendTextToEditCtrl(hEdit, TEXT("mame_stop\r\n"));

	StopConstant = 255;

	return 1;
}

int __stdcall mame_copydata(int id, const char* name)
{
	WCHAR buf[256];

	wsprintf(buf, L"id %d = '%S'\r\n", id, name);

	if (id == 0)
	{
		romFFB = name;
	}

	AppendTextToEditCtrl(hEdit, buf);

	return 1;
}

int __stdcall mame_updatestate(const char* id, int state)
{
	WCHAR buf[256];

	LPCSTR name = get_name_from_id((int)id);

	if (name == NULL)
		name = id;

	wsprintf(buf, L"updatestate: id=%d (%S) state=%d\r\n", id, name, state);
	AppendTextToEditCtrl(hEdit, buf);

	nameFFB = name;
	newstateFFB = state;

	if (HardDrivinFrame)
	{
		if (name == wheelA)
		{
			//if (!(((state == 0xE0) || (state == 0)) && ((frame == 0) || (frame == 4))))
			if ((state != 0xE0) && (state != 0x00))
			{
				vals[frame & 0x7] = state;
				frame++;
			}
		}
	}
	
	return 1;
}

int __stdcall mame_output(const char* name, int value)
{
	WCHAR buf[256];

	wsprintf(buf, L"output: name=%S value=%d\r\n", name, value);
	AppendTextToEditCtrl(hEdit, buf);

	return 1;
}

static BOOL CALLBACK FindWindowBySubstr(HWND hwnd, LPARAM substring)
{
	const DWORD TITLE_SIZE = 1024;
	TCHAR windowTitle[TITLE_SIZE];

	if (GetWindowText(hwnd, windowTitle, TITLE_SIZE))
	{
		if (_tcsstr(windowTitle, LPCTSTR(substring)) != NULL)
		{
			return false;
		}
	}
	return true;
}

DWORD WINAPI ThreadForOutputs(LPVOID lpParam)
{
	WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return 0;
}

DWORD WINAPI ThreadForForcedSpring(LPVOID lpParam)
{
	if (configGameId == 34)
	{
		Sleep(2500);
		ForceSpringEffect = true;
	}
	else
	{
		ForceSpringEffect = true;
	}	

	return 0;
}

//Supermodel Emulator Games
std::string dayto2pe("dayto2pe");
std::string daytona2("daytona2");
std::string dirtdvlsa("dirtdvlsa");
std::string dirtdvls("dirtdvls");
std::string dirtdvlsj("dirtdvlsj");
std::string dirtdvlsg("dirtdvlsg");
std::string ecau("ecau");
std::string eca("eca");
std::string ecap("ecap");
std::string ecaj("ecaj");
std::string lemans24("lemans24");
std::string scud("scud");
std::string scuda("scuda");
std::string scudj("scudj");
std::string scudplus("scudplus");
std::string scudplusa("scudplusa");
std::string srally2("srally2");
std::string srally2x("srally2x");
std::string srally2p("srally2p");
std::string srally2pa("srally2pa");

//MAME Games
std::string aburner2("aburner2");
std::string aburner2g("aburner2g");
std::string vformula("vformula");
std::string vr("vr");
std::string sfrush("sfrush");
std::string sfrushrk("sfrushrk");
std::string sfrushrkwo("sfrushrkwo");
std::string sfrusha("sfrusha");
std::string crusnwld("crusnwld");
std::string crusnwld24("crusnwld24");
std::string crusnwld23("crusnwld23");
std::string crusnwld20("crusnwld20");
std::string crusnwld19("crusnwld19");
std::string crusnwld17("crusnwld17");
std::string crusnwld13("crusnwld13");
std::string offroadc("offroadc");
std::string offroadc4("offroadc4");
std::string offroadc3("offroadc3");
std::string offroadc1("offroadc1");
std::string crusnusa("crusnusa");
std::string crusnusa40("crusnusa40");
std::string crusnusa21("crusnusa21");
std::string calspeed("calspeed");
std::string calspeeda("calspeeda");
std::string calspeedb("calspeedb");
std::string outrunra("outrunra");
std::string outrun("outrun");
std::string outruneh("outruneh");
std::string toutrun("toutrun");
std::string toutrund("toutrund");
std::string toutrunj("toutrunj");
std::string toutrunjd("toutrunjd");
std::string pdrift("pdrift");
std::string pdrifta("pdrifta");
std::string pdrifte("pdrifte");
std::string pdriftj("pdriftj");
std::string pdriftl("pdriftl");
std::string orunners("orunners");
std::string orunnersu("orunnersu");
std::string orunnersj("orunnersj");
std::string sf2049("sf2049");
std::string sf2049se("sf2049se");
std::string sf2049te("sf2049te");
std::string harddriv("harddriv");
std::string harddriv1("harddriv1");
std::string harddrivb6("harddrivb6");
std::string harddrivb("harddrivb");
std::string harddrivg4("harddrivg4");
std::string harddrivg("harddrivg");
std::string harddrivj6("harddrivj6");
std::string harddrivj("harddrivj");
std::string harddriv2("harddriv2");
std::string harddriv3("harddriv3");
std::string harddrivcb("harddrivcb");
std::string harddrivcg("harddrivcg");
std::string harddrivc1("harddrivc1");
std::string harddrivc("harddrivc");
std::string hdrivairp("hdrivairp");
std::string hdrivair("hdrivair");
std::string racedrivb1("racedrivb1");
std::string racedrivb4("racedrivb4");
std::string racedrivb("racedrivb");
std::string racedrivg1("racedrivg1");
std::string racedrivg4("racedrivg4");
std::string racedrivg("racedrivg");
std::string racedriv1("racedriv1");
std::string racedriv2("racedriv2");
std::string racedriv3("racedriv3");
std::string racedriv4("racedriv4");
std::string racedriv("racedriv");
std::string racedrivcb4("racedrivcb4");
std::string racedrivcb("racedrivcb");
std::string racedrivcg4("racedrivcg4");
std::string racedrivcg("racedrivcg");
std::string racedrivc2("racedrivc2");
std::string racedrivc4("racedrivc4");
std::string racedrivc("racedrivc");
std::string racedrivpan("racedrivpan");
std::string othunder("othunder");
std::string othundero("othundero");
std::string othunderuo("othunderuo");
std::string othunderu("othunderu");
std::string othunderj("othunderj");
std::string opwolf("opwolf");
std::string opwolfp("opwolfp");
std::string opwolfj("opwolfj");
std::string opwolfu("opwolfu");
std::string opwolfa("opwolfa");
std::string revx("revx");
std::string revxp5("revxp5");
std::string term2("term2");
std::string term2la1("term2la1");
std::string term2pa2("term2pa2");
std::string term2la2("term2la2");
std::string term2la3("term2la3");
std::string term2lg1("term2lg1");
std::string zombraid("zombraid");
std::string zombraidpj("zombraidpj");
std::string zombraidp("zombraidp");
std::string bbusters("bbusters");
std::string bbustersu("bbustersu");
std::string bbustersua("bbustersua");
std::string bbustersj("bbustersj");
std::string mechatt("mechatt");
std::string mechattu("mechattu");
std::string mechattu1("mechattu1");
std::string mechattj("mechattj");
std::string tshoot("tshoot");
std::string gunbustru("gunbustru");
std::string gunbustr("gunbustr");
std::string gunbustrj("gunbustrj");
std::string alien3("alien3");
std::string alien3u("alien3u");
std::string ptblank2("ptblank2");
std::string ptblank2ua("ptblank2ua");
std::string ghlpanic("ghlpanic");
std::string spacegun("spacegun");
std::string spacegunu("spacegunu");
std::string spacegunj("spacegunj");
std::string rchase("rchase");
std::string rchasej("rchasej");
std::string lghost("lghost");
std::string lghostd("lghostd");
std::string lghostu("lghostu");
std::string lghostud("lghostud");
std::string lghostj("lghostj");
std::string timecris("timecris");
std::string timecrisa("timecrisa");
std::string cischeat("cischeat");
std::string f1gpstar("f1gpstar");
std::string f1gpstaro("f1gpstaro");
std::string f1gpstr2("f1gpstr2");
std::string undrfire("undrfire");
std::string undrfireu("undrfireu");
std::string undrfirej("undrfirej");
std::string cbombers("cbombers");
std::string cbombersj("cbombersj");
std::string cbombersp("cbombersp");

//Our string to load game from
std::string Daytona2Active("Daytona2Active");
std::string DirtDevilsActive("DirtDevilsActive");
std::string Srally2Active("Srally2Active");
std::string VirtuaRacingActive("VirtuaRacingActive");
std::string SanFranActive("SanFranActive");
std::string CrusnWldActive("CrusnWldActive");
std::string OffroadChallengeActive("OffroadChallengeActive");
std::string CrusnUSAActive("CrusnUSAActive");
std::string CalSpeedActive("CalSpeedActive");
std::string SanFran2049Active("SanFran2049Active");
std::string HardDrivinActive("HardDrivinActive"); 
std::string EffectActive("EffectActive");
std::string EffectActive2("EffectActive2");
std::string OutrunActive("OutrunActive");
std::string PDriftActive("PDriftActive");

//Names of FFB Outputs
std::string RawDrive("RawDrive");
std::string digit0("digit0");
std::string wheel("wheel");
std::string lamp1("lamp1");
std::string led2("led2");
std::string Vibration_motor("Vibration_motor");
std::string vibration_motor("vibration_motor");
std::string Wheel_vibration("Wheel_vibration");
std::string upright_wheel_motor("upright_wheel_motor");
std::string MA_Steering_Wheel_motor("MA_Steering_Wheel_motor");
std::string MB_Steering_Wheel_motor("MB_Steering_Wheel_motor");
std::string Left_Gun_Recoil("Left_Gun_Recoil");
std::string Right_Gun_Recoil("Right_Gun_Recoil");
std::string Player1_Recoil_Piston("Player1_Recoil_Piston");
std::string Player2_Recoil_Piston("Player2_Recoil_Piston");
std::string Player1_Gun_Recoil("Player1_Gun_Recoil");
std::string Player2_Gun_Recoil("Player2_Gun_Recoil");
std::string Player3_Gun_Recoil("Player3_Gun_Recoil");
std::string P1_Gun_Recoil("P1_Gun_Recoil");
std::string P2_Gun_Recoil("P2_Gun_Recoil");
std::string P3_Gun_Recoil("P3_Gun_Recoil");
std::string P1_gun_recoil("P1_gun_recoil");
std::string P2_gun_recoil("P2_gun_recoil");
std::string mcuout1("mcuout1");
std::string Bank_Motor_Speed("Bank_Motor_Speed");
std::string Bank_Motor_Direction("Bank_Motor_Direction");
std::string bank_motor_position("bank_motor_position");

//Emulator Name
std::string MAME("MAME");
std::string Supermodel("Supermodel");

void OutputReading::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (!init)
	{
		CreateThread(NULL, 0, ThreadForOutputs, NULL, 0, NULL);

		if (EnableForceSpringEffect == 1)
		{
			CreateThread(NULL, 0, ThreadForForcedSpring, NULL, 0, NULL);
		}

		wchar_t* deviceGUIDString2 = new wchar_t[256];
		int Device2GUID = GetPrivateProfileString(TEXT("Settings"), TEXT("Device2GUID"), NULL, deviceGUIDString2, 256, settingsFilename);
		char joystick_guid[256];
		sprintf(joystick_guid, "%S", deviceGUIDString2);
		SDL_JoystickGUID guid, dev_guid;
		int numJoysticks = SDL_NumJoysticks();
		std::string njs = std::to_string(numJoysticks);
		((char)njs.c_str());
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			extern int joystick1Index;
			if (i == joystick1Index)
			{
				continue;
			}
			SDL_Joystick* js2 = SDL_JoystickOpen(i);
			joystick_index2 = SDL_JoystickInstanceID(js2);
			SDL_JoystickGUID guid = SDL_JoystickGetGUID(js2);
			char guid_str[1024];
			SDL_JoystickGetGUIDString(guid, guid_str, sizeof(guid_str));
			const char* name = SDL_JoystickName(js2);
			char text[256];
			sprintf(text, "Joystick: %d / Name: %s / GUID: %s\n", i, name, guid_str);
			guid = SDL_JoystickGetGUIDFromString(joystick_guid);
			dev_guid = SDL_JoystickGetGUID(js2);
			if (!memcmp(&guid, &dev_guid, sizeof(SDL_JoystickGUID)))
			{
				GameController2 = SDL_JoystickOpen(i);
				ControllerHaptic2 = SDL_HapticOpenFromJoystick(GameController2);
				break;
			}
			SDL_JoystickClose(js2);
		}
		haptic2 = ControllerHaptic2;
		if ((SDL_HapticRumbleSupported(haptic2) == SDL_TRUE))
		{
			SDL_HapticRumbleInit;
			SDL_HapticRumbleInit(ControllerHaptic2);
		}
		SDL_HapticSetGain(haptic2, 100);

		wchar_t* deviceGUIDString3 = new wchar_t[256];
		int Device3GUID = GetPrivateProfileString(TEXT("Settings"), TEXT("Device3GUID"), NULL, deviceGUIDString3, 256, settingsFilename);
		char joystick_guid2[256];
		sprintf(joystick_guid2, "%S", deviceGUIDString3);
		SDL_JoystickGUID guid2, dev_guid2;
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			extern int joystick1Index;
			if (i == joystick1Index)
			{
				continue;
			}
			SDL_Joystick* js3 = SDL_JoystickOpen(i);
			joystick_index3 = SDL_JoystickInstanceID(js3);
			SDL_JoystickGUID guid2 = SDL_JoystickGetGUID(js3);
			char guid_str2[1024];
			SDL_JoystickGetGUIDString(guid2, guid_str2, sizeof(guid_str2));
			const char* name2 = SDL_JoystickName(js3);
			char text2[256];
			sprintf(text2, "Joystick: %d / Name: %s / GUID: %s\n", i, name2, guid_str2);
			guid2 = SDL_JoystickGetGUIDFromString(joystick_guid2);
			dev_guid2 = SDL_JoystickGetGUID(js3);
			if (!memcmp(&guid2, &dev_guid2, sizeof(SDL_JoystickGUID)))
			{
				GameController3 = SDL_JoystickOpen(i);
				ControllerHaptic3 = SDL_HapticOpenFromJoystick(GameController3);
				break;
			}
			SDL_JoystickClose(js3);
		}
		haptic3 = ControllerHaptic3;
		if ((SDL_HapticRumbleSupported(haptic3) == SDL_TRUE))
		{
			SDL_HapticRumbleInit;
			SDL_HapticRumbleInit(ControllerHaptic3);
		}
		SDL_HapticSetGain(haptic3, 100);
		init = true;
	}


	if (EnableForceSpringEffect == 1)
	{
		if (ForceSpringEffect)
		{
			triggers->Springi(ForceSpringStrength / 100.0);
		}
	}

	romname = new char[256]; //name of rom being played
	sprintf(romname, "%s", romFFB);

	name = new char[256]; //name of FFB currently
	sprintf(name, "%s", nameFFB);

	if (!RomGameName)
	{
		if (romname != NULL)
		{
			//Select code to run via rom name
			if (romname == dayto2pe || romname == daytona2 || romname == scud || romname == scuda || romname == scudj || romname == scudplus || romname == scudplusa || romname == lemans24)
			{
				RunningFFB = "Daytona2Active";
			}

			if (romname == dirtdvlsa || romname == dirtdvls || romname == dirtdvlsj || romname == dirtdvlsg)
			{
				RunningFFB = "DirtDevilsActive";
			}

			if (romname == srally2 || romname == srally2x || romname == srally2p || romname == srally2pa || romname == ecau || romname == eca || romname == ecap || romname == ecaj)
			{
				RunningFFB = "Srally2Active";
			}

			if (romname == vr || romname == vformula)
			{
				RunningFFB = "VirtuaRacingActive";
			}

			if (romname == sfrush || romname == sfrusha || romname == sfrushrk || romname == sfrushrkwo)
			{
				RunningFFB = "SanFranActive";
			}

			if (romname == crusnwld || romname == crusnwld24 || romname == crusnwld23 || romname == crusnwld20 || romname == crusnwld19 || romname == crusnwld17 || romname == crusnwld13)
			{
				RunningFFB = "CrusnWldActive";
			}

			if (romname == offroadc || romname == offroadc4 || romname == offroadc3 || romname == offroadc1)
			{
				RunningFFB = "OffroadChallengeActive";
			}

			if (romname == crusnusa || romname == crusnusa40 || romname == crusnusa21)
			{
				RunningFFB = "CrusnUSAActive";
			}

			if (romname == calspeed || romname == calspeeda || romname == calspeedb)
			{
				RunningFFB = "CalSpeedActive";
			}

			if (romname == sf2049 || romname == sf2049se || romname == sf2049te)
			{
				RunningFFB = "SanFran2049Active";
			}

			if (romname == harddriv1 || romname == harddrivb6 || romname == harddrivb || romname == harddrivg4 || romname == harddrivg || romname == harddrivj6 || romname == harddrivj ||
				romname == harddriv2 || romname == harddriv3 || romname == harddriv || romname == harddrivcb || romname == harddrivcg || romname == harddrivc1 || romname == harddrivc ||
				romname == hdrivairp || romname == hdrivair || romname == racedrivb1 || romname == racedrivb4 || romname == racedrivb || romname == racedrivg1 || romname == racedrivg4 ||
				romname == racedrivg || romname == racedriv1 || romname == racedriv2 || romname == racedriv3 || romname == racedriv4 || romname == racedriv || romname == racedrivcb4 || 
				romname == racedrivcb || romname == racedrivcg4 || romname == racedrivcg || romname == racedrivc2 || romname == racedrivc4 || romname == racedrivc || romname == racedrivpan)
			{
				RunningFFB = "HardDrivinActive";
			}

			if (romname == revx || romname == revxp5 || romname == zombraid || romname == zombraidpj || romname == zombraidp || romname == bbusters || romname == bbustersu || romname == bbustersua ||
				romname == bbustersj || romname == mechatt || romname == mechattu || romname == mechattu1 || romname == mechattj || romname == tshoot || romname == gunbustru || romname == gunbustr ||
				romname == gunbustrj || romname == alien3 || romname == alien3u || romname == ptblank2 || romname == ptblank2ua || romname == ghlpanic || romname == spacegun || romname == spacegunu ||
				romname == spacegunj || romname == term2 || romname == term2la1 || romname == term2la2 || romname == term2la3 || romname == term2lg1 || romname == rchase || romname == rchasej || 
				romname == lghost || romname == lghostd || romname == lghostu || romname == lghostud || romname == lghostj || romname == timecris || romname == timecrisa || romname == othunder || 
				romname == othundero || romname == othunderuo || romname == othunderu || romname == othunderj || romname == opwolf || romname == opwolfp || romname == opwolfj || romname == opwolfu ||
				 romname == opwolfa || romname == orunners || romname == orunnersu || romname == orunnersj || romname == toutrun || romname == toutrund || romname == toutrunj || romname == toutrunjd ||
				romname == undrfire || romname == undrfireu || romname == undrfirej || romname == cbombers || romname == cbombersj || romname == cbombersp)				
			{
				RunningFFB = "EffectActive";
			}

			if (romname == outrunra || romname == outrun || romname == outruneh)
			{
				RunningFFB = "OutrunActive";
			}

			if (romname == pdrift || romname == pdrifta || romname == pdrifte || romname == pdriftj || romname == pdriftl)
			{
				RunningFFB = "PDriftActive";
			}

			if (romname == aburner2 || romname == aburner2g || romname == cischeat || romname == f1gpstar || romname == f1gpstaro || romname == f1gpstr2)
			{
				RunningFFB = "EffectActive2";
			}

			if ((RunningFFB != NULL) && (RunningFFB[0] != '\0'))
			{
				RomGameName = true;
			}
		}
	}

	if (!EmuName)
	{
		//Select code to run via emulator name using partial window title to avoid issues with FPS showing etc
		const TCHAR MAMEstring[] = TEXT("MAME");
		EnumWindows(FindWindowBySubstr, (LPARAM)MAMEstring);

		const TCHAR Supermodelstring[] = TEXT("Supermodel");
		EnumWindows(FindWindowBySubstr, (LPARAM)Supermodelstring);

		if (!EnumWindows(FindWindowBySubstr, (LPARAM)MAMEstring))
		{
			EmulatorName = "MAME";
		}

		if (!EnumWindows(FindWindowBySubstr, (LPARAM)Supermodelstring))
		{
			EmulatorName = "Supermodel";
		}

		Emulator = new char[256]; // Emulator name
		sprintf(Emulator, "%s", EmulatorName);

		if ((EmulatorName != NULL) && (EmulatorName[0] != '\0'))
		{
			EmuName = true;
		}
	}
	
	if (RomGameName && EmuName)
	{
		if (RunningFFB == Daytona2Active) //Daytona 2,Scud Race,Le Mans 24
		{
			if (Emulator == Supermodel)
			{
				if (name == RawDrive)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x09) && (stateFFB < 0x10))
				{
					//Spring
					double percentForce = (stateFFB - 9) / 16.0;
					triggers->Spring(percentForce);
				}

				if ((stateFFB > 0x1F) && (stateFFB < 0x30))
				{
					//Clutch
					double percentForce = (stateFFB - 31) / 16.0;
					triggers->Friction(percentForce);
				}

				if ((stateFFB > 0x2F) && (stateFFB < 0x40))
				{
					//Centering
					double percentForce = (stateFFB - 47) / 16.0;
					triggers->Rumble(percentForce, percentForce, 100);
					triggers->Sine(40, 0, percentForce);
				}

				if ((stateFFB > 0x3F) && (stateFFB < 0x50))
				{
					//Uncentering
					double percentForce = (stateFFB - 63) / 16.0;
					triggers->Rumble(percentForce, percentForce, 100);
					triggers->Sine(40, 0, percentForce);
				}

				if ((stateFFB > 0x4F) && (stateFFB < 0x60))
				{
					//Roll Right
					double percentForce = (stateFFB - 79) / 16.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((stateFFB > 0x5F) && (stateFFB < 0x70))
				{
					//Roll Left
					double percentForce = (stateFFB - 95) / 16.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}

				//Test Menu
				if (stateFFB == 0x80)
				{
					triggers->Rumble(0, 0, 0);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, 0);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, 0);
				}
				else if (stateFFB == 0x81)
				{
					triggers->Rumble(0.5, 0, 100);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, 0.5);
				}
				else if (stateFFB == 0x82)
				{
					triggers->Rumble(0, 0.5, 100);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, 0.5);
				}
			}
		}

		if (RunningFFB == DirtDevilsActive) //Dirt Devils
		{
			if (Emulator == Supermodel)
			{
				if (name == RawDrive)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if (stateFFB == 0x10)
				{
					double percentForce = 0.7;
					triggers->Spring(percentForce);
				}

				if ((stateFFB == 0x27) || (stateFFB == 0x30))
				{
					DirtDevilSine = false;
				}

				if (stateFFB == 0x2F)
				{
					DirtDevilSine = true;
				}

				if (DirtDevilSine)
				{
					double percentForce = (stateFFB - 31) / 16.0;
					triggers->Sine(60, 0, percentForce);
					triggers->Rumble(percentForce, percentForce, 100);
				}
			}
		}

		if (RunningFFB == Srally2Active) //Sega Rally 2, Emergency Call Ambulance
		{
			if (Emulator == Supermodel)
			{
				if (name == RawDrive)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x00) && (stateFFB < 0x26))
				{
					double percentForce = (stateFFB) / 37.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((stateFFB > 0x3F) && (stateFFB < 0x66))
				{
					double percentForce = (stateFFB - 64) / 37.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}

		if (RunningFFB == VirtuaRacingActive) //Virtua Racing
		{
			if (Emulator == MAME)
			{
				if (name == digit0)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB == 0x03) || (stateFFB == 0x07) || (stateFFB == 0x09) || (stateFFB == 0x10))
				{
					if (stateFFB == 0x07)
					{
						DontSineUntilRaceStart = true;
					}
					if (stateFFB == 0x09)
					{
						DontSineUntilRaceStart = false;
					}
					//Spring
					double percentForce = 0.8;
					triggers->Spring(percentForce);
				}

				else if ((stateFFB == 0x20) || (stateFFB == 0x28))
				{
					//Clutch
					double percentForce = 0.4;
					triggers->Friction(percentForce);
				}

				else if ((stateFFB > 0x2F) && (stateFFB < 0x40))
				{
					//Centering
					double percentForce = (stateFFB - 47) / 11.0;
					triggers->Spring(percentForce);
				}

				else if ((stateFFB == 0x40) || (stateFFB == 0x46) || (stateFFB == 0x4A))
				{
					if (stateFFB == 0x40)
					{
						//Uncentering
						double percentForce = 0.4;
						triggers->Rumble(percentForce, percentForce, 100);
						triggers->Sine(70, 30, percentForce);
					}
					else
					{
						if (DontSineUntilRaceStart)
						{
							//Uncentering
							double percentForce = 0.4;
							triggers->Rumble(percentForce, percentForce, 100);
							triggers->Sine(70, 30, percentForce);
						}
					}
				}

				else if ((stateFFB == 0x50) || (stateFFB == 0x5F))
				{
					//Roll Left
					double percentForce = 0.5;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((stateFFB == 0x60) || (stateFFB == 0x6F))
				{
					//Roll Right
					double percentForce = 0.5;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}			
		}

		if (RunningFFB == SanFranActive) //San Francisco Rush
		{
			if (Emulator == MAME)
			{
				if (name == wheel)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x80) && (stateFFB < 0x100))
				{
					double percentForce = (256 - stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((stateFFB > 0x00) && (stateFFB < 0x80))
				{
					double percentForce = (stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}

		if (RunningFFB == CrusnWldActive) //Cruis'n World
		{
			if (Emulator == MAME)
			{
				if (name == wheel)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x80) && (stateFFB < 0x100))
				{
					double percentForce = (256 - stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((stateFFB > 0x00) && (stateFFB < 0x80))
				{
					double percentForce = (stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}

		if (RunningFFB == OffroadChallengeActive) //Off Road Challenge
		{
			if (Emulator == MAME)
			{
				if (name == wheel)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x80) && (stateFFB < 0x100))
				{
					double percentForce = (256 - stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((stateFFB > 0x00) && (stateFFB < 0x80))
				{
					double percentForce = (stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}

		if (RunningFFB == CrusnUSAActive) //Crusn USA
		{
			if (Emulator == MAME)
			{
				if (name == wheel)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x80) && (stateFFB < 0x100))
				{
					double percentForce = (256 - stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
				else if ((stateFFB > 0x00) && (stateFFB < 0x80))
				{
					double percentForce = (stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
			}
		}

		if (RunningFFB == CalSpeedActive) //California Speed
		{
			if (Emulator == MAME)
			{
				if (name == wheel)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x80) && (stateFFB < 0x100))
				{
					double percentForce = (256 - stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((stateFFB > 0x00) && (stateFFB < 0x80))
				{
					double percentForce = (stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
			}
		}

		if (RunningFFB == EffectActive) //Shaker Motor/LightGun Games
		{
			if (Emulator == MAME)
			{
				if (name == MA_Steering_Wheel_motor || name == Player1_Recoil_Piston || name == Player1_Gun_Recoil || name == Left_Gun_Recoil || name == P1_Gun_Recoil || name == mcuout1 ||
					name == upright_wheel_motor || name == Vibration_motor || name == P1_gun_recoil || name == Wheel_vibration)
				{
					helpers->log("P1 value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect1 = false;
					}

					stateFFB = newstateFFB;
				}

				if (name == MB_Steering_Wheel_motor || name == Player2_Recoil_Piston || name == Player2_Gun_Recoil || name == Right_Gun_Recoil || name == P2_Gun_Recoil || name == P2_gun_recoil)
				{
					helpers->log("P2 value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect2 = false;
					}

					stateFFBDevice2 = newstateFFB;
				}

				if (name == Player3_Gun_Recoil || name == P3_Gun_Recoil)
				{
					helpers->log("P3 value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect3 = false;
					}

					stateFFBDevice3 = newstateFFB;
				}

				if (stateFFB == 0x01)
				{
					Effect1 = true;
				}
				else
				{
					Effect1 = false;
				}

				if (stateFFBDevice2 == 0x01)
				{
					Effect2 = true;
				}
				else
				{
					Effect2 = false;
				}

				if (stateFFBDevice3 == 0x01)
				{
					Effect3 = true;
				}
				else
				{
					Effect3 = false;
				}

				if (Effect1)
				{
					triggers->Sine(SinePeriod, SineFadePeriod, SineStrength / 100.0);
					triggers->Rumble(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
				}

				if (!Effect1)
				{
					triggers->Sine(0, 0, 0);
					triggers->Rumble(0, 0, 0);
				}

				if (Effect2)
				{
					triggers->SineDevice2(SinePeriod, SineFadePeriod, SineStrength / 100.0);
					triggers->RumbleDevice2(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
				}

				if (!Effect2)
				{
					triggers->SineDevice2(0, 0, 0);
					triggers->RumbleDevice2(0, 0, 0);
				}

				if (Effect3)
				{
					triggers->SineDevice3(SinePeriod, SineFadePeriod, SineStrength / 100.0);
					triggers->RumbleDevice3(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
				}

				if (!Effect3)
				{
					triggers->SineDevice3(0, 0, 0);
					triggers->RumbleDevice3(0, 0, 0);
				}
			}
		}

		if (RunningFFB == EffectActive2) //Afterburner,Cisco Heat,F1 GpStar            //Keep seperate as names are Lamp1/led2 and could possibly interfere with other outputs
		{
			if (Emulator == MAME)
			{
				if ( name == lamp1 || name == led2)
				{
					helpers->log("P1 value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect1 = false;
					}

					stateFFB = newstateFFB;
				}

				if (stateFFB == 0x01)
				{
					Effect1 = true;
				}
				else
				{
					Effect1 = false;
				}

				if (Effect1)
				{
					triggers->Sine(SinePeriod, SineFadePeriod, SineStrength / 100.0);
					triggers->Rumble(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
				}

				if (!Effect1)
				{
					triggers->Sine(0, 0, 0);
					triggers->Rumble(0, 0, 0);
				}
			}
		}

		if (RunningFFB == OutrunActive)
		{
			if (Emulator == MAME)
			{
				if (name == Bank_Motor_Direction)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB != 0)
					{
						stateFFB = newstateFFB;
					}				
				}

				if (name == Vibration_motor)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect1 = false;
					}

					stateFFB2 = newstateFFB;
				}

				if (name == Bank_Motor_Speed)
				{
					stateFFB3 = newstateFFB;					
				}

				if (Motion)
				{
					if (stateFFB == 0x01)
					{
						double percentForce = (1 + stateFFB3) / 8.0;
						triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
					}
					if (stateFFB == 0x02)
					{
						double percentForce = (1 + stateFFB3) / 8.0;
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}
				}
				
				if (stateFFB == 1)
				{
					Motion = true;
					MotionFalse = false;
				}

				if (stateFFB2 == 1)
				{
					Motion = false;
				}

				if (StopConstant == 255)
				{
					MotionFalse = true;
				}

				if (MotionFalse)
				{
					triggers->Constant(constants->DIRECTION_FROM_LEFT, 0);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, 0);
					Motion = false;
					StopConstant = 0;
					MotionFalse = false;				
				}

				if (!Motion)
				{
					
					if (stateFFB2 == 0x01)
					{
						Effect1 = true;
					}
					else
					{
						Effect1 = false;
					}

					if (Effect1)
					{
						triggers->Sine(SinePeriod, SineFadePeriod, SineStrength / 100.0);
						triggers->Rumble(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
					}

					if (!Effect1)
					{
						triggers->Sine(0, 0, 0);
						triggers->Rumble(0, 0, 0);
					}
				}			
			}
		}

		if (RunningFFB == PDriftActive)
		{
			if (Emulator == MAME)
			{
				if (name == bank_motor_position)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if (name == vibration_motor)
				{
					stateFFB2 = newstateFFB;
				}

				if (name == upright_wheel_motor)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					if (newstateFFB == 0)
					{
						Effect1 = false;
					}

					stateFFB3 = newstateFFB;
				}

				if (Motion)
				{
					if ((stateFFB > 0x00) && (stateFFB < 0x04))
					{
						double percentForce = (4 - stateFFB) / 3.0;
						triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
					}
					else if ((stateFFB > 0x04) && (stateFFB < 0x08))
					{
						double percentForce = (stateFFB - 4) / 3.0;
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}

					if (stateFFB2 >= 0)
					{
						double percentForce = stateFFB2 / 7.0;
						triggers->Sine(60, 0, percentForce / 3.0);
					}
				}

				if (stateFFB == 4)
				{
					Motion = true;
					MotionFalse = false;
				}

				if (stateFFB3 == 1)
				{
					Motion = false;
				}

				if (StopConstant == 255)
				{
					MotionFalse = true;
				}

				if (MotionFalse)
				{
					triggers->Constant(constants->DIRECTION_FROM_LEFT, 0);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, 0);
					Motion = false;
					StopConstant = 0;
					MotionFalse = false;
				}

				if (!Motion)
				{
					if (stateFFB3 == 0x01)
					{
						Effect1 = true;
					}
					else
					{
						Effect1 = false;
					}

					if (Effect1)
					{
						triggers->Sine(SinePeriod, SineFadePeriod, SineStrength / 100.0);
						triggers->Rumble(RumbleStrengthLeftMotor / 100.0, RumbleStrengthRightMotor / 100.0, 100);
					}

					if (!Effect1)
					{
						triggers->Sine(0, 0, 0);
						triggers->Rumble(0, 0, 0);
					}
				}
			}
		}

		if (RunningFFB == SanFran2049Active) //San Fran 2049
		{
			if (Emulator == MAME)
			{
				if (name == wheel)
				{
					helpers->log("got value: ");
					std::string ffs = std::to_string(newstateFFB);
					helpers->log((char*)ffs.c_str());

					stateFFB = newstateFFB;
				}

				if ((stateFFB > 0x80) && (stateFFB < 0x100))
				{
					double percentForce = (256 - stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(percentForce, 0, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
				}
				else if ((stateFFB > 0x00) && (stateFFB < 0x80))
				{
					double percentForce = (stateFFB) / 127.0;
					double percentLength = 100;
					triggers->Rumble(0, percentForce, percentLength);
					triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
				}
			}
		}

		if (RunningFFB == HardDrivinActive) //Hard Drivin
		{
			if (Emulator == MAME)
			{
				if (!HardDrivinFrame)
				{
					HardDrivinFrame = true;
				}
			
				if ((frame & 7) == 4)
				{
					HardDrivinFFB = (vals[0] & 15) + ((vals[3] & 7) << 5);

					if ((vals[1] & 0xF0) == 0xF0)
					{
						HardDrivinFFB |= 0x10;
					}
					 
					if ((vals[2] & 0xF0) == 0xF0)
					{
						HardDrivinFFB = -HardDrivinFFB;
					}

					helpers->log("got value: ");
					std::string ffs = std::to_string(HardDrivinFFB);
					helpers->log((char*)ffs.c_str());			

					static char test[256];
					memset(test, 0, 256);
					sprintf(test, "hex print: %d", HardDrivinFFB);
					OutputDebugStringA(test);

/*					if (HardDrivinFFB > 0)
					{
						double percentForce = HardDrivinFFB / 100.0;
						double percentLength = 100;
						triggers->Rumble(percentForce, 0, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
					}

					if (HardDrivinFFB < 0)
					{
						HardDrivinFFB = -HardDrivinFFB;
						double percentForce = HardDrivinFFB / 100.0;
						double percentLength = 100;
						triggers->Rumble(0, percentForce, percentLength);
						triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
					}	*/				
				}
			}
		}
	}
}