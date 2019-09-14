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
#include "SegaRally3.h"

static int __stdcall Out32(DWORD device, DWORD data)
{
	/*static char test[256];
	memset(test, 0, 256);
	sprintf(test, "hex print: %08X", data);
	OutputDebugStringA(test);
	return 0;*/
}

void SegaRally3::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	/*bool init = false;
	HMODULE hMod = GetModuleHandleA("inpout32.dll");
	if (hMod)
	{
		if (!init)
		{
			//injector::MakeJMP((DWORD)GetProcAddress(GetModuleHandle(L"inpout32.dll"), "Inp32"), Inp32);
			injector::MakeJMP((DWORD)GetProcAddress(GetModuleHandle(L"inpout32.dll"), "Out32"), Out32);
			init = true;
		}
	}*/
	helpers->log("in SR3 Ffbloop");
	const int ff = GetTeknoParrotFFB();
	std::string ffs = std::to_string(ff);
	helpers->log((char *)ffs.c_str());

	if (ff > 15)
	{
		helpers->log("moving wheel right");
		// assume that 30 is the weakest and 16 is the strongest
		double percentForce = (31 - ff) / 15.0;
		double percentLength = 100;
		// direction from left => makes wheel turn right
		triggers->LeftRight(percentForce, 0, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
		lastWasStop = 0;
	}
	else if (ff > 0)
	{
		helpers->log("moving wheel left");
		// assume that 1 is the strongest and 15 is the weakest
		double percentForce = (16 - ff) / 15.0;
		double percentLength = 100;
		// direction from right => makes wheel turn left
		triggers->LeftRight(0, percentForce, percentLength);
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
		lastWasStop = 0;
	}
	else
	{
		if (lastWasStop == 0) {
			triggers->Constant(constants->DIRECTION_FROM_LEFT, 0); // just pass the hash of 0 strength so we update lastEffectHash & lastEffectTime
			lastWasStop = 1;
		}
	}
}