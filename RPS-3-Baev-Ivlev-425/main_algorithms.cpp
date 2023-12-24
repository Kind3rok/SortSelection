#include "input.h"
#include "selection_sort.h"
#include "database.h"

void generateRandomArrays(std::vector<std::vector<int>> &arrays, std::vector<std::string>& change_dates, const size_t &number_of_arrays) {
    size_t amount_of_elements{};
    std::vector<std::vector<int>> new_arrays{};
    std::string change_date{};

    // Изменяем размер вектора для массивов согласно указанному количеству
    new_arrays.resize(number_of_arrays);

    for (int i = 0; i < number_of_arrays; i++) {
        // Генерируем случайное количество элементов для текущего массива
        amount_of_elements = getRandInt(LOW_BOUND_FOR_QUANTITY, UP_BOUND_FOR_QUANTITY);

        // Изменяем размер текущего массива согласно сгенерированному количеству элементов
        new_arrays[i].resize(amount_of_elements);

        for (int j = 0; j < amount_of_elements; j++) {
            // Заполняем массив случайными значениями в указанных пределах
            new_arrays[i][j] = getRandInt(LOW_BOUND_FOR_RANDOM, UP_BOUND_FOR_RANDOM);
        }
        // Добавляем новый массив к старым
        arrays.push_back(new_arrays[i]);

        // Получение строки с датой изменения
        change_date = getCurrentDateAndTime();

        // Добавление даты в вектор дат
        change_dates.push_back(change_date);
    }
}


void startSorting(std::vector<std::vector<int>> &arrays) {
    // Вычисляем количество массивов
    size_t number_of_arrays = arrays.size();

    // Создание и инициализация объекта, производящего сортировку выбором
    SelectionSort selection_sort{};

    // Внешний цикл, отвечающий за количество массивов
    for (size_t i = 0; i < number_of_arrays; i++) {
        // Сортировка отдельных массивов
        selection_sort.sort(arrays[i]);
    }
}
