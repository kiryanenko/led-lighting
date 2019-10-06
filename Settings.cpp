//
// Created by kiryanenko on 21.09.19.
//

#include "Settings.h"
#include <EEPROMex.h>

Settings* Settings::_instance = nullptr;
Settings* settings = Settings::getInstance();

#ifdef TTP229_ENABLED
#ifdef ENCODER_KEY
Encoder encoder(ENCODER_S1, ENCODER_S2, ENCODER_KEY);
#else
Encoder encoder(ENCODER_S1, ENCODER_S2);
#endif
#endif

#ifdef TTP229_ENABLED
TTP229 ttp229;
#endif

Blinker blinker;


void Settings::checkCommit() {
    if (_should_save && _timer.isReady()) {
        _save();
    }
}


void Settings::read() {
    clearUserModes();

    int addr = 0;
    _current_mode = EEPROM.readByte(addr++);
    _user_modes_cnt = EEPROM.readByte(addr++);
    if (_user_modes_cnt > MAX_USER_MODES_CNT) {
        reset();
        return;
    }

    addr += EEPROM.readBlock(addr, _modes, MODES_CNT);

    _user_modes = new LedLineSettings* [_user_modes_cnt];
    for (uint8_t i = 0; i < _user_modes_cnt; ++i) {
        _user_modes[i] = new LedLineSettings[LED_LINES_CNT];
        addr += EEPROM.readBlock(addr, _user_modes[i], LED_LINES_CNT);
    }
}

void Settings::save(bool force_save) {
    if (force_save) {
        _save();
    } else {
        _should_save = true;
    }
}


void Settings::_save() {
    Serial.println("Save");

    int addr = 0;
    EEPROM.updateByte(addr++, _current_mode);
    EEPROM.updateByte(addr++, _user_modes_cnt);

    EEPROM.updateBlock(addr, _modes, MODES_CNT);
    addr += sizeof(_modes);

    for (uint8_t i = 0; i < _user_modes_cnt; ++i) {
        EEPROM.updateBlock(addr, _user_modes[i], LED_LINES_CNT);
        addr += sizeof(LedLineSettings) * LED_LINES_CNT;
    }

    _should_save = false;
    _timer.reset();
}

Settings::Settings() : _timer(SAVE_TIMEOUT) {
    read();
}

void Settings::reset() {
    clearUserModes();

    _current_mode = COLOR;
    _user_modes_cnt = USER_MODES_CNT;

    for (auto & mode : _modes) {
        mode.color = CHSV(HUE_RED, 255, 255);
        mode.speed = 1;
    }

    _user_modes = new LedLineSettings* [_user_modes_cnt];
    for (uint8_t i = 0; i < _user_modes_cnt; ++i) {
        _user_modes[i] = new LedLineSettings[LED_LINES_CNT];
    }

    _save();
}

void Settings::setCurrentMode(uint8_t mode) {
    _current_mode = _cleanModeId(mode);
    _should_save = true;
}

void Settings::addUserMode() {
    auto user_modes = new LedLineSettings* [_user_modes_cnt + 1];

    if (_user_modes) {
        for (uint8_t i = 0; i < _user_modes_cnt; ++i) {
            user_modes[i] = _user_modes[i];
        }
        delete[] _user_modes;
    }

    user_modes[_user_modes_cnt] = new LedLineSettings;
    _user_modes = user_modes;
    ++_user_modes_cnt;
    _should_save = true;
}

void Settings::removeUserMode(uint8_t mode) {
    if (_user_modes_cnt > 1) {
        mode = mode % _user_modes_cnt;

        auto user_modes = new LedLineSettings *[_user_modes_cnt - 1];
        for (uint8_t i = 0; i < _user_modes_cnt; ++i) {
            if (i != mode) {
                user_modes[i] = _user_modes[i];
            } else {
                delete[] _user_modes[i];
            }
        }

        _user_modes = user_modes;
        --_user_modes_cnt;
        _should_save = true;
    }
}

void Settings::clearUserModes() {
    if (_user_modes) {
        for (uint8_t i = 0; i < _user_modes_cnt; ++i) {
            delete[] _user_modes[i];
        }
        delete[] _user_modes;
    }

    _user_modes = nullptr;
    _user_modes_cnt = 0;
}

void Settings::setMode(uint8_t mode, const ModeSettings &settings) {
    _modes[mode % MODES_CNT] = settings;
    _should_save = true;
}

