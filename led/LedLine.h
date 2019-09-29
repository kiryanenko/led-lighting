//
// Created by kiryanenko on 21.09.19.
//

#ifndef LED_LIGHTING_LEDLINE_H
#define LED_LIGHTING_LEDLINE_H


#include "../Settings.h"

class LedLine {
    CRGB *_leds;
    int _leds_cnt;
    LedLineSettings _settings;

public:
    LedLine(CRGB *leds, int cnt) : _leds(leds), _leds_cnt(cnt) {}
    void tick();
};


#endif //LED_LIGHTING_LEDLINE_H
