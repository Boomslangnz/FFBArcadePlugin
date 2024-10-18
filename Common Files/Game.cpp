#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"

typedef unsigned char U8;

bool Helpers::fileExists(char *filename)
{
	std::ifstream ifile(filename);
	return !ifile.fail();
}

void Helpers::log(char *msg) {
	if (enableLogging == 0) { return; }
	std::ofstream ofs("FFBlog.txt", std::ofstream::app);
	ofs << msg << std::endl;
	ofs.close();
}

void Helpers::logInt(int value) {
	std::string njs = std::to_string(value);
	log((char *)njs.c_str());
}

void Helpers::logInit(char *msg) {
	if (enableLogging == 0) { return; }
	std::ofstream ofs("FFBlog.txt", std::ofstream::out);
	ofs << msg << std::endl;
	ofs.close();
}

void Helpers::info(const char* format, ...)
{
	va_list args;
	char buffer[1024];

	va_start(args, format);
	int len = _vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	buffer[len] = '\n';
	buffer[len + 1] = '\0';

	OutputDebugStringA(buffer);
}

// reading memory
LPVOID Helpers::GetTranslatedOffset(INT_PTR offset)
{
	return reinterpret_cast<LPVOID>((INT_PTR)GetModuleHandle(NULL) + offset);
}

UINT8 Helpers::ReadByte(INT_PTR offset, bool isRelativeOffset)
{
	UINT8 val = 0;
	SIZE_T read;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	ReadProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(UINT8), &read);
	return val;
}

float Helpers::WriteFloat32(INT_PTR offset, float val, bool isRelativeOffset)
{
	//val = 0.0f;
	SIZE_T written;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	WriteProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(float), &written);
	return val;
};

UINT8 Helpers::WriteByte(INT_PTR offset, UINT8 val, bool isRelativeOffset)
{
	SIZE_T written;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	WriteProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(UINT8), &written);
	return val;
}

WORD Helpers::WriteWord(INT_PTR offset, WORD val, bool isRelativeOffset)
{
	SIZE_T written;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	WriteProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(WORD), &written);
	return val;
}

INT_PTR Helpers::WriteIntPtr(INT_PTR offset, INT_PTR val, bool isRelativeOffset)
{
	SIZE_T written;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	WriteProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(INT_PTR), &written);
	return val;
};

UINT8 Helpers::WriteNop(INT_PTR offset, int countBytes, bool isRelativeOffset)
{
	U8 nop = 0x90;
	SIZE_T written;
	for (int i = 0; i < countBytes; i++)
	{
		offset = offset + i;
		LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
		WriteProcessMemory(GetCurrentProcess(), trueOffset, &nop, 1, &written);
		offset = offset - i;
	}
	return nop;
}

int Helpers::ReadInt32(INT_PTR offset, bool isRelativeOffset)
{
	int val = 0;
	SIZE_T read;
	//log("going to try to RPM");
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	ReadProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(int), &read);
	//log("RPM");
	//char text[256];
	//sprintf_s(text, "%16X / %16X\n", offset, trueOffset);
	//log(text);
	return val;
}

INT_PTR Helpers::ReadIntPtr(INT_PTR offset, bool isRelativeOffset)
{
	SIZE_T read;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	INT_PTR val;
	ReadProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(INT_PTR), &read);
	return val;
};

WORD Helpers::ReadWord(INT_PTR offset, bool isRelativeOffset)
{
	SIZE_T read;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	WORD val;
	ReadProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(WORD), &read);
	return val;
};

long long Helpers::ReadLong(INT_PTR offset, bool isRelativeOffset)
{
	SIZE_T read;
	LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
	long long val;
	ReadProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(long long), &read);
	return val;
};

float Helpers::ReadFloat32(INT_PTR offset, bool isRelativeOffset)
{
		
		float val = 0.0f;
		SIZE_T read;
		//log("going to try to RPM");
		LPVOID trueOffset = (isRelativeOffset ? GetTranslatedOffset(offset) : (LPVOID)offset);
		ReadProcessMemory(GetCurrentProcess(), trueOffset, &val, sizeof(float), &read);
		//char text[256];
		//sprintf_s(text, "%16X / %16X\n", offset, trueOffset);
		//log(text);
		//log("RPM");
		return val;
		
};

void Game::FFBLoop(EffectConstants * constants, Helpers * helpers, EffectTriggers * triggers)
{
	return;
}
