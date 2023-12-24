#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>

/// <summary>
/// Вычисляет текущие дату и время, которые добавляются в базу данных.
/// </summary>
std::string getCurrentDateAndTime();

/// <summary>
/// Вычисляет тип массива (отсортированный или нет), который добавляется в базу данных.
/// </summary>
/// <param name="array"> Вектор целых чисел, массив. </param>
std::string getArrayType(std::vector<int>& array);

/// <summary>
/// Добавляет данные в базу.
/// </summary>
/// <param name="arrays"> Вектор векторов, в котором хранятся массивы. </param>
int initializeDB(std::vector<std::vector<int>>& arrays);

/// <summary>
/// Выгружает данные из базы.
/// </summary>
/// <param name="arrays"> Вектор векторов, в котором хранятся массивы. </param>
/// <param name="change_dates"> Вектор строк, в котором хранятся даты загрузки массивов в базу данных. </param>
void loadDataFromDB(std::vector<std::vector<int>>& arrays, std::vector<std::string>& change_dates);

/// <summary>
/// Очистка базы данных.
/// </summary>
bool clearTable();


#endif
