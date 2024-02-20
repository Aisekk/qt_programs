#include "static_word.h"
#include <iostream>

const int var_0 = 10;

namespace SomeSpace {
const int var_n = 10;
}

static void some_fun() {}

static void fun_1() {
  std::cout << "fun_1() from static_word.cpp" << std::endl;
}
