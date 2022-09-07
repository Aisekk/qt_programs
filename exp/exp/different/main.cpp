#include <iostream>
#include "arrays.h"
#include "LinkedLists.h"
#include "PureVirtualFunction.h"

class E{};
void emptyClass()
{
    E e;
    std::cout << "Empty class size = " << sizeof (E) << std::endl;
    std::cout << "Empty class object size = " << sizeof (e) << std::endl;
}

int main()
{
    //useOutputStroki();
    //transformMap();
    //transformStroka();
    //useNoexcept();
    //RemoveNthNode();
    //divisionByZero();
    //Exp::passDerivedClassByValueToFuncTakeBaseClass();
    output();
    //Std_strcopy_Test();
    //PureVirtualFunctionCall();

    return 0;
}
