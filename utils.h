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


inline CHSV randomHSV(uint8_t brightness) {
    return CHSV(random8(), random8(), brightness);
}

/// Переводит value в диапозон 0..255
inline double cleanColorPart(double value) {
    long intPart = value;
    double floatPart = value - intPart;
    double res = abs(intPart) % 256 + abs(floatPart);
    return value >= 0 ? res : 256 - res;
}

#endif //LED_LIGHTING_UTILS_H
