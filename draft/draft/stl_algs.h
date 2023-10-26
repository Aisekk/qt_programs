#ifndef STL_ALGS_H
#define STL_ALGS_H

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

void mergeArrays() {
     std::vector<int> v1 = {0,2,4,6,8};
     std::vector<int> v2 = {1,3,5,7,9};
     std::vector<int> v;
     std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v));
     Print::print(v);
}

void test() {
    //remove_erase_vec();
    mergeArrays();
}

}

#endif // STL_ALGS_H
