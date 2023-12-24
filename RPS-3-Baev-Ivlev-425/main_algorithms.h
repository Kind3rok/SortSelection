#ifndef MAIN_ALGORITHMS_H
#define MAIN_ALGORITHMS_H

#include <vector>

/// <summary>
/// Генерирует случайные массивы для дальнейшей сортировки.
/// </summary>
/// <param name="arrays"> Вектор векторов, в который будут помещены сгенерированные массивы. </param>
/// <param name="change_dates"> Вектор строк, в котором хранятся даты загрузки массивов в базу данных. </param>
/// <param name="number_of_arrays"> Количество массивов для генерации. </param>
void generateRandomArrays(std::vector<std::vector<int>>& arrays, std::vector<std::string>& change_dates, const size_t& number_of_arrays);


/// <summary>
/// Сортирует массивы, хранящиеся в векторе.
/// </summary>
/// <param name="arrays"> Вектор векторов, в котором сортируются массивы. </param>
void startSorting(std::vector<std::vector<int>>& arrays);

#endif