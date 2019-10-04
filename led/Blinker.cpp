//
// Created by kiryanenko on 04.10.19.
//

#include "Blinker.h"

Blinker::Blinker(uint8_t pin) : _pin(pin), _timer(BLINK_PERIOD / 2) {
    pinMode(pin, OUTPUT);
}

void Blinker::blink(uint8_t cnt) {
    _blink_cnt = cnt;
    is_high = false;
    digitalWrite(_pin, LOW);
}

void Blinker::tick() {
    if (_blink_cnt > 0 && _timer.isReady()) {
        is_high = !is_high;
        digitalWrite(_pin, is_high);
        if (!is_high) {
            --_blink_cnt;
        }
    }
}
