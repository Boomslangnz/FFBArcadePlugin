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

#include "stdafx.h"
#include "MAMEModel2.h"

static wchar_t* settingsFilename = TEXT(".\\FFBPlugin.ini");
static wchar_t* globalSection = TEXT("Settings");

MAMEModel2::MAMEModel2()
{
    LoadConfiguration();
}

MAMEModel2::~MAMEModel2()
{
}

void MAMEModel2::LoadConfiguration()
{
    // Load global settings with game-specific overrides
    configMinForce = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinForceMAMEModel2"), 0, settingsFilename);
    configMaxForce = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxForceMAMEModel2"), 100, settingsFilename);
    configFeedbackLength = GetPrivateProfileInt(TEXT("Settings"), TEXT("FeedbackLengthMAMEModel2"), 120, settingsFilename);
    configEnableDamper = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableDamperMAMEModel2"), 0, settingsFilename);
    configDamperStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("DamperStrengthMAMEModel2"), 100, settingsFilename);
    configEnableSpring = GetPrivateProfileInt(TEXT("Settings"), TEXT("EnableForceSpringEffectMAMEModel2"), 0, settingsFilename);
    configSpringStrength = GetPrivateProfileInt(TEXT("Settings"), TEXT("ForceSpringStrengthMAMEModel2"), 0, settingsFilename);
}

std::string MAMEModel2::GetGameFromWindowTitle()
{
    // MAME window titles typically follow pattern: "romname: Game Title [mame]" or just "Game Title"
    // Examples:
    // "Daytona USA (Deluxe) (Rev A) [daytona]"
    // "daytona - MAME"

    char windowTitle[256];
    if (GetWindowTextA(hWndMAME, windowTitle, sizeof(windowTitle)) == 0)
    {
        return "";
    }

    std::string title(windowTitle);

    // Look for ROM name in brackets [romname]
    size_t bracketStart = title.find('[');
    size_t bracketEnd = title.find(']');
    if (bracketStart != std::string::npos && bracketEnd != std::string::npos && bracketEnd > bracketStart)
    {
        return title.substr(bracketStart + 1, bracketEnd - bracketStart - 1);
    }

    // Alternative: look for "romname - MAME" format
    size_t dashPos = title.find(" - ");
    if (dashPos != std::string::npos)
    {
        std::string romName = title.substr(0, dashPos);
        // Convert to lowercase for consistency
        for (char& c : romName)
        {
            c = tolower(c);
        }
        return romName;
    }

    return "";
}

void MAMEModel2::DetectGame(Helpers* helpers)
{
    // Try to find MAME window running Model 2 games
    if (hWndMAME == NULL)
    {
        // Try various MAME window title formats for Model 2 racing games

        // Daytona USA variants
        hWndMAME = FindWindowA(0, "daytona - MAME");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "Daytona USA (Deluxe) (Rev A) [daytona]");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "daytonas - MAME");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "Daytona USA (With Saturn Adverts) (Rev A) [daytonas]");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "daytonase - MAME");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "Daytona USA Special Edition (Japan, Revision A) [daytonase]");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "daytona93 - MAME");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "daytonat - MAME");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "Daytona USA (Turbo) [daytonat]");

        // Sega Rally variants
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "srallyc - MAME");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "Sega Rally Championship (Revision C) [srallyc]");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "srallycb - MAME");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "Sega Rally Championship (Revision B) [srallycb]");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "srallyp - MAME");

        // Indianapolis 500
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "indy500 - MAME");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "Indianapolis 500 (Revision A) [indy500]");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "indy500d - MAME");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "indy500to - MAME");

        // Over Rev
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "overrev - MAME");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "Over Rev (Revision C) [overrev]");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "overrevb - MAME");

        // Touring Car Championship
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "stcc - MAME");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "Sega Touring Car Championship (Revision A) [stcc]");
        if (hWndMAME == NULL)
            hWndMAME = FindWindowA(0, "stccb - MAME");

        if (hWndMAME != NULL)
        {
            currentGame = GetGameFromWindowTitle();
            gameRunning = true;
        }
    }

    // If we have the window but haven't found base address yet
    if (hWndMAME != NULL && gameBaseAddress == 0)
    {
        // TODO: Research and set the correct base address for MAME Model 2 emulation
        // This will need to be found through memory scanning/Cheat Engine
        // For now, we'll try to read from a placeholder address
        // gameBaseAddress = helpers->ReadIntPtr(0x????????, false);

        // Placeholder - mark as initialized but address unknown
        gameBaseAddress = 1; // Non-zero to indicate we've attempted detection
    }
}

void MAMEModel2::ProcessDaytonaFFB(Helpers* helpers, EffectTriggers* triggers, EffectConstants* constants)
{
    // TODO: Research correct memory addresses for MAME's Model 2 Daytona USA emulation
    // These addresses are PLACEHOLDERS and need to be found using Cheat Engine or similar tools
    //
    // To find these addresses:
    // 1. Attach Cheat Engine to mame64.exe/mame.exe
    // 2. Start Daytona USA
    // 3. Search for changing byte values (0-255) while steering
    // 4. Look for values that correlate with force feedback intensity
    // 5. Look for patterns similar to M2Emulator (ranges like 0x09-0x18, 0x4F-0x68)

    UINT8 ffbValue = 0x00;

    // Example placeholder - replace with actual researched address
    // if (ffbDataAddress != 0)
    // {
    //     ffbValue = helpers->ReadByte(ffbDataAddress, false);
    // }

    // FFB interpretation based on Model 2 hardware FFB protocol
    // (These ranges are based on M2Emulator implementation)

    double percentForce = 0.0;
    double percentLength = configFeedbackLength / 100.0;

    // Spring effect (centering force)
    // Byte range: 0x09 - 0x18
    if ((ffbValue > 0x09) && (ffbValue < 0x18))
    {
        percentForce = (ffbValue - 15.0) / 8.0;
        percentForce = percentForce * (configMaxForce / 100.0);

        if (percentForce > (configMinForce / 100.0))
        {
            triggers->Spring(percentForce);
        }
    }

    // Friction/Clutch effect
    // Byte range: 0x1F - 0x28
    if ((ffbValue > 0x1F) && (ffbValue < 0x28))
    {
        percentForce = (ffbValue - 39.0) / 8.0;
        percentForce = percentForce * (configMaxForce / 100.0);

        if (percentForce > (configMinForce / 100.0))
        {
            triggers->Friction(percentForce);
        }
    }

    // Centering effect (stronger spring)
    // Byte range: 0x2F - 0x38
    if ((ffbValue > 0x2F) && (ffbValue < 0x38))
    {
        percentForce = (ffbValue - 55.0) / 8.0;
        percentForce = percentForce * (configMaxForce / 100.0);

        if (percentForce > (configMinForce / 100.0))
        {
            triggers->Spring(percentForce);
        }
    }

    // Uncentering effect (sine wave)
    // Byte range: 0x3F - 0x48
    if ((ffbValue > 0x3F) && (ffbValue < 0x48))
    {
        percentForce = (ffbValue - 63.0) / 8.0;
        percentForce = percentForce * (configMaxForce / 100.0);

        if (percentForce > (configMinForce / 100.0))
        {
            triggers->Sine(80, 80, percentForce);
            triggers->Rumble(percentForce, 0, percentLength);
        }
    }

    // Roll Left (car rolling/rumble strip left side)
    // Byte range: 0x4F - 0x58
    if ((ffbValue > 0x4F) && (ffbValue < 0x58))
    {
        percentForce = (ffbValue - 79.0) / 8.0;
        percentForce = percentForce * (configMaxForce / 100.0);

        if (percentForce > (configMinForce / 100.0))
        {
            triggers->Rumble(0, percentForce, percentLength);
            triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
        }
    }

    // Roll Right (car rolling/rumble strip right side)
    // Byte range: 0x5F - 0x68
    if ((ffbValue > 0x5F) && (ffbValue < 0x68))
    {
        percentForce = (ffbValue - 95.0) / 8.0;
        percentForce = percentForce * (configMaxForce / 100.0);

        if (percentForce > (configMinForce / 100.0))
        {
            triggers->Rumble(0, percentForce, percentLength);
            triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
        }
    }

    // Optional: Force spring effect (if enabled in config)
    if (configEnableSpring && ffbValue == 0x00)
    {
        triggers->Spring(configSpringStrength / 100.0);
    }

    // Optional: Damper effect (if enabled in config)
    if (configEnableDamper)
    {
        triggers->Damper(configDamperStrength / 100.0);
    }
}

void MAMEModel2::ProcessSegaRallyFFB(Helpers* helpers, EffectTriggers* triggers, EffectConstants* constants)
{
    // TODO: Research correct memory addresses for MAME's Model 2 Sega Rally emulation
    // Similar structure to Daytona but may have different address offsets

    UINT8 ffbValue = 0x00;

    // Placeholder for FFB data reading
    // if (ffbDataAddress != 0)
    // {
    //     ffbValue = helpers->ReadByte(ffbDataAddress, false);
    // }

    double percentForce = 0.0;
    double percentLength = configFeedbackLength / 100.0;

    // Sega Rally FFB interpretation (similar to Daytona)
    // These ranges may differ - need to research

    // Spring effect
    if ((ffbValue > 0x09) && (ffbValue < 0x18))
    {
        percentForce = (ffbValue - 15.0) / 8.0;
        percentForce = percentForce * (configMaxForce / 100.0);

        if (percentForce > (configMinForce / 100.0))
        {
            triggers->Spring(percentForce);
        }
    }

    // Friction
    if ((ffbValue > 0x1F) && (ffbValue < 0x28))
    {
        percentForce = (ffbValue - 39.0) / 8.0;
        percentForce = percentForce * (configMaxForce / 100.0);

        if (percentForce > (configMinForce / 100.0))
        {
            triggers->Friction(percentForce);
        }
    }

    // Surface effects (gravel, tarmac differences)
    if ((ffbValue > 0x4F) && (ffbValue < 0x58))
    {
        percentForce = (ffbValue - 79.0) / 8.0;
        percentForce = percentForce * (configMaxForce / 100.0);

        if (percentForce > (configMinForce / 100.0))
        {
            triggers->Rumble(percentForce, percentForce * 0.8, percentLength);
            triggers->Constant(constants->DIRECTION_FROM_RIGHT, percentForce);
        }
    }

    if ((ffbValue > 0x5F) && (ffbValue < 0x68))
    {
        percentForce = (ffbValue - 95.0) / 8.0;
        percentForce = percentForce * (configMaxForce / 100.0);

        if (percentForce > (configMinForce / 100.0))
        {
            triggers->Rumble(percentForce, percentForce * 0.8, percentLength);
            triggers->Constant(constants->DIRECTION_FROM_LEFT, percentForce);
        }
    }

    if (configEnableDamper)
    {
        triggers->Damper(configDamperStrength / 100.0);
    }
}

void MAMEModel2::ProcessIndy500FFB(Helpers* helpers, EffectTriggers* triggers, EffectConstants* constants)
{
    // TODO: Research correct memory addresses for MAME's Model 2 Indianapolis 500 emulation

    UINT8 ffbValue = 0x00;

    double percentForce = 0.0;
    double percentLength = configFeedbackLength / 100.0;

    // Indianapolis 500 FFB (oval racing - high speed effects)
    // Similar to Daytona but may emphasize high-speed stability

    if ((ffbValue > 0x09) && (ffbValue < 0x18))
    {
        percentForce = (ffbValue - 15.0) / 8.0;
        percentForce = percentForce * (configMaxForce / 100.0);

        if (percentForce > (configMinForce / 100.0))
        {
            triggers->Spring(percentForce);
        }
    }

    if (configEnableDamper)
    {
        triggers->Damper(configDamperStrength / 100.0);
    }
}

void MAMEModel2::ProcessOverRevFFB(Helpers* helpers, EffectTriggers* triggers, EffectConstants* constants)
{
    // TODO: Research correct memory addresses for MAME's Model 2 Over Rev emulation

    UINT8 ffbValue = 0x00;

    double percentForce = 0.0;
    double percentLength = configFeedbackLength / 100.0;

    // Over Rev FFB (similar to Daytona/rally games)

    if ((ffbValue > 0x09) && (ffbValue < 0x18))
    {
        percentForce = (ffbValue - 15.0) / 8.0;
        percentForce = percentForce * (configMaxForce / 100.0);

        if (percentForce > (configMinForce / 100.0))
        {
            triggers->Spring(percentForce);
        }
    }

    if (configEnableDamper)
    {
        triggers->Damper(configDamperStrength / 100.0);
    }
}

void MAMEModel2::ProcessTouringCarFFB(Helpers* helpers, EffectTriggers* triggers, EffectConstants* constants)
{
    // TODO: Research correct memory addresses for MAME's Model 2 Touring Car Championship emulation

    UINT8 ffbValue = 0x00;

    double percentForce = 0.0;
    double percentLength = configFeedbackLength / 100.0;

    // Touring Car Championship FFB (circuit racing)

    if ((ffbValue > 0x09) && (ffbValue < 0x18))
    {
        percentForce = (ffbValue - 15.0) / 8.0;
        percentForce = percentForce * (configMaxForce / 100.0);

        if (percentForce > (configMinForce / 100.0))
        {
            triggers->Spring(percentForce);
        }
    }

    if (configEnableDamper)
    {
        triggers->Damper(configDamperStrength / 100.0);
    }
}

void MAMEModel2::FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers)
{
    // Detect game if not already running
    if (!gameRunning)
    {
        DetectGame(helpers);
        return;
    }

    // Route to game-specific FFB processing based on detected ROM name
    if (currentGame.find("daytona") != std::string::npos)
    {
        ProcessDaytonaFFB(helpers, triggers, constants);
    }
    else if (currentGame.find("srally") != std::string::npos)
    {
        ProcessSegaRallyFFB(helpers, triggers, constants);
    }
    else if (currentGame.find("indy500") != std::string::npos)
    {
        ProcessIndy500FFB(helpers, triggers, constants);
    }
    else if (currentGame.find("overrev") != std::string::npos)
    {
        ProcessOverRevFFB(helpers, triggers, constants);
    }
    else if (currentGame.find("stcc") != std::string::npos || currentGame.find("touring") != std::string::npos)
    {
        ProcessTouringCarFFB(helpers, triggers, constants);
    }
    else
    {
        // Unknown Model 2 game - apply basic centering
        if (configEnableSpring)
        {
            triggers->Spring(configSpringStrength / 100.0);
        }
    }
}
