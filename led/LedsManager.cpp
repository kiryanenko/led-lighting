//
// Created by kiryanenko on 21.09.19.
//

#include "LedsManager.h"

LedsManager::LedsManager() : _all_leds(_leds, LEDS_CNT) {
    CFastLED::addLeds<WS2811, LEDS_PIN, GRB>(_leds, LEDS_CNT);
}

void LedsManager::tick() {
    auto mode_id = settings->getCurrentMode();
    LedLineSettings lineSettings;
    lineSettings.mode = (LedLineMode) mode_id;
    lineSettings.settings = settings->getMode(mode_id);
    _all_leds.update(lineSettings);
    FastLED.show();
}
