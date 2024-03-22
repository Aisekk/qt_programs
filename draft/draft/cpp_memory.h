#ifndef CPP_MEMORY_H
#define CPP_MEMORY_H

#include <iostream>
#include <string>

namespace CppMemory {

void test() {
    char szData[] = "abc";
    szData[0] = 'A';
    std::cout << szData << std::endl;
    const char *pszData = "abc";
    //pszData[0] = 'A'; // compile error
    std::cout << pszData << std::endl;
}

}

#endif // CPP_MEMORY_H
