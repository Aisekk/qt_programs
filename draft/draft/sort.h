#ifndef SORT_H
#define SORT_H

#include <vector>
#include <algorithm>
#include <iostream>
#include "arrays.h"
#include "print.h"

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

void bubble_sort_it(std::vector<int>& a) {
    for (auto it1 = a.begin(); it1 < a.end() - 1; ++it1) {
        for (auto it2 = it1; it2 >= a.begin(); --it2) {
            if (*it2 > *(it2 + 1)) {
                std::swap(*it2, *(it2 + 1));
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

void test() {
    //int *a = Arrays::zeroArray(); std::cout << "sizeof(ZeroArray) = " << sizeof(a) << "; a[0] = " << a[0] << std::endl; delete [] a;
    int a[] = {2,3,1};
    Sort::bubble_sort(a, 3);
    Print::print(a, 3);

    std::vector<int> a1 = {5,2,0,3,1,4};
    Sort::bubble_sort(a1);
    Print::print(a1);

    std::vector<int> a2 = {5,2,0,3,1,4};
    Sort::bubble_sort_it(a2);
    Print::print(a2);
}

}

#endif // SORT_H
