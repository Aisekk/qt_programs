#ifndef OVERFLOW_H
#define OVERFLOW_H

#include <iostream>

namespace Overflow {

void overflow() {
    unsigned char half_limit = 150;
    for (unsigned char i = 0; i < 2 * half_limit; ++i) {
        std::cout << i << std::endl;
    }
}

void test() {
    overflow();
}

}

#endif // OVERFLOW_H
