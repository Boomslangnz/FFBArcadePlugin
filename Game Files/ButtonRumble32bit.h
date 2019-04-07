#pragma once
#include "../Common Files/Game.h"
class ButtonRumble32bit : public Game {

public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
