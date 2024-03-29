#ifndef PRINT_H
#define PRINT_H

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <QMap>

namespace Print {

void print(const std::vector<std::string> &v) {
    for (const auto &e : v) {
        std::cout << e << ' ';
    }
    std::cout << std::endl;
}

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

void print(const std::map<int, int> &m) {
    for (const auto &[k,v] : m) {
        std::cout << k << ' ' << v << ' ';
    }
    std::cout << std::endl;
}

void print(const QMap<int, int> &m) {
    foreach (const auto &elem, m) {
        std::cout << elem << ' ' << elem << ' ';
    }
    std::cout << std::endl;
}

}

#endif // PRINT_H
