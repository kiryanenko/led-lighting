//
// Created by kiryanenko on 21.09.19.
//

#include <Arduino.h>
#include "LedLine.h"

void LedLine::update(const LedLineSettings &lineSettings) {
    switch (lineSettings.mode) {
        case LINE_COLOR:
            setSolidColor(_settings.settings.color);
            break;

        case LINE_RANDOM_COLOR:
            if (_settings != lineSettings || _timer.isReady()) {
                _dst = randomHSV(lineSettings.settings.brightness);

                auto duration = constrain(lineSettings.settings.duration, 1000, 1800000);
                _timer.setInterval(lineSettings.settings.duration);

                auto speed = constrain(lineSettings.settings.speed, 0.0001, duration);
                auto transition_time = duration / speed;
                _delta.hue = (_dst.hue - _color.hue) / transition_time * FRAME_TIME;
                _delta.saturation = (_dst.saturation - _color.saturation) / transition_time * FRAME_TIME;
            }

            if (_frame_timer.isReady()) {
                _color.hue += _delta.hue;
                _color.saturation += _delta.saturation;
                _color.value = lineSettings.settings.brightness;
                setSolidColor(_color);
            }
            break;
    }

    _settings = lineSettings;
}

void LedLine::setSolidColor(const DHSV& color) {
    _color = color;
    for (int i = 0; i < _leds_cnt; ++i) {
        _leds[i] = _color;
    }
}
