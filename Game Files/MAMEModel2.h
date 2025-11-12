#pragma once
#include "../Common Files/Game.h"
#include <string>

class MAMEModel2 : public Game
{
private:
    // Game detection
    HWND hWndMAME = NULL;
    std::string currentGame = "";

    // Memory addresses (will vary per game - these need to be researched)
    INT_PTR gameBaseAddress = 0;
    INT_PTR ffbDataAddress = 0;

    // Configuration
    int configMinForce = 0;
    int configMaxForce = 100;
    int configFeedbackLength = 120;
    int configDamperStrength = 100;
    bool configEnableDamper = false;
    bool configEnableSpring = false;
    int configSpringStrength = 0;

    // Game state
    bool gameRunning = false;
    bool inMenu = false;

    // Helper methods
    void DetectGame(Helpers* helpers);
    void LoadConfiguration();
    std::string GetGameFromWindowTitle();
    void ProcessDaytonaFFB(Helpers* helpers, EffectTriggers* triggers, EffectConstants* constants);
    void ProcessSegaRallyFFB(Helpers* helpers, EffectTriggers* triggers, EffectConstants* constants);
    void ProcessIndy500FFB(Helpers* helpers, EffectTriggers* triggers, EffectConstants* constants);
    void ProcessOverRevFFB(Helpers* helpers, EffectTriggers* triggers, EffectConstants* constants);
    void ProcessTouringCarFFB(Helpers* helpers, EffectTriggers* triggers, EffectConstants* constants);

public:
    MAMEModel2();
    ~MAMEModel2();
    void FFBLoop(EffectConstants* constants, Helpers* helpers, EffectTriggers* triggers) override;
};
