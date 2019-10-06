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
                _timer.reset();
                _dst = randomHSV(lineSettings.settings.brightness);

                auto duration = constrain(lineSettings.settings.duration, COLOR_CHANGE_TIMES[0], COLOR_CHANGE_TIMES[COLOR_CHANGE_TIMES_CNT - 1]);
                _timer.setInterval(lineSettings.settings.duration);

                uint64_t transition_time = constrain(lineSettings.settings.speed, FRAME_TIME, duration);
                CRGB dst = _dst;
                _delta.red = velocity(_color_rgb.red, dst.r, transition_time, FRAME_TIME);
                _delta.green = velocity(_color_rgb.green, dst.g, transition_time, FRAME_TIME);
                _delta.blue = velocity(_color_rgb.blue, dst.b, transition_time, FRAME_TIME);
                Serial.print("Color "); Serial.print(_color_rgb.red); Serial.print(' '); Serial.print(_color_rgb.green); Serial.print(' '); Serial.println(_color_rgb.blue);
                Serial.print("Dst "); Serial.print(dst.red); Serial.print(' '); Serial.print(dst.green); Serial.print(' '); Serial.println(dst.blue);
                Serial.print("Delta "); Serial.print(_delta.red); Serial.print(' '); Serial.print(_delta.green); Serial.print(' '); Serial.println(_delta.blue);
            }

            if (_frame_timer.isReady()) {
                _frame_timer.reset();
                CRGB dst = _dst;
                _color_rgb.red = lerp(_color_rgb.red, dst.r, _delta.red);
                _color_rgb.green = lerp(_color_rgb.green, dst.g, _delta.green);
                _color_rgb.blue = lerp(_color_rgb.blue, dst.b, _delta.blue);
                setSolidColor(_color_rgb);
            }
            break;
    }

    _settings = lineSettings;
}

void LedLine::setSolidColor(const DHSV& color) {
    _color_hsv = color;
    _color_hsv.clean();
    _color_rgb = _color_hsv.rgb();
    for (int i = 0; i < _leds_cnt; ++i) {
        _leds[i] = _color_rgb;
    }
}

void LedLine::setSolidColor(const DRGB &color) {
    _color_rgb = color;
    _color_rgb.clean();
    for (int i = 0; i < _leds_cnt; ++i) {
        _leds[i] = _color_rgb;
    }
}
