#pragma once
#include "../Common Files/TeknoParrotGame.h"

class SegaRally3 : public TeknoParrotGame {
public:
	SegaRally3() : TeknoParrotGame() { }
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};