#ifndef STL_ALGS_H
#define STL_ALGS_H

#include <vector>
#include <map>
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

void transform() {
    std::map<int, std::string> m1 = {{0,"zero"},{1,"one"},{2,"two"}};
    std::map<int,int> m2;
    auto it = m2.begin();
    std::transform(m1.begin(), m1.end(), std::inserter(m2, it), [&it](const std::map<int, std::string>::value_type &val) {
        auto p = std::pair{val.first, val.first};
        std::next(it);
        return p;
    });
    Print::print(m2);
}

void test() {
    //remove_erase_vec();
    //mergeArrays();
    transform();
}

}

#endif // STL_ALGS_H
