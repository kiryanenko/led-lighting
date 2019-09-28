//
// Created by kiryanenko on 21.09.19.
//

#ifndef LED_LIGHTING_INPUTMANAGER_H
#define LED_LIGHTING_INPUTMANAGER_H

#include "../Settings.h"

class InputManager {
    GTimer_ms _sleep_timer;
public:
    InputManager();
    void tick();
    void inputDetected();
    void nextMode();
    CHSV getColor();
    void setColor(const CHSV& color);
};


#endif //LED_LIGHTING_INPUTMANAGER_H
