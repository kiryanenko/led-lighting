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

    GTimer_ms _timer;
    CHSV _dst;
    int8_t _hue_delta;
    int8_t _saturation_delta;

public:
    LedLine(CRGB *leds, int cnt) : _leds(leds), _leds_cnt(cnt) {}
    void update(const LedLineSettings &settings);
};


CHSV randomHSV(uint8_t brightness) {
    return CHSV(random8(), random8(), brightness);
}

#endif //LED_LIGHTING_LEDLINE_H
