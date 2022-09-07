#ifndef SMART_POINTER_H
#define SMART_POINTER_H
#include <iostream>
using namespace std;

template<typename T>
class uniq_ptr
{
    T* rawptr;
public:
    uniq_ptr(T* pType) : rawptr(pType)
    { cout << "uniq_ptr created" << endl; }
    ~uniq_ptr()
    { cout << "uniq_ptr destroyed" << endl; delete rawptr; }
    uniq_ptr(uniq_ptr&& uptrsrc)
    {
        if(uptrsrc.rawptr != nullptr)
        {
            rawptr = uptrsrc.rawptr;
            uptrsrc.rawptr = nullptr;
        }
    }
    uniq_ptr& operator= (uniq_ptr&& uptrsrc)
    {
        if((uptrsrc.rawptr != nullptr) && (&uptrsrc != this))
        {
            delete rawptr;
            rawptr = uptrsrc.rawptr;
            uptrsrc.rawptr = nullptr;
        }
        return *this;
    }

    T& operator*() const{ return *rawptr; }
    T* operator->() const{ return rawptr; }
    T* get() const{ return rawptr; }
    T* release()
    {
        T* raw_ptr = rawptr;
        delete rawptr;
        rawptr = nullptr;
        return raw_ptr;
    }
};

#endif // SMART_POINTER_H
