#ifndef BREAK_H
#define BREAK_H

#include <iostream>
#include <string>

namespace Break {

void two_cycles_break() {
    std::string one = "one";
    std::string two = "two";
    int counter = 0;
    bool broke = false;
    for (auto c1 : one) {
        for (auto c2 : two) {
            ++counter;
            if (c1 == 'n' && c2 == 'w') {
                broke = true;
                break;
            }
        }
        std::cout << "c1 = " << c1 << ": conter = " << counter << "; broke = " << broke << std::endl;
    }
    std::cout << "counter = " << counter << std::endl;
}

}

#endif // BREAK_H
