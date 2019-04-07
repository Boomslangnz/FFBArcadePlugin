#pragma once
#include "../Common Files/TeknoParrotGame.h"

class FordRacing : public TeknoParrotGame {
public:
	FordRacing() : TeknoParrotGame() { }
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};