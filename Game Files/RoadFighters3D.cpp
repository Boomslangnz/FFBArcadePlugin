#include <string>
#include "SDL.h"
#include "RoadFighters3D.h"
#include <Windows.h>
extern HINSTANCE gl_hjgtDll;
extern HINSTANCE gl_hlibavs;
extern int joystick_index1;
extern int joystick_index2;
extern SDL_Joystick* GameController2;

void RoadFighters3D::FFBLoop(EffectConstants *constants, Helpers *helpers, EffectTriggers* triggers) {

	wchar_t *settingsFilename = TEXT(".\\FFBPlugin.ini");
	int InputDeviceWheelEnable = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelEnable"), 0, settingsFilename);
	int InputDeviceWheelSteeringAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelSteeringAxis"), 0, settingsFilename);
	int InputDeviceWheelAcclAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelAcclAxis"), 0, settingsFilename);
	int InputDeviceWheelBrakeAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelBrakeAxis"), 0, settingsFilename);
	int InputDeviceWheelReverseAxis = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceWheelReverseAxis"), 0, settingsFilename);
	int InputDeviceCombinedPedals = GetPrivateProfileInt(TEXT("Settings"), TEXT("InputDeviceCombinedPedals"), 0, settingsFilename);
	int SteeringDeadzone = GetPrivateProfileInt(TEXT("Settings"), TEXT("SteeringDeadzone"), 0, settingsFilename);
	int PedalDeadzone = GetPrivateProfileInt(TEXT("Settings"), TEXT("PedalDeadzone"), 0, settingsFilename);
	int SequentialGears = GetPrivateProfileInt(TEXT("Settings"), TEXT("SequentialGears"), 0, settingsFilename);
	int FFBMode = GetPrivateProfileInt(TEXT("Settings"), TEXT("FFBMode"), 0, settingsFilename);
	int ShowButtonNumbersForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowButtonNumbersForSetup"), 0, settingsFilename);
	int ShowAxisForSetup = GetPrivateProfileInt(TEXT("Settings"), TEXT("ShowAxisForSetup"), 0, settingsFilename);
	int ExitButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ExitButton"), 0, settingsFilename);
	int TestButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("TestButton"), 0, settingsFilename);
	int ServiceButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ServiceButton"), 0, settingsFilename);
	int CreditButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("CreditButton"), 0, settingsFilename);
	int ViewButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ViewButton"), 0, settingsFilename);
	int ThreeDimensionalButton = GetPrivateProfileInt(TEXT("Settings"), TEXT("ThreeDimensionalButton"), 0, settingsFilename);
	int leverUp = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverUp"), 0, settingsFilename);
	int leverDown = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverDown"), 0, settingsFilename);
	int leverLeft = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverLeft"), 0, settingsFilename);
	int leverRight = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverRight"), 0, settingsFilename);
	int ExitButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ExitButtonDevice2"), 0, settingsFilename);
	int TestButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("TestButtonDevice2"), 0, settingsFilename);
	int ServiceButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ServiceButtonDevice2"), 0, settingsFilename);
	int CreditButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("CreditButtonDevice2"), 0, settingsFilename);
	int ViewButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ViewButtonDevice2"), 0, settingsFilename);
	int ThreeDimensionalButtonDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("ThreeDimensionalButtonDevice2"), 0, settingsFilename);
	int leverUpDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverUpDevice2"), 0, settingsFilename);
	int leverDownDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverDownDevice2"), 0, settingsFilename);
	int leverLeftDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverLeftDevice2"), 0, settingsFilename);
	int leverRightDevice2 = GetPrivateProfileInt(TEXT("Settings"), TEXT("leverRightDevice2"), 0, settingsFilename);

	if (InputDeviceWheelEnable == 1)
	{
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18D84B, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18D84C, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18D84D, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18D852, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18D853, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18D854, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18D85C, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18D85D, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18D85E, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18DA89, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18DA8A, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18DA8B, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18DA8C, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18DA8D, false);
		helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x18DA8E, false);

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

		//Added 2nd device stuff from here
		wchar_t * deviceGUIDString2 = new wchar_t[256];
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

		//if (InputDeviceCombinedPedals == 1)
		//{
		//	bool BrakePedalFix = true;
		//}

		if (SequentialGears == 1)
		{
			helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x95DDA, false);
			helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x95DDB, false);
			helpers->WriteNop((INT_PTR)gl_hjgtDll + 0x95DDC, false);
		}

		const int WHEEL_DEAD_ZONE = (SteeringDeadzone * 100.0);
		const int ACCL_DEAD_ZONE = (1 + PedalDeadzone * 100.0);
		const int BRAKE_DEAD_ZONE = (1 + PedalDeadzone * 100.0);
		const int SETUP_DEAD_ZONE = 20000;
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if ((e.type == SDL_JOYAXISMOTION) & (ShowAxisForSetup == 0))
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
						else if ((e.jaxis.value < WHEEL_DEAD_ZONE) & (e.jaxis.value > -WHEEL_DEAD_ZONE))
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
								else if ((e.jaxis.value < ACCL_DEAD_ZONE) & (e.jaxis.value > -ACCL_DEAD_ZONE))
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
							//for (static bool BrakePedalFix = true; BrakePedalFix; BrakePedalFix = false)
							//{
								//helpers->WriteByte((INT_PTR)gl_hjgtDll + 0x7D2B41, 0xFF, false);
							//}

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
								else if ((e.jaxis.value < ACCL_DEAD_ZONE) & (e.jaxis.value > -ACCL_DEAD_ZONE))
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
						if (e.jaxis.axis == 0)
						{
							if (e.jaxis.value < -SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 0 Moved", "", 0);
							}
							else if (e.jaxis.value > SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 0 Moved", "", 0);
							}
						}
						else if (e.jaxis.axis == 1)
						{
							if (e.jaxis.value < -SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 1 Moved", "", 0);
							}
							else if (e.jaxis.value > SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 1 Moved", "", 0);
							}
						}
						else if (e.jaxis.axis == 2)
						{
							if (e.jaxis.value < -SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 2 Moved", "", 0);
							}
							else if (e.jaxis.value > SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 2 Moved", "", 0);
							}
						}
						else if (e.jaxis.axis == 3)
						{
							if (e.jaxis.value < -SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 3 Moved", "", 0);
							}
							else if (e.jaxis.value > SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 3 Moved", "", 0);
							}
						}
						else if (e.jaxis.axis == 4)
						{
							if (e.jaxis.value < -SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 4 Moved", "", 0);
							}
							else if (e.jaxis.value > SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 4 Moved", "", 0);
							}
						}
						else if (e.jaxis.axis == 5)
						{
							if (e.jaxis.value < -SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 5 Moved", "", 0);
							}
							else if (e.jaxis.value > SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 5 Moved", "", 0);
							}
						}
						else if (e.jaxis.axis == 6)
						{
							if (e.jaxis.value < -SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 6 Moved", "", 0);
							}
							else if (e.jaxis.value > SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 6 Moved", "", 0);
							}
						}
						else if (e.jaxis.axis == 7)
						{
							if (e.jaxis.value < -SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 7 Moved", "", 0);
							}
							else if (e.jaxis.value > SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 7 Moved", "", 0);
							}
						}
						else if (e.jaxis.axis == 8)
						{
							if (e.jaxis.value < -SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 8 Moved", "", 0);
							}
							else if (e.jaxis.value > SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 8 Moved", "", 0);
							}
						}
						else if (e.jaxis.axis == 9)
						{
							if (e.jaxis.value < -SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 9 Moved", "", 0);
							}
							else if (e.jaxis.value > SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 9 Moved", "", 0);
							}
						}
						else if (e.jaxis.axis == 10)
						{
							if (e.jaxis.value < -SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value - SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 10 Moved", "", 0);
							}
							else if (e.jaxis.value > SETUP_DEAD_ZONE)
							{
								e.jaxis.value = e.jaxis.value + SETUP_DEAD_ZONE;
								MessageBoxA(NULL, "Axis 10 Moved", "", 0);
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
						else if (e.jbutton.button == 16)
						{
							MessageBoxA(NULL, "Button 16 Pressed", "", 0);
						}
						else if (e.jbutton.button == 17)
						{
							MessageBoxA(NULL, "Button 17 Pressed", "", 0);
						}
						else if (e.jbutton.button == 18)
						{
							MessageBoxA(NULL, "Button 18 Pressed", "", 0);
						}
						else if (e.jbutton.button == 19)
						{
							MessageBoxA(NULL, "Button 19 Pressed", "", 0);
						}
						else if (e.jbutton.button == 20)
						{
							MessageBoxA(NULL, "Button 20 Pressed", "", 0);
						}
						else if (e.jbutton.button == 21)
						{
							MessageBoxA(NULL, "Button 21 Pressed", "", 0);
						}
						else if (e.jbutton.button == 22)
						{
							MessageBoxA(NULL, "Button 22 Pressed", "", 0);
						}
						else if (e.jbutton.button == 23)
						{
							MessageBoxA(NULL, "Button 23 Pressed", "", 0);
						}
						else if (e.jbutton.button == 24)
						{
							MessageBoxA(NULL, "Button 24 Pressed", "", 0);
						}
						else if (e.jbutton.button == 25)
						{
							MessageBoxA(NULL, "Button 25 Pressed", "", 0);
						}
						else if (e.jbutton.button == 26)
						{
							MessageBoxA(NULL, "Button 26 Pressed", "", 0);
						}
						else if (e.jbutton.button == 27)
						{
							MessageBoxA(NULL, "Button 27 Pressed", "", 0);
						}
						else if (e.jbutton.button == 28)
						{
							MessageBoxA(NULL, "Button 28 Pressed", "", 0);
						}
						else if (e.jbutton.button == 29)
						{
							MessageBoxA(NULL, "Button 29 Pressed", "", 0);
						}
						else if (e.jbutton.button == 30)
						{
							MessageBoxA(NULL, "Button 30 Pressed", "", 0);
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
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}

					else if (e.jhat.which == joystick_index2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
				}
				else if (e.jhat.value == SDL_HAT_UP)
				{
					if (e.jhat.which == joystick_index1)
					{
						if (dpdup.compare(exit) == 0)
						{
							system("taskkill /f /im spice.exe");
						}
						else if (dpdup.compare(test) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x02, false);
						}
						else if (dpdup.compare(service) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x01, false);
						}
						else if (dpdup.compare(coin) == 0)
						{
							int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
							helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
						}
						else if (dpdup.compare(view) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x400, false);
						}
						else if (dpdup.compare(three) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x800, false);
						}
						else if (dpdup.compare(lvup) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x1040, false);
						}
						else if (dpdup.compare(lvdown) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x2080, false);
						}
						else if (dpdup.compare(lvleft) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x4000, false);
						}
						else if (dpdup.compare(lvright) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x8000, false);
						}
					}
					else if (e.jhat.which == joystick_index2)
					{
						if (dpdup2.compare(exit2) == 0)
						{
							system("taskkill /f /im spice.exe");
						}
						else if (dpdup2.compare(test2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x02, false);
						}
						else if (dpdup2.compare(service2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x01, false);
						}
						else if (dpdup2.compare(coin2) == 0)
						{
							int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
							helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
						}
						else if (dpdup2.compare(view2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x400, false);
						}
						else if (dpdup2.compare(three2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x800, false);
						}
						else if (dpdup2.compare(lvup2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x1040, false);
						}
						else if (dpdup2.compare(lvdown2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x2080, false);
						}
						else if (dpdup2.compare(lvleft2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x4000, false);
						}
						else if (dpdup2.compare(lvright2) == 0)
						{
							helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x8000, false);
						}
					}
				}
				else if (e.jhat.value == SDL_HAT_DOWN)
				{
				if (e.jhat.which == joystick_index1)
				{
					if (dpddown.compare(exit) == 0)
					{
						system("taskkill /f /im spice.exe");
					}
					else if (dpddown.compare(test) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x02, false);
					}
					else if (dpddown.compare(service) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x01, false);
					}
					else if (dpddown.compare(coin) == 0)
					{
						int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
						helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
					}
					else if (dpddown.compare(view) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x400, false);
					}
					else if (dpddown.compare(three) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x800, false);
					}
					else if (dpddown.compare(lvup) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x1040, false);
					}
					else if (dpddown.compare(lvdown) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x2080, false);
					}
					else if (dpddown.compare(lvleft) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x4000, false);
					}
					else if (dpddown.compare(lvright) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x8000, false);
					}
				}
				else if (e.jhat.which == joystick_index2)
				{
					if (dpddown2.compare(exit2) == 0)
					{
						system("taskkill /f /im spice.exe");
					}
					else if (dpdup2.compare(test2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x02, false);
					}
					else if (dpddown2.compare(service2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x01, false);
					}
					else if (dpddown2.compare(coin2) == 0)
					{
						int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
						helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
					}
					else if (dpddown2.compare(view2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x400, false);
					}
					else if (dpddown2.compare(three2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x800, false);
					}
					else if (dpddown2.compare(lvup2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x1040, false);
					}
					else if (dpddown2.compare(lvdown2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x2080, false);
					}
					else if (dpddown2.compare(lvleft2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x4000, false);
					}
					else if (dpddown2.compare(lvright2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x8000, false);
					}
					}
				}
				else if (e.jhat.value == SDL_HAT_LEFT)
				{
				if (e.jhat.which == joystick_index1)
				{
					if (dpdleft.compare(exit) == 0)
					{
						system("taskkill /f /im spice.exe");
					}
					else if (dpdleft.compare(test) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x02, false);
					}
					else if (dpdleft.compare(service) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x01, false);
					}
					else if (dpdleft.compare(coin) == 0)
					{
						int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
						helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
					}
					else if (dpdleft.compare(view) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x400, false);
					}
					else if (dpdleft.compare(three) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x800, false);
					}
					else if (dpdleft.compare(lvup) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x1040, false);
					}
					else if (dpdleft.compare(lvdown) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x2080, false);
					}
					else if (dpdleft.compare(lvleft) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x4000, false);
					}
					else if (dpdleft.compare(lvright) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x8000, false);
					}
				}
				else if (e.jhat.which == joystick_index2)
				{
					if (dpdleft2.compare(exit2) == 0)
					{
						system("taskkill /f /im spice.exe");
					}
					else if (dpdleft2.compare(test2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x02, false);
					}
					else if (dpdleft2.compare(service2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x01, false);
					}
					else if (dpdleft2.compare(coin2) == 0)
					{
						int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
						helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
					}
					else if (dpdleft2.compare(view2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x400, false);
					}
					else if (dpdleft2.compare(three2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x800, false);
					}
					else if (dpdleft2.compare(lvup2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x1040, false);
					}
					else if (dpdleft2.compare(lvdown2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x2080, false);
					}
					else if (dpdleft2.compare(lvleft2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x4000, false);
					}
					else if (dpdleft2.compare(lvright2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x8000, false);
					}
					}
				}
				else if (e.jhat.value == SDL_HAT_RIGHT)
				{
				if (e.jhat.which == joystick_index1)
				{
					if (dpdright.compare(exit) == 0)
					{
						system("taskkill /f /im spice.exe");
					}
					else if (dpdright.compare(test) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x02, false);
					}
					else if (dpdright.compare(service) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x01, false);
					}
					else if (dpdright.compare(coin) == 0)
					{
						int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
						helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
					}
					else if (dpdright.compare(view) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x400, false);
					}
					else if (dpdright.compare(three) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x800, false);
					}
					else if (dpdright.compare(lvup) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x1040, false);
					}
					else if (dpdright.compare(lvdown) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x2080, false);
					}
					else if (dpdright.compare(lvleft) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x4000, false);
					}
					else if (dpdright.compare(lvright) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x8000, false);
					}
				}
				else if (e.jhat.which == joystick_index2)
				{
					if (dpdright2.compare(exit2) == 0)
					{
						system("taskkill /f /im spice.exe");
					}
					else if (dpdright2.compare(test2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x02, false);
					}
					else if (dpdright2.compare(service2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x01, false);
					}
					else if (dpdright2.compare(coin2) == 0)
					{
						int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
						helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
					}
					else if (dpdright2.compare(view2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x400, false);
					}
					else if (dpdright2.compare(three2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x800, false);
					}
					else if (dpdright2.compare(lvup2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x1040, false);
					}
					else if (dpdright2.compare(lvdown2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x2080, false);
					}
					else if (dpdright2.compare(lvleft2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x4000, false);
					}
					else if (dpdright2.compare(lvright2) == 0)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x8000, false);
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
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x02, false);
					}
					else if (e.jbutton.button == ExitButton)
					{
						system("taskkill /f /im spice.exe");
					}
					else if (e.jbutton.button == ServiceButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x01, false);
					}
					else if (e.jbutton.button == CreditButton)
					{
						int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
						helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
					}
					else if (e.jbutton.button == ViewButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x400, false);
					}
					else if (e.jbutton.button == ThreeDimensionalButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x800, false);
					}
					else if ((e.jbutton.button == leverUp) & (SequentialGears == 0))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x1040, false);
					}
					else if ((e.jbutton.button == leverUp) & (SequentialGears == 1) & (gearnumber3 < 0x06))
					{
						int Writegearnumber = helpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x00953F70, false);
						int Writegearnumber1 = helpers->ReadIntPtr((INT_PTR)Writegearnumber + 0x5C, false);
						int Writegearnumber2 = helpers->ReadIntPtr((INT_PTR)Writegearnumber1 + 0x390, false);
						helpers->WriteIntPtr((INT_PTR)Writegearnumber2 + 0x18, ++gearnumber3, false);
					}
					else if ((e.jbutton.button == leverDown) & (SequentialGears == 0))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x2080, false);
					}
					else if ((e.jbutton.button == leverDown) & (SequentialGears == 1) & (gearnumber3 > 0x01))
					{
						int Writegearnumber = helpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x00953F70, false);
						int Writegearnumber1 = helpers->ReadIntPtr((INT_PTR)Writegearnumber + 0x5C, false);
						int Writegearnumber2 = helpers->ReadIntPtr((INT_PTR)Writegearnumber1 + 0x390, false);
						helpers->WriteIntPtr((INT_PTR)Writegearnumber2 + 0x18, --gearnumber3, false);
					}
					else if (e.jbutton.button == leverLeft)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x4000, false);
					}
					else if (e.jbutton.button == leverRight)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x8000, false);
					}
				}
				else if (e.jbutton.which == joystick_index2)
				{
					if (e.jbutton.button == TestButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x02, false);
					}
					else if (e.jbutton.button == ExitButtonDevice2)
					{
						system("taskkill /f /im spice.exe");
					}
					else if (e.jbutton.button == ServiceButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x01, false);
					}
					else if (e.jbutton.button == CreditButtonDevice2)
					{
						int credit = helpers->ReadIntPtr((INT_PTR)gl_hlibavs + 0x00042C10, false);
						helpers->WriteIntPtr((INT_PTR)credit + 0x20, ++creditnumber1, false);
					}
					else if (e.jbutton.button == ViewButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x400, false);
					}
					else if (e.jbutton.button == ThreeDimensionalButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x800, false);
					}
					else if ((e.jbutton.button == leverUpDevice2) & (SequentialGears == 0))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x1040, false);
					}
					else if ((e.jbutton.button == leverUpDevice2) & (SequentialGears == 1) & (gearnumber3 < 0x06))
					{
						int Writegearnumber = helpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x00953F70, false);
						int Writegearnumber1 = helpers->ReadIntPtr((INT_PTR)Writegearnumber + 0x5C, false);
						int Writegearnumber2 = helpers->ReadIntPtr((INT_PTR)Writegearnumber1 + 0x390, false);
						helpers->WriteIntPtr((INT_PTR)Writegearnumber2 + 0x18, ++gearnumber3, false);
					}
					else if ((e.jbutton.button == leverDownDevice2) & (SequentialGears == 0))
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x2080, false);
					}
					else if ((e.jbutton.button == leverDownDevice2) & (SequentialGears == 1) & (gearnumber3 > 0x01))
					{
						int Writegearnumber = helpers->ReadIntPtr((INT_PTR)gl_hjgtDll + 0x00953F70, false);
						int Writegearnumber1 = helpers->ReadIntPtr((INT_PTR)Writegearnumber + 0x5C, false);
						int Writegearnumber2 = helpers->ReadIntPtr((INT_PTR)Writegearnumber1 + 0x390, false);
						helpers->WriteIntPtr((INT_PTR)Writegearnumber2 + 0x18, --gearnumber3, false);
					}
					else if (e.jbutton.button == leverLeftDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x4000, false);
					}
					else if (e.jbutton.button == leverRightDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x8000, false);
					}
				}
			}
			if (e.type == SDL_JOYBUTTONUP)
			{
				if (e.jbutton.which == joystick_index1)
				{
					if (e.jbutton.button == TestButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == ServiceButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == ViewButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == ThreeDimensionalButton)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == leverUp)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == leverDown)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == leverLeft)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == leverRight)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
				}
				else if (e.jbutton.which == joystick_index2)
				{
					if (e.jbutton.button == TestButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == ServiceButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == ViewButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == ThreeDimensionalButtonDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == leverUpDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == leverDownDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == leverLeftDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
					else if (e.jbutton.button == leverRightDevice2)
					{
						helpers->WriteIntPtr((INT_PTR)gl_hjgtDll + 0x7D2B24, 0x0000, false);
					}
				}
			}
		}
	}

		
		UINT8 ff1 = helpers->ReadByte((INT_PTR)gl_hjgtDll + 0x7D2BB9, false);
		UINT8 ff2 = helpers->ReadByte((INT_PTR)gl_hjgtDll + 0x7D2BBA, false);
		helpers->log("got value: ");
		std::string ffs = std::to_string(ff2);
		helpers->log((char *)ffs.c_str());
		
		if (FFBMode == 0)
		{
			if ((ff2 > 0x00) & (ff2 < 0x40))
			{				
				double percentForce = (ff2) / 63.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, percentForce, percentLength);
				triggers->Sine(120, 120, percentForce);
			}
			if ((ff1 > 0x00) & (ff1 < 0x08))
			{
				//helpers->log("moving wheel left");
				double percentForce = (ff1) / 7.0;
				double percentLength = 100;
				triggers->LeftRight(0, percentForce, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
			}
			else if ((ff1 > 0x07) & (ff1 < 0x10))
			{
				//helpers->log("moving wheel right");
				double percentForce = (16 - ff1) / 8.0;
				double percentLength = 100;
				triggers->LeftRight(percentForce, 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
			}
		}
		else if (FFBMode == 1)
		{
			if ((ff2 > 0x00) & (ff2 < 0x40))
			{
				double percentForce = (ff2) / 63.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), pow(percentForce, 0.5), percentLength);
				triggers->Sine(120, 120, pow(percentForce, 0.5));
			}
			if ((ff1 > 0x00) & (ff1 < 0x08))
			{
				//helpers->log("moving wheel left");
				double percentForce = (ff1) / 7.0;
				double percentLength = 100;
				triggers->LeftRight(pow(percentForce, 0.5), 0, percentLength);
				triggers->Constant(constants->DIRECTION_FROM_LEFT, (pow(percentForce, 0.5)));
			}
			else if ((ff1 > 0x07) & (ff1 < 0x10))
			{
				//helpers->log("moving wheel right");
				double percentForce = (16 - ff1) / 8.0;
				double percentLength = 100;
				triggers->LeftRight(0, pow(percentForce, 0.5), percentLength);
				triggers->Constant(constants->DIRECTION_FROM_RIGHT, (pow(percentForce, 0.5)));
			}
		}
	}