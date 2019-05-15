#include <string>
#include "Outrun2Real.h"
#include "SDL.h"
#include <Windows.h>
static EffectTriggers *myTriggers;
static EffectConstants *myConstants;
static Helpers *myHelpers;
static SDL_Event e;
static int SpeedStrength;
static wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
static int ShowButtonNumbersForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowButtonNumbersForSetup"), 0, settingsFilename);
static int ChangeGearsViaPlugin = GetPrivateProfileInt(TEXT("Settings"), TEXT("ChangeGearsViaPlugin"), 0, settingsFilename);
static int Gear1 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear1"), 0, settingsFilename);
static int Gear2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear2"), 0, settingsFilename);
static int Gear3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear3"), 0, settingsFilename);
static int Gear4 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear4"), 0, settingsFilename);
static int Gear5 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear5"), 0, settingsFilename);
static int Gear6 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear6"), 0, settingsFilename);

//B hitting right wall hard constant
//1B hitting left wall hard constant
//2 driving on grass sine
//10 scraping car against side rail left side
//4 driving from grass, sand to road if from right side
//14 driving from grass, sand to road if from left side
//00 when over grass, sand etc

void SendForceFeedback(__int8 force)
{
	float ffspeed = myHelpers->ReadFloat32(0x08273DF0, /* isRelativeOffset */ false); //speedo
	/*char gay[256];
	memset(gay, 0, 256);
	sprintf(gay, "hex print: %08X", force);
	OutputDebugStringA(gay);*/
	if ((force == 0x10) || (force == 0x0B) || (force == 0x04))
	{
		double percentForce = SpeedStrength / 100.0;
		double percentLength = 100;
		myTriggers->LeftRight(0, percentForce, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
	}
	if ((force == 0x00) || (force == 0x1B) || (force == 0x14))
	{
		double percentForce = SpeedStrength / 100.0;
		double percentLength = 100;
		myTriggers->LeftRight(percentForce, 0, percentLength);
		myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
	}
	if (force == 0x02)
	{
		double percentForce = SpeedStrength / 100.0;
		double percentLength = 100;
		myTriggers->LeftRight(percentForce, percentForce, percentLength);
		myTriggers->Sine(70, 80, percentForce);
	}
}

signed int cdecl or2FfbFunction(unsigned __int8 unk1, unsigned __int8 unk2, unsigned __int8 force, char unk3)
{
	int SpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("SpringStrength"), 0, TEXT(".\\FFBPlugin.ini"));
	if (unk1 == 0x7D)
	{
		//not used
	}
	if (unk1 == 0x7B)
	{
		SendForceFeedback(force);
	}
	else if (unk1 != 0x7B)
	{
		double percentForce = SpringStrength / 100.0;
		myTriggers->Springi(percentForce);
	}
	return 0;
}

static int RunningThread(void *ptr)
{
	int cnt;
	for (cnt = 0; cnt >= 0; ++cnt)
	{
		UINT8 gear = myHelpers->ReadByte(0x0827A160, /* isRelativeOffset */ false); // gear address
		UINT8 ff8 = myHelpers->ReadByte(0x08304ADC, /* isRelativeOffset */ false); // 1 when race
		float ffspeed = myHelpers->ReadFloat32(0x08273DF0, /* isRelativeOffset */ false); //speedo
		UINT8 static oldgear = 0;
		float newgear = gear;

		if ((ffspeed >= 0.1) && (ffspeed <= 80))
		{
			SpeedStrength = 10;
		}
		else if ((ffspeed >= 80.1) && (ffspeed <= 130))
		{
			SpeedStrength = 20;
		}
		else if ((ffspeed >= 130.1) && (ffspeed <= 180))
		{
			SpeedStrength = 30;
		}
		else if ((ffspeed >= 180.1) && (ffspeed <= 220))
		{
			SpeedStrength = 40;
		}
		else if ((ffspeed >= 220.1) && (ffspeed <= 270))
		{
			SpeedStrength = 50;
		}
		else if ((ffspeed >= 270.1) && (ffspeed <= 320))
		{
			SpeedStrength = 60;
		}
		else if ((ffspeed >= 320.1) && (ffspeed <= 380))
		{
			SpeedStrength = 70;
		}
		else if ((ffspeed >= 380.1) && (ffspeed <= 430))
		{
			SpeedStrength = 80;
		}
		else if ((ffspeed >= 430.1) && (ffspeed <= 500))
		{
			SpeedStrength = 90;
		}
		else if ((ffspeed >= 500.1) && (ffspeed <= 1000))
		{
			SpeedStrength = 100;
		}
		else
		{
			SpeedStrength = 0;
		}

		if ((oldgear != newgear) && (ff8 == 1) && (ffspeed >= 0.1))
		{
			double percentForce = 0.1;
			double percentLength = 100;
			myTriggers->Sine(240, 320, percentForce);
			myTriggers->LeftRight(percentForce, percentForce, percentLength);
		}
		oldgear = newgear;
	}
	return 0;
}

void OutRun2Real::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {	
	SDL_Thread *thread;
	thread = SDL_CreateThread(RunningThread, "RunningThread", (void *)NULL);
		
	while (SDL_WaitEvent(&e) != 0)
	{	
		bool init = true;
		if (init)
		{
			DWORD tempdw = 0x08105A48;
			DWORD loadffb = (DWORD)(void *)or2FfbFunction;
			DWORD tempdw2 = loadffb - tempdw - 5;
			*(BYTE *)tempdw = 0xE9;
			*(DWORD *)(tempdw + 1) = tempdw2;
			init = false;
		}
		UINT8 transmission = helpers->ReadByte(0x082932C2, /* isRelativeOffset */ false); // Auto or Manual
		myTriggers = triggers;
		myConstants = constants;
		myHelpers = helpers;
		if (ShowButtonNumbersForSetup == 1)
		{
			if (e.type == SDL_JOYBUTTONDOWN)
			{
				if (e.jbutton.button == 0)
				{
					MessageBoxA(NULL, "Button 0 Pressed", "", 0);
				}
				else if (e.jbutton.button == 1)
				{
					MessageBoxA(NULL, "Button 1 Pressed", "", 0);
				}
				else if (e.jbutton.button == 2)
				{
					MessageBoxA(NULL, "Button 2 Pressed", "", 0);
				}
				else if (e.jbutton.button == 3)
				{
					MessageBoxA(NULL, "Button 3 Pressed", "", 0);
				}
				else if (e.jbutton.button == 4)
				{
					MessageBoxA(NULL, "Button 4 Pressed", "", 0);
				}
				else if (e.jbutton.button == 5)
				{
					MessageBoxA(NULL, "Button 5 Pressed", "", 0);
				}
				else if (e.jbutton.button == 6)
				{
					MessageBoxA(NULL, "Button 6 Pressed", "", 0);
				}
				else if (e.jbutton.button == 7)
				{
					MessageBoxA(NULL, "Button 7 Pressed", "", 0);
				}
				else if (e.jbutton.button == 8)
				{
					MessageBoxA(NULL, "Button 8 Pressed", "", 0);
				}
				else if (e.jbutton.button == 9)
				{
					MessageBoxA(NULL, "Button 9 Pressed", "", 0);
				}
				else if (e.jbutton.button == 10)
				{
					MessageBoxA(NULL, "Button 10 Pressed", "", 0);
				}
				else if (e.jbutton.button == 11)
				{
					MessageBoxA(NULL, "Button 11 Pressed", "", 0);
				}
				else if (e.jbutton.button == 12)
				{
					MessageBoxA(NULL, "Button 12 Pressed", "", 0);
				}
				else if (e.jbutton.button == 13)
				{
					MessageBoxA(NULL, "Button 13 Pressed", "", 0);
				}
				else if (e.jbutton.button == 14)
				{
					MessageBoxA(NULL, "Button 14 Pressed", "", 0);
				}
				else if (e.jbutton.button == 15)
				{
					MessageBoxA(NULL, "Button 15 Pressed", "", 0);
				}
			}
		}
		if (e.type == SDL_JOYBUTTONDOWN)
		{
			if ((ChangeGearsViaPlugin == 1) && (transmission == 1))
			{
				if (e.jbutton.button == Gear1)
				{
					helpers->WriteByte(0x0827A160, 0x01, false);
				}
				else if (e.jbutton.button == Gear2)
				{
					helpers->WriteByte(0x0827A160, 0x02, false);
				}
				else if (e.jbutton.button == Gear3)
				{
					helpers->WriteByte(0x0827A160, 0x03, false);
				}
				else if (e.jbutton.button == Gear4)
				{
					helpers->WriteByte(0x0827A160, 0x04, false);
				}
				else if (e.jbutton.button == Gear5)
				{
					helpers->WriteByte(0x0827A160, 0x05, false);
				}
				else if (e.jbutton.button == Gear6)
				{
					helpers->WriteByte(0x0827A160, 0x06, false);
				}
			}
		}
	}
}