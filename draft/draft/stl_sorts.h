#ifndef STL_SORTS_H
#define STL_SORTS_H

#include <vector>
#include <algorithm>
#include "print.h"

namespace StlSorts {

template<class Iter>
void merge_sort(Iter first, Iter last)
{
    if (last - first > 1)
    {
        Iter middle = first + (last - first) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last);
    }
}

void test() {
    std::vector<int> v = {5, 8, 3, 9, 0, 1};
    merge_sort(v.begin(), v.end());
    Print::print(v);
}

}

#endif // STL_SORTS_H
