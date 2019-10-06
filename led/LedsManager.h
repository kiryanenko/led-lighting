//
// Created by kiryanenko on 21.09.19.
//

#ifndef LED_LIGHTING_LEDSMANAGER_H
#define LED_LIGHTING_LEDSMANAGER_H

#include "LedLine.h"

class LedsManager {
    CRGB _leds[LEDS_CNT];
    LedLine _all_leds;
    SimpleTimer _frame_timer;

public:
    LedsManager();
    void tick();
};


#endif //LED_LIGHTING_LEDSMANAGER_H
