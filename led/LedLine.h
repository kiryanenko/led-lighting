//
// Created by kiryanenko on 21.09.19.
//

#ifndef LED_LIGHTING_LEDLINE_H
#define LED_LIGHTING_LEDLINE_H


#include "../Settings.h"


struct DHSV {
    double hue = 0;
    double saturation = 255;
    double value = 255;

    DHSV() = default;
    DHSV(const CHSV& hsv) : hue(hsv.hue), saturation(hsv.saturation), value(hsv.value) {}

    operator CHSV() const {
        return CHSV(hue, saturation, value);
    }
};


class LedLine {
    CRGB *_leds;
    int _leds_cnt;
    LedLineSettings _settings;  // Выставленные настройки
    DHSV _color;                // Текущий цвет

    GTimer_ms _frame_timer;
    GTimer_ms _timer;
    CHSV _dst;
    DHSV _delta;

public:
    LedLine(CRGB *leds, int cnt) : _leds(leds), _leds_cnt(cnt), _frame_timer(FRAME_TIME) {}
    void update(const LedLineSettings &settings);

private:
    void setSolidColor(const DHSV& color);
};


CHSV randomHSV(uint8_t brightness) {
    return CHSV(random8(), random8(), brightness);
}

#endif //LED_LIGHTING_LEDLINE_H
