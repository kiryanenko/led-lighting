//
// Created by kiryanenko on 21.09.19.
//

#include <Arduino.h>
#include "LedLine.h"
#include "../utils.h"

void LedLine::update(const LedLineSettings &lineSettings) {
    switch (lineSettings.mode) {
        case LINE_COLOR:
            setSolidColor(_settings.settings.color);
            break;

        case LINE_RANDOM_COLOR:
            if (_settings != lineSettings || _timer.isReady()) {
                _timer.reset();
                _dst = randomHSV(lineSettings.settings.brightness);

                auto duration = constrain(lineSettings.settings.duration, 1000, 1800000);
                _timer.setInterval(lineSettings.settings.duration);

                auto transition_time = constrain(lineSettings.settings.speed, FRAME_TIME, duration);
                _delta.hue = (float(_dst.hue) - _color.hue) / transition_time * FRAME_TIME;
                _delta.saturation = (float(_dst.saturation) - _color.saturation) / transition_time * FRAME_TIME;
            }

            if (_frame_timer.isReady()) {
                _frame_timer.reset();
                if (_delta.hue > 0) _color.hue = constrain(_color.hue + _delta.hue, _color.hue, _dst.hue);
                else _color.hue = constrain(_color.hue + _delta.hue, _dst.hue, _color.hue);
                if (_delta.saturation > 0) _color.saturation = constrain(_color.saturation + _delta.saturation, _color.saturation, _dst.saturation);
                else _color.saturation = constrain(_color.saturation + _delta.saturation, _dst.saturation, _color.saturation);
                _color.value = lineSettings.settings.brightness;
                setSolidColor(_color);
            }
            break;
    }

    _settings = lineSettings;
}

void LedLine::setSolidColor(const DHSV& color) {
    _color = color;
    _color.clean();
    for (int i = 0; i < _leds_cnt; ++i) {
        _leds[i] = _color;
    }
}
