#include "../Common Files/Game.h"
#include <string>
#include <windows.h>
#include "SDL.h"

extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;
static bool testbuttonA;
static bool servicebuttonA;
static bool startbuttonA;
static bool viewbuttonA;
static bool shiftupA;
static bool shiftdownA;
static bool coinA;
static bool Inputsinit = false;
static bool InputFind = false;
extern SDL_Event e;

extern INT_PTR SteeringAddress;
extern INT_PTR AcclAddress;
extern INT_PTR BrakeAddress;
extern INT_PTR StartViewAddress;
extern INT_PTR ShiftUpDownAddress;
extern INT_PTR ServiceTestAddress;
extern INT_PTR CoinAddress;

extern wchar_t* settingsFilename;
static int InputDeviceWheelEnable = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelEnable"), 0, settingsFilename);
static int InputDeviceWheelSteeringAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelSteeringAxis"), 0, settingsFilename);
static int InputDeviceWheelAcclAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelAcclAxis"), 0, settingsFilename);
static int InputDeviceWheelBrakeAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelBrakeAxis"), 0, settingsFilename);
static int InputDeviceWheelReverseAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelReverseAxis"), 0, settingsFilename);
static int InputDeviceCombinedPedals = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceCombinedPedals"), 0, settingsFilename);
static int SteeringDeadzone = GetPrivateProfileInt(TEXT("Settings"), TEXT("SteeringDeadzone"), 0, settingsFilename);
static int PedalDeadzone = GetPrivateProfileInt(TEXT("Settings"), TEXT("PedalDeadzone"), 0, settingsFilename);
static int ShowButtonNumbersForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowButtonNumbersForSetup"), 0, settingsFilename);
static int ShowAxisForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowAxisForSetup"), 0, settingsFilename);
static int ExitButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ExitButton"), 0, settingsFilename);
static int TestButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("TestButton"), 0, settingsFilename);
static int ServiceButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ServiceButton"), 0, settingsFilename);
static int CreditButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("CreditButton"), 0, settingsFilename);
static int ViewButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ViewButton"), 0, settingsFilename);
static int StartButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("StartButton"), 0, settingsFilename);
static int ShiftUp = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShiftUp"), 0, settingsFilename);
static int ShiftDown = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShiftDown"), 0, settingsFilename);
static int Gear1 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear1"), 0, settingsFilename);
static int Gear2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear2"), 0, settingsFilename);
static int Gear3 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear3"), 0, settingsFilename);
static int Gear4 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear4"), 0, settingsFilename);
static int ExitButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ExitButtonDevice2"), 0, settingsFilename);
static int TestButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("TestButtonDevice2"), 0, settingsFilename);
static int ServiceButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ServiceButtonDevice2"), 0, settingsFilename);
static int CreditButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("CreditButtonDevice2"), 0, settingsFilename);
static int ViewButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ViewButtonDevice2"), 0, settingsFilename);
static int StartButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("StartButtonDevice2"), 0, settingsFilename);
static int ShiftUpDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShiftUpDevice2"), 0, settingsFilename);
static int ShiftDownDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShiftDownDevice2"), 0, settingsFilename);
static int Gear1Device2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear1Device2"), 0, settingsFilename);
static int Gear2Device2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear2Device2"), 0, settingsFilename);
static int Gear3Device2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear3Device2"), 0, settingsFilename);
static int Gear4Device2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("Gear4Device2"), 0, settingsFilename);

void NascarInputsEnabled(Helpers* helpers)
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
	std::string start("StartButton");
	std::string sftup("ShiftUp");
	std::string sftdown("ShiftDown");
	std::string exit2("ExitButtonDevice2");
	std::string test2("TestButtonDevice2");
	std::string service2("ServiceButtonDevice2");
	std::string coin2("CoinButtonDevice2");
	std::string view2("ViewButtonDevice2");
	std::string start2("StartButtonDevice2");
	std::string sftup2("ShiftUpDevice2");
	std::string sftdown2("ShiftDownDevice2");
	std::string dpdup(DpadUpChar);
	std::string dpddown(DpadDownChar);
	std::string dpdleft(DpadLeftChar);
	std::string dpdright(DpadRightChar);
	std::string dpdup2(DpadUpCharDevice2);
	std::string dpddown2(DpadDownCharDevice2);
	std::string dpdleft2(DpadLeftCharDevice2);
	std::string dpdright2(DpadRightCharDevice2);

	const int WHEEL_DEAD_ZONE = (SteeringDeadzone * 100.0);
	const int ACCL_DEAD_ZONE = (1 + PedalDeadzone * 100.0);
	const int BRAKE_DEAD_ZONE = (1 + PedalDeadzone * 100.0);
	const int SETUP_DEAD_ZONE = 20000;

	UINT8 startviewread = helpers->ReadByte(StartViewAddress, false);
	UINT8 shiftupdownread = helpers->ReadByte(ShiftUpDownAddress, false);
	UINT8 coinread = helpers->ReadByte(CoinAddress, false);
	UINT8 servicetestread = helpers->ReadByte(ServiceTestAddress, false);

	while (SDL_WaitEvent(&e) != 0)
	{
		UINT8 shiftupdownreadA = helpers->ReadByte(ShiftUpDownAddress, false);
		if ((e.type == SDL_JOYAXISMOTION) && (ShowAxisForSetup == 0))
		{
			if (e.jaxis.which == joystick_index1)
			{
				if (e.jaxis.axis == InputDeviceWheelSteeringAxis)
				{
					//Left of dead zone
					if (e.jaxis.value < -WHEEL_DEAD_ZONE)
					{
						e.jaxis.value = e.jaxis.value - WHEEL_DEAD_ZONE;
						helpers->WriteByte(SteeringAddress, (128 + (e.jaxis.value + WHEEL_DEAD_ZONE) / 255), false);
					}
					//Right of dead zone
					else if (e.jaxis.value > WHEEL_DEAD_ZONE)
					{
						e.jaxis.value = e.jaxis.value + WHEEL_DEAD_ZONE;
						helpers->WriteByte(SteeringAddress, (127 + (e.jaxis.value - WHEEL_DEAD_ZONE) / 255), false);
					}
					else if ((e.jaxis.value < WHEEL_DEAD_ZONE) && (e.jaxis.value > -WHEEL_DEAD_ZONE))
					{
						helpers->WriteByte(SteeringAddress, 0x7F, false);
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
								helpers->WriteByte(AcclAddress, ((-e.jaxis.value + ACCL_DEAD_ZONE) / 128.5), false);
							}
							else if (e.jaxis.value > ACCL_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - ACCL_DEAD_ZONE;
								helpers->WriteByte(BrakeAddress, ((e.jaxis.value + ACCL_DEAD_ZONE) / 128), false);
							}
							else if ((e.jaxis.value < ACCL_DEAD_ZONE) && (e.jaxis.value > -ACCL_DEAD_ZONE))
							{
								helpers->WriteByte(AcclAddress, 0x00, false);
								helpers->WriteByte(BrakeAddress, 0x00, false);
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
								helpers->WriteByte(AcclAddress, 127 - e.jaxis.value, false);
							}
							else if (e.jaxis.value > ACCL_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								helpers->WriteByte(AcclAddress, 128 - e.jaxis.value, false);
							}
						}
						else if (e.jaxis.axis == InputDeviceWheelBrakeAxis)
						{
							if (e.jaxis.value < -BRAKE_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								helpers->WriteByte(BrakeAddress, 127 - e.jaxis.value, false);
							}
							else if (e.jaxis.value > BRAKE_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								helpers->WriteByte(BrakeAddress, 128 - e.jaxis.value, false);
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
								helpers->WriteByte(AcclAddress, ((e.jaxis.value + ACCL_DEAD_ZONE) / 128), false);
							}
							else if (e.jaxis.value > ACCL_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + ACCL_DEAD_ZONE;
								helpers->WriteByte(BrakeAddress, ((-e.jaxis.value + ACCL_DEAD_ZONE) / 128), false);
							}
							else if ((e.jaxis.value < ACCL_DEAD_ZONE) && (e.jaxis.value > -ACCL_DEAD_ZONE))
							{
								helpers->WriteByte(AcclAddress, 0xFF, false);
								helpers->WriteByte(BrakeAddress, 0xFF, false);
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
								helpers->WriteByte(AcclAddress, 128 + e.jaxis.value, false);
							}
							else if (e.jaxis.value > ACCL_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								helpers->WriteByte(AcclAddress, 127 + e.jaxis.value, false);
							}
						}
						if (e.jaxis.axis == InputDeviceWheelBrakeAxis)
						{
							if (e.jaxis.value < -BRAKE_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								helpers->WriteByte(BrakeAddress, 128 + e.jaxis.value, false);
							}
							else if (e.jaxis.value > BRAKE_DEAD_ZONE)
							{
								e.jaxis.value = (e.jaxis.value / 255);
								helpers->WriteByte(BrakeAddress, 127 + e.jaxis.value, false);
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
						helpers->WriteByte(ServiceTestAddress, servicetestread += 0x08, false);
						testbuttonA = false;
					}
					if (servicebuttonA)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread += 0x04, false);
						servicebuttonA = false;
					}
					if (viewbuttonA)
					{
						helpers->WriteByte(StartViewAddress, startviewread -= 0x10, false);
						viewbuttonA = false;
					}
					if (startbuttonA)
					{
						helpers->WriteByte(StartViewAddress, startviewread -= 0x80, false);
						startbuttonA = false;
					}
					if (shiftupA)
					{
						shiftupA = false;
					}
					if (shiftdownA)
					{
						shiftdownA = false;
					}
				}
				else if (e.jhat.which == joystick_index2)
				{
					if (testbuttonA)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread += 0x08, false);
						testbuttonA = false;
					}
					if (servicebuttonA)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread += 0x04, false);
						servicebuttonA = false;
					}
					if (viewbuttonA)
					{
						helpers->WriteByte(StartViewAddress, startviewread -= 0x10, false);
						viewbuttonA = false;
					}
					if (startbuttonA)
					{
						helpers->WriteByte(StartViewAddress, startviewread -= 0x80, false);
						startbuttonA = false;
					}
					if (shiftupA)
					{
						shiftupA = false;
					}
					if (shiftdownA)
					{
						shiftdownA = false;
					}
				}
			}
			if (e.jhat.value == SDL_HAT_UP)
			{
				if (e.jhat.which == joystick_index1)
				{
					if (dpdup.compare(exit) == 0)
					{
						system("taskkill /f /im demul.exe");
					}
					if (dpdup.compare(test) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x08, false);
						testbuttonA = true;
					}
					if (dpdup.compare(service) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x04, false);
						servicebuttonA = true;
					}
					if (dpdup.compare(coin) == 0)
					{
						helpers->WriteByte(CoinAddress, coinread += 0x01, false);
					}
					if (dpdup.compare(view) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x10, false);
						viewbuttonA = true;
					}
					if (dpdup.compare(start) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x80, false);
						startbuttonA = true;
					}
					if (dpdup.compare(sftup) == 0)
					{
						if (shiftupdownreadA == 0x28)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x10, false);
						}
						shiftupA = true;
					}
					if (dpdup.compare(sftdown) == 0)
					{
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x28, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x10)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						shiftdownA = true;
					}
				}
				else if (e.jhat.which == joystick_index2)
				{
					if (dpdup2.compare(exit2) == 0)
					{
						system("taskkill /f /im demul.exe");
					}
					if (dpdup2.compare(test2) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x08, false);
						testbuttonA = true;
					}
					if (dpdup2.compare(service2) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x04, false);
						servicebuttonA = true;
					}
					if (dpdup2.compare(coin2) == 0)
					{
						helpers->WriteByte(CoinAddress, coinread += 0x01, false);
					}
					if (dpdup2.compare(view2) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x10, false);
						viewbuttonA = true;
					}
					if (dpdup2.compare(start2) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x80, false);
						startbuttonA = true;
					}
					if (dpdup2.compare(sftup2) == 0)
					{
						if (shiftupdownreadA == 0x28)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x10, false);
						}
						shiftupA = true;
					}
					if (dpdup2.compare(sftdown2) == 0)
					{
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x28, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x10)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						shiftdownA = true;
					}
				}
			}
			if (e.jhat.value == SDL_HAT_DOWN)
			{
				if (e.jhat.which == joystick_index1)
				{
					if (dpddown.compare(exit) == 0)
					{
						system("taskkill /f /im demul.exe");
					}
					if (dpddown.compare(test) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x08, false);
						testbuttonA = true;
					}
					if (dpddown.compare(service) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x04, false);
						servicebuttonA = true;
					}
					if (dpddown.compare(coin) == 0)
					{
						helpers->WriteByte(CoinAddress, coinread += 0x01, false);
					}
					if (dpddown.compare(view) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x10, false);
						viewbuttonA = true;
					}
					if (dpddown.compare(start) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x80, false);
						startbuttonA = true;
					}
					if (dpddown.compare(sftup) == 0)
					{
						if (shiftupdownreadA == 0x28)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x10, false);
						}
						shiftupA = true;
					}
					if (dpddown.compare(sftdown) == 0)
					{
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x28, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x10)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						shiftdownA = true;
					}
				}
				else if (e.jhat.which == joystick_index2)
				{
					if (dpddown2.compare(exit2) == 0)
					{
						system("taskkill /f /im demul.exe");
					}
					if (dpddown2.compare(test2) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x08, false);
						testbuttonA = true;
					}
					if (dpddown2.compare(service2) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x04, false);
						servicebuttonA = true;
					}
					if (dpddown2.compare(coin2) == 0)
					{
						helpers->WriteByte(CoinAddress, coinread += 0x01, false);
					}
					if (dpddown2.compare(view2) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x10, false);
						viewbuttonA = true;
					}
					if (dpddown2.compare(start2) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x80, false);
						startbuttonA = true;
					}
					if (dpddown2.compare(sftup2) == 0)
					{
						if (shiftupdownreadA == 0x28)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x10, false);
						}
						shiftupA = true;
					}
					if (dpddown2.compare(sftdown2) == 0)
					{
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x28, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x10)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						shiftdownA = true;
					}
				}
			}
			if (e.jhat.value == SDL_HAT_LEFT)
			{
				if (e.jhat.which == joystick_index1)
				{
					if (dpdleft.compare(exit) == 0)
					{
						system("taskkill /f /im demul.exe");
					}
					if (dpdleft.compare(test) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x08, false);
						testbuttonA = true;
					}
					if (dpdleft.compare(service) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x04, false);
						servicebuttonA = true;
					}
					if (dpdleft.compare(coin) == 0)
					{
						helpers->WriteByte(CoinAddress, coinread += 0x01, false);
					}
					if (dpdleft.compare(view) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x10, false);
						viewbuttonA = true;
					}
					if (dpdleft.compare(start) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x80, false);
						startbuttonA = true;
					}
					if (dpdleft.compare(sftup) == 0)
					{
						if (shiftupdownreadA == 0x28)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x10, false);
						}
						shiftupA = true;
					}
					if (dpdleft.compare(sftdown) == 0)
					{
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x28, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x10)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						shiftdownA = true;
					}
				}
				else if (e.jhat.which == joystick_index2)
				{
					if (dpdleft2.compare(exit2) == 0)
					{
						system("taskkill /f /im demul.exe");
					}
					if (dpdleft2.compare(test2) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x08, false);
						testbuttonA = true;
					}
					if (dpdleft2.compare(service2) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x04, false);
						servicebuttonA = true;
					}
					if (dpdleft2.compare(coin2) == 0)
					{
						helpers->WriteByte(CoinAddress, coinread += 0x01, false);
					}
					if (dpdleft2.compare(view2) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x10, false);
						viewbuttonA = true;
					}
					if (dpdleft2.compare(start2) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x80, false);
						startbuttonA = true;
					}
					if (dpdleft2.compare(sftup2) == 0)
					{
						if (shiftupdownreadA == 0x28)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x10, false);
						}
						shiftupA = true;
					}
					if (dpdleft2.compare(sftdown2) == 0)
					{
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x28, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x10)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						shiftdownA = true;
					}
				}
			}
			if (e.jhat.value == SDL_HAT_RIGHT)
			{
				if (e.jhat.which == joystick_index1)
				{
					if (dpdright.compare(exit) == 0)
					{
						system("taskkill /f /im demul.exe");
					}
					if (dpdright.compare(test) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x08, false);
						testbuttonA = true;
					}
					if (dpdright.compare(service) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x04, false);
						servicebuttonA = true;
					}
					if (dpdright.compare(coin) == 0)
					{
						helpers->WriteByte(CoinAddress, coinread += 0x01, false);
					}
					if (dpdright.compare(view) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x10, false);
						viewbuttonA = true;
					}
					if (dpdright.compare(start) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x80, false);
						startbuttonA = true;
					}
					if (dpdright.compare(sftup) == 0)
					{
						if (shiftupdownreadA == 0x28)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x10, false);
						}
						shiftupA = true;
					}
					if (dpdright.compare(sftdown) == 0)
					{
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x28, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x10)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						shiftdownA = true;
					}
				}
				else if (e.jhat.which == joystick_index2)
				{
					if (dpdright2.compare(exit2) == 0)
					{
						system("taskkill /f /im demul.exe");
					}
					if (dpdright2.compare(test2) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x08, false);
						testbuttonA = true;
					}
					if (dpdright2.compare(service2) == 0)
					{
						helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x04, false);
						servicebuttonA = true;
					}
					if (dpdright2.compare(coin2) == 0)
					{
						helpers->WriteByte(CoinAddress, coinread += 0x01, false);
					}
					if (dpdright2.compare(view2) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x10, false);
						viewbuttonA = true;
					}
					if (dpdright2.compare(start2) == 0)
					{
						helpers->WriteByte(StartViewAddress, startviewread += 0x80, false);
						startbuttonA = true;
					}
					if (dpdright2.compare(sftup2) == 0)
					{
						if (shiftupdownreadA == 0x28)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x10, false);
						}
						shiftupA = true;
					}
					if (dpdright2.compare(sftdown2) == 0)
					{
						if (shiftupdownreadA == 0x18)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x28, false);
						}
						if (shiftupdownreadA == 0x20)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
						}
						if (shiftupdownreadA == 0x10)
						{
							helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
						}
						shiftdownA = true;
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
					helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x08, false);
				}
				if (e.jbutton.button == ExitButton)
				{
					system("taskkill /f /im demul.exe");
				}
				if (e.jbutton.button == ServiceButton)
				{
					helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x04, false);
				}
				if (e.jbutton.button == CreditButton)
				{
					helpers->WriteByte(CoinAddress, ++coinread, false);
				}
				if (e.jbutton.button == ViewButton)
				{
					helpers->WriteByte(StartViewAddress, startviewread += 0x10, false);
				}
				if (e.jbutton.button == StartButton)
				{
					helpers->WriteByte(StartViewAddress, startviewread += 0x80, false);
				}
				if (e.jbutton.button == Gear1)
				{
					helpers->WriteByte(ShiftUpDownAddress, 0x28, false);
				}
				if (e.jbutton.button == Gear2)
				{
					helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
				}
				if (e.jbutton.button == Gear3)
				{
					helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
				}
				if (e.jbutton.button == Gear4)
				{
					helpers->WriteByte(ShiftUpDownAddress, 0x10, false);
				}
				if (e.jbutton.button == ShiftUp)
				{
					if (shiftupdownreadA == 0x28)
					{
						helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
					}
					if (shiftupdownreadA == 0x18)
					{
						helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
					}
					if (shiftupdownreadA == 0x20)
					{
						helpers->WriteByte(ShiftUpDownAddress, 0x10, false);
					}
				}
				if (e.jbutton.button == ShiftDown)
				{
					if (shiftupdownreadA == 0x18)
					{
						helpers->WriteByte(ShiftUpDownAddress, 0x28, false);
					}
					if (shiftupdownreadA == 0x20)
					{
						helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
					}
					if (shiftupdownreadA == 0x10)
					{
						helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
					}
				}
			}
			else if (e.jbutton.which == joystick_index2)
			{
				if (e.jbutton.button == TestButtonDevice2)
				{
					helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x08, false);
				}
				if (e.jbutton.button == ExitButtonDevice2)
				{
					system("taskkill /f /im demul.exe");
				}
				if (e.jbutton.button == ServiceButtonDevice2)
				{
					helpers->WriteByte(ServiceTestAddress, servicetestread -= 0x04, false);
				}
				if (e.jbutton.button == CreditButtonDevice2)
				{
					helpers->WriteByte(CoinAddress, ++coinread, false);
				}
				if (e.jbutton.button == ViewButtonDevice2)
				{
					helpers->WriteByte(StartViewAddress, startviewread += 0x10, false);
				}
				if (e.jbutton.button == StartButtonDevice2)
				{
					helpers->WriteByte(StartViewAddress, startviewread += 0x80, false);
				}
				if (e.jbutton.button == Gear1Device2)
				{
					helpers->WriteByte(ShiftUpDownAddress, 0x28, false);
				}
				if (e.jbutton.button == Gear2Device2)
				{
					helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
				}
				if (e.jbutton.button == Gear3Device2)
				{
					helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
				}
				if (e.jbutton.button == Gear4Device2)
				{
					helpers->WriteByte(ShiftUpDownAddress, 0x10, false);
				}
				if (e.jbutton.button == ShiftUpDevice2)
				{
					if (shiftupdownreadA == 0x28)
					{
						helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
					}
					if (shiftupdownreadA == 0x18)
					{
						helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
					}
					if (shiftupdownreadA == 0x20)
					{
						helpers->WriteByte(ShiftUpDownAddress, 0x10, false);
					}
				}
				if (e.jbutton.button == ShiftDownDevice2)
				{
					if (shiftupdownreadA == 0x18)
					{
						helpers->WriteByte(ShiftUpDownAddress, 0x28, false);
					}
					if (shiftupdownreadA == 0x20)
					{
						helpers->WriteByte(ShiftUpDownAddress, 0x18, false);
					}
					if (shiftupdownreadA == 0x10)
					{
						helpers->WriteByte(ShiftUpDownAddress, 0x20, false);
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
					helpers->WriteByte(ServiceTestAddress, servicetestread += 0x08, false);
				}
				if (e.jbutton.button == ServiceButton)
				{
					helpers->WriteByte(ServiceTestAddress, servicetestread += 0x04, false);
				}
				if (e.jbutton.button == ViewButton)
				{
					helpers->WriteByte(StartViewAddress, startviewread -= 0x10, false);
				}
				if (e.jbutton.button == StartButton)
				{
					helpers->WriteByte(StartViewAddress, startviewread -= 0x80, false);
				}
			}
			else if (e.jbutton.which == joystick_index2)
			{
				if (e.jbutton.button == TestButtonDevice2)
				{
					helpers->WriteByte(ServiceTestAddress, servicetestread += 0x08, false);
				}
				if (e.jbutton.button == ServiceButtonDevice2)
				{
					helpers->WriteByte(ServiceTestAddress, servicetestread += 0x04, false);
				}
				if (e.jbutton.button == ViewButtonDevice2)
				{
					helpers->WriteByte(StartViewAddress, startviewread -= 0x10, false);
				}
				if (e.jbutton.button == StartButtonDevice2)
				{
					helpers->WriteByte(StartViewAddress, startviewread -= 0x80, false);
				}
			}
		}
	}
}