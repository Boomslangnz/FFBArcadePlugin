#pragma once
#include "../Common Files/Game.h"

class AfterburnerClimax : public Game {
public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
