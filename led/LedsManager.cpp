//
// Created by kiryanenko on 21.09.19.
//

#include "LedsManager.h"

LedsManager::LedsManager() {
    CFastLED::addLeds<WS2811, LEDS_PIN, GRB>(_leds, LEDS_CNT);
}

void LedsManager::tick() {
    auto mode_id = settings->getCurrentMode();
    auto mode = settings->getMode(mode_id);
    switch (mode_id) {
        case COLOR:
            for (auto & _led : _leds) {
                _led = mode.color;
            }
            FastLED.show();
            break;
        case RANDOM_COLOR:
            for (auto & _led : _leds) {
                _led = mode.color;
            }
            FastLED.show();
            break;
    }
}
