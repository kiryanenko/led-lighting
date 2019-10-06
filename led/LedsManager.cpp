//
// Created by kiryanenko on 21.09.19.
//

#include "LedsManager.h"

LedsManager::LedsManager() : _all_leds(_leds, LEDS_CNT), _frame_timer(FRAME_TIME) {
    CFastLED::addLeds<WS2811, LEDS_PIN, GRB>(_leds, LEDS_CNT);

    auto mode_id = settings->getCurrentMode();
    LedLineSettings lineSettings;
    lineSettings.mode = (LedLineMode) mode_id;
    lineSettings.settings = settings->getMode(mode_id);
    _all_leds.update(lineSettings, true);
    FastLED.show();
}

void LedsManager::tick() {
    if (_frame_timer.isReady()) {
        _frame_timer.reset();

        auto mode_id = settings->getCurrentMode();
        LedLineSettings lineSettings;
        lineSettings.mode = (LedLineMode) mode_id;
        lineSettings.settings = settings->getMode(mode_id);
        if (_all_leds.update(lineSettings)) {
            FastLED.show();
        }
    }
}
