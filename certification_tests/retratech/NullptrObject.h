#ifndef NULLPTROBJECT_H
#define NULLPTROBJECT_H

#include <iostream>

void* operator new(size_t size) throw (std::bad_alloc)
{
    return nullptr;
}

void AssignByNullptrObject()
{
    int* p = new int;
    *p = 0;
    std::cout << p << "; " << *p << std::endl;
}


#endif // NULLPTROBJECT_H
