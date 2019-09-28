//
// Created by kiryanenko on 28.09.19.
//

#include "EncoderHandler.h"

void EncoderHandler::handle(InputManager &manager, Encoder &encoder)
{
    if (encoder.isClick()) {
        manager.nextMode();
    }

    if (encoder.isTurn()) {
        auto color = manager.getColor();
        if (encoder.isRight()) {
            color.hue += 6;
        } else {
            color.hue -= 6;
        }
        manager.setColor(color);
    }
}
