#pragma once
#include "../Common Files/Game.h"
class FordRacingOther : public Game {

public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};