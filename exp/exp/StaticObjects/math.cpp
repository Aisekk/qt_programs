#include "StaticFuncInHeader.h"

void outStaticVar()
{
  std::cout << "static var = " << svar << std::endl;
}

int sum(int a, int b)
{
  return a + b;
}

