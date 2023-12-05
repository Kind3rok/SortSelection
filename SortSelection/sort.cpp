#include "Sort.h"
/// <summary> функция для сортировки вектора целочисленных значений сортировкой выбором </summary>/// <param name="vect"> вектор целочисленных значений </param>
void SelectionSort(std::vector<int>& vect)
{
    size_t n = vect.size();
    size_t minIndex = 0;

    for (size_t i = 0; i < n - 1; i++)
    {
        minIndex = i;

        for (size_t j = i + 1; j < n; j++)
        {
            if (vect[j] < vect[minIndex])
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            int temp = vect[i];
            vect[i] = vect[minIndex];
            vect[minIndex] = temp;
        }
    }
}