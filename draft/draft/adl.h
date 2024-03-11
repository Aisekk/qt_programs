#ifndef ADL_H
#define ADL_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "print.h"

namespace ArgDependLookup {

void ADL_examples() {
    std::cout << "Test\n"; // There is no operator<< in global namespace, but ADL
    // examines std namespace because the left argument is in
    // std and finds std::operator<<(std::ostream&, const char*)
    operator<<(std::cout, "Test\n"); // Same, using function call notation

    // However,
    //std::cout << endl; // Error: 'endl' is not declared in this namespace.
    // This is not a function call to endl(), so ADL does not apply

    endl(std::cout); // OK: this is a function call: ADL examines std namespace
    // because the argument of endl is in std, and finds std::endl

    //(endl)(std::cout); // Error: 'endl' is not declared in this namespace.
    // The sub-expression (endl) is not an unqualified-id

    std::vector<int> v{0,1,2,3,4,5,6,7,8};
    std::remove(begin(v), end(v), 3);
    remove(begin(v), end(v), 4);
    Print::print(v);
}

}
#endif // ADL_H
