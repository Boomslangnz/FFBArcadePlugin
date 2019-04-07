#pragma once
#include "../Common Files/Game.h"
class M2Emulator : public Game {

public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};
