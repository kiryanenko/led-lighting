//
// Created by kiryanenko on 21.09.19.
//

#ifndef LED_LIGHTING_LEDLINE_H
#define LED_LIGHTING_LEDLINE_H


#include "../Settings.h"
#include "../utils.h"


struct DRGB;
struct DHSV;

struct DRGB {
    double red = 0;
    double green = 100;
    double blue = 100;

    DRGB() = default;
    DRGB(const CRGB& rgb) : red(rgb.red), green(rgb.green), blue(rgb.blue) {}

    operator CRGB() const {
        return CRGB(cleanColorPart(red), cleanColorPart(green), cleanColorPart(blue));
    }

    inline void clean() {
        red = cleanColorPart(red);
        green = cleanColorPart(green);
        blue = cleanColorPart(blue);
    }
};


struct DHSV {
    double hue = 0;
    double saturation = 255;
    double value = 255;

    DHSV() = default;
    DHSV(const CHSV& hsv) : hue(hsv.hue), saturation(hsv.saturation), value(hsv.value) {}

    operator CHSV() const {
        return CHSV(cleanColorPart(hue), cleanColorPart(saturation), cleanColorPart(value));
    }

    inline void clean() {
        hue = cleanColorPart(hue);
        saturation = cleanColorPart(saturation);
        value = cleanColorPart(value);
    }

    CRGB rgb() {
        return CRGB(*this);
    }
};


class LedLine {
    CRGB *_leds;
    int _leds_cnt;
    LedLineSettings _settings;  // Выставленные настройки
    // Текущий цвет
    DHSV _color_hsv;
    DRGB _color_rgb;

    SimpleTimer _frame_timer;
    SimpleTimer _timer;
    CHSV _dst;
    DRGB _delta;

public:
    LedLine(CRGB *leds, int cnt) : _leds(leds), _leds_cnt(cnt), _frame_timer(FRAME_TIME) {}
    void update(const LedLineSettings &settings);

private:
    void setSolidColor(const DHSV& color);
    void setSolidColor(const DRGB& color);
};


#endif //LED_LIGHTING_LEDLINE_H
