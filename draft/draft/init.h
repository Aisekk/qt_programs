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

}

#endif // INIT_H
