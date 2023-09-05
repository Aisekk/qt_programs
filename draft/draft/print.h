#ifndef PRINT_H
#define PRINT_H

#include <vector>
#include <iostream>

namespace Print {

void print(const std::vector<int> &v) {
    for (int e : v) {
        std::cout << e << ' ';
    }
    std::cout << std::endl;
}

void print(int a[], const int N) {
    for (int i = 0; i < N; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
}

}

#endif // PRINT_H
