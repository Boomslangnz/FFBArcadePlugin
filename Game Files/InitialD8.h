#pragma once
#include "../Common Files/TeknoParrotGame.h"

class InitialD8 : public TeknoParrotGame {
public:
	InitialD8() : TeknoParrotGame() { }
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};