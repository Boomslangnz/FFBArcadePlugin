@echo off
mkdir "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\Supermodel 32bit Outputs\ONLY COPY FILE INSIDE THIS FOLDER IF OLDER SUPERMODEL VERSION BEFORE r791"
mkdir "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\Supermodel 64bit Outputs\ONLY COPY FILE INSIDE THIS FOLDER IF OLDER SUPERMODEL VERSION BEFORE r791"
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.x64\dinput8.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\Button Rumble 64bit" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.x64\SDL2.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\Button Rumble 64bit" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.x64\dinput8.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\InitialD Zero" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.x64\SDL2.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\InitialD Zero" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.x64\dinput8.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\MAME 64bit Outputs" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.x64\SDL2.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\MAME 64bit Outputs" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.x64\dinput8.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\PokkenTournament" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.x64\SDL2.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\PokkenTournament" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.x64\dinput8.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\Supermodel 64bit Outputs" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.x64\SDL2.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\Supermodel 64bit Outputs" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.x64\dinput8.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\WMMT5" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.x64\SDL2.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\WMMT5" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\MAME32.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\MAME 32bit Outputs" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\MAME64.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\MAME 64bit Outputs" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\MAME32.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\Supermodel 32bit Outputs" /Y
xcopy "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\MAME64.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\Supermodel 64bit Outputs" /Y
cd Release.Win32
cd Afterburner Climax
rename dinput8.dll opengl32.dll
cd..
cd Aliens Extermination
rename dinput8.dll opengl32.dll
cd..
cd Batman
rename dinput8.dll d3d11.dll
cd..
cd Battle Gear 4 Tuned
rename dinput8.dll d3d9.dll
cd..
cd Chase HQ 2
rename dinput8.dll d3d9.dll
cd..
cd Demul
rename dinput8.dll winmm.dll
cd..
cd Dirty Drivin'
rename dinput8.dll d3d9.dll
cd..
cd H2Overdrive
rename dinput8.dll d3d9.dll
cd..
cd HOTD4
rename dinput8.dll opengl32.dll
cd..
cd InitialD 4
rename dinput8.dll opengl32.dll
cd..
cd InitialD 4 Japan
rename dinput8.dll opengl32.dll
cd..
cd InitialD 5
rename dinput8.dll opengl32.dll
cd..
cd KODrive
rename dinput8.dll d3d9.dll
cd..
cd LGI
rename dinput8.dll d3d9.dll
cd..
cd LGI3D
rename dinput8.dll d3d9.dll
cd..
cd Machstorm
rename dinput8.dll xinput1_3.dll
cd..
cd Outrun 2 Special Tours Deluxe Custom
rename dinput8.dll opengl32.dll
cd..
cd Outrun 2 Special Tours Deluxe Real
rename dinput8.dll opengl32.dll
cd..
cd Rambo
rename dinput8.dll opengl32.dll
cd..
cd R-Tuned
rename dinput8.dll opengl32.dll
cd..
cd "Sonic & Sega All Stars Racing"
rename dinput8.dll d3d9.dll
cd..
cd Supermodel 32bit Outputs
rename dinput8.dll opengl32.dll
cd..
cd Supermodel 64bit Outputs
rename dinput8.dll opengl32.dll
cd..
cd Wacky Races
rename dinput8.dll d3d9.dll
cd..
cd WMMT5
rename dinput8.dll d3d11.dll
cd..
del dinput8.exp
del dinput8.lib
del SDL2.dll
move "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\Supermodel 32bit Outputs\SDL2.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\Supermodel 32bit Outputs\ONLY COPY FILE INSIDE THIS FOLDER IF OLDER SUPERMODEL VERSION BEFORE r791"
move "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\Supermodel 64bit Outputs\SDL2.dll" "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\Supermodel 64bit Outputs\ONLY COPY FILE INSIDE THIS FOLDER IF OLDER SUPERMODEL VERSION BEFORE r791"
rd /s /q "C:\Users\booms\Documents\GitHub\FFBArcadePlugin\Release.Win32\DInput8Wrapper\"
EXIT

