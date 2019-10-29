***FFB Arcade Plugin***

Version 1.1

Brought to you by Boomslangnz, Ducon2016, Spazzy & pinkimo.

This is a plugin to provide Force Feedback and Rumble (and in certain cases added input support) to various arcade games. Initially this was a small project
to add FFB to Daytona Championship USA and it grew from there to support several more games and rumble was added. 
While best efforts were made to try to resemble the real arcade force feedback, It will never be 100% accurate & 
in some cases eg Mario Kart GP DX, Pokken Tournament and Battle Gear 4,effects were created entirely from scratch
so are not using real force feedback values. Most games use correct ffb values however :)

***1.1 Changes***

  Big Thanks to pinkimo for his efforts, Open Source has added good value already!

- Huge modification of WMMT5 FFB effects completely re-done by pinkimo!!

- Huge modification of FFBPlugin GUI. Big Changes from Development point of view aswell as for users & much needed work!!
  Helper function added, New WMMT5 options (including cheats) & SO MUCH MORE (pinkimo)

- Fixed issue with newer Fanatec wheels which would show as 2 x devices and load wrong "device" and ffb wouldn't work (pinkimo)

- Fixed issue where values could go over max allowed with SDL2 and generate reversed FFB effects (pinkimo)

- Fixed & Improved Sine Effect (pinkimo)

- Added AlternativeFFB for Sine & Triangle Effects (pinkimo)

- Removed ResetFeedback as not necessary (pinkimo)

- Changed Enable Rumble to select Force Feedback or Rumble and never both to avoid issues with conflicting effects (read below for details if using ini directly)

- Replaced code for ShowButtonNumbersForSetup & ShowAxisForSetup if not using GUI to use every button/axis available

- Updated SDL2 from 2.0.5 to 2.0.9 to match Teknoparrot (Delete SDL22.dll if leftover from old release in any teknoparrot folders)
BE AWARE THIS WILL CHANGE YOUR GUID NUMBER OF DEVICES, RE-SET UP!!!

- Renamed FFBPlugin.txt to FFBPluginReadme.txt to make it obvious its a readme 

- Fixed issue where coin rumble wouldn't work at all on Mario Kart GP DX 1.10

- Fixed issue with LGI & LGI3D where rumble wouldn't always work

- Added Rumble Support for HOTD4 

- Overhauled Daytona Championship USA Menu Movement Input to allow initials to be selected after races etc aswell

- Added CabinetID code to Road Fighters 3D to not require hex edited files etc anymore. Simply select Cabinet ID in GUI and LAN Play will work :)

- Modified Button Rumble Plugin to work better as previously could have slight lag on rumble

- Added FFB Support for GRID

- Modified and cleaned constant effect up

- General code cleanup

***1.0 Changes***

- Made Code Open Source (Good luck trying to decipher my poor coding)

https://nodejs.org/en/ Install this if you want to auto build into named folders etc

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

***0.9c Changes***

- Added FFB Support for KO Drive

***0.9b Changes***

- Fixed issue where M2 Emulator wouldn't close correctly while using FFB Plugin

- Added FFB support for Ford Racing to non-TP loaders (use FordRacingOther plugin)

- Fixed wrong SDL2.dll file with WMMT5 on last release (sorry)

***0.9a Changes***

- Fixed issue where MAME plugins would not load

***0.9 Changes***

- Added scroll bar to MKDX and Road Fighters 3D input side as couldn't see all options unless very high resolution monitor on GUI

- Completely Modified OR2 SP Real plugin as effects were set quite wrong previously & added gear shift rumble as requested

- Added optional input support for OR2 SP for H-Pattern gear changes (will only work if you select manual transmission)

- Fixed issue which would cause Force Feedback to not work on Road Fighters 3D due to dinput8 blocker i was using previously on certain wheels.
PLEASE REMOVE d3d9.dll & dinput8.dll if used old version!!!
Blocker is not necessary anymore and ive fixed it properly compared to being lazy lol. Enable input support to disable default dinput8 controls used by Road Fighters 3D

- Modified Road Fighters 3D FFB to only work when racing starts as otherwise it does crazy stuff before race or while attract mode plays

- Added option to disable 3D for Road Fighters 3D

- Added option to do a hack to try skip past error menu screen quickly for Road Fighters 3D on startup

- Added option to close Libmovie error popup automatically if it happens for Road Fighters 3D

- Lowered default Max Force for WMMT5 since people never read readme, then complain it's too strong

- Huge overhaul for when adding inputs to input supported games via gui, Works much better (Click on axis/button number on right side to remove if required)

- Re-wrote input system for every supported game via plugin itself

- Fixed various bugs found in GUI

- Renamed Input Setup in FFBPluginGUI.exe to Input / Miscellaneous Setup as it has options other then JUST input on certain games

- Added Force Feedback test page to GUI for users to test effects on their devices

- Fixed issue where Feedback Length wouldn't allow enough characters and modify ini setting automatically

- Defaulted log to off, not as necessary anymore with GUI around

- Modified Initial D4,D5,D6,D7 & D8 plugin (Be sure to try out both FFBMode and without) Remember to set FORCE=10 in test menu

- Added support for new haptic effect forces damper, inertia, ramp, sawtoothup, sawtoothdown & triangle

- Modified Daytona Championship USA exit method for better way

- Modified forces to avoid the "tick" feeling with certain effects

- Raised spring strength in Sega Racing Classic plugin

- Tidied up Battle Gear 4 code and replace simple rumble with left/right effects for rumble

- Added test code to rumble for infinite time period. Set GameID to -7 if you want to check rumble works via plugin

- Fixed issue where plugin could crash game if no FFBPlugin.ini was present in game folder

***0.8 Changes***

- Sorry! Been so busy,never had time to test last release correctly and upgrading SDL2 version broke effects working correctly on all games! 

Reverting back to SDL2 2.0.5 and modified lindbergh game plugins to load SDL22.dll.

SDL22.dll will be supplied in plugin folders for Lindbergh games and need to be placed into the Teknoparrot folder INSIDE the MAIN Teknoparrot folder. 

SDL2.dll will still be supplied aswell to be placed in same folder as FFBPlugin.ini if you want to use FFBPluginGUI.exe

Hopefully this makes sense, please ask if you are confused.

- Outrun 2 now has 2 x plugins. One is the custom effects created from scratch you have been using all this time :) and the other is using the real FFB Address now.
(Big thanks to Reaver for help on getting the real ffb working)

***0.7 Changes***

- Upgraded FFB Arcade Plugin to use SDL 2 2.0.9 version compared to the old 2.0.5 used previously. Will sort out FFB Plugin working when using Faudio on new teknoparrot

***0.6a Changes***

- Modified GUI to check FFBPlugin and load game settings as soon as you choose Force Feedback Setup or Input Setup instead of having game list and potentially writing unnecessary values to ini

- Added logo on first GUI page made by POOTERMAN (Thanks mate)

- Defaulted WMMT5 logging to off as plugin hooks GUI lol

- Added GUI to every plugin folder by default now as it was confusing users with copying GUI to correct folders etc. I have setup correct 32bit and 64bit exe with each plugin

- Just a note if you are using Lindbergh games and want to use GUI. Copy MetroFramework.dll & SDL2.dll to same folder as elf file (Where FFBPlugin.ini goes too),
opengl32.dll & SDL2.dll goes to Teknoparrot folder as usual. You do not need to copy GUI or Metroframework.dll to Teknoparrot folder at all.


***0.6 Changes***

- Added support for Mame 0.206 with same games from old 0.199 games. Works with 32bit, 64bit Mame Binary or MameUI64

- Added Optional GUI to make modifying settings or setting up deviceguid a bit easier (read below for details, HAS TO BE IN SAME FOLDER WITH PLUGIN FILES & METROFRAMEWORK.dll)


***0.5 Changes***

- Removed spring effect from Mario Kart 1.10 as it had issues with pulling wheel to side and replaced with constant effect for steering. Added options to enable and disable and modify strength (Do not lower below 128 in ini!!)

- Added Dpad support for Road Fighters 3D input (read below for details)

- Added ForceShowDeviceGUIDMessageBox option in ini to force Device Name and Device GUID to show in messagebox popup for each device connected

- Added option to reverse rumble motors if motors rumbling in reverse to how you like it


***0.4 Changes***

- Modified Button Rumble plugin to allow 2 x controllers to rumble
(Plugin can be renamed to either dinput8.dll,dinput.dll,d3d9.dll,d3d11.dll,xinput1_3.dll,opengl32.dll or winmm.dll to hook application)

- Modified Machstorm plugin to allow modifying rumble strength and length if required on effects

- Modified Afterburner Climax plugin to allow modifying strength and length if required on effects

- Modified Pokken Tournament plugin to allow modifying strength and length if required on effects (ini contains HowtoRumbleEffect. 0 = both motors, 1 = left motor, 2 = right motor so you can customize to how it suits)

- Fixed bug on Pokken Tournament where rumble wouldn't work

- Added rumble support for Let's Go Island (ini contains HowtoRumbleEffect. 0 = both motors, 1 = left motor, 2 = right motor so you can customize to how it suits, supports multiple controllers for 2p)

- Added rumble support for Let's Go Island 3D (ini contains HowtoRumbleEffect. 0 = both motors, 1 = left motor, 2 = right motor so you can customize to how it suits, supports multiple controllers for 2p)

- Added FFB Support for San Francisco Rush and San Francisco Rush The Rock for mame 0.199 60fps custom hack version (http://forum.arcadecontrols.com/index.php?topic=158489.0)


***0.3 Changes***

- Added general button plugin to rumble controller when button pressed, modify length for how long in ini (Great for lightgun games!)

- Added options to Daytona Championship USA ini to enable or disable Exit Button, Menu Movement or Gear Changes (Teknoparrot version now has this all built in)

- Added FFB support for Nascar Racing on Demul (180428 version)

- Added FFB support for GTI Club Supermini Festa on Teknoparrot

- Added FFB support for Road Fighters 3D using spicetools, added option for input support for analog and buttons. Read bottom of this for details 

- Fixed issue where Sega Racing Classic FFB wouldn't work while playing over network

- Renamed the log.txt to FFBlog.txt as certain games already created a log.txt which could cause issues

- Added Daytona USA Multiplayer AI Hack (up to 4 player so far) on M2 Emulator, enable in ini file to enable. While racing network, positions will include AI Car positions too.

- Added Daytona Force Panoramic Attract option on M2 Emulator to force the game to use panoramic attract mode on less then 4 players even


***0.2 Changes***

- Added support for California Speed, Cruis'n World, Cruis'n USA & Off Road Challenge on Mame 32 or 64bit Binary OR MameUI64 ONLY for Mame 0.199.

- Added support for Sega Rally Championship,Daytona USA,Indy 500,Sega Touring Car Championship,Over Rev & Super GT 24h on M2 Emulator 1.1a (just alternative to built in FFB)
 (Disable FFB in Emulator.ini if you want to use FFB Plugin instead of M2 Emulator's built in FFB support. Set hardware type to STCC for OverRev & I/O board to A or B for Super GT 24h in test menu!! )

- Added support for Initial D4 Japan, Initial D5,Sonic & Sega All Stars Racing & Outrun 2 Special Tours Deluxe for Teknoparrot

- Added strength options in ini for most effects in Mario Kart 1.10. Wheels can only use MAX of 100, Controller can go higher
Multiplier option is if you want to raise the strength of Water and Drift effects, 200 would double the strength etc. Set to 100 by default

- Added option to certain games in ini to give a bit more strength to lower forces. FFBMode=0 is the standard and FFBMode=1 is the new mode 
(BE WARNED ON CERTAIN WHEELS THIS COULD CAUSE OSCILLATION TO OCCUR)

- Added option to Daytona Championship USA ini to hide mouse cursor

- Added AlternativeFFB option to ini which is for wheels such as PWM2M2 or certain direct drive wheels etc which use constant effect incorrectly ingame.
eg Roll left and Roll Right doesn't work correctly, Enable Alternative FFB to modify this and added strength options for it


***0.1a Changes***

- Added support for San Francisco Rush, San Francisco Rush The Rock, San Francisco Rush 2049,
San Francisco Rush 2049 SE & Rave Racer on Mame 32 or 64bit Binary OR MameUI64 ONLY for Mame 0.199.

 Please turn on Feedback steering in game settings on Rave Racer or you will not recieve FFB & I suggest you 
 adjust deadzone for your wheel in mame settings.

(This was added just for a little fun as no one really has done ffb on mame yet)

- Added Daytona Championship USA exit key (escape), Gear change added for Gears 1,2,3 & 4 or Sequential Gear Up/Down.
Change Button Number in ini if necessary (x360ce not necessary for gear change).
Make ShowButtonNumbersForSetup=1 if you want to have popup boxes to work out Button Layout. Press button to see box
Track selection menu & Name Entry has added control too now


- Modified Mario Kart DX 1.10 FFB adding a bunch of new effects and ini can now Enable or Disable Effects
- Will rumble when picking up coins
- Will rumble when picking up weapons
- Will rumble when using weapons
- Drift effect on rumble (stronger the more you turn)(rumble each way when turning etc)
- Boost effect on rumble
- Rumble when kart hits ground from jumps or flying
- Water effect on rumble (rumble each way when turning etc)
- Speed of kart taken into effect etc

***REQUIREMENTS***

- Requires Visual Runtime Files https://www.techpowerup.com/download/visual-c-redistributable-runtime-package-all-in-one/

- GUI Requires Visual Runtime 2015 (pretty sure its this lol) and has to be in same folder with metroframework.dll & SDL2.dll

***CREDITS***

- Reaver from Teknoparrot . Huge thanks to Reaver for supplying code necessary for some games & general force feedback,
extremely generous.

- Jackchen for his Daytona Championship USA FFB work at beginning of year.

- Howard Castro for help on game FFB code. Always helpful and a big reason this plugin was ever made

- Mame team

- SailorSat for finding the offsets etc required for Daytona USA Multiplayer AI hack

- Nuexzz for finding offset required for Daytona Panoramic Force Hack

- POOTERMAN for making logo on GUI

- Everyone who helps and gives back to this awesome scene. Thanks for everything!


***SUPPORTED GAMES***

-Afterburner Climax (Rumble only) [opengl32.dll into Teknoparrot folder inside Main Teknoparrot folder]

-Battle Gear 4 Tuned (Japan version v2.07) [d3d9.dll into game exe folder]

-ChaseHQ 2 [d3d9.dll into game exe folder]

-Daytona USA [dinput8.dll into m2 emulator 1.1a folder]

-Daytona Championship USA [dinput8.dll into game exe folder]

-Ford Racing [dinput8.dll into game exe folder]

-Indy 500 [dinput8.dll into m2 emulator 1.1a folder]

-Initial D4 [opengl32.dll into Teknoparrot folder inside Main Teknoparrot folder]

-Initial D4 Japan [opengl32.dll into Teknoparrot folder inside Main Teknoparrot folder]

-Initial D5 [opengl32.dll into Teknoparrot folder inside Main Teknoparrot folder]

-Initial D6 [dinput8.dll into game exe folder]

-Initial D7 [dinput8.dll into game exe folder]

-Initial D8 [dinput8.dll into game exe folder]

-Machstorm (Rumble only) [xinput1_3.dll into game exe folder]

-Mario Kart GP DX (Version 1.00 & version 1.10) [dinput8.dll into game exe folder]

-Pokken Tournament (Rumble only) [dinput8.dll into game exe folder]

-Sega Touring Car Championship [dinput8.dll into m2 emulator 1.1a folder]

-Sega Racing Classic [dinput8.dll into game exe folder]

-Sega Rally Championship [dinput8.dll into m2 emulator 1.1a folder]

-Sega Rally 3 [dinput8.dll into game exe folder]

-Super GT 24h [dinput8.dll into m2 emulator 1.1a folder]

-Sonic & Sega All Stars Racing [d3d9.dll into game exe folder]

-Outrun 2 Special Tours Deluxe [opengl32.dll into Teknoparrot folder inside Main Teknoparrot folder]

-Over Rev [dinput8.dll into m2 emulator 1.1a folder]

-Wacky Races [d3d9.dll into game exe folder]

-Wangan Midnight Maximum Tune 5 (Update 5) [d3d11.dll into game exe folder]

-San Francisco Rush, San Francisco Rush The Rock, San Francisco Rush 2049 & San Francisco Rush 2049 SE 
(will ONLY work on either Mame Binary 32 or 64 bit or MameUI64 for Mame version 0.199 or 0.206 [dinput8.dll into any mame 0.199 or mame 0.206 folder]

-Rave Racer [dinput8.dll into any mame 0.199 folder]
TURN ON FEEDBACK STEERING IN GAME SETTINGS OR YOU WILL NOT RECIEVE FORCE FEEDBACK!
(will ONLY work on either Mame Binary 32 or 64 bit or MameUI64 for Mame version 0.199 or 0.206  [dinput8.dll into any mame 0.199 or mame 0.206 folder]

-California Speed
(will ONLY work on either Mame Binary 32 or 64 bit or MameUI64 for Mame version 0.199 or 0.206 [dinput8.dll into any mame 0.199 or mame 0.206 folder]

-Cruis'n World
(will ONLY work on either Mame Binary 32 or 64 bit or MameUI64 for Mame version 0.199 or 0.206 [dinput8.dll into any mame 0.199 or mame 0.206 folder]

-Cruis'n USA
(will ONLY work on either Mame Binary 32 or 64 bit or MameUI64 for Mame version 0.199 or 0.206 [dinput8.dll into any mame 0.199 or mame 0.206 folder]

-Off Road Challenge
(will ONLY work on either Mame Binary 32 or 64 bit or MameUI64 for Mame version 0.199 or 0.206 [dinput8.dll into any mame 0.199 or mame 0.206 folder]

-GTI Club Supermini Festa [dinput8.dll into game exe folder]

-Road Fighters 3D [dinput8.dll into game exe folder]

-Nascar Racing [dinput8.dll into demul 180428 version folder]

-Let's Go Island [d3d9.dll into game exe folder]

-Let's Go Island 3D [d3d9.dll into game exe folder]

-KO Drive [d3d9.dll into game exe folder]


***HOW TO USE***

Place the main dll file, SDL2.dll & FFBPlugin.ini into game folder for most games. 

For Teknoparrot Lindbergh games place opengl32.dll into Teknoparrot folder inside Main Teknoparrot folder & FFBPlugin.ini,SDL2.dll, MetroFramework.dll & FFBPluginGUI.exe into same folder as elf file for each game.

Elf file is like the lindbergh version of an exe eg the file you choose to load via teknoparrot

If you are using FFB Plugin on Teknoparrot instead of using Teknoparrot built in FFB, Please turn off Force Feedback in TeknoparrotUI. (Not necessary on latest TP Versions)

ini file contains settings to adjust for each game

GameId= **GameId for code to identify game, also has a test FFB mode,-1 for Constant test ,-2 for
Sine test, -3 for Friction test, -4 for Spring test, -5 for Heavy test or -6 for loose test**

MinForce= **Minimum FFB force with 0 being lowest value available**

MaxForce= **Maximum FFB force with 100 being highest value available**

DeviceGUID= **Set Device GUID to connect to specific wheel or controller**

FFBorRumble= **Turn to 0 if using wheel & want Force Feedback effects. For controllers change to 1 to enable rumble**

Logging= **Turn On (1) to allow log.txt to be made to log plugin. Device GUID is given in here**

FeedbackLength= **Length of a feedback command**

DefaultCentering= **If a game does not specify its own Centering force then a default centering can be applied here.
If a game has any of its own such forces,these values will be overwritten immediately in-game. Use -1 to disable**

DefaultFriction= **If a game does not specify its own Friction force then a default friction can be applied here.
If a game has any of its own such forces,these values will be overwritten immediately in-game. Use -1 to disable**

BeepWhenHook= **Beep should occur if dll is hooked by executable when turned on (1)**

FFBMode= **This will raise strength of lower forces, potentially could cause oscillation to occur on certain games. Set 1 to turn on**

AlternativeFFB= **This is for certain wheels where roll effect does not work correctly normally (such as PWM2M2 or Thrustmaster 300rs etc). Set 1 to turn on **

Device2GUID= **Set Device 2 GUID to connect to secondary specific wheel or controller (buttons only)**


*** GUI SUPPORT ***

- REQUIRES visual runtime 2015,SDL2.dll & Metroframework.dll. SDL2.dll & Metroframework.dll are supplied in each plugin folder

- Is designed to be used in conjunction with FFBPlugin.ini files included with each plugin folder. Place all plugin files into game exe folder(unless Lindbergh)

- If FFBPlugin.ini exists, it will read the values and display values etc on game page. As soon as you adjust any value, it automatically writes to FFBPlugin.ini the new value

- If FFBPlugin.ini doesn't exist it will give you message saying so or if GameId number is missing from FFBPlugin.ini

- Input support will only work on the supported games, otherwise message will tell you it is unsupported for that games plugin


*** INPUT SUPPORT ***

To enable input on supported games, firstly setup GUID as normal and enable InputDeviceWheelEnable in ini (1 to turn on, 0 to turn off).

Ive pre-set the axis for Logitech G920 wheel however if this is incorrect I have added options 
to change in FFBPlugin.ini. 

- Added option for Device2GUID in ini for a 2nd device to include inputs (great for seperate usb shifter etc, add the button numbers to the device2 buttons in ini )

- Enable ShowButtonNumbersForSetup to give window popup to give button numbers for setup into FFBPlugin.ini

- Enable ShowAxisSetup to give window popup to give axis numbers for setup into FFBPlugin.ini

- You can enable ShowButtonNumbersForSetup & ShowAxisSetup at same time if you wish

- SteeringDeadzone to modify the steering deadzone for either wheel or controller. 
(Recommend around 2 for wheel and 70 for controller, but feel free to play around for best setting)

- SequentialGears option will disable standard h pattern gear shift and use leverUp & leverDown to shift up and down gears easily

- Enable InputDeviceCombinedPedals if your wheel or controller uses combined axis, setup as InputDeviceWheelAcclAxis in ini

- Set DpadUp,DpadDown,DpadLeft & DpadRight = as any button name in ini eg DpadUp=StartButton and DpadUp will now do start button ingame. You can use Dpad and normal button at same time if you wish

After setting up Axis and Buttons then Disable ShowButtonNumbersForSetup & ShowAxisSetup if enabled and play!


*** TROUBLESHOOTING ***

OMG FFB DOESN'T WORK!!

1) Firstly copy files to where supported games section says
2) Run Game then exit after a few seconds
3) Check FFBlog.txt for device guid number
4) Copy this number to FFBPlugin.ini to DeviceGUID=
5) Disable logging in FFBPlugin.ini if you wish for no logging
6) Play Game
7) If still no FFB, ensure you have visual runtime files installed

INPUT HELP
1) Device does nothing ingame!! (enable InputDeviceWheelEnable)
2) Steering doesn't work (set up correct axis in ini)
3) Pedals don't work (set up correct axis in ini)
4) Pedals only work when not pressed (enable reverse axis)
5) Pedals need to be combined (enable combined pedals)
6) Buttons don't work (set up correct button numbers in ini)
7) Device2 doesn't work (set up correct button numbers in ini under Device2buttons)

Default Axis and Button Numbers to help with setup on certain controllers/wheels

For Xbox One & Xbox 360 Controller:
[Axis Numbers]
Left Stick X Axis = 0
Left Stick Y Axis = 1
Right Stick X Axis = 3
Right Stick Y Axis = 4
Left Trigger = 2
Right Trigger = 5

[Button Numbers]
A Button = 0
B Button = 1
X Button = 2
Y Button = 3
Left Shoulder Button = 4
Right Shoulder Button = 5
Back Button/View Button = 6
Start Button/Menu Button = 7
Left Stick Down Button = 8
Right Stick Down Button = 9

For Thrustmaster T300RS:
[Axis Numbers]

[If Seperate Axis]
Steering Axis = 0
Accl Axis = 2
Brake Axis = 1

[If Combined Axis]
Steering Axis = 0
Accl Axis = 1
Brake Axis = 1

[Button Numbers]
PS Button = 12
L2 Button = 9
R2 Button = 8
ST Button = 7
SE Button = 6
X Button = 5
[] Button = 3
() Button = 4
/\ Button = 2
Right Paddle = 1
Left Paddle = 0