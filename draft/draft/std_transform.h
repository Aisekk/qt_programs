#ifndef STD_TRANSFORM_H
#define STD_TRANSFORM_H

#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include "print.h"

namespace StdTransform {

void std_transform() {
    std::vector<int> v{100,200,300};
    std::map<int, std::string> m {
        {1, "one"}, {2, "two"}, {3, "three"}
    };
    //std::transform(m.begin(), m.end(), std::back_inserter(v), [](const std::map<int, std::string>::value_type& val) { return val.first; });
    std::transform(m.begin(), m.end(), std::back_inserter(v), [](const auto& val) { return val.first; });
    Print::print(v);
}

}

#endif // STD_TRANSFORM_H
