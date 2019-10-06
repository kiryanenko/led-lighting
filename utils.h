//
// Created by kiryanenko on 04.10.19.
//

#ifndef LED_LIGHTING_UTILS_H
#define LED_LIGHTING_UTILS_H

#include <Arduino.h>
#include <FastLED.h>

/// Выдача первого числа из масссива arr, которое больше value, если таковых нету то вернет value
/// \param arr Массив отсортированный по возрастанию
float next(float value, const float *arr, int size);
/// Выдача последнего числа из масссива arr, которое меньше value, если таковых нету то вернет value
/// \param arr Массив отсортированный по возрастанию
float prev(float value, const float *arr, int size);


/// Поиск ближайшего числа в массиве
/// \param value Сравниваемое значение
/// \return Id ближайшего числа, если массив пустой вернет -1
int nearestId(float value, const float *arr, int size);

/// Вычисление скорости
/// \param src Точка отправления
/// \param dst Точка назначиния
/// \param time Время
/// \param frame Время фрейма
/// \return Скорость
inline double velocity(uint8_t src, uint8_t dst, uint64_t time, uint64_t frame = 1) {
    return (double(dst) - src) / time * frame;
}
/// Интерполяция
/// \param src Точка отправления
/// \param dst Точка назначиния
/// \param velocity Скорость
/// \return Результат интерполяции с плавающей запятой между src и dst
inline double lerp(double src, double dst, double velocity) {
    if (velocity > 0) {
        return constrain(src + velocity, src, dst);
    } else {
        return constrain(src + velocity, dst, src);
    }
}


/// Переводит value в диапозон 0..255
double cleanColorPart(double value);


struct DRGB {
    double red = 0;
    double green = 100;
    double blue = 100;

    DRGB() = default;
    DRGB(const CRGB& rgb) : red(rgb.red), green(rgb.green), blue(rgb.blue) {}

    operator CRGB() const {
        return CRGB(cleanColorPart(red), cleanColorPart(green), cleanColorPart(blue));
    }

    inline void clean() {
        red = cleanColorPart(red);
        green = cleanColorPart(green);
        blue = cleanColorPart(blue);
    }
};


struct DHSV {
    double hue = 0;
    double saturation = 255;
    double value = 255;

    DHSV() = default;
    DHSV(const CHSV& hsv) : hue(hsv.hue), saturation(hsv.saturation), value(hsv.value) {}

    operator CHSV() const {
        return CHSV(cleanColorPart(hue), cleanColorPart(saturation), cleanColorPart(value));
    }

    inline void clean() {
        hue = cleanColorPart(hue);
        saturation = cleanColorPart(saturation);
        value = cleanColorPart(value);
    }

    CRGB rgb() {
        return CRGB(*this);
    }
};


/// Интерполяция
/// \param src Точка отправления
/// \param dst Точка назначиния
/// \param velocity Скорость
/// \return Результат интерполяции с плавающей запятой между src и dst
inline DRGB colorLerp(const DRGB &src, const CRGB &dst, const DRGB &velocity) {
    DRGB res;
    res.red = lerp(src.red, dst.r, velocity.red);
    res.green = lerp(src.green, dst.g, velocity.green);
    res.blue = lerp(src.blue, dst.b, velocity.blue);
    return res;
}

inline CHSV randomHSV(uint8_t brightness) {
    return CHSV(random8(), random8(), brightness);
}


#endif //LED_LIGHTING_UTILS_H
