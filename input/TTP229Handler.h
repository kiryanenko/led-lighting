//
// Created by kiryanenko on 29.09.19.
//

#ifndef LED_LIGHTING_TTP229HANDLER_H
#define LED_LIGHTING_TTP229HANDLER_H

#include <TTP229.h>
#include "InputManager.h"

class TTP229Handler {
    GTimer_ms _press_timer;
    GTimer_ms _reset_timer;

public:
    TTP229Handler() : _press_timer(10), _reset_timer(3000) {}
    void handle(InputManager &manager, TTP229 &ttp229);
};


#endif //LED_LIGHTING_TTP229HANDLER_H
