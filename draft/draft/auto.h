#ifndef AUTO_H
#define AUTO_H

#include <typeinfo>
#include <iostream>
#include <string>
#include <cstring>

namespace AutoTypeOut {

void autoOut() {
    auto lit = "literal";
    lit = "another literal";
    std::cout << "typeid(s).name() = " << typeid(lit).name() << std::endl;
    std::cout << "typeid(const char*).name() = " << typeid(const char*).name() << std::endl;

    auto dynCharArr = new char[10];
    std::cout << "typeid(dynCharArr).name() = " << typeid(dynCharArr).name() << std::endl;
    std::cout << "typeid(char*).name() = " << typeid(char*).name() << std::endl;
    delete [] dynCharArr;

    {
        //char statCharArr[6] = "abcde";
        char statCharArr[] = "abcde";
        std::cout << "typeid(statCharArr).name() = " << typeid(statCharArr).name() << std::endl;
        std::cout << "typeid(char[6]).name() = " << typeid(char[6]).name() << std::endl;
    }
}

}

#endif // AUTO_H
