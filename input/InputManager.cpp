//
// Created by kiryanenko on 21.09.19.
//

#include "InputManager.h"

InputManager::InputManager() : _sleep_timer(SLEEP_TIMEOUT), _printTimer(SAVE_TIMEOUT) {

}

void InputManager::tick() {

}

void InputManager::inputDetected() {
    _sleep_timer.reset();
    blinker.blink();
}

void InputManager::nextMode() {
    inputDetected();

    auto nextMode = settings->getCurrentMode() + 1;
    settings->setCurrentMode(settings->getCurrentMode() + 1);
    printSettings();
}

bool InputManager::isMode(Mode mode) {
    return settings->getCurrentMode() == mode;
}

ModeSettings InputManager::getModeSettings() {
    auto mode_id = settings->getCurrentMode();
    return settings->getMode(mode_id);
}

void InputManager::setModeSettings(const ModeSettings &modeSettings) {
    inputDetected();
    auto mode_id = settings->getCurrentMode();
    settings->setMode(mode_id, modeSettings);

    if (_printTimer.isReady()){
        _printTimer.reset();
        printSettings();
    }
}

void InputManager::printSettings() {
    auto modeId = settings->getCurrentMode();
    auto modeSettings = settings->getMode(modeId);

    Serial.print("Mode "); Serial.println(modeId);
    Serial.println("====================");

    CRGB rgb = modeSettings.color;
    Serial.print('#'); Serial.print(rgb.red); Serial.print(rgb.green); Serial.print(rgb.blue);
    Serial.print(" Brightness "); Serial.print(modeSettings.color.value);
    Serial.print(" Saturation "); Serial.println(modeSettings.color.saturation);

    Serial.print("Speed "); Serial.print(modeSettings.speed);
    Serial.print(" Duration "); Serial.println(modeSettings.duration);
    Serial.println("--------------------");

}
