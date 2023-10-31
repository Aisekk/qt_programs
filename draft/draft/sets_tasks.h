#ifndef SETS_TASKS_H
#define SETS_TASKS_H

#include <vector>
#include <algorithm>
#include "print.h"

namespace SetsTasks {

void merge() {
    std::vector<int> v1 = {5, 5, 3, 9, 0, 1};
    std::vector<int> v2 = {7, 1, 2, 6, 2};
    std::sort(v1.begin(), v1.end(), std::less<int>());
    std::sort(v2.begin(), v2.end(), std::less<int>());
    std::vector<int> v;
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v));
    std::cout << "merge: ";
    Print::print(v);
    //std::sort(v.begin(), v.end(), std::less<int>());
    //std::sort(v.begin(), v.end(), std::greater<int>{});
    //Print::print(v);
}

void _union() {
    std::vector<int> v1 = {5, 5, 3, 9, 0, 1};
    std::vector<int> v2 = {7, 1, 2, 6, 2};
    std::sort(v1.begin(), v1.end(), std::less<int>());
    std::sort(v2.begin(), v2.end(), std::less<int>());
    std::vector<int> v;
    std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v));
    std::cout << "union: ";
    Print::print(v);
}

void intersection() {
    std::vector<int> v1 = {5, 3, 9, 0, 1, 5};
    std::vector<int> v2 = {7, 1, 5, 6, 3, 1};
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    std::vector<int> v;
    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v));
    std::cout << "intersection: ";
    Print::print(v);
}

void difference() {
    std::vector<int> v1 = {5, 3, 9, 0, 1, 1, 5};
    std::vector<int> v2 = {7, 1, 5, 6, 3, 1, 1, 8};
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    std::vector<int> v;
    std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v));
    std::cout << "difference: ";
    Print::print(v);
}

void symmetric_difference() {
    std::vector<int> v1 = {5, 3, 0, 1, 1, 5};
    std::vector<int> v2 = {7, 1, 5, 6, 3, 1};
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    std::vector<int> v;
    std::set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v));
    std::cout << "symmetric_difference: ";
    Print::print(v);
}

template<class ForwardIt>
ForwardIt unique_(ForwardIt first, ForwardIt last)
{
    if (first == last)
        return last;

    ForwardIt result = first;
    while (++first != last)
        //if (!(*result == *first) && ++result != first)
        if (*result != *first && ++result != first)
        {
            *result = std::move(*first);
            std::cout << *result << ' ';
        }

    std::cout << std::endl;
    return ++result;
}

void unique() {
    std::cout << "\nstd::unique: " << std::endl;
    std::vector<int> v = {5, 5, 3, 9, 0, 1, 2, 1};
    std::sort(v.begin(), v.end());
    std::cout << "before unique: ";
    Print::print(v);
    std::cout << "unique results: ";
    //auto last = std::unique(v.begin(), v.end());
    auto last = unique_(v.begin(), v.end());
    std::cout << "before erase: ";
    Print::print(v);
    std::cout << "unique: ";
    v.erase(last, v.end());
    Print::print(v);
}

void merge_inplace() {
    std::vector<int> v = {6, 7, 8, 0, 1, 2, 3};
    std::inplace_merge(v.begin(), v.begin() + std::distance(v.begin(), v.end()) / 2, v.end());
    std::cout << "std::inplace_merge(): ";
    Print::print(v);
}

void test() {
    merge();
    _union();
    intersection();
    difference();
    symmetric_difference();
    unique();
    merge_inplace();
}

}

#endif // SETS_TASKS_H
