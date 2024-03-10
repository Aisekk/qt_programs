#ifndef ITERATORS_H
#define ITERATORS_H

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

namespace Iterators {

void invalidate_vec_iters() {
    std::vector<int> v{0,1,2,3,4,5,6};
    v.reserve(10);
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it == 2) {
            v.push_back(10);
        }
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}

void no_invalidate_list_iters() {
    std::list<int> l{0,1,2,3,4,5};
    for (auto it = l.begin(); it != l.end();) {
        std::cout << *it << ' ';
        if (*it == 2) {
            it = l.insert(it, 10);
            it = std::next(it, 2);
        } else {
            ++it;
        }
    }
    std::cout << std::endl;
    for (auto it = l.begin(); it != l.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}

void insert_iters() {
    std::multiset<int> s{1, 2, 3};

    // std::inserter is commonly used with multi-sets
    std::fill_n(std::inserter(s, s.end()), 5, 2);

    for (int n : s)
        std::cout << n << ' ';
    std::cout << '\n';

    std::vector<int> d{100, 200, 300};
    std::vector<int> v{1, 2, 3, 4, 5};

    // when inserting in a sequence container, insertion point advances
    // because each std::insert_iterator::operator= updates the target iterator
    //std::copy(d.begin(), d.end(), std::inserter(v, std::next(v.begin())));
    std::copy(d.begin(), d.end(), std::inserter(v, std::next(v.begin(), 0)));

    for (int n : v)
        std::cout << n << ' ';
    std::cout << '\n';

    std::multiset<int> ms1{1,2,3};
    std::vector<int> v1{4,5,6};
    std::copy(ms1.begin(), ms1.end(), std::back_inserter(v1));
    for (auto n : v1) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}

}

#endif // ITERATORS_H
