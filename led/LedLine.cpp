//
// Created by kiryanenko on 21.09.19.
//

#include "LedLine.h"

void LedLine::update(const LedLineSettings &lineSettings) {
    switch (lineSettings.mode) {
        case LINE_COLOR:
            for (int i = 0; i < _leds_cnt; ++i) {
                _leds[i] = _settings.settings.color;
            }
            break;
        case LINE_RANDOM_COLOR:
            if (_settings.mode != LINE_RANDOM_COLOR || _timer.isReady()) {
                auto src = _dst;
                if (_settings.mode != LINE_RANDOM_COLOR) {
                    src = randomHSV(lineSettings.settings.brightness);
                }
                _dst = randomHSV(lineSettings.settings.brightness);
                auto duration = 60000 * lineSettings.settings.duration;
                _timer.setInterval(duration);
                auto transition_time = duration / lineSettings.settings.speed;
                _hue_delta = (_dst.hue - src.hue) / transition_time;
                _saturation_delta = (_dst.saturation - src.saturation) / transition_time;
            }
            for (int i = 0; i < _leds_cnt; ++i) {
                _leds[i] = _settings.settings.color;
            }
            break;
    }
    _settings = lineSettings;
}
