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
#include "SDL.h"
extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;
extern SDL_Haptic* ControllerHaptic2;
extern SDL_Haptic* haptic2;

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static int MinimumSpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinimumSpringStrength"), 0, settingsFilename);

static bool init = false;

HINSTANCE hInstance;
HINSTANCE hPrevInstance;
LPSTR lpCmdLine;
int nCmdShow;

const char* nameFFB;
int newstateFFB;
int stateFFB;
int stateFFBDevice2;

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
	HINSTANCE ProcDLL;
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

	hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
		8, 8, 488, 464, hWnd, NULL, GetModuleHandle(NULL), NULL);

	if (hEdit == NULL)
		MessageBox(hWnd, L"Could not create edit box.", L"Error", MB_OK | MB_ICONERROR);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

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

	return 1;
}

int __stdcall mame_copydata(int id, const char* name)
{
	WCHAR buf[256];

	wsprintf(buf, L"id %d = '%S'\r\n", id, name);

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

	return 1;
}

int __stdcall mame_output(const char* name, int value)
{
	WCHAR buf[256];

	wsprintf(buf, L"output: name=%S value=%d\r\n", name, value);
	AppendTextToEditCtrl(hEdit, buf);

	return 1;
}

DWORD WINAPI ThreadForLoop(LPVOID lpParam)
{
	WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return 0;
}

static int sanfran(int ffsan) {
	switch (ffsan) {

	case 0xFF:
		return 232;
	case 0xFE:
		return 231;
	case 0xFD:
		return 230;
	case 0xFC:
		return 229;
	case 0xFB:
		return 228;
	case 0xFA:
		return 227;
	case 0xF9:
		return 226;
	case 0xF8:
		return 225;
	case 0xF7:
		return 224;
	case 0xF6:
		return 223;
	case 0xF5:
		return 222;
	case 0xF4:
		return 221;
	case 0xF3:
		return 220;
	case 0xF2:
		return 219;
	case 0xF1:
		return 218;
	case 0xEF:
		return 217;
	case 0xEE:
		return 216;
	case 0xED:
		return 215;
	case 0xEC:
		return 214;
	case 0xEB:
		return 213;
	case 0xEA:
		return 212;
	case 0xE9:
		return 211;
	case 0xE8:
		return 210;
	case 0xE7:
		return 209;
	case 0xE6:
		return 208;
	case 0xE5:
		return 207;
	case 0xE4:
		return 206;
	case 0xE3:
		return 205;
	case 0xE2:
		return 204;
	case 0xE1:
		return 203;
	case 0xDF:
		return 202;
	case 0xDE:
		return 201;
	case 0xDD:
		return 200;
	case 0xDC:
		return 199;
	case 0xDB:
		return 198;
	case 0xDA:
		return 197;
	case 0xD9:
		return 196;
	case 0xD8:
		return 195;
	case 0xD7:
		return 194;
	case 0xD6:
		return 193;
	case 0xD5:
		return 192;
	case 0xD4:
		return 191;
	case 0xD3:
		return 190;
	case 0xD2:
		return 189;
	case 0xD1:
		return 188;
	case 0xCF:
		return 187;
	case 0xCE:
		return 186;
	case 0xCD:
		return 185;
	case 0xCC:
		return 184;
	case 0xCB:
		return 183;
	case 0xCA:
		return 182;
	case 0xC9:
		return 181;
	case 0xC8:
		return 180;
	case 0xC7:
		return 179;
	case 0xC6:
		return 178;
	case 0xC5:
		return 177;
	case 0xC4:
		return 176;
	case 0xC3:
		return 175;
	case 0xC2:
		return 174;
	case 0xC1:
		return 173;
	case 0xBF:
		return 172;
	case 0xBE:
		return 171;
	case 0xBD:
		return 170;
	case 0xBC:
		return 169;
	case 0xBB:
		return 168;
	case 0xBA:
		return 167;
	case 0xB9:
		return 166;
	case 0xB8:
		return 165;
	case 0xB7:
		return 164;
	case 0xB6:
		return 163;
	case 0xB5:
		return 162;
	case 0xB4:
		return 161;
	case 0xB3:
		return 160;
	case 0xB2:
		return 159;
	case 0xB1:
		return 158;
	case 0xAF:
		return 157;
	case 0xAE:
		return 156;
	case 0xAD:
		return 155;
	case 0xAC:
		return 154;
	case 0xAB:
		return 153;
	case 0xAA:
		return 152;
	case 0xA9:
		return 151;
	case 0xA8:
		return 150;
	case 0xA7:
		return 149;
	case 0xA6:
		return 148;
	case 0xA5:
		return 147;
	case 0xA4:
		return 146;
	case 0xA3:
		return 145;
	case 0xA2:
		return 144;
	case 0xA1:
		return 143;
	case 0x9F:
		return 142;
	case 0x9E:
		return 141;
	case 0x9D:
		return 140;
	case 0x9C:
		return 139;
	case 0x9B:
		return 138;
	case 0x9A:
		return 137;
	case 0x99:
		return 136;
	case 0x98:
		return 135;
	case 0x97:
		return 134;
	case 0x96:
		return 133;
	case 0x95:
		return 132;
	case 0x94:
		return 131;
	case 0x93:
		return 130;
	case 0x92:
		return 129;
	case 0x91:
		return 128;
	case 0x8F:
		return 127;
	case 0x8E:
		return 126;
	case 0x8D:
		return 125;
	case 0x8C:
		return 124;
	case 0x8B:
		return 123;
	case 0x8A:
		return 122;
	case 0x89:
		return 121;
	case 0x88:
		return 120;
	case 0x87:
		return 119;
	case 0x86:
		return 118;
	case 0x85:
		return 117;
	case 0x84:
		return 116;
	case 0x83:
		return 115;
	case 0x82:
		return 114;
	case 0x81:
		return 113;

	case 0x7F:
		return 112;
	case 0x7E:
		return 111;
	case 0x7D:
		return 110;
	case 0x7C:
		return 109;
	case 0x7B:
		return 108;
	case 0x7A:
		return 107;
	case 0x79:
		return 106;
	case 0x78:
		return 105;
	case 0x77:
		return 104;
	case 0x76:
		return 103;
	case 0x75:
		return 102;
	case 0x74:
		return 101;
	case 0x73:
		return 100;
	case 0x72:
		return 99;
	case 0x71:
		return 98;
	case 0x6F:
		return 97;
	case 0x6E:
		return 96;
	case 0x6D:
		return 95;
	case 0x6C:
		return 94;
	case 0x6B:
		return 93;
	case 0x6A:
		return 92;
	case 0x69:
		return 91;
	case 0x68:
		return 90;
	case 0x67:
		return 89;
	case 0x66:
		return 88;
	case 0x65:
		return 87;
	case 0x64:
		return 86;
	case 0x63:
		return 85;
	case 0x62:
		return 84;
	case 0x61:
		return 83;
	case 0x5F:
		return 82;
	case 0x5E:
		return 81;
	case 0x5D:
		return 80;
	case 0x5C:
		return 79;
	case 0x5B:
		return 78;
	case 0x5A:
		return 77;
	case 0x59:
		return 76;
	case 0x58:
		return 75;
	case 0x57:
		return 74;
	case 0x56:
		return 73;
	case 0x55:
		return 72;
	case 0x54:
		return 71;
	case 0x53:
		return 70;
	case 0x52:
		return 69;
	case 0x51:
		return 68;
	case 0x4F:
		return 67;
	case 0x4E:
		return 66;
	case 0x4D:
		return 65;
	case 0x4C:
		return 64;
	case 0x4B:
		return 63;
	case 0x4A:
		return 62;
	case 0x49:
		return 61;
	case 0x48:
		return 60;
	case 0x47:
		return 59;
	case 0x46:
		return 58;
	case 0x45:
		return 57;
	case 0x44:
		return 56;
	case 0x43:
		return 55;
	case 0x42:
		return 54;
	case 0x41:
		return 53;
	case 0x3F:
		return 52;
	case 0x3E:
		return 51;
	case 0x3D:
		return 50;
	case 0x3C:
		return 49;
	case 0x3B:
		return 48;
	case 0x3A:
		return 47;
	case 0x39:
		return 46;
	case 0x38:
		return 45;
	case 0x37:
		return 44;
	case 0x36:
		return 43;
	case 0x35:
		return 42;
	case 0x34:
		return 41;
	case 0x33:
		return 40;
	case 0x32:
		return 39;
	case 0x31:
		return 38;
	case 0x29:
		return 37;
	case 0x28:
		return 36;
	case 0x27:
		return 35;
	case 0x26:
		return 34;
	case 0x25:
		return 33;
	case 0x24:
		return 32;
	case 0x23:
		return 31;
	case 0x22:
		return 30;
	case 0x21:
		return 29;
	case 0x1F:
		return 28;
	case 0x1E:
		return 27;
	case 0x1D:
		return 26;
	case 0x1C:
		return 25;
	case 0x1B:
		return 24;
	case 0x1A:
		return 23;
	case 0x19:
		return 22;
	case 0x18:
		return 21;
	case 0x17:
		return 20;
	case 0x16:
		return 19;
	case 0x15:
		return 18;
	case 0x14:
		return 17;
	case 0x13:
		return 16;
	case 0x12:
		return 15;
	case 0x11:
		return 14;
	case 0x0F:
		return 13;
	case 0x0E:
		return 12;
	case 0x0D:
		return 11;
	case 0x0C:
		return 10;
	case 0x0B:
		return 9;
	case 0x0A:
		return 8;
	case 0x09:
		return 7;
	case 0x08:
		return 6;
	case 0x07:
		return 5;
	case 0x06:
		return 4;
	case 0x05:
		return 3;
	case 0x04:
		return 2;
	case 0x03:
		return 1;
	default:
		return 0;
	}
}

static int crusnwld(int ffcru) {
	switch (ffcru) {

	case 0xFF:
		return 225;
	case 0xFE:
		return 224;
	case 0xFD:
		return 223;
	case 0xFC:
		return 222;
	case 0xFB:
		return 221;
	case 0xFA:
		return 220;
	case 0xF9:
		return 219;
	case 0xF8:
		return 218;
	case 0xF7:
		return 217;
	case 0xF6:
		return 216;
	case 0xF5:
		return 215;
	case 0xF4:
		return 214;
	case 0xF3:
		return 213;
	case 0xF2:
		return 212;
	case 0xF1:
		return 211;
	case 0xEF:
		return 210;
	case 0xEE:
		return 209;
	case 0xED:
		return 208;
	case 0xEC:
		return 207;
	case 0xEB:
		return 206;
	case 0xEA:
		return 205;
	case 0xE9:
		return 204;
	case 0xE8:
		return 203;
	case 0xE7:
		return 202;
	case 0xE6:
		return 201;
	case 0xE5:
		return 200;
	case 0xE4:
		return 199;
	case 0xE3:
		return 198;
	case 0xE2:
		return 197;
	case 0xE1:
		return 196;
	case 0xDF:
		return 195;
	case 0xDE:
		return 194;
	case 0xDD:
		return 193;
	case 0xDC:
		return 192;
	case 0xDB:
		return 191;
	case 0xDA:
		return 190;
	case 0xD9:
		return 189;
	case 0xD8:
		return 188;
	case 0xD7:
		return 187;
	case 0xD6:
		return 186;
	case 0xD5:
		return 185;
	case 0xD4:
		return 184;
	case 0xD3:
		return 183;
	case 0xD2:
		return 182;
	case 0xD1:
		return 181;
	case 0xCF:
		return 180;
	case 0xCE:
		return 179;
	case 0xCD:
		return 178;
	case 0xCC:
		return 177;
	case 0xCB:
		return 176;
	case 0xCA:
		return 175;
	case 0xC9:
		return 174;
	case 0xC7:
		return 173;
	case 0xC6:
		return 172;
	case 0xC5:
		return 171;
	case 0xC3:
		return 170;
	case 0xBF:
		return 169;
	case 0xBE:
		return 168;
	case 0xBD:
		return 167;
	case 0xBC:
		return 166;
	case 0xBB:
		return 165;
	case 0xBA:
		return 164;
	case 0xB9:
		return 163;
	case 0xB8:
		return 162;
	case 0xB7:
		return 161;
	case 0xB6:
		return 160;
	case 0xB5:
		return 159;
	case 0xB4:
		return 158;
	case 0xB3:
		return 157;
	case 0xB2:
		return 156;
	case 0xB1:
		return 155;
	case 0xAF:
		return 154;
	case 0xAE:
		return 153;
	case 0xAD:
		return 152;
	case 0xAC:
		return 151;
	case 0xAB:
		return 150;
	case 0xAA:
		return 149;
	case 0xA9:
		return 148;
	case 0xA8:
		return 147;
	case 0xA7:
		return 146;
	case 0xA6:
		return 145;
	case 0xA5:
		return 144;
	case 0xA4:
		return 143;
	case 0xA3:
		return 142;
	case 0xA2:
		return 141;
	case 0xA1:
		return 140;
	case 0x9F:
		return 139;
	case 0x9E:
		return 138;
	case 0x9D:
		return 137;
	case 0x9C:
		return 136;
	case 0x9B:
		return 135;
	case 0x9A:
		return 134;
	case 0x99:
		return 133;
	case 0x98:
		return 132;
	case 0x97:
		return 131;
	case 0x96:
		return 130;
	case 0x95:
		return 129;
	case 0x94:
		return 128;
	case 0x93:
		return 127;
	case 0x92:
		return 126;
	case 0x91:
		return 125;
	case 0x8F:
		return 124;
	case 0x8E:
		return 123;
	case 0x8D:
		return 122;
	case 0x8C:
		return 121;
	case 0x8B:
		return 120;
	case 0x8A:
		return 119;
	case 0x89:
		return 118;
	case 0x88:
		return 117;
	case 0x87:
		return 116;
	case 0x86:
		return 115;
	case 0x85:
		return 114;
	case 0x84:
		return 113;
	case 0x83:
		return 112;
	case 0x82:
		return 111;


	case 0x7E:
		return 110;
	case 0x7D:
		return 109;
	case 0x7C:
		return 108;
	case 0x7B:
		return 107;
	case 0x7A:
		return 106;
	case 0x79:
		return 105;
	case 0x78:
		return 104;
	case 0x77:
		return 103;
	case 0x76:
		return 102;
	case 0x75:
		return 101;
	case 0x74:
		return 100;
	case 0x73:
		return 99;
	case 0x72:
		return 98;
	case 0x71:
		return 97;
	case 0x6F:
		return 96;
	case 0x6E:
		return 95;
	case 0x6D:
		return 94;
	case 0x6C:
		return 93;
	case 0x6B:
		return 92;
	case 0x6A:
		return 91;
	case 0x69:
		return 90;
	case 0x68:
		return 89;
	case 0x67:
		return 88;
	case 0x66:
		return 87;
	case 0x65:
		return 86;
	case 0x64:
		return 85;
	case 0x63:
		return 84;
	case 0x62:
		return 83;
	case 0x61:
		return 82;
	case 0x5F:
		return 81;
	case 0x5E:
		return 80;
	case 0x5D:
		return 79;
	case 0x5C:
		return 78;
	case 0x5B:
		return 77;
	case 0x5A:
		return 76;
	case 0x59:
		return 75;
	case 0x58:
		return 74;
	case 0x57:
		return 73;
	case 0x56:
		return 72;
	case 0x55:
		return 71;
	case 0x54:
		return 70;
	case 0x53:
		return 69;
	case 0x52:
		return 68;
	case 0x51:
		return 67;
	case 0x4F:
		return 66;
	case 0x4E:
		return 65;
	case 0x4D:
		return 64;
	case 0x4C:
		return 63;
	case 0x4B:
		return 62;
	case 0x4A:
		return 61;
	case 0x49:
		return 60;
	case 0x48:
		return 59;
	case 0x47:
		return 58;
	case 0x46:
		return 57;
	case 0x45:
		return 56;
	case 0x44:
		return 55;
	case 0x43:
		return 54;
	case 0x42:
		return 53;
	case 0x41:
		return 52;
	case 0x3F:
		return 51;
	case 0x3E:
		return 50;
	case 0x3D:
		return 49;
	case 0x3C:
		return 48;
	case 0x3B:
		return 47;
	case 0x3A:
		return 46;
	case 0x39:
		return 45;
	case 0x38:
		return 44;
	case 0x37:
		return 43;
	case 0x36:
		return 42;
	case 0x35:
		return 41;
	case 0x34:
		return 40;
	case 0x33:
		return 39;
	case 0x32:
		return 38;
	case 0x31:
		return 37;
	case 0x29:
		return 36;
	case 0x28:
		return 35;
	case 0x27:
		return 34;
	case 0x26:
		return 33;
	case 0x25:
		return 32;
	case 0x24:
		return 31;
	case 0x23:
		return 30;
	case 0x22:
		return 29;
	case 0x21:
		return 28;
	case 0x1F:
		return 27;
	case 0x1E:
		return 26;
	case 0x1D:
		return 25;
	case 0x1C:
		return 24;
	case 0x1B:
		return 23;
	case 0x1A:
		return 22;
	case 0x19:
		return 21;
	case 0x18:
		return 20;
	case 0x17:
		return 19;
	case 0x16:
		return 18;
	case 0x15:
		return 17;
	case 0x14:
		return 16;
	case 0x13:
		return 15;
	case 0x12:
		return 14;
	case 0x11:
		return 13;
	case 0x0F:
		return 12;
	case 0x0E:
		return 11;
	case 0x0D:
		return 10;
	case 0x0C:
		return 9;
	case 0x0B:
		return 8;
	case 0x0A:
		return 7;
	case 0x09:
		return 6;
	case 0x07:
		return 5;
	case 0x06:
		return 4;
	case 0x05:
		return 3;
	case 0x03:
		return 2;
	case 0x01:
		return 1;
	default:
		return 0;
	}
}

static int crusnusa(int ffusa) {
	switch (ffusa) {

	case 0xFF:
		return 214;
	case 0xFE:
		return 213;
	case 0xFC:
		return 212;
	case 0xFB:
		return 211;
	case 0xFA:
		return 210;
	case 0xF9:
		return 209;
	case 0xF8:
		return 208;
	case 0xF7:
		return 207;
	case 0xF6:
		return 206;
	case 0xF5:
		return 205;
	case 0xF4:
		return 204;
	case 0xF3:
		return 203;
	case 0xF2:
		return 202;
	case 0xF1:
		return 201;
	case 0xEF:
		return 200;
	case 0xEE:
		return 199;
	case 0xED:
		return 198;
	case 0xEC:
		return 197;
	case 0xEB:
		return 196;
	case 0xEA:
		return 195;
	case 0xE9:
		return 194;
	case 0xE8:
		return 193;
	case 0xE7:
		return 192;
	case 0xE6:
		return 191;
	case 0xE5:
		return 190;
	case 0xE4:
		return 189;
	case 0xE3:
		return 188;
	case 0xE2:
		return 187;
	case 0xE1:
		return 186;
	case 0xDF:
		return 185;
	case 0xDE:
		return 184;
	case 0xDD:
		return 183;
	case 0xDC:
		return 182;
	case 0xDB:
		return 181;
	case 0xDA:
		return 180;
	case 0xD9:
		return 179;
	case 0xD8:
		return 178;
	case 0xD7:
		return 177;
	case 0xD3:
		return 176;
	case 0xD2:
		return 175;
	case 0xD1:
		return 174;
	case 0xCF:
		return 173;
	case 0xCE:
		return 172;
	case 0xCD:
		return 171;
	case 0xCC:
		return 170;
	case 0xCB:
		return 169;
	case 0xCA:
		return 168;
	case 0xC9:
		return 167;
	case 0xC7:
		return 166;
	case 0xC6:
		return 165;
	case 0xC5:
		return 164;
	case 0xC3:
		return 163;
	case 0xBF:
		return 162;
	case 0xBE:
		return 161;
	case 0xBD:
		return 160;
	case 0xBC:
		return 159;
	case 0xBB:
		return 158;
	case 0xBA:
		return 157;
	case 0xB9:
		return 156;
	case 0xB8:
		return 155;
	case 0xB7:
		return 154;
	case 0xB6:
		return 153;
	case 0xB5:
		return 152;
	case 0xB4:
		return 151;
	case 0xB3:
		return 150;
	case 0xB2:
		return 149;
	case 0xB1:
		return 148;
	case 0xAF:
		return 147;
	case 0xAE:
		return 146;
	case 0xAD:
		return 145;
	case 0xAC:
		return 144;
	case 0xAB:
		return 143;
	case 0xAA:
		return 142;
	case 0xA9:
		return 141;
	case 0xA8:
		return 140;
	case 0xA7:
		return 139;
	case 0xA6:
		return 138;
	case 0xA5:
		return 137;
	case 0xA4:
		return 136;
	case 0xA3:
		return 135;
	case 0xA2:
		return 134;
	case 0xA1:
		return 133;
	case 0x9F:
		return 132;
	case 0x9E:
		return 131;
	case 0x9D:
		return 130;
	case 0x9C:
		return 129;
	case 0x9B:
		return 128;
	case 0x9A:
		return 127;
	case 0x99:
		return 126;
	case 0x98:
		return 125;
	case 0x97:
		return 124;
	case 0x96:
		return 123;
	case 0x95:
		return 122;
	case 0x94:
		return 121;
	case 0x93:
		return 120;
	case 0x92:
		return 119;
	case 0x91:
		return 118;
	case 0x8F:
		return 117;
	case 0x8E:
		return 116;
	case 0x8D:
		return 115;
	case 0x8C:
		return 114;
	case 0x8B:
		return 113;
	case 0x8A:
		return 112;
	case 0x89:
		return 111;
	case 0x88:
		return 110;
	case 0x87:
		return 109;
	case 0x86:
		return 108;
	case 0x84:
		return 107;
	case 0x83:
		return 106;
	case 0x82:
		return 105;


	case 0x7E:
		return 104;
	case 0x7D:
		return 103;
	case 0x7C:
		return 102;
	case 0x7B:
		return 101;
	case 0x7A:
		return 100;
	case 0x79:
		return 99;
	case 0x78:
		return 98;
	case 0x77:
		return 97;
	case 0x76:
		return 96;
	case 0x75:
		return 95;
	case 0x74:
		return 94;
	case 0x73:
		return 93;
	case 0x71:
		return 92;
	case 0x6F:
		return 91;
	case 0x6E:
		return 90;
	case 0x6D:
		return 89;
	case 0x6C:
		return 88;
	case 0x6B:
		return 87;
	case 0x6A:
		return 86;
	case 0x69:
		return 85;
	case 0x68:
		return 84;
	case 0x67:
		return 83;
	case 0x66:
		return 82;
	case 0x65:
		return 81;
	case 0x64:
		return 80;
	case 0x63:
		return 79;
	case 0x62:
		return 78;
	case 0x61:
		return 77;
	case 0x5F:
		return 76;
	case 0x5E:
		return 75;
	case 0x5D:
		return 74;
	case 0x5C:
		return 73;
	case 0x5B:
		return 72;
	case 0x5A:
		return 71;
	case 0x59:
		return 70;
	case 0x58:
		return 69;
	case 0x57:
		return 68;
	case 0x56:
		return 67;
	case 0x55:
		return 66;
	case 0x54:
		return 65;
	case 0x53:
		return 64;
	case 0x52:
		return 63;
	case 0x51:
		return 62;
	case 0x4F:
		return 61;
	case 0x4E:
		return 60;
	case 0x4D:
		return 59;
	case 0x4C:
		return 58;
	case 0x4B:
		return 57;
	case 0x4A:
		return 56;
	case 0x49:
		return 55;
	case 0x48:
		return 54;
	case 0x47:
		return 53;
	case 0x46:
		return 52;
	case 0x45:
		return 51;
	case 0x44:
		return 50;
	case 0x43:
		return 49;
	case 0x42:
		return 48;
	case 0x41:
		return 47;
	case 0x3F:
		return 46;
	case 0x3E:
		return 45;
	case 0x3D:
		return 44;
	case 0x3B:
		return 43;
	case 0x3A:
		return 42;
	case 0x39:
		return 41;
	case 0x38:
		return 40;
	case 0x37:
		return 39;
	case 0x36:
		return 38;
	case 0x35:
		return 37;
	case 0x34:
		return 36;
	case 0x33:
		return 35;
	case 0x32:
		return 34;
	case 0x31:
		return 33;
	case 0x29:
		return 32;
	case 0x28:
		return 31;
	case 0x27:
		return 30;
	case 0x26:
		return 29;
	case 0x25:
		return 28;
	case 0x24:
		return 27;
	case 0x23:
		return 26;
	case 0x22:
		return 25;
	case 0x21:
		return 24;
	case 0x1F:
		return 23;
	case 0x1E:
		return 22;
	case 0x1D:
		return 21;
	case 0x1B:
		return 20;
	case 0x1A:
		return 19;
	case 0x19:
		return 18;
	case 0x18:
		return 17;
	case 0x17:
		return 16;
	case 0x16:
		return 15;
	case 0x15:
		return 14;
	case 0x14:
		return 13;
	case 0x13:
		return 12;
	case 0x12:
		return 11;
	case 0x11:
		return 10;
	case 0x0F:
		return 9;
	case 0x0D:
		return 8;
	case 0x0C:
		return 7;
	case 0x0B:
		return 6;
	case 0x09:
		return 5;
	case 0x07:
		return 4;
	case 0x06:
		return 3;
	case 0x03:
		return 2;
	case 0x01:
		return 1;
	default:
		return 0;
	}
}

std::string RawDrive("RawDrive");
std::string digit0("digit0");
std::string wheel("wheel");
std::string Vibration_motor("Vibration_motor");
std::string upright_wheel_motor("upright_wheel_motor");
std::string MA_Steering_Wheel_motor("MA_Steering_Wheel_motor");
std::string MB_Steering_Wheel_motor("MB_Steering_Wheel_motor");

void OutputReading::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (!init)
	{
		CreateThread(NULL, 0, ThreadForLoop, NULL, 0, NULL);
		init = true;
	}

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
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
	}

	char* name = new char[256];
	sprintf(name, "%s", nameFFB);

	//Supermodel Emulator Games
	HWND hWnd1 = FindWindowA(0, ("Supermodel - Daytona USA 2 - Power Edition"));
	HWND hWnd2 = FindWindowA(0, ("Supermodel - Daytona USA 2 - Battle on the Edge"));
	HWND hWnd3 = FindWindowA(0, ("Supermodel - Scud Race"));
	HWND hWnd4 = FindWindowA(0, ("Supermodel - Scud Race Plus"));
	HWND hWnd5 = FindWindowA(0, ("Supermodel - Le Mans 24"));

	//MAME Games
	HWND hWnd10 = FindWindowA(0, ("MAME: Virtua Racing [vr]"));
	HWND hWnd11 = FindWindowA(0, ("MAME: San Francisco Rush (boot rom L 1.0) [sfrush]"));
	HWND hWnd12 = FindWindowA(0, ("MAME: San Francisco Rush: The Rock (boot rom L 1.0, GUTS Oct 6 1997 / MAIN Oct 16 1997) [sfrushrk]"));
	HWND hWnd13 = FindWindowA(0, ("MAME: San Francisco Rush: The Rock (Wavenet, boot rom L 1.38, GUTS Aug 6 1997 / MAIN Aug 5 1997) [sfrushrkwo]"));
	HWND hWnd14 = FindWindowA(0, ("MAME: San Francisco Rush (boot rom L 1.06A) [sfrusha]"));
	HWND hWnd15 = FindWindowA(0, ("MAME: Cruis'n World (rev L2.5) [crusnwld]"));
	HWND hWnd16 = FindWindowA(0, ("MAME: Cruis'n World (rev L2.4) [crusnwld24]"));
	HWND hWnd17 = FindWindowA(0, ("MAME: Cruis'n World (rev L2.3) [crusnwld23]"));
	HWND hWnd18 = FindWindowA(0, ("MAME: Cruis'n World (rev L2.0) [crusnwld20]"));
	HWND hWnd19 = FindWindowA(0, ("MAME: Cruis'n World (rev L1.9) [crusnwld19]"));
	HWND hWnd20 = FindWindowA(0, ("MAME: Cruis'n World (rev L1.7) [crusnwld17]"));
	HWND hWnd21 = FindWindowA(0, ("MAME: Cruis'n World (rev L1.3) [crusnwld13]"));
	HWND hWnd22 = FindWindowA(0, ("MAME: Off Road Challenge (v1.63) [offroadc]"));
	HWND hWnd23 = FindWindowA(0, ("MAME: Off Road Challenge (v1.63) [offroadc]"));
	HWND hWnd24 = FindWindowA(0, ("MAME: Off Road Challenge (v1.40) [offroadc4]"));
	HWND hWnd25 = FindWindowA(0, ("MAME: Off Road Challenge (v1.30) [offroadc3]"));
	HWND hWnd26 = FindWindowA(0, ("MAME: Off Road Challenge (v1.10) [offroadc1]"));
	HWND hWnd27 = FindWindowA(0, ("MAME: Cruis'n USA (rev L4.1) [crusnusa]"));
	HWND hWnd28 = FindWindowA(0, ("MAME: Cruis'n USA (rev L4.0) [crusnusa40]"));
	HWND hWnd29 = FindWindowA(0, ("MAME: Cruis'n USA (rev L2.1) [crusnusa21]"));
	HWND hWnd30 = FindWindowA(0, ("MAME: California Speed (Version 2.1a Apr 17 1998, GUTS 1.25 Apr 17 1998 / MAIN Apr 17 1998) [calspeed]"));
	HWND hWnd31 = FindWindowA(0, ("MAME: California Speed (Version 1.0r8 Mar 10 1998, GUTS Mar 10 1998 / MAIN Mar 10 1998) [calspeeda]"));
	HWND hWnd32 = FindWindowA(0, ("MAME: California Speed (Version 1.0r7a Mar 4 1998, GUTS Mar 3 1998 / MAIN Jan 19 1998) [calspeedb]"));
	HWND hWnd33 = FindWindowA(0, ("MAME: Out Run (sitdown/upright, Rev A) [outrunra]"));
	HWND hWnd34 = FindWindowA(0, ("MAME: Out Run (sitdown/upright, Rev B) [outrun]"));
	HWND hWnd35 = FindWindowA(0, ("MAME: Out Run (sitdown/upright, Rev B) (Enhanced Edition v1.1.0) [outruneh]"));
	HWND hWnd36 = FindWindowA(0, ("MAME: Turbo Out Run (Out Run upgrade) (FD1094 317-0118) [toutrun]"));
	HWND hWnd37 = FindWindowA(0, ("MAME: Turbo Out Run (Out Run upgrade) (bootleg of FD1094 317-0118 set) [toutrund]"));
	HWND hWnd38 = FindWindowA(0, ("MAME: Turbo Out Run (Japan, Out Run upgrade) (FD1094 317-0117) [toutrunj]"));
	HWND hWnd39 = FindWindowA(0, ("MAME: Turbo Out Run (Japan, Out Run upgrade) (bootleg of FD1094 317-0117 set) [toutrunjd]"));
	HWND hWnd40 = FindWindowA(0, ("MAME: Power Drift (World, Rev A) [pdrift]"));
	HWND hWnd41 = FindWindowA(0, ("MAME: Power Drift (World) [pdrifta]"));
	HWND hWnd42 = FindWindowA(0, ("MAME: Power Drift (World, Earlier) [pdrifte]"));
	HWND hWnd43 = FindWindowA(0, ("MAME: Power Drift (Japan) [pdriftj]"));
	HWND hWnd44 = FindWindowA(0, ("MAME: Power Drift - Link Version (Japan, Rev A) [pdriftl]"));
	HWND hWnd45 = FindWindowA(0, ("MAME: OutRunners (World) [orunners]"));

	if ((hWnd1 > NULL) || (hWnd2 > NULL) || (hWnd3 > NULL) || (hWnd4 > NULL) || (hWnd5 > NULL)) //Daytona 2,Scud Race & Le Mans 24
	{
		if (name == RawDrive)
		{
			stateFFB = newstateFFB;
		}

		if ((stateFFB > 0x09) && (stateFFB < 0x18))
		{
			//Spring
			double percentForce = (stateFFB - 9) / 14.0;
			if (percentForce < (MinimumSpringStrength / 100.0))
			{
				percentForce = MinimumSpringStrength / 100.0;
			}

			triggers->Spring(percentForce);
		}

		if ((stateFFB > 0x1F) && (stateFFB < 0x28))
		{
			//Clutch
			double percentForce = (stateFFB - 31) / 8.0;
			triggers->Friction(percentForce);
		}

		if ((stateFFB > 0x2F) && (stateFFB < 0x40))
		{
			//Centering
			double percentForce = (stateFFB - 47) / 16.0;
			triggers->Sine(70, 30, percentForce);
		}

		if ((stateFFB > 0x3F) && (stateFFB < 0x50))
		{
			//Uncentering
			double percentForce = (stateFFB - 63) / 16.0;
			triggers->Sine(70, 30, percentForce);
		}

		if ((stateFFB > 0x4F) && (stateFFB < 0x58))
		{
			//Roll Right
			double percentForce = (stateFFB - 79) / 8.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((stateFFB > 0x5F) && (stateFFB < 0x68))
		{
			//Roll Left
			double percentForce = (stateFFB - 95) / 8.0;
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

	if (hWnd10 > NULL) //Virtua Racing
	{
		static bool DontSineUntilRaceStart = false;

		if (name == digit0)
		{
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
				triggers->Sine(70, 30, percentForce);
			}
			else
			{
				if (DontSineUntilRaceStart)
				{
					//Uncentering
					double percentForce = 0.4;
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

	if ((hWnd11 > NULL) || (hWnd12 > NULL) || (hWnd13 > NULL) || (hWnd14 > NULL)) //San Francisco Rush
	{
		if (name == wheel)
		{
			stateFFB = newstateFFB;
		}

		int ffsanfranrush = 0;
		ffsanfranrush = sanfran(stateFFB);

		if ((ffsanfranrush > 0x70) && (ffsanfranrush < 0xE9))
		{
			double percentForce = (233 - ffsanfranrush) / 119.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((ffsanfranrush > 0x00) && (ffsanfranrush < 0x71))
		{
			double percentForce = (ffsanfranrush) / 112.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
	}

	if ((hWnd15 > NULL) || (hWnd16 > NULL) || (hWnd17 > NULL) || (hWnd18 > NULL) || (hWnd19 > NULL) || (hWnd20 > NULL) || (hWnd21 > NULL)) //Cruis'n USA
	{
		if (name == wheel)
		{
			stateFFB = newstateFFB;
		}

		int ffcrusnwld = 0;
		ffcrusnwld = crusnwld(stateFFB);

		if ((ffcrusnwld > 110)& (ffcrusnwld < 226))
		{
			double percentForce = (225 - ffcrusnwld) / 114.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((ffcrusnwld > 0)& (ffcrusnwld < 111))
		{
			double percentForce = (ffcrusnwld) / 110.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
	}

	if ((hWnd22 > NULL) || (hWnd23 > NULL) || (hWnd24 > NULL) || (hWnd25 > NULL) || (hWnd26 > NULL)) //Off Road Challenge
	{
		if (name == wheel)
		{
			stateFFB = newstateFFB;
		}

		if ((stateFFB > 0x83) && (stateFFB < 0x100))
		{
			double percentForce = (255 - stateFFB) / 124.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((stateFFB > 0x00) && (stateFFB < 0x7D))
		{
			double percentForce = (stateFFB) / 124.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
	}

	if ((hWnd27 > NULL) || (hWnd28 > NULL) || (hWnd29 > NULL))
	{
		if (name == wheel)
		{
			stateFFB = newstateFFB;
		}

		int ffcrusnusa = 0;
		ffcrusnusa = crusnusa(stateFFB);

		if ((ffcrusnusa > 0x68) && (ffcrusnusa < 0xD7))
		{
			double percentForce = (215 - ffcrusnusa) / 110.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
		else if ((ffcrusnusa > 0x00) && (ffcrusnusa < 0x69))
		{
			double percentForce = (ffcrusnusa) / 104.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
	}

	if ((hWnd30 > NULL) || (hWnd31 > NULL) || (hWnd32 > NULL)) //California Speed
	{
		if (name == wheel)
		{
			stateFFB = newstateFFB;
		}

		if ((stateFFB > 0x80) && (stateFFB < 0x100))
		{
			double percentForce = (255 - stateFFB) / 126.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((stateFFB > 0x00) && (stateFFB < 0x80))
		{
			double percentForce = (stateFFB) / 126.0;
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}

	if ((hWnd33 > NULL) || (hWnd34 > NULL) || (hWnd35 > NULL) || (hWnd36 > NULL) || (hWnd37 > NULL) || (hWnd38 > NULL) || (hWnd39 > NULL)) //Outrun,Turbo Outrun
	{
		if (name == Vibration_motor)
		{
			stateFFB = newstateFFB;
		}

		if (stateFFB == 0x01)
		{
			triggers->Sine(100, 0, 1.0);
		}

		if (stateFFB == 0x00)
		{
			triggers->Sine(0, 0, 0);
		}
	}

	if ((hWnd40 > NULL) || (hWnd41 > NULL) || (hWnd42 > NULL) || (hWnd43 > NULL) || (hWnd44 > NULL)) //Power Drift
	{
		if (name == upright_wheel_motor)
		{
			stateFFB = newstateFFB;
		}

		if (stateFFB == 0x01)
		{
			triggers->Sine(100, 0, 1.0);
		}

		if (stateFFB == 0x00)
		{
			triggers->Sine(0, 0, 0);
		}
	}

	if (hWnd45 > NULL) //OutRunners
	{
		static bool MAEffect = false;
		static bool MBEffect = false;

		if (name == MA_Steering_Wheel_motor)
		{
			stateFFB = newstateFFB;
		}
		else if (name == MB_Steering_Wheel_motor)
		{
			stateFFBDevice2 = newstateFFB;
		}

		if (stateFFB == 0x01)
		{
			MAEffect = true;
		}

		if (stateFFB == 0x00)
		{
			MAEffect = false;
		}

		if (stateFFBDevice2 == 0x01)
		{
			MBEffect = true;
		}

		if (stateFFBDevice2 == 0x00)
		{
			MBEffect = false;
		}

		if (MAEffect)
		{
			triggers->Sine(100, 0, 1.0);
		}

		if (!MAEffect)
		{
			triggers->Sine(0, 0, 0);
		}

		if (MBEffect)
		{
			// Need to add device 2
		}

		if (!MBEffect)
		{
			// Need to add device 2
		}
	}
}