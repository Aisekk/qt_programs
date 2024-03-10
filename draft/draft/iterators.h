#ifndef ITERATORS_H
#define ITERATORS_H

#include <iostream>
#include <vector>
#include <list>

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

}

#endif // ITERATORS_H
