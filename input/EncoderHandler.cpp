//
// Created by kiryanenko on 28.09.19.
//

#include <Arduino.h>
#include "EncoderHandler.h"

void EncoderHandler::handle(InputManager &manager, Encoder &encoder)
{
    if (encoder.isTurn()) {
        auto color = manager.getColor();

        if (encoder.isRightH()) {
            if (_is_brightness_setting) {
                color.value = constrain(color.value - 10, 0, 255);
            } else {
                color.saturation = constrain(color.saturation + 10, 0, 255);
            }
            manager.setColor(color);
            return;
        }
        if (encoder.isLeftH()) {
            if (_is_brightness_setting) {
                color.value = constrain(color.value + 10, 0, 255);
            } else {
                color.saturation = constrain(color.saturation - 10, 0, 255);
            }
            manager.setColor(color);
            return;
        }

        if (encoder.isFastR()) {
            color.hue += 5;
            manager.setColor(color);
            return;
        }
        if (encoder.isFastL()) {
            color.hue -= 5;
            manager.setColor(color);
            return;
        }

        if (encoder.isRight()) {
            ++color.hue;
            manager.setColor(color);
            return;
        }
        if (encoder.isLeft()) {
            --color.hue;
            manager.setColor(color);
            return;
        }
    }

    if (encoder.isClick()) {
        _is_brightness_setting = !_is_brightness_setting;
        return;
    }
}
