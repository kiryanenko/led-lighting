//
// Created by kiryanenko on 04.10.19.
//

#ifndef LED_LIGHTING_BLINKER_H
#define LED_LIGHTING_BLINKER_H

#include <Arduino.h>
#include <SimpleTimer.h>

#define BLINK_PERIOD 200

class Blinker {
    uint8_t _pin = LED_BUILTIN;
    SimpleTimer _timer;
    uint8_t _blink_cnt = 0;
    bool is_high = false;

public:
    Blinker(uint8_t pin = LED_BUILTIN);
    void blink(uint8_t cnt = 1);
    void tick();
};


#endif //LED_LIGHTING_BLINKER_H
