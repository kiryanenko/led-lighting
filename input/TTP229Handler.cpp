//
// Created by kiryanenko on 29.09.19.
//

#include "TTP229Handler.h"
#include "../utils.h"

void TTP229Handler::handle(InputManager &manager, TTP229 &ttp229) {
    if (ttp229.getKey() != -1) {
        manager.inputDetected();
    }

    // Режим
    if (ttp229.isKeyUp(TTP229_MODE_PIN)) {
        manager.nextMode();
        return;
    }

    // Яркость
    if (ttp229.isKeyDown(TTP229_BRIGHTNESS_UP_PIN) || (ttp229.isKeyPress(TTP229_BRIGHTNESS_UP_PIN) && _press_timer.isReady())) {
        _press_timer.reset();
        auto color = manager.getColor();
        color.value = constrain(color.value + 1, 0, 255);
        manager.setColor(color);
        return;
    }
    if (ttp229.isKeyDown(TTP229_BRIGHTNESS_DOWN_PIN) || (ttp229.isKeyPress(TTP229_BRIGHTNESS_DOWN_PIN) && _press_timer.isReady())) {
        _press_timer.reset();
        auto color = manager.getColor();
        color.value = constrain(color.value - 1, 0, 255);
        manager.setColor(color);
        return;
    }

    // Насыщенность
    if (ttp229.isKeyDown(TTP229_SATURATION_UP_PIN) || (ttp229.isKeyPress(TTP229_SATURATION_UP_PIN) && _press_timer.isReady())) {
        _press_timer.reset();
        auto color = manager.getColor();
        color.saturation = constrain(color.saturation + 1, 0, 255);
        manager.setColor(color);
        return;
    }
    if (ttp229.isKeyDown(TTP229_SATURATION_DOWN_PIN) || (ttp229.isKeyPress(TTP229_SATURATION_DOWN_PIN) && _press_timer.isReady())) {
        _press_timer.reset();
        auto color = manager.getColor();
        color.saturation = constrain(color.saturation - 1, 0, 255);
        manager.setColor(color);
        return;
    }


    if (ttp229.isKeyUp(TTP229_SPEED_UP_PIN)) {
        auto modeId = settings->getCurrentMode();
        if (manager.isMode(RANDOM_COLOR)) {
            auto settingId = nearestId(manager.get)
        }
        manager.nextMode();
        return;
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
