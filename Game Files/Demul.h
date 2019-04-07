#pragma once
#include "../Common Files/Game.h"
class Demul : public Game {
	
public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};