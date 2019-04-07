#pragma once
#include "../Common Files/Game.h"
class ButtonRumble64bit : public Game {

public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
