//
// Created by kiryanenko on 04.10.19.
//

#ifndef LED_LIGHTING_UTILS_H
#define LED_LIGHTING_UTILS_H

#include <Arduino.h>

/// Поиск ближайшего числа в массиве
/// \param value Сравниваемое значение
/// \return Id ближайшего числа, если массив пустой вернет -1
int nearestId(float value, const float *arr, int size) {
    uint32_t lessId = -1;
    for (uint32_t i = 0; i < size; ++i) {
        if (arr[i] <= value && (lessId == -1 || abs(value - arr[i]) < abs(arr[lessId] - value))) {
            lessId = i;
        }
    }
    uint32_t moreId = -1;
    for (uint32_t i = 0; i < size; ++i) {
        if (arr[i] > value && (moreId == -1 || abs(value - arr[i]) < abs(arr[moreId] - value))) {
            moreId = i;
        }
    }

    if (lessId != -1 && moreId != -1) {
        return abs(value - arr[lessId]) < abs(arr[moreId] - value) ? lessId : moreId;
    }
    return lessId != -1 ? lessId : moreId;
}

#endif //LED_LIGHTING_UTILS_H
