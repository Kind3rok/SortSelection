#include "input.h"


int getRandInt(int low_bound, int up_bound) {
    // Генерация случайного числа в заданном диапазоне
    return (rand() % (up_bound - low_bound) + low_bound);
}