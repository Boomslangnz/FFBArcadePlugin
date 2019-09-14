#pragma once
#include "../Common Files/Game.h"

class KODrive : public Game {
public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};