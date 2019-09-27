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

}

void InputManager::setColor(CRGB) {

}
