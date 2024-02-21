#ifndef DIRECTIVES_H
#define DIRECTIVES_H

#include <iostream>
#define X 0

namespace Directives {

void test() {
#if X == 1
    std::cout << "1" << std::endl;
#elif X == 2
    std::cout << "2" << std::endl;
#else
    std::cout << "any" << std::endl;
#endif
}

}

#endif // DIRECTIVES_H
