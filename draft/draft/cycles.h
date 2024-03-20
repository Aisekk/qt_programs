#ifndef CYCLES_H
#define CYCLES_H
#include <iostream>

namespace Cycles {

void forever_cycle() {
    unsigned char half_limit = 150;
    //std::cout << (char)2 * half_limit << std::endl;
    for (unsigned char i = 0;
         i < 2 * half_limit;
         ++i) {
        std::cout << i << std::endl;
    }
}

}

#endif // CYCLES_H
