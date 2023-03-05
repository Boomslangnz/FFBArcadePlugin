#include "../Common Files/Game.h"
#include <string>
#include <windows.h>
#include "SDL.h"
static DWORD imageBase;
extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;
static bool testA;
static bool serviceA;
static bool startA;
static bool vr1A;
static bool vr2A;
static bool vr3A;
static bool vr4A;
static bool shift1A;
static bool shift2A;
static bool shift3A;
static bool shift4A;
static bool shiftupA;
static bool shiftdwnA;
static bool coin1A;
static bool coin2A;
static bool ShiftUpPressed;
static bool ShiftDownPressed;
static bool Inputsinit = false;
extern SDL_Event e;
extern HWND hWndM2;

static INT_PTR SteeringAddress;
static INT_PTR AcclAddress;
static INT_PTR BrakeAddress;
static INT_PTR Button1Address;
static INT_PTR Button2Address;

static int SteeringValue;
static int AcclValue;
static int BrakeValue;
static UINT8 GearValue;

extern wchar_t* settingsFilename;
static int InputDeviceWheelEnable = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelEnable"), 0, settingsFilename);
static int InputDeviceWheelSteeringAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelSteeringAxis"), 0, settingsFilename);
static int InputDeviceWheelAcclAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelAcclAxis"), 0, settingsFilename);
static int InputDeviceWheelBrakeAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelBrakeAxis"), 0, settingsFilename);
static int InputDeviceWheelSteeringAxisDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelSteeringAxisDevice2 "), 0, settingsFilename);
static int InputDeviceWheelAcclAxisDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelAcclAxisDevice2 "), 0, settingsFilename);
static int InputDeviceWheelBrakeAxisDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelBrakeAxisDevice2 "), 0, settingsFilename);
static int InputDeviceWheelReverseAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelReverseAxis"), 0, settingsFilename);
static int InputDeviceCombinedPedals = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceCombinedPedals"), 0, settingsFilename);
static int SteeringDeadzone = GetPrivateProfileInt(TEXT("Settings"), TEXT("SteeringDeadzone"), 0, settingsFilename);
static int PedalDeadzone = GetPrivateProfileInt(TEXT("Settings"), TEXT("PedalDeadzone"), 0, settingsFilename);
static int ShowButtonNumbersForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowButtonNumbersForSetup"), 0, settingsFilename);
static int ShowKeyBoardNameForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowKeyBoardNameForSetup"), 0, settingsFilename);
static int ShowAxisForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowAxisForSetup"), 0, settingsFilename);
static int ExitButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ExitButton"), 0, settingsFilename);
static int TestButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("TestButton"), 0, settingsFilename);
static int ServiceButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ServiceButton"), 0, settingsFilename);
static int Coin1Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("Coin1Button"), 0, settingsFilename);
static int Coin2Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("Coin2Button"), 0, settingsFilename);
static int VR1Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("VR1Button"), 0, settingsFilename);
static int VR2Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("VR2Button"), 0, settingsFilename);
static int VR3Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("VR3Button"), 0, settingsFilename);
static int VR4Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("VR4Button"), 0, settingsFilename);
static int StartButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("StartButton"), 0, settingsFilename);
static int Shift1Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("Shift1Button"), 0, settingsFilename);
static int Shift2Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("Shift2Button"), 0, settingsFilename);
static int Shift3Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("Shift3Button"), 0, settingsFilename);
static int Shift4Button = GetPrivateProfileInt(TEXT("Settings"), TEXT("Shift4Button"), 0, settingsFilename);
static int ShiftUpButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShiftUpButton"), 0, settingsFilename);
static int ShiftDownButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShiftDownButton"), 0, settingsFilename);
static int ExitButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ExitButtonDevice2"), 0, settingsFilename);
static int TestButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("TestButtonDevice2"), 0, settingsFilename);
static int ServiceButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ServiceButtonDevice2"), 0, settingsFilename);
static int Coin1ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Coin1ButtonDevice2"), 0, settingsFilename);
static int Coin2ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Coin2ButtonDevice2"), 0, settingsFilename);
static int VR1ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("VR1ButtonDevice2"), 0, settingsFilename);
static int VR2ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("VR2ButtonDevice2"), 0, settingsFilename);
static int VR3ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("VR3ButtonDevice2"), 0, settingsFilename);
static int VR4ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("VR4ButtonDevice2"), 0, settingsFilename);
static int StartButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("StartButtonDevice2"), 0, settingsFilename);
static int Shift1ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Shift1ButtonDevice2"), 0, settingsFilename);
static int Shift2ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Shift2ButtonDevice2"), 0, settingsFilename);
static int Shift3ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Shift3ButtonDevice2"), 0, settingsFilename);
static int Shift4ButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Shift4ButtonDevice2"), 0, settingsFilename);
static int ShiftUpButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShiftUpButtonDevice2"), 0, settingsFilename);
static int ShiftDownButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShiftDownButtonDevice2"), 0, settingsFilename);

void M2EmulatorDaytonaUSAInputsEnabled(Helpers* helpers)
{
	if (!Inputsinit)
	{
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
				joystick_index2 = SDL_JoystickInstanceID(GameController2);
				break;
			}
		}

		imageBase = (DWORD)GetModuleHandleA(0);
		SteeringAddress = imageBase + 0x1AA876;
		AcclAddress = imageBase + 0x1AA874;
		BrakeAddress = imageBase + 0x1AA875;
		Button1Address = imageBase + 0x1AA87A;
		Button2Address = imageBase + 0x1AA879;

		helpers->WriteByte(Button1Address, 0xFF, false);
		helpers->WriteByte(Button2Address, 0xFF, false);
		helpers->WriteByte(SteeringAddress, 0x80, false);
		helpers->WriteByte(AcclAddress, 0x00, false);
		helpers->WriteByte(BrakeAddress, 0x00, false);
		Inputsinit = true;
	}

	// Dpad stuff here to set as any button
	char DpadUpChar[256];
	char DpadDownChar[256];
	char DpadLeftChar[256];
	char DpadRightChar[256];
	char DpadUpCharDevice2[256];
	char DpadDownCharDevice2[256];
	char DpadLeftCharDevice2[256];
	char DpadRightCharDevice2[256];
	char KeyBrdExitChar[256];
	char KeyBrdTestChar[256];
	char KeyBrdServiceChar[256];
	char KeyBrdCoin1Char[256];
	char KeyBrdCoin2Char[256];
	char KeyBrdVR1Char[256];
	char KeyBrdVR2Char[256];
	char KeyBrdVR3Char[256];
	char KeyBrdVR4Char[256];
	char KeyBrdStartChar[256];
	char KeyBrdShift1Char[256];
	char KeyBrdShift2Char[256];
	char KeyBrdShift3Char[256];
	char KeyBrdShift4Char[256];
	char KeyBrdShiftUpChar[256];
	char KeyBrdShiftDownChar[256];
	GetPrivateProfileStringA("Settings", "DpadUp", "", DpadUpChar, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "DpadDown", "", DpadDownChar, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "DpadLeft", "", DpadLeftChar, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "DpadRight", "", DpadRightChar, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "DpadUpDevice2", "", DpadUpCharDevice2, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "DpadDownDevice2", "", DpadDownCharDevice2, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "DpadLeftDevice2", "", DpadLeftCharDevice2, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "DpadRightDevice2", "", DpadRightCharDevice2, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "ExitButtonKeyBrd", "", KeyBrdExitChar, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "TestButtonKeyBrd", "", KeyBrdTestChar, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "ServiceButtonKeyBrd", "", KeyBrdServiceChar, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "Coin1ButtonKeyBrd", "", KeyBrdCoin1Char, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "Coin2ButtonKeyBrd", "", KeyBrdCoin2Char, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "VR1ButtonKeyBrd", "", KeyBrdVR1Char, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "VR2ButtonKeyBrd", "", KeyBrdVR2Char, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "VR3ButtonKeyBrd", "", KeyBrdVR3Char, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "VR4ButtonKeyBrd", "", KeyBrdVR4Char, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "StartButtonKeyBrd", "", KeyBrdStartChar, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "Shift1ButtonKeyBrd", "", KeyBrdShift1Char, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "Shift2ButtonKeyBrd", "", KeyBrdShift2Char, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "Shift3ButtonKeyBrd", "", KeyBrdShift3Char, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "Shift4ButtonKeyBrd", "", KeyBrdShift4Char, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "ShiftUpButtonKeyBrd", "", KeyBrdShiftUpChar, 256, ".\\FFBplugin.ini");
	GetPrivateProfileStringA("Settings", "ShiftDownButtonKeyBrd", "", KeyBrdShiftDownChar, 256, ".\\FFBplugin.ini");
	std::string exit("ExitButton");
	std::string test("TestButton");
	std::string service("ServiceButton");
	std::string coin1("Coin1Button");
	std::string coin2("Coin2Button");
	std::string vr1("VR1Button");
	std::string vr2("VR2Button");
	std::string vr3("VR3Button");
	std::string vr4("VR4Button");
	std::string start("StartButton");
	std::string shift1("Shift1Button");
	std::string shift2("Shift2Button");
	std::string shift3("Shift3Button");
	std::string shift4("Shift4Button");
	std::string shiftup("ShiftUpButton");
	std::string shiftdwn("ShiftDownButton");
	std::string exit2("ExitButtonDevice2");
	std::string test2("TestButtonDevice2");
	std::string service2("ServiceButtonDevice2");
	std::string coin12("Coin1ButtonDevice2");
	std::string coin22("Coin2ButtonDevice2");
	std::string vr12("VR1ButtonDevice2");
	std::string vr22("VR2ButtonDevice2");
	std::string vr32("VR3ButtonDevice2");
	std::string vr42("VR4ButtonDevice2");
	std::string start2("StartButtonDevice2");
	std::string shift12("Shift1ButtonDevice2");
	std::string shift22("Shift2ButtonDevice2");
	std::string shift32("Shift3ButtonDevice2");
	std::string shift42("Shift4ButtonDevice2");
	std::string shiftup2("ShiftUpButtonDevice2");
	std::string shiftdwn2("ShiftDownButtonDevice2");
	std::string dpdup(DpadUpChar);
	std::string dpddown(DpadDownChar);
	std::string dpdleft(DpadLeftChar);
	std::string dpdright(DpadRightChar);
	std::string dpdup2(DpadUpCharDevice2);
	std::string dpddown2(DpadDownCharDevice2);
	std::string dpdleft2(DpadLeftCharDevice2);
	std::string dpdright2(DpadRightCharDevice2);
	std::string KeyBrdExit(KeyBrdExitChar);
	std::string KeyBrdTest(KeyBrdTestChar);
	std::string KeyBrdService(KeyBrdServiceChar);
	std::string KeyBrdCoin1(KeyBrdCoin1Char);
	std::string KeyBrdCoin2(KeyBrdCoin2Char);
	std::string KeyBrdVR1(KeyBrdVR1Char);
	std::string KeyBrdVR2(KeyBrdVR2Char);
	std::string KeyBrdVR3(KeyBrdVR3Char);
	std::string KeyBrdVR4(KeyBrdVR4Char);
	std::string KeyBrdStart(KeyBrdStartChar);
	std::string KeyBrdShift1(KeyBrdShift1Char);
	std::string KeyBrdShift2(KeyBrdShift2Char);
	std::string KeyBrdShift3(KeyBrdShift3Char);
	std::string KeyBrdShift4(KeyBrdShift4Char);
	std::string KeyBrdShiftUp(KeyBrdShiftUpChar);
	std::string KeyBrdShiftDown(KeyBrdShiftDownChar);

	const int WHEEL_DEAD_ZONE = (SteeringDeadzone * 100.0);
	const int ACCL_DEAD_ZONE = (1 + PedalDeadzone * 100.0);
	const int BRAKE_DEAD_ZONE = (1 + PedalDeadzone * 100.0);
	const int SETUP_DEAD_ZONE = 20000;

	SDL_Window* w =  SDL_CreateWindowFrom(hWndM2);
	SDL_MinimizeWindow(w);
	SDL_RestoreWindow(w);

	while (SDL_WaitEvent(&e) != 0)
	{
		UINT8 button1read = helpers->ReadByte(Button1Address, false);
		UINT8 button2read = helpers->ReadByte(Button2Address, false);

		INT_PTR Rambase = helpers->ReadIntPtr(0x1AA888, true);
		INT_PTR Rambase1 = helpers->ReadIntPtr(Rambase + 0x100, false);
		GearValue = helpers->ReadByte(Rambase1 + 0x52CC, false);

		if ((e.type == SDL_JOYAXISMOTION) && (ShowAxisForSetup == 0))
		{
			if (e.jaxis.which == joystick_index1)
			{
				if (e.jaxis.axis == InputDeviceWheelSteeringAxis)
				{
					if (e.jaxis.value < -WHEEL_DEAD_ZONE)
					{
						e.jaxis.value = e.jaxis.value - WHEEL_DEAD_ZONE;
						SteeringValue = 128 + (e.jaxis.value + WHEEL_DEAD_ZONE) / 255;
					}
					else if (e.jaxis.value > WHEEL_DEAD_ZONE)
					{
						e.jaxis.value = e.jaxis.value + WHEEL_DEAD_ZONE;
						SteeringValue = 127 + (e.jaxis.value - WHEEL_DEAD_ZONE) / 255;
					}
					else
					{
						SteeringValue = 0x80;
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
								AcclValue = (-e.jaxis.value + ACCL_DEAD_ZONE) / 128.5;
							}
							else if (e.jaxis.value > ACCL_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - ACCL_DEAD_ZONE;
								BrakeValue = (e.jaxis.value + ACCL_DEAD_ZONE) / 128;
							}
							else
							{
								AcclValue = 0x00;
								BrakeValue = 0x00;
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
								AcclValue = 127 - e.jaxis.value;
							}
							else if (e.jaxis.value > ACCL_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								AcclValue = 128 - e.jaxis.value;
							}
						}
						else if (e.jaxis.axis == InputDeviceWheelBrakeAxis)
						{
							if (e.jaxis.value < -BRAKE_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								BrakeValue = 127 - e.jaxis.value;
							}
							else if (e.jaxis.value > BRAKE_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								BrakeValue = 128 - e.jaxis.value;
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
								AcclValue = (e.jaxis.value + ACCL_DEAD_ZONE) / 128;
							}
							else if (e.jaxis.value > ACCL_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + ACCL_DEAD_ZONE;
								BrakeValue = (-e.jaxis.value + ACCL_DEAD_ZONE) / 128;
							}
							else if ((e.jaxis.value < ACCL_DEAD_ZONE) && (e.jaxis.value > -ACCL_DEAD_ZONE))
							{
								AcclValue = 0xFF;
								BrakeValue = 0xFF;
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
								AcclValue = 128 + e.jaxis.value;
							}
							else if (e.jaxis.value > ACCL_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								AcclValue = 127 + e.jaxis.value;
							}
						}
						if (e.jaxis.axis == InputDeviceWheelBrakeAxis)
						{
							if (e.jaxis.value < -BRAKE_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								BrakeValue = 128 + e.jaxis.value;
							}
							else if (e.jaxis.value > BRAKE_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								BrakeValue = 127 + e.jaxis.value;
							}
						}
					}
				}
				helpers->WriteByte(SteeringAddress, SteeringValue, false);
				helpers->WriteByte(AcclAddress, AcclValue, false);
				helpers->WriteByte(BrakeAddress, BrakeValue, false);
			}
			if (e.jaxis.which == joystick_index2)
			{
				if (e.jaxis.axis == InputDeviceWheelSteeringAxisDevice2)
				{
					if (e.jaxis.value < -WHEEL_DEAD_ZONE)
					{
						e.jaxis.value = e.jaxis.value - WHEEL_DEAD_ZONE;
						SteeringValue = 128 + (e.jaxis.value + WHEEL_DEAD_ZONE) / 255;
					}
					else if (e.jaxis.value > WHEEL_DEAD_ZONE)
					{
						e.jaxis.value = e.jaxis.value + WHEEL_DEAD_ZONE;
						SteeringValue = 127 + (e.jaxis.value - WHEEL_DEAD_ZONE) / 255;
					}
					else
					{
						SteeringValue = 0x80;
					}
				}
				if (InputDeviceWheelReverseAxis == 1)
				{
					if (InputDeviceCombinedPedals == 1)
					{
						if (e.jaxis.axis == InputDeviceWheelAcclAxisDevice2)
						{
							if (e.jaxis.value < -ACCL_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + ACCL_DEAD_ZONE;
								AcclValue = (-e.jaxis.value + ACCL_DEAD_ZONE) / 128.5;
							}
							else if (e.jaxis.value > ACCL_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - ACCL_DEAD_ZONE;
								BrakeValue = (e.jaxis.value + ACCL_DEAD_ZONE) / 128;
							}
							else
							{
								AcclValue = 0x00;
								BrakeValue = 0x00;
							}
						}
					}
					else
					{
						if (e.jaxis.axis == InputDeviceWheelAcclAxisDevice2)
						{
							if (e.jaxis.value < -ACCL_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								AcclValue = 127 - e.jaxis.value;
							}
							else if (e.jaxis.value > ACCL_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								AcclValue = 128 - e.jaxis.value;
							}
						}
						else if (e.jaxis.axis == InputDeviceWheelBrakeAxisDevice2)
						{
							if (e.jaxis.value < -BRAKE_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								BrakeValue = 127 - e.jaxis.value;
							}
							else if (e.jaxis.value > BRAKE_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								BrakeValue = 128 - e.jaxis.value;
							}
						}
					}
				}
				else
				{
					if (InputDeviceCombinedPedals == 1)
					{
						if (e.jaxis.axis == InputDeviceWheelAcclAxisDevice2)
						{
							if (e.jaxis.value < -ACCL_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - ACCL_DEAD_ZONE;
								AcclValue = (e.jaxis.value + ACCL_DEAD_ZONE) / 128;
							}
							else if (e.jaxis.value > ACCL_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + ACCL_DEAD_ZONE;
								BrakeValue = (-e.jaxis.value + ACCL_DEAD_ZONE) / 128;
							}
							else if ((e.jaxis.value < ACCL_DEAD_ZONE) && (e.jaxis.value > -ACCL_DEAD_ZONE))
							{
								AcclValue = 0xFF;
								BrakeValue = 0xFF;
							}
						}
					}
					else
					{
						if (e.jaxis.axis == InputDeviceWheelAcclAxisDevice2)
						{
							if (e.jaxis.value < -ACCL_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								AcclValue = 128 + e.jaxis.value;
							}
							else if (e.jaxis.value > ACCL_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								AcclValue = 127 + e.jaxis.value;
							}
						}
						if (e.jaxis.axis == InputDeviceWheelBrakeAxisDevice2)
						{
							if (e.jaxis.value < -BRAKE_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								BrakeValue = 128 + e.jaxis.value;
							}
							else if (e.jaxis.value > BRAKE_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								BrakeValue = 127 + e.jaxis.value;
							}
						}
					}
				}
				helpers->WriteByte(SteeringAddress, SteeringValue, false);
				helpers->WriteByte(AcclAddress, AcclValue, false);
				helpers->WriteByte(BrakeAddress, BrakeValue, false);
			}
		}

		if (ShowAxisForSetup)
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

		if (ShowButtonNumbersForSetup)
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

		if (ShowKeyBoardNameForSetup)
		{
			if (e.type == SDL_KEYDOWN)
			{
				const char* KeyPressed = SDL_GetKeyName(e.key.keysym.sym);

				char buff[100];
				sprintf_s(buff, "Key %s Pressed", KeyPressed);
				MessageBoxA(NULL, buff, "", NULL);
			}
		}

		if (e.jhat.type == SDL_JOYHATMOTION)
		{
			if (e.jhat.value == SDL_HAT_CENTERED)
			{
				if (e.jhat.which == joystick_index1 || e.jhat.which == joystick_index2)
				{
					if (testA)
					{
						helpers->WriteByte(Button2Address, button2read += 0x04, false);
						testA = false;
					}
					if (serviceA)
					{
						helpers->WriteByte(Button2Address, button2read += 0x08, false);
						serviceA = false;
					}
					if (startA)
					{
						helpers->WriteByte(Button2Address, button2read += 0x10, false);
						startA = false;
					}
					if (vr1A)
					{
						helpers->WriteByte(Button2Address, button2read += 0x20, false);
						vr1A = false;
					}
					if (vr2A)
					{
						helpers->WriteByte(Button2Address, button2read += 0x40, false);
						vr2A = false;
					}
					if (vr3A)
					{
						helpers->WriteByte(Button2Address, button2read += 0x80, false);
						vr3A = false;
					}
					if (vr4A)
					{
						helpers->WriteByte(Button1Address, button1read += 0x01, false);
						vr4A = false;
					}
					if (coin1A)
					{
						helpers->WriteByte(Button2Address, button2read += 0x01, false);
						coin1A = false;
					}
					if (coin2A)
					{
						helpers->WriteByte(Button2Address, button2read += 0x02, false);
						coin2A = false;
					}
					if (shiftupA)
						shiftupA = false;
					if (shiftdwnA)
						shiftdwnA = false;
				}
			}
			if (e.jhat.value == SDL_HAT_UP)
			{
				if (e.jhat.which == joystick_index1)
				{
					if (dpdup.compare(exit) == 0)
					{
						SendMessage(hWndM2, WM_CLOSE, NULL, NULL);
					}
					if (dpdup.compare(test) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x04, false);
						testA = true;
					}
					if (dpdup.compare(service) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x08, false);
						serviceA = true;
					}
					if (dpdup.compare(coin1) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x01, false);
						coin1A = true;
					}
					if (dpdup.compare(coin2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x02, false);
						coin2A = true;
					}
					if (dpdup.compare(start) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x10, false);
						startA = true;
					}
					if (dpdup.compare(shift1) == 0)
					{
						helpers->WriteByte(Button1Address, 0xAF, false);
						shift1A = true;
					}
					if (dpdup.compare(shift2) == 0)
					{
						helpers->WriteByte(Button1Address, 0x9F, false);
						shift2A = true;
					}
					if (dpdup.compare(shift3) == 0)
					{
						helpers->WriteByte(Button1Address, 0xEF, false);
						shift3A = true;
					}
					if (dpdup.compare(shift4) == 0)
					{
						helpers->WriteByte(Button1Address, 0xDF, false);
						shift4A = true;
					}
					if (dpdup.compare(shiftup) == 0)
					{
						switch (GearValue)
						{
						case 0x00:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x01:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0xDF, false);
							break;
						}
						shiftupA = true;
					}
					if (dpdup.compare(shiftdwn) == 0)
					{
						switch (GearValue)
						{
						case 0x01:
							helpers->WriteByte(Button1Address, 0xAF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x03:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						}
						shiftdwnA = true;
					}
					if (dpdup.compare(vr1) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x20, false);
						vr1A = true;
					}
					if (dpdup.compare(vr2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x40, false);
						vr2A = true;
					}
					if (dpdup.compare(vr3) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x80, false);
						vr3A = true;
					}
					if (dpdup.compare(vr4) == 0)
					{
						helpers->WriteByte(Button1Address, button1read -= 0x01, false);
						vr4A = true;
					}
				}
				else if (e.jhat.which == joystick_index2)
				{
					if (dpdup2.compare(exit2) == 0)
					{
						SendMessage(hWndM2, WM_CLOSE, NULL, NULL);
					}
					if (dpdup2.compare(test2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x04, false);
						testA = true;
					}
					if (dpdup2.compare(service2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x08, false);
						serviceA = true;
					}
					if (dpdup2.compare(coin12) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x01, false);
						coin1A = true;
					}
					if (dpdup2.compare(coin22) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x02, false);
						coin2A = true;
					}
					if (dpdup2.compare(start2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x10, false);
						startA = true;
					}
					if (dpdup2.compare(shift12) == 0)
					{
						helpers->WriteByte(Button1Address, 0xAF, false);
						shift1A = true;
					}
					if (dpdup2.compare(shift22) == 0)
					{
						helpers->WriteByte(Button1Address, 0x9F, false);
						shift2A = true;
					}
					if (dpdup2.compare(shift32) == 0)
					{
						helpers->WriteByte(Button1Address, 0xEF, false);
						shift3A = true;
					}
					if (dpdup2.compare(shift42) == 0)
					{
						helpers->WriteByte(Button1Address, 0xDF, false);
						shift4A = true;
					}
					if (dpdup2.compare(shiftup2) == 0)
					{
						switch (GearValue)
						{
						case 0x00:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x01:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0xDF, false);
							break;
						}
						shiftupA = true;
					}
					if (dpdup2.compare(shiftdwn2) == 0)
					{
						switch (GearValue)
						{
						case 0x01:
							helpers->WriteByte(Button1Address, 0xAF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x03:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						}
						shiftdwnA = true;
					}
					if (dpdup2.compare(vr12) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x20, false);
						vr1A = true;
					}
					if (dpdup2.compare(vr22) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x40, false);
						vr2A = true;
					}
					if (dpdup2.compare(vr32) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x80, false);
						vr3A = true;
					}
					if (dpdup2.compare(vr42) == 0)
					{
						helpers->WriteByte(Button1Address, button1read -= 0x01, false);
						vr4A = true;
					}
				}
			}
			if (e.jhat.value == SDL_HAT_DOWN)
			{
				if (e.jhat.which == joystick_index1)
				{
					if (dpddown.compare(exit) == 0)
					{
						SendMessage(hWndM2, WM_CLOSE, NULL, NULL);
					}
					if (dpddown.compare(test) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x04, false);
						testA = true;
					}
					if (dpddown.compare(service) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x08, false);
						serviceA = true;
					}
					if (dpddown.compare(coin1) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x01, false);
						coin1A = true;
					}
					if (dpddown.compare(coin2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x02, false);
						coin2A = true;
					}
					if (dpddown.compare(start) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x10, false);
						startA = true;
					}
					if (dpddown.compare(shift1) == 0)
					{
						helpers->WriteByte(Button1Address, 0xAF, false);
						shift1A = true;
					}
					if (dpddown.compare(shift2) == 0)
					{
						helpers->WriteByte(Button1Address, 0x9F, false);
						shift2A = true;
					}
					if (dpddown.compare(shift3) == 0)
					{
						helpers->WriteByte(Button1Address, 0xEF, false);
						shift3A = true;
					}
					if (dpddown.compare(shift4) == 0)
					{
						helpers->WriteByte(Button1Address, 0xDF, false);
						shift4A = true;
					}
					if (dpddown.compare(shiftup) == 0)
					{
						switch (GearValue)
						{
						case 0x00:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x01:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0xDF, false);
							break;
						}
						shiftupA = true;
					}
					if (dpddown.compare(shiftdwn) == 0)
					{
						switch (GearValue)
						{
						case 0x01:
							helpers->WriteByte(Button1Address, 0xAF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x03:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						}
						shiftdwnA = true;
					}
					if (dpddown.compare(vr1) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x20, false);
						vr1A = true;
					}
					if (dpddown.compare(vr2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x40, false);
						vr2A = true;
					}
					if (dpddown.compare(vr3) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x80, false);
						vr3A = true;
					}
					if (dpddown.compare(vr4) == 0)
					{
						helpers->WriteByte(Button1Address, button1read -= 0x01, false);
						vr4A = true;
					}
				}
				else if (e.jhat.which == joystick_index2)
				{
					if (dpddown2.compare(exit2) == 0)
					{
						SendMessage(hWndM2, WM_CLOSE, NULL, NULL);
					}
					if (dpddown2.compare(test2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x04, false);
						testA = true;
					}
					if (dpddown2.compare(service2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x08, false);
						serviceA = true;
					}
					if (dpddown2.compare(coin12) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x01, false);
						coin1A = true;
					}
					if (dpddown2.compare(coin22) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x02, false);
						coin2A = true;
					}
					if (dpddown2.compare(start2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x10, false);
						startA = true;
					}
					if (dpddown2.compare(shift12) == 0)
					{
						helpers->WriteByte(Button1Address, 0xAF, false);
						shift1A = true;
					}
					if (dpddown2.compare(shift22) == 0)
					{
						helpers->WriteByte(Button1Address, 0x9F, false);
						shift2A = true;
					}
					if (dpddown2.compare(shift32) == 0)
					{
						helpers->WriteByte(Button1Address, 0xEF, false);
						shift3A = true;
					}
					if (dpddown2.compare(shift42) == 0)
					{
						helpers->WriteByte(Button1Address, 0xDF, false);
						shift4A = true;
					}
					if (dpddown2.compare(shiftup2) == 0)
					{
						switch (GearValue)
						{
						case 0x00:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x01:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0xDF, false);
							break;
						}
						shiftupA = true;
					}
					if (dpddown2.compare(shiftdwn2) == 0)
					{
						switch (GearValue)
						{
						case 0x01:
							helpers->WriteByte(Button1Address, 0xAF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x03:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						}
						shiftdwnA = true;
					}
					if (dpddown2.compare(vr12) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x20, false);
						vr1A = true;
					}
					if (dpddown2.compare(vr22) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x40, false);
						vr2A = true;
					}
					if (dpddown2.compare(vr32) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x80, false);
						vr3A = true;
					}
					if (dpddown2.compare(vr42) == 0)
					{
						helpers->WriteByte(Button1Address, button1read -= 0x01, false);
						vr4A = true;
					}
				}
			}
			if (e.jhat.value == SDL_HAT_LEFT)
			{
				if (e.jhat.which == joystick_index1)
				{
					if (dpdleft.compare(exit) == 0)
					{
						SendMessage(hWndM2, WM_CLOSE, NULL, NULL);
					}
					if (dpdleft.compare(test) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x04, false);
						testA = true;
					}
					if (dpdleft.compare(service) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x08, false);
						serviceA = true;
					}
					if (dpdleft.compare(coin1) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x01, false);
						coin1A = true;
					}
					if (dpdleft.compare(coin2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x02, false);
						coin2A = true;
					}
					if (dpdleft.compare(start) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x10, false);
						startA = true;
					}
					if (dpdleft.compare(shift1) == 0)
					{
						helpers->WriteByte(Button1Address, 0xAF, false);
						shift1A = true;
					}
					if (dpdleft.compare(shift2) == 0)
					{
						helpers->WriteByte(Button1Address, 0x9F, false);
						shift2A = true;
					}
					if (dpdleft.compare(shift3) == 0)
					{
						helpers->WriteByte(Button1Address, 0xEF, false);
						shift3A = true;
					}
					if (dpdleft.compare(shift4) == 0)
					{
						helpers->WriteByte(Button1Address, 0xDF, false);
						shift4A = true;
					}
					if (dpdleft.compare(shiftup) == 0)
					{
						switch (GearValue)
						{
						case 0x00:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x01:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0xDF, false);
							break;
						}
						shiftupA = true;
					}
					if (dpdleft.compare(shiftdwn) == 0)
					{
						switch (GearValue)
						{
						case 0x01:
							helpers->WriteByte(Button1Address, 0xAF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x03:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						}
						shiftdwnA = true;
					}
					if (dpdleft.compare(vr1) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x20, false);
						vr1A = true;
					}
					if (dpdleft.compare(vr2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x40, false);
						vr2A = true;
					}
					if (dpdleft.compare(vr3) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x80, false);
						vr3A = true;
					}
					if (dpdleft.compare(vr4) == 0)
					{
						helpers->WriteByte(Button1Address, button1read -= 0x01, false);
						vr4A = true;
					}
				}
				else if (e.jhat.which == joystick_index2)
				{
					if (dpdleft2.compare(exit2) == 0)
					{
						SendMessage(hWndM2, WM_CLOSE, NULL, NULL);
					}
					if (dpdleft2.compare(test2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x04, false);
						testA = true;
					}
					if (dpdleft2.compare(service2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x08, false);
						serviceA = true;
					}
					if (dpdleft2.compare(coin12) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x01, false);
						coin1A = true;
					}
					if (dpdleft2.compare(coin22) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x02, false);
						coin2A = true;
					}
					if (dpdleft2.compare(start2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x10, false);
						startA = true;
					}
					if (dpdleft2.compare(shift12) == 0)
					{
						helpers->WriteByte(Button1Address, 0xAF, false);
						shift1A = true;
					}
					if (dpdleft2.compare(shift22) == 0)
					{
						helpers->WriteByte(Button1Address, 0x9F, false);
						shift2A = true;
					}
					if (dpdleft2.compare(shift32) == 0)
					{
						helpers->WriteByte(Button1Address, 0xEF, false);
						shift3A = true;
					}
					if (dpdleft2.compare(shift42) == 0)
					{
						helpers->WriteByte(Button1Address, 0xDF, false);
						shift4A = true;
					}
					if (dpdleft2.compare(shiftup2) == 0)
					{
						switch (GearValue)
						{
						case 0x00:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x01:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0xDF, false);
							break;
						}
						shiftupA = true;
					}
					if (dpdleft2.compare(shiftdwn2) == 0)
					{
						switch (GearValue)
						{
						case 0x01:
							helpers->WriteByte(Button1Address, 0xAF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x03:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						}
						shiftdwnA = true;
					}
					if (dpdleft2.compare(vr12) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x20, false);
						vr1A = true;
					}
					if (dpdleft2.compare(vr22) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x40, false);
						vr2A = true;
					}
					if (dpdleft2.compare(vr32) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x80, false);
						vr3A = true;
					}
					if (dpdleft2.compare(vr42) == 0)
					{
						helpers->WriteByte(Button1Address, button1read -= 0x01, false);
						vr4A = true;
					}
				}
			}
			if (e.jhat.value == SDL_HAT_RIGHT)
			{
				if (e.jhat.which == joystick_index1)
				{
					if (dpdright.compare(exit) == 0)
					{
						SendMessage(hWndM2, WM_CLOSE, NULL, NULL);
					}
					if (dpdright.compare(test) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x04, false);
						testA = true;
					}
					if (dpdright.compare(service) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x08, false);
						serviceA = true;
					}
					if (dpdright.compare(coin1) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x01, false);
						coin1A = true;
					}
					if (dpdright.compare(coin2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x02, false);
						coin2A = true;
					}
					if (dpdright.compare(start) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x10, false);
						startA = true;
					}
					if (dpdright.compare(shift1) == 0)
					{
						helpers->WriteByte(Button1Address, 0xAF, false);
						shift1A = true;
					}
					if (dpdright.compare(shift2) == 0)
					{
						helpers->WriteByte(Button1Address, 0x9F, false);
						shift2A = true;
					}
					if (dpdright.compare(shift3) == 0)
					{
						helpers->WriteByte(Button1Address, 0xEF, false);
						shift3A = true;
					}
					if (dpdright.compare(shift4) == 0)
					{
						helpers->WriteByte(Button1Address, 0xDF, false);
						shift4A = true;
					}
					if (dpdright.compare(shiftup) == 0)
					{
						switch (GearValue)
						{
						case 0x00:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x01:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0xDF, false);
							break;
						}
						shiftupA = true;
					}
					if (dpdright.compare(shiftdwn) == 0)
					{
						switch (GearValue)
						{
						case 0x01:
							helpers->WriteByte(Button1Address, 0xAF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x03:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						}
						shiftdwnA = true;
					}
					if (dpdright.compare(vr1) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x20, false);
						vr1A = true;
					}
					if (dpdright.compare(vr2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x40, false);
						vr2A = true;
					}
					if (dpdright.compare(vr3) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x80, false);
						vr3A = true;
					}
					if (dpdright.compare(vr4) == 0)
					{
						helpers->WriteByte(Button1Address, button1read -= 0x01, false);
						vr4A = true;
					}
				}
				else if (e.jhat.which == joystick_index2)
				{
					if (dpdright2.compare(exit2) == 0)
					{
						SendMessage(hWndM2, WM_CLOSE, NULL, NULL);
					}
					if (dpdright2.compare(test2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x04, false);
						testA = true;
					}
					if (dpdright2.compare(service2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x08, false);
						serviceA = true;
					}
					if (dpdright2.compare(coin12) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x01, false);
						coin1A = true;
					}
					if (dpdright2.compare(coin22) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x02, false);
						coin2A = true;
					}
					if (dpdright2.compare(start2) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x10, false);
						startA = true;
					}
					if (dpdright2.compare(shift12) == 0)
					{
						helpers->WriteByte(Button1Address, 0xAF, false);
						shift1A = true;
					}
					if (dpdright2.compare(shift22) == 0)
					{
						helpers->WriteByte(Button1Address, 0x9F, false);
						shift2A = true;
					}
					if (dpdright2.compare(shift32) == 0)
					{
						helpers->WriteByte(Button1Address, 0xEF, false);
						shift3A = true;
					}
					if (dpdright2.compare(shift42) == 0)
					{
						helpers->WriteByte(Button1Address, 0xDF, false);
						shift4A = true;
					}
					if (dpdright2.compare(shiftup2) == 0)
					{
						switch (GearValue)
						{
						case 0x00:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x01:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0xDF, false);
							break;
						}
						shiftupA = true;
					}
					if (dpdright2.compare(shiftdwn2) == 0)
					{
						switch (GearValue)
						{
						case 0x01:
							helpers->WriteByte(Button1Address, 0xAF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x03:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						}
						shiftdwnA = true;
					}
					if (dpdright2.compare(vr12) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x20, false);
						vr1A = true;
					}
					if (dpdright2.compare(vr22) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x40, false);
						vr2A = true;
					}
					if (dpdright2.compare(vr32) == 0)
					{
						helpers->WriteByte(Button2Address, button2read -= 0x80, false);
						vr3A = true;
					}
					if (dpdright2.compare(vr42) == 0)
					{
						helpers->WriteByte(Button1Address, button1read -= 0x01, false);
						vr4A = true;
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
					helpers->WriteByte(Button2Address, button2read -= 0x04, false);
				}
				if (e.jbutton.button == ExitButton)
				{
					SendMessage(hWndM2, WM_CLOSE, NULL, NULL);
				}
				if (e.jbutton.button == ServiceButton)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x08, false);
				}
				if (e.jbutton.button == Coin1Button)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x01, false);
				}
				if (e.jbutton.button == Coin2Button)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x02, false);
				}
				if (e.jbutton.button == StartButton)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x10, false);
				}
				if (e.jbutton.button == VR1Button)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x20, false);
				}
				if (e.jbutton.button == VR2Button)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x40, false);
				}
				if (e.jbutton.button == VR3Button)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x80, false);
				}
				if (e.jbutton.button == VR4Button)
				{
					helpers->WriteByte(Button1Address, button1read -= 0x01, false);
				}
				if (e.jbutton.button == Shift1Button)
				{
					helpers->WriteByte(Button1Address, 0xAF, false);
				}
				if (e.jbutton.button == Shift2Button)
				{
					helpers->WriteByte(Button1Address, 0x9F, false);
				}
				if (e.jbutton.button == Shift3Button)
				{
					helpers->WriteByte(Button1Address, 0xEF, false);
				}
				if (e.jbutton.button == Shift4Button)
				{
					helpers->WriteByte(Button1Address, 0xDF, false);
				}
				if (e.jbutton.button == ShiftUpButton)
				{
					if (!ShiftUpPressed)
					{
						ShiftUpPressed = true;
						switch (GearValue)
						{
						case 0x00:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x01:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0xDF, false);
							break;
						}
					}
				}
				if (e.jbutton.button == ShiftDownButton)
				{
					if (!ShiftDownPressed)
					{
						ShiftDownPressed = true;
						switch (GearValue)
						{
						case 0x01:
							helpers->WriteByte(Button1Address, 0xAF, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x03:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						}
					}
				}
			}
			else if (e.jbutton.which == joystick_index2)
			{
				if (e.jbutton.button == TestButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x04, false);
				}
				if (e.jbutton.button == ExitButtonDevice2)
				{
					SendMessage(hWndM2, WM_CLOSE, NULL, NULL);
				}
				if (e.jbutton.button == ServiceButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x08, false);
				}
				if (e.jbutton.button == Coin1ButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x01, false);
				}
				if (e.jbutton.button == Coin2ButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x02, false);
				}
				if (e.jbutton.button == StartButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x10, false);
				}
				if (e.jbutton.button == VR1ButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x20, false);
				}
				if (e.jbutton.button == VR2ButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x40, false);
				}
				if (e.jbutton.button == VR3ButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x80, false);
				}
				if (e.jbutton.button == VR4ButtonDevice2)
				{
					helpers->WriteByte(Button1Address, button1read -= 0x01, false);
				}
				if (e.jbutton.button == Shift1ButtonDevice2)
				{
					helpers->WriteByte(Button1Address, 0xAF, false);
				}
				if (e.jbutton.button == Shift2ButtonDevice2)
				{
					helpers->WriteByte(Button1Address, 0x9F, false);
				}
				if (e.jbutton.button == Shift3ButtonDevice2)
				{
					helpers->WriteByte(Button1Address, 0xEF, false);
				}
				if (e.jbutton.button == Shift4ButtonDevice2)
				{
					helpers->WriteByte(Button1Address, 0xDF, false);
				}
				if (e.jbutton.button == ShiftUpButtonDevice2)
				{
					if (!ShiftUpPressed)
					{
						ShiftUpPressed = true;
						switch (GearValue)
						{
						case 0x01:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x02:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						case 0x03:
							helpers->WriteByte(Button1Address, 0xDF, false);
							break;
						}
					}
				}
				if (e.jbutton.button == ShiftDownButtonDevice2)
				{
					if (!ShiftDownPressed)
					{
						ShiftDownPressed = true;
						switch (GearValue)
						{
						case 0x02:
							helpers->WriteByte(Button1Address, 0xAF, false);
							break;
						case 0x03:
							helpers->WriteByte(Button1Address, 0x9F, false);
							break;
						case 0x04:
							helpers->WriteByte(Button1Address, 0xEF, false);
							break;
						}
					}
				}
			}
		}
		if (e.type == SDL_JOYBUTTONUP)
		{
			if (e.jbutton.which == joystick_index1)
			{
				if (e.jbutton.button == TestButton)
				{
					helpers->WriteByte(Button2Address, button2read += 0x04, false);
				}
				if (e.jbutton.button == ServiceButton)
				{
					helpers->WriteByte(Button2Address, button2read += 0x08, false);
				}
				if (e.jbutton.button == Coin1Button)
				{
					helpers->WriteByte(Button2Address, button2read += 0x01, false);
				}
				if (e.jbutton.button == Coin2Button)
				{
					helpers->WriteByte(Button2Address, button2read += 0x02, false);
				}
				if (e.jbutton.button == StartButton)
				{
					helpers->WriteByte(Button2Address, button2read += 0x10, false);
				}
				if (e.jbutton.button == VR1Button)
				{
					helpers->WriteByte(Button2Address, button2read += 0x20, false);
				}
				if (e.jbutton.button == VR2Button)
				{
					helpers->WriteByte(Button2Address, button2read += 0x40, false);
				}
				if (e.jbutton.button == VR3Button)
				{
					helpers->WriteByte(Button2Address, button2read += 0x80, false);
				}
				if (e.jbutton.button == VR4Button)
				{
					helpers->WriteByte(Button1Address, button1read += 0x01, false);
				}
				if (e.jbutton.button == ShiftUpButton)
				{
					if (ShiftUpPressed)
						ShiftUpPressed = false;
				}
				if (e.jbutton.button == ShiftDownButton)
				{
					if (ShiftDownPressed)
						ShiftDownPressed = false;
				}
			}
			else if (e.jbutton.which == joystick_index2)
			{
				if (e.jbutton.button == TestButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read += 0x04, false);
				}
				if (e.jbutton.button == ServiceButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read += 0x08, false);
				}
				if (e.jbutton.button == Coin1ButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read += 0x01, false);
				}
				if (e.jbutton.button == Coin2ButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read += 0x02, false);
				}
				if (e.jbutton.button == StartButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read += 0x10, false);
				}
				if (e.jbutton.button == VR1ButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read += 0x20, false);
				}
				if (e.jbutton.button == VR2ButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read += 0x40, false);
				}
				if (e.jbutton.button == VR3ButtonDevice2)
				{
					helpers->WriteByte(Button2Address, button2read += 0x80, false);
				}
				if (e.jbutton.button == VR4ButtonDevice2)
				{
					helpers->WriteByte(Button1Address, button1read += 0x01, false);
				}
				if (e.jbutton.button == ShiftUpButtonDevice2)
				{
					if (ShiftUpPressed)
						ShiftUpPressed = false;
				}
				if (e.jbutton.button == ShiftDownButtonDevice2)
				{
					if (ShiftDownPressed)
						ShiftDownPressed = false;
				}
			}
		}
		
		if (e.type == SDL_KEYDOWN)
		{
			const char* KeyPressed = SDL_GetKeyName(e.key.keysym.sym);

			if (KeyBrdExit.compare(KeyPressed) == 0)
			{
				SendMessage(hWndM2, WM_CLOSE, NULL, NULL);
			}
			if (KeyBrdTest.compare(KeyPressed) == 0)
			{
				if (!testA)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x04, false);
					testA = true;
				}
			}
			if (KeyBrdService.compare(KeyPressed) == 0)
			{
				if (!serviceA)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x08, false);
					serviceA = true;
				}
			}
			if (KeyBrdCoin1.compare(KeyPressed) == 0)
			{
				if (!coin1A)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x01, false);
					coin1A = true;
				}
			}
			if (KeyBrdCoin2.compare(KeyPressed) == 0)
			{
				if (!coin2A)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x02, false);
					coin2A = true;
				}
			}
			if (KeyBrdVR1.compare(KeyPressed) == 0)
			{
				if (!vr1A)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x20, false);
					vr1A = true;
				}
			}
			if (KeyBrdVR2.compare(KeyPressed) == 0)
			{
				if (!vr2A)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x40, false);
					vr2A = true;
				}
			}
			if (KeyBrdVR3.compare(KeyPressed) == 0)
			{
				if (!vr3A)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x80, false);
					vr3A = true;
				}
			}
			if (KeyBrdVR4.compare(KeyPressed) == 0)
			{
				if (!vr4A)
				{
					helpers->WriteByte(Button1Address, button1read -= 0x01, false);
					vr4A = true;
				}
			}
			if (KeyBrdStart.compare(KeyPressed) == 0)
			{
				if (!startA)
				{
					helpers->WriteByte(Button2Address, button2read -= 0x10, false);
					startA = true;
				}
			}
			if (KeyBrdShift1.compare(KeyPressed) == 0)
			{
				if (!shift1A)
				{
					helpers->WriteByte(Button1Address, 0xAF, false);
					shift1A = true;
				}
			}
			if (KeyBrdShift2.compare(KeyPressed) == 0)
			{
				if (!shift2A)
				{
					helpers->WriteByte(Button1Address, 0x9F, false);
					shift2A = true;
				}
			}
			if (KeyBrdShift3.compare(KeyPressed) == 0)
			{
				if (!shift3A)
				{
					helpers->WriteByte(Button1Address, 0xEF, false);
					shift3A = true;
				}
			}
			if (KeyBrdShift4.compare(KeyPressed) == 0)
			{
				if (!shift4A)
				{
					helpers->WriteByte(Button1Address, 0xDF, false);
					shift4A = true;
				}
			}
			if (KeyBrdShiftUp.compare(KeyPressed) == 0)
			{
				if (!shiftupA)
				{
					switch (GearValue)
					{
					case 0x00:
						helpers->WriteByte(Button1Address, 0x9F, false);
						break;
					case 0x01:
						helpers->WriteByte(Button1Address, 0xEF, false);
						break;
					case 0x02:
						helpers->WriteByte(Button1Address, 0xDF, false);
						break;
					}
					shiftupA = true;
				}
			}
			if (KeyBrdShiftDown.compare(KeyPressed) == 0)
			{
				if (!shiftdwnA)
				{
					switch (GearValue)
					{
					case 0x01:
						helpers->WriteByte(Button1Address, 0xAF, false);
						break;
					case 0x02:
						helpers->WriteByte(Button1Address, 0x9F, false);
						break;
					case 0x03:
						helpers->WriteByte(Button1Address, 0xEF, false);
						break;
					}
					shiftdwnA = true;
				}
			}		
		}

		if (e.type == SDL_KEYUP)
		{
			const char* KeyPressed = SDL_GetKeyName(e.key.keysym.sym);

			if (KeyBrdTest.compare(KeyPressed) == 0)
			{
				if (testA)
				{
					helpers->WriteByte(Button2Address, button2read += 0x04, false);
					testA = false;
				}
			}
			if (KeyBrdService.compare(KeyPressed) == 0)
			{
				if (serviceA)
				{
					helpers->WriteByte(Button2Address, button2read += 0x08, false);
					serviceA = false;
				}
			}
			if (KeyBrdCoin1.compare(KeyPressed) == 0)
			{
				if (coin1A)
				{
					helpers->WriteByte(Button2Address, button2read += 0x01, false);
					coin1A = false;
				}
			}
			if (KeyBrdCoin2.compare(KeyPressed) == 0)
			{
				if (coin2A)
				{
					helpers->WriteByte(Button2Address, button2read += 0x02, false);
					coin2A = false;
				}
			}
			if (KeyBrdVR1.compare(KeyPressed) == 0)
			{
				if (vr1A)
				{
					helpers->WriteByte(Button2Address, button2read += 0x20, false);
					vr1A = false;
				}
			}
			if (KeyBrdVR2.compare(KeyPressed) == 0)
			{
				if (vr2A)
				{
					helpers->WriteByte(Button2Address, button2read += 0x40, false);
					vr2A = false;
				}
			}
			if (KeyBrdVR3.compare(KeyPressed) == 0)
			{
				if (vr3A)
				{
					helpers->WriteByte(Button2Address, button2read += 0x80, false);
					vr3A = false;
				}
			}
			if (KeyBrdVR4.compare(KeyPressed) == 0)
			{
				if (vr4A)
				{
					helpers->WriteByte(Button1Address, button1read += 0x01, false);
					vr4A = false;
				}
			}
			if (KeyBrdStart.compare(KeyPressed) == 0)
			{
				if (startA)
				{
					helpers->WriteByte(Button2Address, button2read += 0x10, false);
					startA = false;
				}
			}
			if (KeyBrdShift1.compare(KeyPressed) == 0)
			{
				if (shift1A)
					shift1A = false;
			}
			if (KeyBrdShift2.compare(KeyPressed) == 0)
			{
				if (shift2A)
					shift2A = false;
			}
			if (KeyBrdShift3.compare(KeyPressed) == 0)
			{
				if (shift3A)
					shift3A = false;
			}
			if (KeyBrdShift4.compare(KeyPressed) == 0)
			{
				if (shift4A)
					shift4A = false;
			}
			if (KeyBrdShiftUp.compare(KeyPressed) == 0)
			{
				if (shiftupA)
					shiftupA = false;
			}
			if (KeyBrdShiftDown.compare(KeyPressed) == 0)
			{
				if (shiftdwnA)
					shiftdwnA = false;
			}
		}
	}
}