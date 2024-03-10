#ifndef SMART_POINTERS_H
#define SMART_POINTERS_H

#include <memory>

namespace SmartPointers {

void del(void(*)()) {}

void fun() {}

int ptr_to_fun() {
    std::shared_ptr<void()> ee(fun, del);
    (*ee)();
    return 0;
}

}

#endif // SMART_POINTERS_H
