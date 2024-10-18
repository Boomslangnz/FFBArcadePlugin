#pragma once
#include <Windows.h>
#include "MinHook.h"

// struct
struct EffectTriggers {
	void(*Constant)(int direction, double strength);
	void(*Spring)(double strength);
	void(*Friction)(double strength);
	void(*Sine)(UINT16 period, UINT16 fadePeriod, double strength);
	void(*SineDevice2)(UINT16 period, UINT16 fadePeriod, double strength);
	void(*SineDevice3)(UINT16 period, UINT16 fadePeriod, double strength);
	void(*Rumble)(double lowfrequency, double highfrequency, double length);
	void(*RumbleDevice2)(double lowfrequency, double highfrequency, double length);
	void(*RumbleDevice3)(double lowfrequency, double highfrequency, double length);
	void(*RumbleTriggers)(double lefttrigger, double righttrigger, double length);
	void(*LeftRight)(double smallstrength, double largestrength, double length);
	void(*LeftRightDevice2)(double smallstrength, double largestrength, double length);
	void(*Springi)(double strength);
	void(*Inertia)(double strength);
	void(*Ramp)(double start, double end, double length);
	void(*Damper)(double strength);
	void(*SawtoothUp)(double strength, double length);
	void(*SawtoothDown)(double strength, double length);
	void(*Triangle)(double strength, double length);
};

// classes
class EffectCollection {
public:
	int effect_constant_id;
	int effect_leftramp_id;
	int effect_rightramp_id;
	int effect_friction_id;
	int effect_leftright_id;
	int effect_sine_id;
	int effect_sine_id_device2;
	int effect_sine_id_device3;
	int effect_spring_id;
	int effect_vibration_id;
	int effect_inertia_id;
	int effect_ramp_id;
	int effect_damper_id;
	int effect_sawtoothup_id;
	int effect_sawtoothdown_id;
	int effect_triangle_id;
};

class EffectConstants {
public:
	// constants
	// Haptic forces are defined by the direction that generates the force
	// e.g. DIRECTION_FROM_LEFT causes wheel to go right.
	const int DIRECTION_FROM_LEFT = -1;
	const int DIRECTION_FROM_RIGHT = 1;
};

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

#define SDL_HAT_CENTERED    0x00
#define SDL_HAT_UP          0x01
#define SDL_HAT_RIGHT       0x02
#define SDL_HAT_DOWN        0x04
#define SDL_HAT_LEFT        0x08
#define SDL_HAT_RIGHTUP     (SDL_HAT_RIGHT|SDL_HAT_UP)
#define SDL_HAT_RIGHTDOWN   (SDL_HAT_RIGHT|SDL_HAT_DOWN)
#define SDL_HAT_LEFTUP      (SDL_HAT_LEFT|SDL_HAT_UP)
#define SDL_HAT_LEFTDOWN    (SDL_HAT_LEFT|SDL_HAT_DOWN)

class Helpers {
public:
	int enableLogging = 0;
	// helper functions
	bool fileExists(char *filename);
	// logging
	void log(char *msg);
	void logInt(int value);
	void logInit(char *msg);
	void info(const char* format, ...);
	// reading memory
	LPVOID GetTranslatedOffset(INT_PTR offset);
	int ReadInt32(INT_PTR offset, bool isRelativeOffset);
	UINT8 ReadByte(INT_PTR offset, bool isRelativeOffset);
	WORD ReadWord(INT_PTR offset, bool isRelativeOffset);
	float WriteFloat32(INT_PTR offset, float val, bool isRelativeOffset);
	UINT8 WriteByte(INT_PTR offset, UINT8 val, bool isRelativeOffset);
	INT_PTR WriteIntPtr(INT_PTR offset, INT_PTR val, bool isRelativeOffset);
	UINT8 WriteNop(INT_PTR offset, int countBytes, bool isRelativeOffset);
	WORD WriteWord(INT_PTR offset, WORD val, bool isRelativeOffset);
	INT_PTR ReadIntPtr(INT_PTR offset, bool isRelativeOffset);
	long long ReadLong(INT_PTR offset, bool isRelativeOffset);
	float ReadFloat32(INT_PTR offset, bool isRelativeOffset);
};

class Game {
public:
	virtual void FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers *triggers);
};