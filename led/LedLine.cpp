//
// Created by kiryanenko on 21.09.19.
//

#include <Arduino.h>
#include "LedLine.h"

bool LedLine::update(const LedLineSettings &lineSettings, bool forceUpdate) {
    bool shouldUpdate = false;
    switch (lineSettings.mode) {
        case LINE_COLOR:
            if (_settings != lineSettings || forceUpdate) {
                setSolidColor(_settings.settings.color);
                shouldUpdate = true;
            }
            break;

        case LINE_RANDOM_COLOR:
            if (_settings.mode == lineSettings.mode && _settings != lineSettings) {
                _color_hsv.value = lineSettings.settings.color.value;
                setSolidColor(_color_hsv);
                _dst = _color_hsv;
                setColorRandom(_dst, lineSettings);
                shouldUpdate = true;
            } else if (_settings.mode != lineSettings.mode || _timer.isReady()) {
                _timer.reset();
                _dst = randomHSV(lineSettings.settings.color.value);
                _color_hsv = _dst;
                setColorRandom(_dst, lineSettings);
            } else {
                CRGB dst = _dst;
                if (dst != _color_rgb) {
                    _color_rgb.red = lerp(_color_rgb.red, dst.r, _delta.red);
                    _color_rgb.green = lerp(_color_rgb.green, dst.g, _delta.green);
                    _color_rgb.blue = lerp(_color_rgb.blue, dst.b, _delta.blue);
                    setSolidColor(_color_rgb);
                    shouldUpdate = true;
                }
            }
            break;
    }

    _settings = lineSettings;
    return forceUpdate || shouldUpdate;
}

void LedLine::setSolidColor(const DHSV& color) {
    _color_hsv = color;
    _color_hsv.clean();
    setSolidColor(_color_hsv.rgb());
}

void LedLine::setSolidColor(const DRGB &color) {
    _color_rgb = color;
    _color_rgb.clean();
    for (int i = 0; i < _leds_cnt; ++i) {
        _leds[i] = _color_rgb;
    }
}

DRGB LedLine::setColorRandom(const CRGB& dst, const LedLineSettings &lineSettings) {
    uint64_t duration = constrain(lineSettings.settings.duration, COLOR_CHANGE_TIMES[0], COLOR_CHANGE_TIMES[COLOR_CHANGE_TIMES_CNT - 1]);
    _timer.setInterval(duration);

    uint64_t transition_time = constrain(lineSettings.settings.speed, TRANSITION_TIMES[0], duration);
    _delta.red = velocity(_color_rgb.red, dst.r, transition_time, FRAME_TIME);
    _delta.green = velocity(_color_rgb.green, dst.g, transition_time, FRAME_TIME);
    _delta.blue = velocity(_color_rgb.blue, dst.b, transition_time, FRAME_TIME);
}
