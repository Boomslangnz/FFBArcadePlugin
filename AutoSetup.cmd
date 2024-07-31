@echo off
set /p Build=<Version.txt
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\Button Rumble 64bit" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\Button Rumble 64bit" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\Initial D Zero v131" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\Initial D Zero v131" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\Initial D Zero v211" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\Initial D Zero v211" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\Initial D Zero v230" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\Initial D Zero v230" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\Initial D The Arcade v231" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\Initial D The Arcade v231" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\Sega World Drivers Championship 2018" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\Sega World Drivers Championship 2018" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\MAME 64bit Outputs" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\MAME 64bit Outputs" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\PokkenTournament" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\PokkenTournament" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\Supermodel 64bit Outputs" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\Supermodel 64bit Outputs" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\Spring Effect 64bit" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\Spring Effect 64bit" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\Flycast" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\Flycast" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\WMMT5" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\WMMT5" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\WMMT5DX" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\WMMT5DX" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\WMMT5DX+" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\WMMT5DX+" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\WMMT6" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\WMMT6" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\WMMT6R" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\WMMT6R" /Y
xcopy ".\Release.x64\dinput8.dll" ".\Release.Win32\WMMT6RR" /Y
xcopy ".\Release.x64\SDL2.dll" ".\Release.Win32\WMMT6RR" /Y
xcopy ".\MAME32.dll" ".\Release.Win32\MAME 32bit Outputs" /Y
xcopy ".\MAME64.dll" ".\Release.Win32\MAME 64bit Outputs" /Y
xcopy ".\MAME32.dll" ".\Release.Win32\Supermodel 32bit Outputs" /Y
xcopy ".\MAME64.dll" ".\Release.Win32\Supermodel 64bit Outputs" /Y
xcopy ".\MAME64.dll" ".\Release.Win32\Flycast" /Y
cd Release.Win32
cd Afterburner Climax
rename dinput8.dll opengl32.dll
cd..
cd Aliens Extermination
rename dinput8.dll opengl32.dll
cd..
cd Arctic Thunder
rename dinput8.dll d3d9.dll
cd..
cd Batman
rename dinput8.dll d3d11.dll
cd..
cd Battle Gear 4 Tuned
rename dinput8.dll d3d9.dll
cd..
cd Cruisn Blast
rename dinput8.dll winmm.dll
cd..
cd Crazy Taxi Steam
rename dinput8.dll xinput1_3.dll
cd..
cd Chase HQ 2
rename dinput8.dll d3d9.dll
cd..
cd Dead Heat
rename dinput8.dll opengl32.dll
cd..
cd Dead Heat Riders
rename dinput8.dll opengl32.dll
cd..
cd Gaelco Tuning Race
rename dinput8.dll opengl32.dll
cd..
cd Tokyo Cop
rename dinput8.dll opengl32.dll
cd..
cd Ring Riders
rename dinput8.dll opengl32.dll
cd..
cd D1GP Arcade
rename dinput8.dll winmm.dll
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
cd Hummer Extreme
rename dinput8.dll winmm.dll
cd..
cd HOTD4
rename dinput8.dll opengl32.dll
cd..
cd Flycast
rename dinput8.dll winmm.dll
cd..
cd Initial D 4
rename dinput8.dll opengl32.dll
cd..
cd Initial D 4 Japan
rename dinput8.dll opengl32.dll
cd..
cd Initial D 5
rename dinput8.dll opengl32.dll
cd..
cd Initial D The Arcade v231
rename dinput8.dll d3d11.dll
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
cd "Sega Race TV"
rename dinput8.dll opengl32.dll
cd..
cd "Sega World Drivers Championship 2018"
rename dinput8.dll d3d11.dll
cd..
cd "Sonic & Sega All Stars Racing"
rename dinput8.dll d3d9.dll
cd..
cd "Storm Racer G"
rename dinput8.dll xinput1_3.dll
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
cd WMMT3
rename dinput8.dll opengl32.dll
cd..
cd WMMT3DX+
rename dinput8.dll opengl32.dll
cd..
cd WMMT5
rename dinput8.dll d3d11.dll
cd..
cd WMMT5DX
rename dinput8.dll d3d11.dll
cd..
cd WMMT5DX+
rename dinput8.dll d3d11.dll
cd..
cd WMMT6
rename dinput8.dll d3d11.dll
cd..
cd WMMT6R
rename dinput8.dll d3d11.dll
cd..
cd WMMT6RR
rename dinput8.dll d3d11.dll
cd..
del dinput8.exp
del dinput8.lib
del SDL2.dll
rd /s /q ".\DInput8Wrapper\"
"C:\Program Files\7-Zip\7z.exe" a ".\FFB Arcade Plugin %Build%.zip" ".\*"
move ".\FFB Arcade Plugin %Build%.zip" "..\"
"C:\Program Files\7-Zip\7z.exe" a ".\FFB Arcade Plugin %Build%.7z" ".\*"
move ".\FFB Arcade Plugin %Build%.7z" "..\"
EXIT

