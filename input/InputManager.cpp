//
// Created by kiryanenko on 21.09.19.
//

#include "InputManager.h"

InputManager::InputManager() : _sleep_timer(SLEEP_TIMEOUT) {

}

void InputManager::tick() {

}

void InputManager::inputDetected() {
    _sleep_timer.reset();
}

void InputManager::nextMode() {
    inputDetected();
    auto settings = Settings::getInstance();

    settings->setCurrentMode(settings->getCurrentMode() + 1);
}

void InputManager::setColor(const CHSV& color) {
    inputDetected();

    auto mode_id = settings->getCurrentMode();
    auto mode = settings->getMode(mode_id);
    mode.color = color;
    settings->setMode(mode_id, mode);
}

CHSV InputManager::getColor() {
    auto mode_id = settings->getCurrentMode();
    auto mode = settings->getMode(mode_id);
    return mode.color;
}
