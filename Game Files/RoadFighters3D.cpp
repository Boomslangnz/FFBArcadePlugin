/*This file is part of FFB Arcade Plugin.
FFB Arcade Plugin is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
FFB Arcade Plugin is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with FFB Arcade Plugin.If not, see < https://www.gnu.org/licenses/>.
*/

#include <string>
#include "SDL.h"
#include "RoadFighters3D.h"
#include <Windows.h>
static EffectTriggers *myTriggers;
static EffectConstants *myConstants;
static Helpers *myHelpers;
extern HINSTANCE gl_hjgtDll;
extern HINSTANCE gl_hlibavs;
extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;
extern int EnableDamper;
extern int DamperStrength;
static bool avoiderror = true;
static bool testbuttonA;
static bool servicebuttonA;
static bool threedeebuttonA;
static bool viewbuttonA;
static bool leverupA;
static bool leverdownA;
static bool leverleftA;
static bool leverrightA;
static bool stophack;
static bool init = false;
extern SDL_Event e;

static void MEMwrite(void *adr, void *ptr, int size)
{
	DWORD OldProtection;
	VirtualProtect(adr, size, PAGE_EXECUTE_READWRITE, &OldProtection);
	memcpy(adr, ptr, size);
	VirtualProtect(adr, size, OldProtection, &OldProtection);
}

static wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
static int CabinetID = GetPrivateProfileInt(TEXT("Settings"), TEXT("CabinetID"), 0, settingsFilename);
static int Only2D = GetPrivateProfileInt(TEXT("Settings"), TEXT("Only2D"), 0, settingsFilename);
static int HackToSkipMenuError = GetPrivateProfileInt(TEXT("Settings"), TEXT("HackToSkipMenuError"), 0, settingsFilename);
static int HackToCloseLibmovieErrorAuto = GetPrivateProfileInt(TEXT("Settings"), TEXT("HackToCloseLibmovieErrorAuto"), 0, settingsFilename);
static int InputDeviceWheelEnable = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelEnable"), 0, settingsFilename);
static int InputDeviceWheelSteeringAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelSteeringAxis"), 0, settingsFilename);
static int InputDeviceWheelAcclAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelAcclAxis"), 0, settingsFilename);
static int InputDeviceWheelBrakeAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelBrakeAxis"), 0, settingsFilename);
static int InputDeviceWheelReverseAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelReverseAxis"), 0, settingsFilename);
static int InputDeviceCombinedPedals = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceCombinedPedals"), 0, settingsFilename);
static int SteeringDeadzone = GetPrivateProfileInt(TEXT("Settings"), TEXT("SteeringDeadzone"), 0, settingsFilename);
static int PedalDeadzone = GetPrivateProfileInt(TEXT("Settings"), TEXT("PedalDeadzone"), 0, settingsFilename);
static int SequentialGears = GetPrivateProfileInt(TEXT("Settings"), TEXT("SequentialGears"), 0, settingsFilename);
static int ShowButtonNumbersForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowButtonNumbersForSetup"), 0, settingsFilename);
static int ShowAxisForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowAxisForSetup"), 0, settingsFilename);
static int ExitButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ExitButton"), 0, settingsFilename);
static int TestButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("TestButton"), 0, settingsFilename);
static int ServiceButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ServiceButton"), 0, settingsFilename);
static int CreditButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("CreditButton"), 0, settingsFilename);
static int ViewButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ViewButton"), 0, settingsFilename);
static int ThreeDimensionalButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ThreeDimensionalButton"), 0, settingsFilename);
static int leverUp = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverUp"), 0, settingsFilename);
static int leverDown = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverDown"), 0, settingsFilename);
static int leverLeft = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverLeft"), 0, settingsFilename);
static int leverRight = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverRight"), 0, settingsFilename);
static int Gear1Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear1Button"), 0, settingsFilename);
static int Gear2Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear2Button"), 0, settingsFilename);
static int Gear3Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear3Button"), 0, settingsFilename);
static int Gear4Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear4Button"), 0, settingsFilename);
static int Gear5Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear5Button"), 0, settingsFilename);
static int Gear6Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear6Button"), 0, settingsFilename);
static int ExitButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ExitButtonDevice2"), 0, settingsFilename);
static int TestButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("TestButtonDevice2"), 0, settingsFilename);
static int ServiceButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ServiceButtonDevice2"), 0, settingsFilename);
static int CreditButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("CreditButtonDevice2"), 0, settingsFilename);
static int ViewButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ViewButtonDevice2"), 0, settingsFilename);
static int ThreeDimensionalButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ThreeDimensionalButtonDevice2"), 0, settingsFilename);
static int leverUpDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverUpDevice2"), 0, settingsFilename);
static int leverDownDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverDownDevice2"), 0, settingsFilename);
static int leverLeftDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverLeftDevice2"), 0, settingsFilename);
static int leverRightDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverRightDevice2"), 0, settingsFilename);
static int Gear1ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear1ButtonDevice2"), 0, settingsFilename);
static int Gear2ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear2ButtonDevice2"), 0, settingsFilename);
static int Gear3ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear3ButtonDevice2"), 0, settingsFilename);
static int Gear4ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear4ButtonDevice2"), 0, settingsFilename);
static int Gear5ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear5ButtonDevice2"), 0, settingsFilename);
static int Gear6ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear6ButtonDevice2"), 0, settingsFilename);

static int ThreadLoop()
{
	int menuvalue = myHelpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x0094BFFC, false);
	int menuvalue1 = myHelpers->ReadIntPtr((INT_PTR)menuvalue + 0x46C, false);
	int serviceread3 = myHelpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, false);
	int timer = myHelpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x954394, false);
	int cabid = myHelpers->ReadByte((INT_PTR)gl_hjgtDll + 0x951034, false);
	int cabid2 = myHelpers->ReadByte((INT_PTR)gl_hjgtDll + 0x952B9C, false);
	float timeroutofmenu = myHelpers->ReadByte((INT_PTR)gl_hjgtDll + 0x94BEE8, false);
	 uintptr_t jgtBase = (uintptr_t)GetModuleHandleA("jgt.dll");

	if (CabinetID == 2)
	{
		MEMwrite((void*)(jgtBase + 0x951034), (void*)"\x01", 1);
		MEMwrite((void*)(jgtBase + 0x42EBB9), (void*)"\x75", 1);
	}
	else if (CabinetID == 3)
	{
		MEMwrite((void*)(jgtBase + 0x951034), (void*)"\x02", 1);
		MEMwrite((void*)(jgtBase + 0x42EBB9), (void*)"\x75", 1);
	}
	else if (CabinetID == 4)
	{
		MEMwrite((void*)(jgtBase + 0x951034), (void*)"\x03", 1);
		MEMwrite((void*)(jgtBase + 0x42EBB9), (void*)"\x75", 1);
	}
	else
	{
		MEMwrite((void*)(jgtBase + 0x951034), (void*)"\x00", 1);
		MEMwrite((void*)(jgtBase + 0x42EBB9), (void*)"\x74", 1);
	}

	if (HackToCloseLibmovieErrorAuto == 1)
	{
		//Remove fucken window error popup
		HWND hWnd = FindWindowA(0, ("Libmovie Error Report"));
		if (hWnd > NULL)
		{
			SendMessage(hWnd, WM_CLOSE, NULL, NULL);
		}
	}
	if (HackToSkipMenuError == 1)
	{
		// Hack to quickly bypass error at start
		if (avoiderror)
		{
			if (cabid > 0)
			{
				if (menuvalue1 > 700000)
				{
					myHelpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x02, false);
				}
				if (menuvalue1 == 0)
				{
					SDL_Delay(50);
					myHelpers->WriteIntPtr((INT_PTR)menuvalue + 0x46C, 0x0F, false);
				}
				if (menuvalue1 == 15)
				{
					myHelpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x01, false);
				}
				if (timeroutofmenu != 0)
				{
					myHelpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x00, false);
					avoiderror = false;
				}
			}
			else
			{
				if (menuvalue1 > 700000)
				{
					myHelpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x01, false);
				}
				if (timeroutofmenu != 0)
				{
					myHelpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x00, false);
					myHelpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B39, 0x7F, false);
					avoiderror = false;
				}
			}
		}
	}

	if (Only2D == 1)
	{
		//2D Only
		myHelpers->WriteNop((INT_PTR)gl_hjgtDll + 0x24C9F, 3, false);
		myHelpers->WriteNop((INT_PTR)gl_hjgtDll + 0x24CAA, 3, false);
		myHelpers->WriteNop((INT_PTR)gl_hjgtDll + 0x24CBA, 3, false);
		myHelpers->WriteNop((INT_PTR)gl_hjgtDll + 0x478F, 3, false);
		myHelpers->WriteNop((INT_PTR)gl_hjgtDll + 0x3E6DB, 3, false);
		myHelpers->WriteNop((INT_PTR)gl_hjgtDll + 0x1391D8, 3, false);
		myHelpers->WriteNop((INT_PTR)gl_hjgtDll + 0x1391EF, 3, false);
		myHelpers->WriteNop((INT_PTR)gl_hjgtDll + 0x5962F, 3, false);
		int TwoDee1 = myHelpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x00946DA0, false);
		int TwoDee2 = myHelpers->ReadIntPtr((INT_PTR)TwoDee1 + 0x38, false);
		int TwoDee3 = myHelpers->ReadIntPtr((INT_PTR)TwoDee2 + 0x94, false);
		myHelpers->WriteIntPtr((INT_PTR)TwoDee3 + 0x74, 0x00, false);
	}
	if (InputDeviceWheelEnable == 1)
	{
		//Write New Calibration Values	
		myHelpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B00, 0x00, false);
		myHelpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B01, 0x7F, false);
		myHelpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B0C, 0x00, false);
		myHelpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B0D, 0xFF, false);
		myHelpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B14, 0x00, false);
		myHelpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B15, 0xFF, false);
		myHelpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B10, 0x00, false);
		myHelpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B11, 0xFF, false);
		myHelpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B21, 0x00, false);

		// Remove error flashing
		myHelpers->WriteByte((INT_PTR)gl_hjgtDll + 0x951154, 0x01, false);
		myHelpers->WriteByte((INT_PTR)gl_hjgtDll + 0x951155, 0x01, false);
		myHelpers->WriteByte((INT_PTR)gl_hjgtDll + 0x951156, 0x01, false);
	}

	UINT8 ff1 = myHelpers->ReadByte((INT_PTR)gl_hjgtDll + 0x7D2BB9, false);
	UINT8 ff2 = myHelpers->ReadByte((INT_PTR)gl_hjgtDll + 0x7D2BBA, false);
	UINT8 ff3 = myHelpers->ReadByte((INT_PTR)gl_hjgtDll + 0x7D2BBB, false);
	UINT8 ff4 = myHelpers->ReadByte((INT_PTR)gl_hjgtDll + 0x7D2BBC, false);
	//Change timer back to 0 when test menu & FFB Only while timer above 0
	if ((timer != 0) || (menuvalue1 == 0x00))
	{
		if (menuvalue1 == 0x00)
		{
			myHelpers->WriteFloat32((INT_PTR)gl_hjgtDll + 0x954394, 0, false);
		}

		if (EnableDamper == 1)
		{
			myTriggers->Damper(DamperStrength / 100.0);
		}

		if ((ff3 != 0x00) && (ff4 != 0x00))
		{
			if (ff2 > 0x00 && ff2 < 0x40)
			{
				double percentForce = (ff2) / 63.0;
				double percentLength = 100;
				myTriggers->Rumble(percentForce, percentForce, percentLength);
				myTriggers->Sine(120, 120, percentForce);
			}

			if (ff1 > 0x00 && ff1 < 0x08)
			{
				//helpers->log("moving wheel left");
				double percentForce = (ff1) / 7.0;
				double percentLength = 100;
				myTriggers->Rumble(0, percentForce, percentLength);
				myTriggers->Constant(myConstants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if (ff1 > 0x07 && ff1 < 0x10)
			{
				//helpers->log("moving wheel right");
				double percentForce = (16 - ff1) / 8.0;
				double percentLength = 100;
				myTriggers->Rumble(percentForce, 0, percentLength);
				myTriggers->Constant(myConstants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}
	}
	return 0;
}

static DWORD WINAPI RunningLoop(LPVOID lpParam)
{
	while (true)
	{
		ThreadLoop();
		Sleep(16);
	}
}

void RoadFighters3D::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	if (InputDeviceWheelEnable == 1)
	{
		if (!init)
		{
			myTriggers = triggers;
			myConstants = constants;
			myHelpers = helpers;

			CreateThread(NULL, 0, RunningLoop, NULL, 0, NULL);

			//Added 2nd device stuff from here
			wchar_t* deviceGUIDString2 = new wchar_t[256];
			int Device2GUID = GetPrivateProfileString(TEXT("Settings"), TEXT("Device2GUID"), NULL, deviceGUIDString2, 256, settingsFilename);
			char joystick_guid[256];
			sprintf(joystick_guid, "%S", deviceGUIDString2);
			SDL_JoystickGUID guid, dev_guid;
			int numJoysticks = SDL_NumJoysticks();
			std::string njs = std::to_string(numJoysticks);
			((char)njs.c_str());
			for (int i = 0; i < SDL_NumJoysticks(); i++)
			{
				SDL_Joystick* js2 = SDL_JoystickOpen(i);
				joystick_index2 = SDL_JoystickInstanceID(js2);
				SDL_JoystickGUID guid = SDL_JoystickGetGUID(js2);
				char guid_str[1024];
				SDL_JoystickGetGUIDString(guid, guid_str, sizeof(guid_str));
				const char* name = SDL_JoystickName(js2);
				char text[256];
				sprintf(text, "Joystick: %d / Name: %s / GUID: %s\n", i, name, guid_str);
				guid = SDL_JoystickGetGUIDFromString(joystick_guid);
				dev_guid = SDL_JoystickGetGUID(js2);
				SDL_JoystickClose(js2);
				if (!memcmp(&guid, &dev_guid, sizeof(SDL_JoystickGUID)))
				{
					GameController2 = SDL_JoystickOpen(i);
					break;
				}
			}
			init = true;
		}

			helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18D84B, 3, false);
			helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18D852, 3, false);
			helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18D85C, 3, false);
			// Spicetools shit below. STOPS test buttons showing in menu etc if not nop
		    helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18DA89, 6, false);
			helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18DAA3, 3, false);
			helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18DA97, 6, false);

		// Dpad stuff here to set as any button
		char DpadUpChar[256];
		char DpadDownChar[256];
		char DpadLeftChar[256];
		char DpadRightChar[256];
		char DpadUpCharDevice2[256];
		char DpadDownCharDevice2[256];
		char DpadLeftCharDevice2[256];
		char DpadRightCharDevice2[256];
		GetPrivateProfileStringA("Settings", "DpadUp", "", DpadUpChar, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadDown", "", DpadDownChar, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadLeft", "", DpadLeftChar, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadRight", "", DpadRightChar, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadUpDevice2", "", DpadUpCharDevice2, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadDownDevice2", "", DpadDownCharDevice2, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadLeftDevice2", "", DpadLeftCharDevice2, 256, ".\\FFBplugin.ini");
		GetPrivateProfileStringA("Settings", "DpadRightDevice2", "", DpadRightCharDevice2, 256, ".\\FFBplugin.ini");
		std::string exit("ExitButton");
		std::string test("TestButton");
		std::string service("ServiceButton");
		std::string coin("CoinButton");
		std::string view("ViewButton");
		std::string three("ThreeDimensionalButton");
		std::string lvup("leverUp");
		std::string lvdown("leverDown");
		std::string lvleft("leverLeft");
		std::string lvright("leverRight");
		std::string exit2("ExitButtonDevice2");
		std::string test2("TestButtonDevice2");
		std::string service2("ServiceButtonDevice2");
		std::string coin2("CoinButtonDevice2");
		std::string view2("ViewButtonDevice2");
		std::string three2("ThreeDimensionalButtonDevice2");
		std::string lvup2("leverUpDevice2");
		std::string lvdown2("leverDownDevice2");
		std::string lvleft2("leverLeftDevice2");
		std::string lvright2("leverRightDevice2");
		std::string dpdup(DpadUpChar);
		std::string dpddown(DpadDownChar);
		std::string dpdleft(DpadLeftChar);
		std::string dpdright(DpadRightChar);
		std::string dpdup2(DpadUpCharDevice2);
		std::string dpddown2(DpadDownCharDevice2);
		std::string dpdleft2(DpadLeftCharDevice2);
		std::string dpdright2(DpadRightCharDevice2);

		int serviceread = helpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, true);
		int creditnumber = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
		int creditnumber1 = helpers->ReadIntPtr((INT_PTR)creditnumber + 0x20, false);
		int gearnumber = helpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x00953F70, false);
		int gearnumber1 = helpers->ReadIntPtr((INT_PTR)gearnumber + 0x5C, false);
		int gearnumber2 = helpers->ReadIntPtr((INT_PTR)gearnumber1 + 0x390, false);
		int gearnumber3 = helpers->ReadIntPtr((INT_PTR)gearnumber2 + 0x18, false);

		if (SequentialGears == 1)
		{
			helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x95DDA, 3, false);
		}

		const int WHEEL_DEAD_ZONE = (SteeringDeadzone * 100.0);
		const int ACCL_DEAD_ZONE = (1 + PedalDeadzone * 100.0);
		const int BRAKE_DEAD_ZONE = (1 + PedalDeadzone * 100.0);
		const int SETUP_DEAD_ZONE = 20000;

		while (SDL_WaitEvent(&e) != 0)
		{
		int menuvalue = myHelpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x0094BFFC, false);
		int menuvalue1 = myHelpers->ReadIntPtr((INT_PTR)menuvalue + 0x46C, false);

		myTriggers = triggers;
		myConstants = constants;
		myHelpers = helpers;
			if (e.type == SDL_JOYAXISMOTION && ShowAxisForSetup == 0)
			{
				if (e.jaxis.which == joystick_index1)
				{
					if (e.jaxis.axis == InputDeviceWheelSteeringAxis)
					{
						//Left of dead zone
						if (e.jaxis.value < -WHEEL_DEAD_ZONE)
						{
							e.jaxis.value = e.jaxis.value - WHEEL_DEAD_ZONE;
							helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B39, (128 + (e.jaxis.value + WHEEL_DEAD_ZONE) / 255), false);
						}
						//Right of dead zone
						else if (e.jaxis.value > WHEEL_DEAD_ZONE)
						{
							e.jaxis.value = e.jaxis.value + WHEEL_DEAD_ZONE;
							helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B39, (127 + (e.jaxis.value - WHEEL_DEAD_ZONE) / 255), false);
						}
						else if (e.jaxis.value < WHEEL_DEAD_ZONE && e.jaxis.value > -WHEEL_DEAD_ZONE)
						{
							helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B39, 0x7F, false);
						}
					}
					if (InputDeviceWheelReverseAxis == 1)
					{
						if (InputDeviceCombinedPedals == 1)
						{
							if (e.jaxis.axis == InputDeviceWheelAcclAxis)
							{
								if (e.jaxis.value < -ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value + ACCL_DEAD_ZONE;
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B3D, ((-e.jaxis.value + ACCL_DEAD_ZONE) / 128.5), false);
								}
								else if (e.jaxis.value > ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value - ACCL_DEAD_ZONE;
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B41, ((e.jaxis.value + ACCL_DEAD_ZONE) / 128), false);
								}
								else if (e.jaxis.value < ACCL_DEAD_ZONE && e.jaxis.value > -ACCL_DEAD_ZONE)
								{
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B41, 0x00, false);
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B3D, 0x00, false);
								}
							}
						}
						else
						{
							if (e.jaxis.axis == InputDeviceWheelAcclAxis)
							{
								if (e.jaxis.value < -ACCL_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B3D, 127 - e.jaxis.value, false);
								}
								else if (e.jaxis.value > ACCL_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B3D, 128 - e.jaxis.value, false);
								}
							}
							else if (e.jaxis.axis == InputDeviceWheelBrakeAxis)
							{
								if (e.jaxis.value < -BRAKE_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B41, 127 - e.jaxis.value, false);
								}
								else if (e.jaxis.value > BRAKE_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B41, 128 - e.jaxis.value, false);
								}
							}
						}
					}
					else
					{
						if (InputDeviceCombinedPedals == 1)
						{
							if (e.jaxis.axis == InputDeviceWheelAcclAxis)
							{
								if (e.jaxis.value < -ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value - ACCL_DEAD_ZONE;
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B3D, ((e.jaxis.value + ACCL_DEAD_ZONE) / 128), false);
								}
								else if (e.jaxis.value > ACCL_DEAD_ZONE)
								{
									e.jaxis.value = e.jaxis.value + ACCL_DEAD_ZONE;
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B41, ((-e.jaxis.value + ACCL_DEAD_ZONE) / 128), false);
								}
								else if (e.jaxis.value < ACCL_DEAD_ZONE && e.jaxis.value > -ACCL_DEAD_ZONE)
								{
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B41, 0xFF, false);
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B3D, 0xFF, false);
								}
							}
						}
						else
						{
							if (e.jaxis.axis == InputDeviceWheelAcclAxis)
							{
								if (e.jaxis.value < -ACCL_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B3D, 128 + e.jaxis.value, false);
								}
								else if (e.jaxis.value > ACCL_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B3D, 127 + e.jaxis.value, false);
								}
							}
							if (e.jaxis.axis == InputDeviceWheelBrakeAxis)
							{
								if (e.jaxis.value < -BRAKE_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B41, 128 + e.jaxis.value, false);
								}
								else if (e.jaxis.value > BRAKE_DEAD_ZONE)
								{
									e.jaxis.value = (e.jaxis.value / 255);
									helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B41, 127 + e.jaxis.value, false);
								}
							}
						}
					}
				}
			}

			if (ShowAxisForSetup == 1)
			{
				if (e.type == SDL_JOYAXISMOTION)
				{
					if (e.jaxis.which == joystick_index1)
					{
						if (e.jaxis.axis >= 0)
						{
							if (e.jaxis.value < -SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - SETUP_DEAD_ZONE;
								char buff[100];
								sprintf_s(buff, "Axis %d Moved", e.jaxis.axis);
								MessageBoxA(NULL, buff, "", NULL);
							}
							else if (e.jaxis.value > SETUP_DEAD_ZONE)
							{
								char buff[100];
								sprintf_s(buff, "Axis %d Moved", e.jaxis.axis);
								MessageBoxA(NULL, buff, "", NULL);
							}
						}
					}
				}
			}

			if (ShowButtonNumbersForSetup == 1)
			{
				if (e.type == SDL_JOYBUTTONDOWN)
				{
					if (e.jaxis.which == joystick_index1 || e.jaxis.which == joystick_index2)
					{
						if (e.jbutton.button >= 0)
						{
							char buff[100];
							sprintf_s(buff, "Button %d Pressed", e.jbutton.button);
							MessageBoxA(NULL, buff, "", NULL);
						}
					}
				}
			}

			if (e.jhat.type == SDL_JOYHATMOTION)
			{
				if (e.jhat.value == SDL_HAT_CENTERED)
				{
					if (e.jhat.which == joystick_index1)
					{
						if (testbuttonA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x02, false);
							testbuttonA = false;
						}
						if (servicebuttonA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x01, false);
							servicebuttonA = false;
						}
						if (viewbuttonA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x400, false);
							viewbuttonA = false;
						}
						if (threedeebuttonA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x800, false);
							threedeebuttonA = false;
						}						
						if (leverupA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x1040, false);
							leverupA = false;
						}
						if (leverdownA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x2080, false);
							leverdownA = false;
						}
						if (leverleftA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x4000, false);
							leverleftA = false;
						}
						if (leverrightA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x8000, false);
							leverrightA = false;
						}
					}
					else if (e.jhat.which == joystick_index2)
					{
						if (testbuttonA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x02, false);
							testbuttonA = false;
						}
						if (servicebuttonA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x01, false);
							servicebuttonA = false;
						}
						if (viewbuttonA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x400, false);
							viewbuttonA = false;
						}
						if (threedeebuttonA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x800, false);
							threedeebuttonA = false;
						}
						if (leverupA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x1040, false);
							leverupA = false;
						}
						if (leverdownA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x2080, false);
							leverdownA = false;
						}
						if (leverleftA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x4000, false);
							leverleftA = false;
						}
						if (leverrightA)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x8000, false);
							leverrightA = false;
						}
					}
				}
				if (e.jhat.value == SDL_HAT_UP)
				{
					if (e.jhat.which == joystick_index1)
					{
						if (dpdup.compare(exit) == 0)
						{
							system("taskkill /f /im spice.exe");
						}
						if (dpdup.compare(test) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x02, false);
							testbuttonA = true;
						}
						if (dpdup.compare(service) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x01, false);
							servicebuttonA = true;
						}
						if (dpdup.compare(coin) == 0)
						{
							int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
							helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
						}
						if (dpdup.compare(view) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x400, false);
							viewbuttonA = true;
						}
						if (dpdup.compare(three) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x800, false);
							threedeebuttonA = true;
						}
						if (dpdup.compare(lvup) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
							leverupA = true;
						}
						if (dpdup.compare(lvdown) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
							leverdownA = true;
						}
						if (dpdup.compare(lvleft) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
							leverleftA = true;
						}
						if (dpdup.compare(lvright) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
							leverrightA = true;
						}
					}
					else if (e.jhat.which == joystick_index2)
					{
						if (dpdup2.compare(exit2) == 0)
						{
							system("taskkill /f /im spice.exe");
						}
						if (dpdup2.compare(test2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x02, false);
							testbuttonA = true;
						}
						if (dpdup2.compare(service2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x01, false);
							servicebuttonA = true;
						}
						if (dpdup2.compare(coin2) == 0)
						{
							int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
							helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
						}
						if (dpdup2.compare(view2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x400, false);
							viewbuttonA = true;
						}
						if (dpdup2.compare(three2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x800, false);
							threedeebuttonA = true;
						}
						if (dpdup2.compare(lvup2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
							leverupA = true;
						}
						if (dpdup2.compare(lvdown2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
							leverdownA = true;
						}
						if (dpdup2.compare(lvleft2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
							leverleftA = true;
						}
						if (dpdup2.compare(lvright2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
							leverrightA = true;
						}
					}
				}
				if (e.jhat.value == SDL_HAT_DOWN)
				{
					if (e.jhat.which == joystick_index1)
					{
						if (dpddown.compare(exit) == 0)
						{
							system("taskkill /f /im spice.exe");
						}
						if (dpddown.compare(test) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x02, false);
							testbuttonA = true;
						}
						if (dpddown.compare(service) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x01, false);
							servicebuttonA = true;
						}
						if (dpddown.compare(coin) == 0)
						{
							int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
							helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
						}
						if (dpddown.compare(view) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x400, false);
							viewbuttonA = true;
						}
						if (dpddown.compare(three) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x800, false);
							threedeebuttonA = true;
						}
						if (dpddown.compare(lvup) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
							leverupA = true;
						}
						if (dpddown.compare(lvdown) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
							leverdownA = true;
						}
						if (dpddown.compare(lvleft) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
							leverleftA = true;
						}
						if (dpddown.compare(lvright) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
							leverrightA = true;
						}
					}
					else if (e.jhat.which == joystick_index2)
					{
						if (dpddown2.compare(exit2) == 0)
						{
							system("taskkill /f /im spice.exe");
						}
						if (dpdup2.compare(test2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x02, false);
							testbuttonA = true;
						}
						if (dpddown2.compare(service2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x01, false);
							servicebuttonA = true;
						}
						if (dpddown2.compare(coin2) == 0)
						{
							int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
							helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
						}
						if (dpddown2.compare(view2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x400, false);
							viewbuttonA = true;
						}
						if (dpddown2.compare(three2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x800, false);
							threedeebuttonA = true;
						}
						if (dpddown2.compare(lvup2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
							leverupA = true;
						}
						if (dpddown2.compare(lvdown2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
							leverdownA = true;
						}
						if (dpddown2.compare(lvleft2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
							leverleftA = true;
						}
						if (dpddown2.compare(lvright2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
							leverrightA = true;
						}
					}
				}
				if (e.jhat.value == SDL_HAT_LEFT)
					{
					if (e.jhat.which == joystick_index1)
					{
						if (dpdleft.compare(exit) == 0)
						{
							system("taskkill /f /im spice.exe");
						}
						if (dpdleft.compare(test) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x02, false);
							testbuttonA = true;
						}
						if (dpdleft.compare(service) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x01, false);
							servicebuttonA = true;
						}
						if (dpdleft.compare(coin) == 0)
						{
							int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
							helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
						}
						if (dpdleft.compare(view) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x400, false);
							viewbuttonA = true;
						}
						if (dpdleft.compare(three) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x800, false);
							threedeebuttonA = true;
						}
						if (dpdleft.compare(lvup) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
							leverupA = true;
						}
						if (dpdleft.compare(lvdown) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
							leverdownA = true;
						}
						if (dpdleft.compare(lvleft) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
							leverleftA = true;
						}
						if (dpdleft.compare(lvright) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
							leverrightA = true;
						}
					}
				else if (e.jhat.which == joystick_index2)
				{
						if (dpdleft2.compare(exit2) == 0)
						{
							system("taskkill /f /im spice.exe");
						}
						if (dpdleft2.compare(test2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x02, false);
							testbuttonA = true;
						}
						if (dpdleft2.compare(service2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x01, false);
							servicebuttonA = true;
						}
						if (dpdleft2.compare(coin2) == 0)
						{
							int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
							helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
						}
						if (dpdleft2.compare(view2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x400, false);
							viewbuttonA = true;
						}
						if (dpdleft2.compare(three2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x800, false);
							threedeebuttonA = true;
						}
						if (dpdleft2.compare(lvup2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
							leverupA = true;
						}
						if (dpdleft2.compare(lvdown2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
							leverdownA = true;
						}
						if (dpdleft2.compare(lvleft2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
							leverleftA = true;
						}
						if (dpdleft2.compare(lvright2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
							leverrightA = true;
						}
					}
				}
				if (e.jhat.value == SDL_HAT_RIGHT)
				{
					if (e.jhat.which == joystick_index1)
					{
						if (dpdright.compare(exit) == 0)
						{
							system("taskkill /f /im spice.exe");
						}
						if (dpdright.compare(test) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x02, false);
							testbuttonA = true;
						}
						if (dpdright.compare(service) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x01, false);
							servicebuttonA = true;
						}
						if (dpdright.compare(coin) == 0)
						{
							int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
							helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
						}
						if (dpdright.compare(view) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x400, false);
							viewbuttonA = true;
						}
						if (dpdright.compare(three) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x800, false);
							threedeebuttonA = true;
						}
						if (dpdright.compare(lvup) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
							leverupA = true;
						}
						if (dpdright.compare(lvdown) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
							leverdownA = true;
						}
						if (dpdright.compare(lvleft) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
							leverleftA = true;
						}
						if (dpdright.compare(lvright) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
							leverrightA = true;
						}
					}
					else if (e.jhat.which == joystick_index2)
					{
						if (dpdright2.compare(exit2) == 0)
						{
							system("taskkill /f /im spice.exe");
						}
						if (dpdright2.compare(test2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x02, false);
							testbuttonA = true;
						}
						if (dpdright2.compare(service2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x01, false);
							testbuttonA = true;
						}
						if (dpdright2.compare(coin2) == 0)
						{
							int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
							helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
						}
						if (dpdright2.compare(view2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x400, false);
							viewbuttonA = true;
						}
						if (dpdright2.compare(three2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x800, false);
							threedeebuttonA = true;
						}
						if (dpdright2.compare(lvup2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
							leverupA = true;
						}
						if (dpdright2.compare(lvdown2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
							leverdownA = true;
						}
						if (dpdright2.compare(lvleft2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
							leverleftA = true;
						}
						if (dpdright2.compare(lvright2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
							leverrightA = true;
						}
					}
				}
			}

			if (e.type == SDL_JOYBUTTONDOWN)
			{
				if (e.jbutton.which == joystick_index1)
				{
					if (e.jbutton.button == TestButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x02, false);
					}
					if (e.jbutton.button == ExitButton)
					{
						system("taskkill /f /im spice.exe");
					}
					if (e.jbutton.button == ServiceButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x01, false);
					}
					if (e.jbutton.button == CreditButton)
					{
						int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
						helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
					}
					if (e.jbutton.button == ViewButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x400, false);
					}
					if (e.jbutton.button == ThreeDimensionalButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x800, false);
					}
					if ((e.jbutton.button == leverUp) && (SequentialGears == 0))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
					}
					if ((e.jbutton.button == leverUp) && (SequentialGears == 1) && (menuvalue1 == 0x00))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
					}
					if ((e.jbutton.button == leverUp) && (SequentialGears == 1) && (gearnumber3 < 0x06))
					{
						int Writegearnumber = helpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x00953F70, false);
						int Writegearnumber1 = helpers->ReadIntPtr((INT_PTR)Writegearnumber + 0x5C, false);
						int Writegearnumber2 = helpers->ReadIntPtr((INT_PTR)Writegearnumber1 + 0x390, false);
						helpers->WriteIntPtr((INT_PTR)Writegearnumber2 + 0x18, ++gearnumber3, false);
					}
					if ((e.jbutton.button == leverDown) && (SequentialGears == 0))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
					}
					if ((e.jbutton.button == leverDown) && (SequentialGears == 1) && (menuvalue1 == 0x00))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
					}
					if ((e.jbutton.button == leverDown) && (SequentialGears == 1) && (gearnumber3 > 0x01))
					{
						int Writegearnumber = helpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x00953F70, false);
						int Writegearnumber1 = helpers->ReadIntPtr((INT_PTR)Writegearnumber + 0x5C, false);
						int Writegearnumber2 = helpers->ReadIntPtr((INT_PTR)Writegearnumber1 + 0x390, false);
						helpers->WriteIntPtr((INT_PTR)Writegearnumber2 + 0x18, --gearnumber3, false);
					}
					if (e.jbutton.button == leverLeft)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
					}
					if (e.jbutton.button == leverRight)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
					}
					if (e.jbutton.button == Gear1Button)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
					}
					if (e.jbutton.button == Gear2Button)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
					}
					if (e.jbutton.button == Gear3Button)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
					}
					if (e.jbutton.button == Gear4Button)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
					}
					if (e.jbutton.button == Gear5Button)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
					}
					if (e.jbutton.button == Gear6Button)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
					}
				}
				else if (e.jbutton.which == joystick_index2)
				{
					if (e.jbutton.button == TestButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x02, false);
					}
					if (e.jbutton.button == ExitButtonDevice2)
					{
						system("taskkill /f /im spice.exe");
					}
					if (e.jbutton.button == ServiceButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x01, false);
					}
					if (e.jbutton.button == CreditButtonDevice2)
					{
						int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
						helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
					}
					if (e.jbutton.button == ViewButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x400, false);
					}
					if (e.jbutton.button == ThreeDimensionalButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x800, false);
					}
					if ((e.jbutton.button == leverUpDevice2) && (SequentialGears == 0))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
					}
					if ((e.jbutton.button == leverUpDevice2) && (SequentialGears == 1) && (menuvalue1 == 0x00))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
					}
					if ((e.jbutton.button == leverUpDevice2) && (SequentialGears == 1) && (gearnumber3 < 0x06))
					{
						int Writegearnumber = helpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x00953F70, false);
						int Writegearnumber1 = helpers->ReadIntPtr((INT_PTR)Writegearnumber + 0x5C, false);
						int Writegearnumber2 = helpers->ReadIntPtr((INT_PTR)Writegearnumber1 + 0x390, false);
						helpers->WriteIntPtr((INT_PTR)Writegearnumber2 + 0x18, ++gearnumber3, false);
					}
					if (e.jbutton.button == leverDownDevice2 && SequentialGears == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
					}
					if (e.jbutton.button == leverDownDevice2 && SequentialGears == 1 && menuvalue1 == 0x00)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
					}
					if (e.jbutton.button == leverDownDevice2 && SequentialGears == 1 && gearnumber3 > 0x01)
					{
						int Writegearnumber = helpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x00953F70, false);
						int Writegearnumber1 = helpers->ReadIntPtr((INT_PTR)Writegearnumber + 0x5C, false);
						int Writegearnumber2 = helpers->ReadIntPtr((INT_PTR)Writegearnumber1 + 0x390, false);
						helpers->WriteIntPtr((INT_PTR)Writegearnumber2 + 0x18, --gearnumber3, false);
					}
					if (e.jbutton.button == leverLeftDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
					}
					if (e.jbutton.button == leverRightDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
					}
					if (e.jbutton.button == Gear1ButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
					}
					if (e.jbutton.button == Gear2ButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x4000, false);
					}
					if (e.jbutton.button == Gear3ButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
					}
					if (e.jbutton.button == Gear4ButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
					}
					if (e.jbutton.button == Gear5ButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x1040, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
					}
					if (e.jbutton.button == Gear6ButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x2080, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread += 0x8000, false);
					}
				}
			}
			if (e.type == SDL_JOYBUTTONUP)
			{
				if (e.jbutton.which == joystick_index1)
				{
					if (e.jbutton.button == TestButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x02, false);
					}
					if (e.jbutton.button == ServiceButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x01, false);
					}
					if (e.jbutton.button == ViewButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x400, false);
					}
					if (e.jbutton.button == ThreeDimensionalButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x800, false);
					}
					if (e.jbutton.button == leverUp && SequentialGears == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x1040, false);
					}
					if (e.jbutton.button == leverUp && SequentialGears == 1 && menuvalue1 == 0x00)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x1040, false);
					}
					if (e.jbutton.button == leverDown && SequentialGears == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x2080, false);
					}
					if ((e.jbutton.button == leverDown) && (SequentialGears == 1) && (menuvalue1 == 0x00))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x2080, false);
					}
					if (e.jbutton.button == leverLeft)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x4000, false);
					}
					if (e.jbutton.button == leverRight)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x8000, false);
					}
					if (e.jbutton.button == Gear1Button)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x1040, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x4000, false);
					}
					if (e.jbutton.button == Gear2Button)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x2080, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x4000, false);
					}
					if (e.jbutton.button == Gear3Button)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x1040, false);
					}
					if (e.jbutton.button == Gear4Button)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x2080, false);
					}
					if (e.jbutton.button == Gear5Button)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x1040, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x8000, false);
					}
					if (e.jbutton.button == Gear6Button)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x2080, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x8000, false);
					}
				}
				else if (e.jbutton.which == joystick_index2)
				{
					if (e.jbutton.button == TestButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x02, false);
					}
					if (e.jbutton.button == ServiceButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x01, false);
					}
					if (e.jbutton.button == ViewButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x400, false);
					}
					if (e.jbutton.button == ThreeDimensionalButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x800, false);
					}
					if ((e.jbutton.button == leverUpDevice2) && (SequentialGears == 0))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x1040, false);
					}
					if ((e.jbutton.button == leverUpDevice2) && (SequentialGears == 1) && (menuvalue1 == 0x00))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x1040, false);
					}
					if ((e.jbutton.button == leverDownDevice2) && (SequentialGears == 0))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x2080, false);
					}
					if ((e.jbutton.button == leverDownDevice2) && (SequentialGears == 1) && (menuvalue1 == 0x00))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x2080, false);
					}
					if (e.jbutton.button == leverLeftDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x4000, false);
					}
					if (e.jbutton.button == leverRightDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x8000, false);
					}
					if (e.jbutton.button == Gear1ButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x1040, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x4000, false);
					}
					if (e.jbutton.button == Gear2ButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x2080, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x4000, false);
					}
					if (e.jbutton.button == Gear3ButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x1040, false);
					}
					if (e.jbutton.button == Gear4ButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x2080, false);
					}
					if (e.jbutton.button == Gear5ButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x1040, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x8000, false);
					}
					if (e.jbutton.button == Gear6ButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x2080, false);
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, serviceread -= 0x8000, false);
					}
				}
			}
		}
	}
	else
	{
		if (!init)
		{
			myTriggers = triggers;
			myConstants = constants;
			myHelpers = helpers;
			CreateThread(NULL, 0, RunningLoop, NULL, 0, NULL);
			init = true;
		}

		while (SDL_WaitEvent(&e) != 0)
		{
			myTriggers = triggers;
			myConstants = constants;
			myHelpers = helpers;
		}
	}
}