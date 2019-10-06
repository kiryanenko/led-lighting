//
// Created by kiryanenko on 28.09.19.
//

#include <Arduino.h>
#include "EncoderHandler.h"

void EncoderHandler::handle(InputManager &manager, Encoder &encoder)
{
    auto isTurn = encoder.isTurn();
    if (isTurn || encoder.isHold()) {
        manager.inputDetected();
    }


    if (isTurn) {
        if (manager.isMode(COLOR) && !encoder.isHold()) {
            setColor(manager, encoder);
            return;
        }

        if ((manager.isMode(COLOR) && encoder.isHold() && _is_brightness_setting) ||
            (manager.isMode(RANDOM_COLOR) && !encoder.isHold())) {
            setBrightness(manager, encoder);
            return;
        }

        if ((manager.isMode(COLOR) && encoder.isHold() && !_is_brightness_setting)) {
            setSaturation(manager, encoder);
            return;
        }

        if ((manager.isMode(RANDOM_COLOR) && encoder.isHold() && _is_speed_setting)) {
            setSpeed(manager, encoder);
            return;
        }

        if ((manager.isMode(RANDOM_COLOR) && encoder.isHold() && !_is_speed_setting)) {
            setDuration(manager, encoder);
            return;
        }
    }

    if (encoder.isClick()) {
        if (manager.isMode(COLOR)) {
            _is_brightness_setting = !_is_brightness_setting;
        } else {
            _is_speed_setting = !_is_speed_setting;
        }
        return;
    }
}

void EncoderHandler::setColor(InputManager &manager, Encoder &encoder) {
    auto modeSettings = manager.getModeSettings();

    if (encoder.isFastR()) {
        modeSettings.color.hue += 5;
        manager.setModeSettings(modeSettings);
        return;
    }
    if (encoder.isFastL()) {
        modeSettings.color.hue -= 5;
        manager.setModeSettings(modeSettings);
        return;
    }

    if (isTurnRight(encoder)) {
        ++modeSettings.color.hue;
        manager.setModeSettings(modeSettings);
        return;
    }
    if (isTurnLeft(encoder)) {
        --modeSettings.color.hue;
        manager.setModeSettings(modeSettings);
        return;
    }
}

void EncoderHandler::setBrightness(InputManager &manager, Encoder &encoder) {
    auto modeSettings = manager.getModeSettings();

    if (isTurnRight(encoder)) {
        modeSettings.color.value = constrain(modeSettings.color.value - 10, 0, 255);
        manager.setModeSettings(modeSettings);
        return;
    }
    if (isTurnLeft(encoder)) {
        modeSettings.color.value = constrain(modeSettings.color.value + 10, 0, 255);
        manager.setModeSettings(modeSettings);
        return;
    }
}

void EncoderHandler::setSaturation(InputManager &manager, Encoder &encoder) {
    auto modeSettings = manager.getModeSettings();

    if (isTurnRight(encoder)) {
        modeSettings.color.saturation = constrain(modeSettings.color.saturation + 10, 0, 255);
        manager.setModeSettings(modeSettings);
        return;
    }
    if (isTurnLeft(encoder)) {
        modeSettings.color.saturation = constrain(modeSettings.color.saturation - 10, 0, 255);
        manager.setModeSettings(modeSettings);
        return;
    }
}

void EncoderHandler::setSpeed(InputManager &manager, Encoder &encoder) {
    auto modeSettings = manager.getModeSettings();

    if (manager.isMode(RANDOM_COLOR)) {
        if (encoder.isFastR()) {
            modeSettings.speed = constrain(modeSettings.speed + 15000, 0, modeSettings.duration);
            manager.setModeSettings(modeSettings);
            return;
        }
        if (encoder.isFastL()) {
            modeSettings.speed = constrain(modeSettings.speed - 15000, 0, modeSettings.duration);
            manager.setModeSettings(modeSettings);
            return;
        }

        if (isTurnRight(encoder)) {
            modeSettings.speed = constrain(modeSettings.speed + 1000, 0, modeSettings.duration);
            manager.setModeSettings(modeSettings);
            return;
        }
        if (isTurnLeft(encoder)) {
            modeSettings.speed = constrain(modeSettings.speed - 1000, 0, modeSettings.duration);
            manager.setModeSettings(modeSettings);
            return;
        }
    }
}

void EncoderHandler::setDuration(InputManager &manager, Encoder &encoder) {
    auto modeSettings = manager.getModeSettings();

    if (manager.isMode(RANDOM_COLOR)) {
        if (encoder.isFastR()) {
            modeSettings.duration = constrain(modeSettings.duration + 60000, 1000, 3600000);
            manager.setModeSettings(modeSettings);
            return;
        }
        if (encoder.isFastL()) {
            modeSettings.duration = constrain(modeSettings.duration - 60000, 1000, 3600000);
            manager.setModeSettings(modeSettings);
            return;
        }

        if (isTurnRight(encoder)) {
            modeSettings.duration = constrain(modeSettings.duration + 5000, 1000, 3600000);
            manager.setModeSettings(modeSettings);
            return;
        }
        if (isTurnLeft(encoder)) {
            modeSettings.duration = constrain(modeSettings.duration - 5000, 1000, 3600000);
            manager.setModeSettings(modeSettings);
            return;
        }
    }
}

bool EncoderHandler::isTurnRight(Encoder &encoder) {
    return encoder.isRight() || encoder.isRightH();
}

bool EncoderHandler::isTurnLeft(Encoder &encoder) {
    return encoder.isLeft() || encoder.isLeftH();
}
