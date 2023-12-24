#include "selection_sort.h"


void SelectionSort::sort(std::vector<int> &vect) {
    size_t n = vect.size();
    size_t min_index = 0;

    for (size_t i = 0; i < n - 1; i++) {
        min_index = i;

        for (size_t j = i + 1; j < n; j++) {
            if (vect[j] < vect[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            int temp = vect[i];
            vect[i] = vect[min_index];
            vect[min_index] = temp;
        }
    }
}
