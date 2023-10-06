#ifndef INIT_H
#define INIT_H

#include <iostream>

namespace Init {

struct SomeData {
    int a{};
    long b{};
    float c{};
    double d{};
    bool i{};
};

void out() {
    SomeData sm;
    std::cout << sm.a << ' ' << sm.b << ' ' << sm.c << ' ' << sm.d << ' ' << sm.i << std::endl;
}

int& Sum(int a, int b) {  // ошибка!
    int result = a + b;
    return result;
}

int sumOut() {
    std::cout << Sum(2, 3) << "\n";  // неопределённое поведение!
}

}

#endif // INIT_H
