#ifndef SORT_H
#define SORT_H

#include <vector>
#include <algorithm>

namespace Sort {

void bubble_sort(std::vector<int>& a) {
    for (int i = 0; i < (int)a.size() - 1; ++i) {
        for (int j = i; j + 1 > 0 ; --j) {
            if (a[j] > a[j+1]) {
                std::swap(a[j], a[j+1]);
            }
        }
    }
}

void bubble_sort(int a[], const int N) {
    for (int i = 0; i < N - 1; ++i) {
        for (int j = i; j + 1 > 0 ; --j) {
            if (a[j] > a[j+1]) {
                std::swap(a[j], a[j+1]);
            }
        }
    }
}

}

#endif // SORT_H
