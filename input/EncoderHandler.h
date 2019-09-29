//
// Created by kiryanenko on 28.09.19.
//

#ifndef LED_LIGHTING_ENCODERHANDLER_H
#define LED_LIGHTING_ENCODERHANDLER_H

#include <GyverEncoder.h>
#include "InputManager.h"

class EncoderHandler {
    bool _is_brightness_setting = true;
public:
    void handle(InputManager &manager, Encoder &encoder);
};


#endif //LED_LIGHTING_ENCODERHANDLER_H
