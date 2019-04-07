#pragma once
#include "../Common Files/Game.h"
class Mame020632bit : public Game {

public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};