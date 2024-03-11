#ifndef MOVE_SEMANTICS_H
#define MOVE_SEMANTICS_H

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace MoveSemantics {

void std_string_move() {
    std::vector<std::string> letters;

    letters.push_back("abc");
    std::string s{"def"};
    letters.push_back(std::move(s));

    std::cout << "std::vector letters holds: ";
    for (auto&& e : letters)
        std::cout << std::quoted(e) << ' ';

    std::cout << "\nMoved-from string s holds: " << std::quoted(s) << '\n';
}

}

#endif // MOVE_SEMANTICS_H
