//
// Created by kiryanenko on 28.09.19.
//

#ifndef LED_LIGHTING_ENCODERHANDLER_H
#define LED_LIGHTING_ENCODERHANDLER_H

#include <GyverEncoder.h>
#include "InputManager.h"

class EncoderHandler {
    bool _is_brightness_setting = true;
    bool _is_speed_setting = true;
public:
    void handle(InputManager &manager, Encoder &encoder);

private:
    void setColor(InputManager &manager, Encoder &encoder);
    void setBrightness(InputManager &manager, Encoder &encoder);
    void setSaturation(InputManager &manager, Encoder &encoder);
    void setSpeed(InputManager &manager, Encoder &encoder);
    void setDuration(InputManager &manager, Encoder &encoder);

    inline bool isTurnRight(Encoder &encoder);
    inline bool isTurnLeft(Encoder &encoder);
};


#endif //LED_LIGHTING_ENCODERHANDLER_H
