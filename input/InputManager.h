//
// Created by kiryanenko on 21.09.19.
//

#ifndef LED_LIGHTING_INPUTMANAGER_H
#define LED_LIGHTING_INPUTMANAGER_H

#include "../Settings.h"

class InputManager {
    SimpleTimer _sleep_timer;
    SimpleTimer _printTimer;

public:
    InputManager();
    void tick();
    void inputDetected();

    bool isMode(Mode mode);
    void nextMode();
    ModeSettings getModeSettings();
    void setModeSettings(const ModeSettings & modeSettings);

    void printSettings();
};


#endif //LED_LIGHTING_INPUTMANAGER_H
