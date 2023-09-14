#ifndef EXTERN_H
#define EXTERN_H

#include <iostream>

extern int global;
//extern int static_var;

namespace Extern {

void outGlobal() {
    std::cout << "global = " << global << std::endl;
    //std::cout << "static_var = " << static_var << std::endl;
}

}

#endif // EXTERN_H
