//
// Created by kiryanenko on 21.09.19.
//

#ifndef LED_LIGHTING_SETTINGS_H
#define LED_LIGHTING_SETTINGS_H

#include <FastLED.h>
#include <GyverEncoder.h>
#include <GyverTimer.h>


#define RESET                   /// При старте сбросит настройки

#define LEDS_CNT 15             /// Суммарное кол-во светодиодов
#define LED_LINES_CNT 3         /// Количество кусков ленты
#define LEDS_PIN 12

#define MODES_CNT  2            /// Количество установленных режимов
#define USER_MODES_CNT 3        /// Изначальное количество режимов пользователя
#define MAX_USER_MODES_CNT 30   /// Максимальное количество режимов пользователя
#define SLEEP_TIMEOUT 18000000  /// Время через которое будет выключаться (5 часов)
#define SAVE_TIMEOUT 5000       /// Время, через которое будет производиться сохранение в ПЗУ (5 сек)

#define ENCODER_ENABLED
#define ENCODER_S1 2
#define ENCODER_S2 3
#define ENCODER_KEY 4
#define ENCODER_TYPE 1      /// 0 - полушаговый энкодер, 1 - полношаговый

#define TTP229_ENABLED
#define TTP229_MODE_PIN 0
#define TTP229_BRIGHTNESS_UP_PIN 9
#define TTP229_BRIGHTNESS_DOWN_PIN 12
#define TTP229_SATURATION_UP_PIN 10
#define TTP229_SATURATION_DOWN_PIN 7
#define TTP229_SPEED_UP_PIN 10
#define TTP229_SPEED_DOWN_PIN 7
#define TTP229_RESET_PIN 14


/// Режимы для всей ленты
enum Mode {
    COLOR,          // Режим однотонного цвета
    RANDOM_COLOR,   // Режим случайного смены цвета
};

/// Режимы для каждого куска ленты
enum LedLineMode {
    LINE_SELECTED,       // Режим при выборе ленты для настройки
    LINE_COLOR,          // Режим однотонного цвета
    LINE_RANDOM_COLOR,   // Режим случайного смены цвета
};


struct ModeSettings {
    uint8_t brightness = 200;
    CHSV color = CHSV(HUE_RED, 255, 255);
    float speed = 1;
};

struct LedLineSettings {
    LedLineMode mode = LINE_COLOR;
    ModeSettings settings;
};


/// Синглтон класса настроек
class Settings {
    static Settings * _instance;

    bool _should_save = false;
    GTimer_ms _timer;

    uint8_t _current_mode = COLOR;
    uint8_t _user_modes_cnt = USER_MODES_CNT;

    ModeSettings _modes[MODES_CNT];
    LedLineSettings **_user_modes = nullptr;

public:
    static Settings * getInstance() {
        if(!_instance)
            _instance = new Settings();
        return _instance;
    }

    void checkCommit();
    void read();
    void save(bool force_save=false);
    void reset();

    uint8_t getCurrentMode() { return _current_mode; }
    void setCurrentMode(uint8_t mode);
    ModeSettings getMode(uint8_t mode) { return _modes[mode % MODES_CNT]; }
    void setMode(uint8_t mode, const ModeSettings &settings);
    uint8_t userModesCount() { return _user_modes_cnt; }
    LedLineSettings * getUserMode(uint8_t mode) { return _user_modes[mode % _user_modes_cnt]; }
    void addUserMode();
    void removeUserMode(uint8_t mode);

private:
    Settings();
    Settings( const Settings& );
    Settings& operator=( Settings& );

    void _save();
    inline uint8_t _cleanModeId(uint8_t mode) { return mode % (MODES_CNT + _user_modes_cnt); }
    void clearUserModes();
};


extern Settings* settings;

#endif //LED_LIGHTING_SETTINGS_H
