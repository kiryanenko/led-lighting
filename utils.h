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


inline CHSV randomHSV(uint8_t brightness) {
    return CHSV(random8(), random8(), brightness);
}

#endif //LED_LIGHTING_UTILS_H
