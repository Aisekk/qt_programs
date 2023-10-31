#ifndef TEST_STD_ALGS_H
#define TEST_STD_ALGS_H

#include <algorithm>
#include <vector>
#include <iostream>

namespace TestStdAlgs {

template<typename T>
void print(const T &value) {
    std::cout << "value = " << value << std::endl;
}

void test_for_each() {
    std::vector<int> vec{1,2,3};
    int averaged = 0;
    std::for_each(vec.begin(), vec.end(), [&averaged](const int &value) {
        averaged += value;
    });
    print(averaged);
}

}

#endif // TEST_STD_ALGS_H
