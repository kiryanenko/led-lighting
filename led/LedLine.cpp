//
// Created by kiryanenko on 21.09.19.
//

#include "LedLine.h"

void LedLine::tick() {
    switch (mode_id) {
        case LINE_COLOR:
            for (int i = 0; i < _leds_cnt; ++i) {
                _led = mode.color;
            }
            FastLED.show();
            break;
        case LINE_RANDOM_COLOR:
            for (auto & _led : _leds) {
                _led = mode.color;
            }
            FastLED.show();
            break;
    }
}
