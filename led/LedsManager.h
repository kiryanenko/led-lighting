//
// Created by kiryanenko on 21.09.19.
//

#ifndef LED_LIGHTING_LEDSMANAGER_H
#define LED_LIGHTING_LEDSMANAGER_H

#include "../Settings.h"

class LedsManager {
private:
    CRGB _leds[LEDS_CNT];

public:
    LedsManager();
    void tick();
};


#endif //LED_LIGHTING_LEDSMANAGER_H
