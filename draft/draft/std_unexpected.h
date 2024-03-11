#ifndef STD_UNEXPECTED_H
#define STD_UNEXPECTED_H

#include <iostream>       // std::cerr
#include <exception>      // std::set_unexpected

namespace StdUnexpected {

void myunexpected () {
  std::cerr << "unexpected called\n";
  throw 0;     // throws int (in exception-specification)
}

void myfunction () { //throw (int) {
  throw 'x';   // throws char (not in exception-specification)
}

void std_unexpected() {
    std::set_unexpected (myunexpected);
    try {
      myfunction();
    }
    catch (int) { std::cerr << "caught int\n"; }
    catch (...) { std::cerr << "caught some other exception type\n"; }
}

}

#endif // STD_UNEXPECTED_H
