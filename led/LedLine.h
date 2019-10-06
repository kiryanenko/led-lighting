//
// Created by kiryanenko on 21.09.19.
//

#ifndef LED_LIGHTING_LEDLINE_H
#define LED_LIGHTING_LEDLINE_H


#include "../Settings.h"


struct DRGB {
    double red = 0;
    double green = 100;
    double blue = 100;

    DRGB() = default;
    DRGB(const CRGB& rgb) : red(rgb.red), green(rgb.green), blue(rgb.blue) {}

    operator CRGB() const {
        return CRGB(red, green, blue);
    }

    inline void clean() {
        red = clean(red);
        green = clean(green);
        blue = clean(blue);
    }

    static inline double clean(double value) {
        long intPart = value;
        double floatPart = value - intPart;
        double res = abs(intPart) % 256 + abs(floatPart);
        return value > 0 ? res : 256 - res;
    }
};


struct DHSV {
    double hue = 0;
    double saturation = 255;
    double value = 255;

    DHSV() = default;
    DHSV(const CHSV& hsv) : hue(hsv.hue), saturation(hsv.saturation), value(hsv.value) {}

    operator CHSV() const {
        return CHSV(hue, saturation, value);
    }

    inline void clean() {
        hue = clean(hue);
        saturation = clean(saturation);
        value = clean(value);
    }

    static inline double clean(double value) {
        long intPart = value;
        double floatPart = value - intPart;
        double res = abs(intPart) % 256 + abs(floatPart);
        return value > 0 ? res : 256 - res;
    }
};


class LedLine {
    CRGB *_leds;
    int _leds_cnt;
    LedLineSettings _settings;  // Выставленные настройки
    DHSV _color;                // Текущий цвет

    SimpleTimer _frame_timer;
    SimpleTimer _timer;
    CHSV _dst;
    DHSV _delta;

public:
    LedLine(CRGB *leds, int cnt) : _leds(leds), _leds_cnt(cnt), _frame_timer(FRAME_TIME) {}
    void update(const LedLineSettings &settings);

private:
    void setSolidColor(const DHSV& color);
};


#endif //LED_LIGHTING_LEDLINE_H
