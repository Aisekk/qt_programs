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
    operator bool()
    { if(rawptr == nullptr) return false; else return true; }

    T& operator*() const{ return *rawptr; }
    T* operator->() const{ return rawptr; }
    T* get() const{ return rawptr; }
    T* release()
    { T* raw_ptr = rawptr; delete rawptr; rawptr = nullptr; return raw_ptr; }
    void reset(T* ptr)
    {
        if(ptr == nullptr)
        { if(rawptr != nullptr) delete rawptr; rawptr = nullptr; return; }
        if(rawptr == nullptr){ rawptr = ptr; }
        else{ delete rawptr; rawptr = ptr; }
    }
    void swap(uniq_ptr&& uptr)
    {
        if(uptr.rawptr != nullptr)
        {
            T* temp_rawptr = rawptr;
            rawptr = uptr.rawptr;
            uptr.rawptr = temp_rawptr;
        }
    }
};

template<typename T>
class shar_ptr
{
private:
    long count;
    T* rawptr;
    static long calcCount(bool inc)
    {
        static long count = 0;
        if(inc) ++count; else --count;
        return count;
    }
public:
    shar_ptr(T* pType) : rawptr(pType)
    {
        count = 1;
        //count = calcCount(true);
        cout << "shar_ptr created" << endl;
    }
    ~shar_ptr()
    {
        count = calcCount(false);
        if(count == 0){ delete rawptr; cout << "last shar_ptr destroyed" << endl; }
        else cout << "shar_ptr copy destroyed" << endl;
    }
    shar_ptr(shar_ptr& spcopy)
    {
        if(spcopy.rawptr != nullptr)
        {
            rawptr = spcopy.rawptr;
            //count = calcCount(true);
            count = calcCount(true);
            spcopy.count = count;
        }
    }
    shar_ptr& operator= (shar_ptr& spcopy)
    {
        if(this != &spcopy && spcopy.rawptr != nullptr)
        {
            if(rawptr != nullptr) delete rawptr;
            rawptr = spcopy.rawptr;
            count = calcCount(true);
            spcopy.count = count;
        }
        return *this;
    }
    shar_ptr(shar_ptr&& sptrsrc)
    {
        if(sptrsrc.rawptr != nullptr)
        {
            rawptr = sptrsrc.rawptr;
            sptrsrc.rawptr = nullptr;
        }
    }
    shar_ptr& operator= (shar_ptr&& sptrsrc)
    {
        if((sptrsrc.rawptr != nullptr) && (&sptrsrc != this))
        {
            delete rawptr;
            rawptr = sptrsrc.rawptr;
            sptrsrc.rawptr = nullptr;
        }
        return *this;
    }
    operator bool()
    { if(rawptr == nullptr) return false; else return true; }

    T& operator*() const{ return *rawptr; }
    T* operator->() const{ return rawptr; }
    T* get() const{ return rawptr; }
    void reset(T* ptr)
    {
        if(ptr == nullptr)
        { if(rawptr != nullptr) delete rawptr; rawptr = nullptr; return; }
        if(rawptr == nullptr){ rawptr = ptr; }
        else{ delete rawptr; rawptr = ptr; }
    }
    void swap(shar_ptr&& sptr)
    {
        if(sptr.rawptr != nullptr)
        {
            T* temp_rawptr = rawptr;
            rawptr = sptr.rawptr;
            sptr.rawptr = temp_rawptr;
        }
    }
    long use_count() const{ return count; }
};

#endif // SMART_POINTER_H
