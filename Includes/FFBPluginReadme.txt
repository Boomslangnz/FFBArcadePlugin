***FFB Arcade Plugin***

Brought to you by Boomslangnz, MightyMike, Ducon2016, Spazzy, Adam_, jpb, Rocco & pinkimo.

This is a plugin to provide Force Feedback and Rumble to various arcade games.


***REQUIREMENTS***

- Requires Visual Runtime Files https://www.techpowerup.com/download/visual-c-redistributable-runtime-package-all-in-one/

- GUI Requires Visual Runtime 2019 and has to be in same folder with metroframework.dll & SDL2.dll


***HOW TO USE***

Launch FFBPluginGUI.exe & Go to Setup Help Section. 

For more advanced information read below


***Advanced information***

-Alternative FFB is for certain wheels such as Thrustmaster wheels or PWM2M2 etc where rotation always goes only 1 direction, enable this to fix if your wheel does this

-MinForce is the lowest force the wheel strength will be, if AlternativeFFB is enabled, use AlternativeFFB MinForce instead.

-MaxForce is the maximum force the wheel strength will be, if AlternativeFFB is enabled, use AlternativeFFB MaxForce instead.

-Feedback length is how long the force feedback effect will last for

-Enable Rumble is to enable or disable Rumble for controllers

-Reverse Rumble is to swap the motors around if it rumbles opposite to how you want

-PowerMode is to raise the strength of low values to increase strength feel on certain games

-Some games such as Road Fighters 3D have input support. Go to Input section and enable Input Support and set up axis/buttons


*** OUTPUT SUPPORT ***

(For MAME)

- Create a ini file on root of MAME folder called Mame.ini and place inside it and save
#
# OSD OUTPUT OPTIONS
#
output                    windows

- Ensure either MAME32.dll or MAME64.dll is with FFB Plugin files in MAME folder depending on 32bit or 64bit MAME

(For SUPERMODEL EMULATOR)

- If you wish to use FFB Plugin over Supermodel's FFB then disable Supermodel's FFB.

- When you launch game, ensure you have command -outputs=win for FFB Plugin to recieve Output Values etc

- Ensure either MAME32.dll or MAME64.dll is with FFB Plugin files in Supermodel folder depending on 32bit or 64bit Supermodel


***CREDITS***

- Reaver from Teknoparrot . Huge thanks to Reaver for supplying code necessary for some games & general force feedback,
extremely generous.

- Jackchen for his Daytona Championship USA FFB work.

- seam for always testing and helping

- Howard Castro for help on game FFB code. Always helpful and a big reason this plugin was ever made

- Mame team

- SailorSat for finding the offsets etc required for Daytona USA Multiplayer AI hack

- Nuexzz for finding offset required for Daytona Panoramic Force Hack

- POOTERMAN for making logo on GUI

- headkaze for making MAMEInterOp SDK

- Rocco for WMMT6RR FFB.

- Everyone who helps and gives back to this awesome scene. Thanks for everything!


***SUPPORTED GAMES***

MAME:

-Ace Driver
-Ace Driver: Victory Lap
-Alien 3
-Afterburner II
-Beast Busters
-California Speed
-Chase Bombers
-Cisco Heat
-Cruisn'USA
-Cruisn' World
-Daytona USA
-F-1 Grand Prix Star
-F-1 Grand Prix Star II
-Ghoul Panic
-Gun Buster
-Hard Drivin'
-Hyperdrive
-Laser Ghost
-Outrun
-Mechanized Attack
-OffRoad Challenge
-Operation Thunderbolt
-Operation Wolf
-Outrunners
-Point Blank 2
-Power Drift
-Race Drivin'
-Rail Chase
-Rave Racer (TURN ON FEEDBACK STEERING IN GAME SETTINGS OR YOU WILL NOT RECIEVE FORCE FEEDBACK)
-Revolution X
-San Francisco Rush
-San Francisco Rush The Rock
-San Francisco Rush 2049
-Sega Rally Championship
-Sega Touring Car Championship
-Super Chase - Criminal Termination
-Super GT 24h
-Space gun
-Terminator 2
-Turbo Outrun
-Turkey Shoot
-Under Fire
-Vapor TRX
-Virtua Racing (CHANGE TO UPRIGHT CABINET)


MODEL 2 EMULATOR:

-Daytona USA
-Indy 500
-Over Rev
-Sega Rally Championship
-Sega Touring Car Championship
-Super GT 24h


SUPERMODEL3:

-Daytona USA 2 - Power Edition
-Daytona USA 2 - Battle on the Edge
-Dirt Devils
-Emergency Call Ambulance
-LeMans 24
-Scud Race
-Scud Race Plus
-Sega Rally 2


DEMUL:

-ATV Track
-Initial D Arcade Stage
-Initial D Arcade Stage 2
-Initial D Arcade Stage 3
-Faster Than Speed
-Maximum Speed
-Smashing Drive
-Nascar Racing


FLYCAST:

-18 Wheeler
-Club Kart
-F355 Challenge
-F355 Challenge 2
-Faster Than Speed
-Initial D Arcade Stage
-Initial D Arcade Stage 2
-Initial D Arcade Stage 3
-King Of Route 66
-Maximum Speed
-Sega Driving Simulator



PC STEAM:

-Crazy Taxi (Steam)


TEKNOPARROT:

-Alien Extermination
-Afterburner Climax
-Batman (2013)
-Battle Gear 4 Tuned (Japan version v2.07)
-ChaseHQ 2
-Cruisn' Blast
-Daytona Championship USA
-Daytona Championship USA New Season Edition
-Dead Heat
-Dead Heat Riders
-Dirty Drivin
-Ford Racing
-FNF
-FNF Drift
-FNF Supercars
-Gaelco Tuning Race
-Golden Gun
-GRID
-GTI Club Supermini Festa
-House of the dead 4
-Hummer Extreme
-Initial D Arcade Stage 4
-Initial D Arcade Stage 4 Japan
-Initial D Arcade Stage 5
-Initial D Arcade Stage 6
-Initial D Arcade Stage 7
-Initial D Arcade Stage 8
-Initial D Arcade Stage Zero
-Initial D Arcade The Arcade v2.31
-KO Drive
-Let's Go Island
-Let's Go Island 3D
-Machstorm
-Mario Kart GP DX
-Outrun 2 Special Tours Deluxe
-Pokken Tournament
-Ring Riders
-Rambo
-Road Fighters 3D
-R-Tuned : Ultimate Street Racing
-Sega Racing Classic
-Sega Rally 3
-Sega World Drivers Championship 2018
-Showdown
-SnoCross
-Sonic & Sega All Stars Racing
-Storm Racer G
-Tokyo Cop
-Transformers: Human Alliance
-Wacky Races
-Wasteland Racers 2071
-Wangan Midnight Maximum Tune 3
-Wangan Midnight Maximum Tune 3DX+
-Wangan Midnight Maximum Tune 5
-Wangan Midnight Maximum Tune 5DX
-Wangan Midnight Maximum Tune 5DX+
-Wangan Midnight Maximum Tune 6
-Wangan Midnight Maximum Tune 6R