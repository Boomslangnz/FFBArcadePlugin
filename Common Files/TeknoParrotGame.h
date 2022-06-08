#pragma once
#include "Game.h"

class TeknoParrotGame : public Game {

	// TP-related
	HANDLE hSection;
	LPVOID secData;

protected:
	int ffbOffset = 0;
	int ffbOffset2 = 0;
	int ffbOffset3 = 0;
	int ffbOffset4 = 0;
	int GetTeknoParrotFFB();
	int GetTeknoParrotFFB2();
	int GetTeknoParrotFFB3();
	int GetTeknoParrotFFB4();
	TeknoParrotGame();

public:
	void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers);
};