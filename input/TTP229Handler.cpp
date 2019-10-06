//
// Created by kiryanenko on 29.09.19.
//

#include "TTP229Handler.h"
#include "../utils.h"

void TTP229Handler::handle(InputManager &manager, TTP229 &ttp229) {
    if (ttp229.getKey() != -1) {
        manager.inputDetected();
    }

    auto modeSettings = manager.getModeSettings();

    // Режим
    if (ttp229.isKeyUp(TTP229_MODE_PIN)) {
        manager.nextMode();
        return;
    }

    // Яркость
    if (ttp229.isKeyDown(TTP229_BRIGHTNESS_UP_PIN) || (ttp229.isKeyPress(TTP229_BRIGHTNESS_UP_PIN) && _press_timer.isReady())) {
        _press_timer.reset();
        modeSettings.color.value = constrain(modeSettings.color.value + 1, 0, 255);
        manager.setModeSettings(modeSettings);
        return;
    }
    if (ttp229.isKeyDown(TTP229_BRIGHTNESS_DOWN_PIN) || (ttp229.isKeyPress(TTP229_BRIGHTNESS_DOWN_PIN) && _press_timer.isReady())) {
        _press_timer.reset();
        modeSettings.color.value = constrain(modeSettings.color.value - 1, 0, 255);
        manager.setModeSettings(modeSettings);
        return;
    }

    // Насыщенность
    if (ttp229.isKeyDown(TTP229_SATURATION_UP_PIN) || (ttp229.isKeyPress(TTP229_SATURATION_UP_PIN) && _press_timer.isReady())) {
        _press_timer.reset();
        modeSettings.color.saturation = constrain(modeSettings.color.saturation + 1, 0, 255);
        manager.setModeSettings(modeSettings);
        return;
    }
    if (ttp229.isKeyDown(TTP229_SATURATION_DOWN_PIN) || (ttp229.isKeyPress(TTP229_SATURATION_DOWN_PIN) && _press_timer.isReady())) {
        _press_timer.reset();
        modeSettings.color.saturation = constrain(modeSettings.color.saturation - 1, 0, 255);
        manager.setModeSettings(modeSettings);
        return;
    }


    // Скорость
    if (ttp229.isKeyUp(TTP229_SPEED_UP_PIN)) {
        if (manager.isMode(RANDOM_COLOR)) {
            modeSettings.speed = prev(modeSettings.speed, TRANSITION_TIMES, sizeof(TRANSITION_TIMES) / sizeof(float));
            manager.setModeSettings(modeSettings);
            return;
        }
    }
    if (ttp229.isKeyUp(TTP229_SPEED_DOWN_PIN)) {
        if (manager.isMode(RANDOM_COLOR)) {
            modeSettings.speed = next(modeSettings.speed, TRANSITION_TIMES, sizeof(TRANSITION_TIMES) / sizeof(float));
            manager.setModeSettings(modeSettings);
            return;
        }
    }


    // Продолжительность
    if (ttp229.isKeyUp(TTP229_DURATION_UP_PIN)) {
        if (manager.isMode(RANDOM_COLOR)) {
            modeSettings.duration = next(modeSettings.duration, COLOR_CHANGE_TIMES, sizeof(COLOR_CHANGE_TIMES) / sizeof(float));
            manager.setModeSettings(modeSettings);
            return;
        }
    }
    if (ttp229.isKeyUp(TTP229_DURATION_DOWN_PIN)) {
        if (manager.isMode(RANDOM_COLOR)) {
            modeSettings.duration = prev(modeSettings.duration, COLOR_CHANGE_TIMES, sizeof(COLOR_CHANGE_TIMES) / sizeof(float));
            manager.setModeSettings(modeSettings);
            return;
        }
    }


    // Reset
    if (ttp229.isKeyDown(TTP229_RESET_PIN)) {
        _reset_timer.reset();
        return;
    }
    if (ttp229.isKeyPress(TTP229_RESET_PIN) && _reset_timer.isReady()) {
        settings->reset();
        return;
    }
}
