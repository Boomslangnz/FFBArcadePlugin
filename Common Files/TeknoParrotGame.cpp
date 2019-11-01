#include "TeknoParrotGame.h"
TeknoParrotGame::TeknoParrotGame()
{
	hSection = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, 64, L"TeknoParrot_JvsState");
	secData = MapViewOfFile(hSection, FILE_MAP_ALL_ACCESS, 0, 0, 64);
	ffbOffset = *((int *)secData + 2);
}

int TeknoParrotGame::GetTeknoParrotFFB()
{
	ffbOffset = *((int *)secData + 2);
	return ffbOffset;
}

void TeknoParrotGame::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {
	helpers->log("TeknoParrot game not implemented");
}