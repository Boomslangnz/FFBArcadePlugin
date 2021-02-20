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
#include "TestGame.h"
#include "SDL.h"

wchar_t *settingsFN = TEXT(".\\FFBPlugin.ini");

int configGameIdEffect = GetPrivateProfileInt(TEXT("Settings"), TEXT("GameId"), 1, settingsFN);

void TestGame::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	switch (configGameIdEffect) {
	case -1:
		// turn left
		triggers->Constant(constants->DIRECTION_FROM_RIGHT, 1);
		break;
	case -2:
		triggers->Sine(125, 100, 0.25);
		break;
	case -3:
		triggers->Friction(1);
		break;
	case -4:
		triggers->Spring(1);
		break;
	case -5:
		triggers->Friction(1);
		triggers->Spring(1);
		break;
	case -6:
		triggers->Friction(0);
		triggers->Spring(0);
		break;
	case -7:
		triggers->Rumble(1.0, 1.0, SDL_HAPTIC_INFINITY);
		break;
	case -8:
		triggers->RumbleTriggers(1.0, 1.0, SDL_HAPTIC_INFINITY);
		break;
	}
}