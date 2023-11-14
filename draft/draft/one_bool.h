#ifndef ONE_BOOL_H
#define ONE_BOOL_H

#include <vector>
#include <iostream>

namespace OneBool {

void test() {
    std::vector<bool> v {false, true, false, true};
    std::vector<bool> v2 {true, false, true, true};
    bool res = true;
    for (bool b : v2) {
        res &= b;
    }
    std::cout << "res: " << res << std::endl;
}

}

#endif // ONE_BOOL_H
