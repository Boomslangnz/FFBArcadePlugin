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
#include "Flycast.h"
#include "math.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "SDL.h"
#include "../Common Files/CRCCheck.h"
#include "../Common Files/SignatureScanning.h"

static const char* initiald = "INITIAL ";

static bool InitialDRunning;
static bool FFBGameInit;
static bool LetsStartFFB;
static INT_PTR FFBAddress;

WNDPROC pOrigProc;

LRESULT CALLBACK HookWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (!LetsStartFFB)
		LetsStartFFB = true;

	return CallWindowProc(pOrigProc, hwnd, uMsg, wParam, lParam);
}

static void getGameInfo(char* GameName)
{
	if (_strcmpi(GameName, initiald) == 0)
	{
		FFBAddress = (INT_PTR)aAddy2 + 0xAF;
		InitialDRunning = true;
	}		
}

void Flycast::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) {

	if (!FFBGameInit)
	{
		HWND hwnd = FindWindowA(0, "Flycast");
		HWND hwnddojo = FindWindowA(0, "Flycast Dojo");

		if (pOrigProc == NULL && hwnd)
			pOrigProc = (WNDPROC)::SetWindowLongPtr((HWND)hwnd, GWLP_WNDPROC, (LONG_PTR)HookWndProc);

		if (pOrigProc == NULL && hwnddojo)
			pOrigProc = (WNDPROC)::SetWindowLongPtr((HWND)hwnddojo, GWLP_WNDPROC, (LONG_PTR)HookWndProc);

		if (LetsStartFFB)
		{
			Sleep(15000);

			aAddy2 = PatternScan("\x4E\x49\x54\x49\x41\x4C\x20\x44\x20\x56\x65\x72\x2E\x33\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x30\xDF\x9C\xAB\xBA\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x84\x00\x50\x54\x05\x00\x00\x00\x05\x00\x00\x00\x80\xAA\x6D\x68\x00\x55", "xxxxxxxx???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????xxxxxx");

			long long InitialDName = helpers->ReadLong((INT_PTR)aAddy2 - 0x01, false);

			char x[256] = { 0 };

			std::memcpy(x, &InitialDName, 8);

			std::string myString(x);
			getGameInfo((char*)myString.c_str());

			FFBGameInit = true;
		}
	}

	if (InitialDRunning)
	{
		UINT8 ff1 = helpers->ReadByte(FFBAddress, false);
		UINT8 ff2 = helpers->ReadByte(FFBAddress + 0x01, false);
		UINT8 ff3 = helpers->ReadByte(FFBAddress + 0x02, false);

		if ((ff1 == 0x80) && (ff3 == 0x01))
			triggers->Spring(1.0);

		if ((ff1 == 0x85) && (ff2 == 0x3F) && (ff3 > 0x00) && (ff3 < 0x30))
		{
			double percentForce = ff3 / 47.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, percentForce, percentLength);
			triggers->Sine(40, 0, percentForce);
		}

		if ((ff1 == 0x86) && (ff2 == 0x02) && (ff3 > 0x09) && (ff3 < 0x3C))
		{
			double percentForce = (60 - ff3) / 43.0;
			double percentLength = 100;
			triggers->Spring(percentForce);
		}

		if ((ff1 == 0x84) && (ff2 == 0x00) && (ff3 > 0x37) && (ff3 < 0x80))
		{
			double percentForce = (128 - ff3) / 72.0;
			double percentLength = 100;
			triggers->Rumble(percentForce, 0, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		}
		else if ((ff1 == 0x84) && (ff2 == 0x01) && (ff3 > 0x00) && (ff3 < 0x49))
		{
			double percentForce = (ff3 / 72.0);
			double percentLength = 100;
			triggers->Rumble(0, percentForce, percentLength);
			triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		}
	}
}