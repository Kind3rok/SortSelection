#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <iostream>

// Константы, использующиеся в функции, генерирующей случайный набор массивов
enum ConstValuesForRandomInput {
    LOW_BOUND_FOR_RANDOM = -1000,
    UP_BOUND_FOR_RANDOM = 1000,
    LOW_BOUND_FOR_QUANTITY = 3,
    UP_BOUND_FOR_QUANTITY = 100
};

// Заголовки таблицы в графическом интерфейсе
enum TableHeaders {
    Array_data,
    Change_date,
    Type
};

// Константы для подключения к серверу
const std::string server = "tcp://localhost:3306";
const std::string username = "root";
const std::string database = "rps_lab3";
const std::string password = "ki22r31ya";

/// <summary>
/// Функция для получения случайного целого числа в заданном диапазоне.
/// </summary>
int getRandInt(int low_bound, int up_bound);


#endif