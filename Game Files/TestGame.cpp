#include <string>
#include "TestGame.h"
#include "SDL.h"

//settingsFN copied from DllMain.cpp; renamed from settingsFilename
wchar_t *settingsFN = TEXT(".\\FFBPlugin.ini");

//GameId test values:
//const int TEST_GAME_CONST = -1;
//const int TEST_GAME_SINE = -2;
//const int TEST_GAME_FRICTION = -3;
//const int TEST_GAME_SPRING = -4;
//const int TEST_GAME_HEAVY = -5;
//const int TEST_GAME_LOOSE = -6;
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
		triggers->LeftRight(1.0, 1.0, SDL_HAPTIC_INFINITY);
		break;
	}
}