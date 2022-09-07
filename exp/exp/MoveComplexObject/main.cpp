#include <iostream>
#include "complexclass.h"
using namespace std;

int main()
{
    ComplexClass object("char array", 1, "std stroka");
    object.out();

    ComplexClass object1(std::move(object));

    std::cout << "Move ctor: " << std::endl;
    object.out(); // = null
    object1.out();

    std::cout << "Move operator: " << std::endl;

    ComplexClass object2("char array 2", 2, "std stroka 2");
    object2.out();
    object2 = std::move(object1);

    object1.out(); // = null
    object2.out();

    return 0;
}
