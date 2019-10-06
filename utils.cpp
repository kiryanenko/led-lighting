//
// Created by kiryanenko on 05.10.19.
//
#include "utils.h"


/// Выдача первого числа из масссива arr, которое больше value, если таковых нету то вернет value
/// \param arr Массив отсортированный по возрастанию
float next(float value, const float *arr, int size) {
    for (auto i = 0; i < size; ++i) {
        if (arr[i] > value) {
            return arr[i];
        }
    }
    return value;
}


/// Выдача последнего числа из масссива arr, которое меньше value, если таковых нету то вернет value
/// \param arr Массив отсортированный по возрастанию
float prev(float value, const float *arr, int size) {
    for (auto i = size - 1; i >= 0; --i) {
        if (arr[i] < value) {
            return arr[i];
        }
    }
    return value;
}


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


/// Переводит value в диапозон 0..255
double cleanColorPart(double value) {
    long intPart = value;
    double floatPart = value - intPart;
    double res = abs(intPart) % 256 + abs(floatPart);
    return value >= 0 ? res : 256 - res;
}
