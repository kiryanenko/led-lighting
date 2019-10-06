//
// Created by kiryanenko on 21.09.19.
//

#ifndef LED_LIGHTING_LEDLINE_H
#define LED_LIGHTING_LEDLINE_H


#include "../Settings.h"
#include "../utils.h"


class LedLine {
    CRGB *_leds;
    int _leds_cnt;
    LedLineSettings _settings;  // Выставленные настройки
    // Текущий цвет
    DHSV _color_hsv;
    DRGB _color_rgb;

    SimpleTimer _timer;
    CHSV _dst;
    DRGB _delta;

public:
    LedLine(CRGB *leds, int cnt) : _leds(leds), _leds_cnt(cnt) {}
    bool update(const LedLineSettings &lineSettings, bool forceUpdate = false);

private:
    void setSolidColor(const DHSV& color);
    void setSolidColor(const DRGB& color);

    DRGB setColorRandom(const CRGB& dst, const LedLineSettings &lineSettings);
};


#endif //LED_LIGHTING_LEDLINE_H
