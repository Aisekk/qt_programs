#ifndef REMOVE_ERASE_H
#define REMOVE_ERASE_H

#include <vector>
#include <algorithm>
#include "print.h"

namespace STL {

void remove_erase_vec() {
    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9};
    Print::print(v);
    auto it = std::remove(v.begin(), v.end(), 3);
    v.erase(it);
    Print::print(v);
    it = std::remove_if(v.begin(), v.end(), [](int e){ return e % 2 == 0; });
    v.erase(it, v.end());
    Print::print(v);
}

void test() {
    remove_erase_vec();
}

}

#endif // REMOVE_ERASE_H
