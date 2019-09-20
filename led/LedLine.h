//
// Created by kiryanenko on 21.09.19.
//

#ifndef LED_LIGHTING_LEDLINE_H
#define LED_LIGHTING_LEDLINE_H


enum LedMode {
    SELECTED,       // Режим при выборе ленты для настройки
    COLOR,          // Режим однотонного цвета
    RANDOM_COLOR,   // Режим случайного смены цвета
};


class LedLine {
    unsigned int _id = 0;
    unsigned int _first_led_id = 0;
    unsigned int _last_led_id;
    double _brightness = 1;
};


#endif //LED_LIGHTING_LEDLINE_H
