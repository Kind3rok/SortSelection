#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <vector>


/// <summary>
/// Класс, реализующий сортировку выбором.
/// </summary>
class SelectionSort {
public:
    /// <summary>
    /// Сортирует вектор с использованием сортировки выбором.
    /// </summary>
    /// <param name="array">Вектор, который нужно отсортировать.</param>
    void sort(std::vector<int> &array);
};


#endif