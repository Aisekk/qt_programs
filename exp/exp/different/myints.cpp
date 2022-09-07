#include "myints.h"

Ints::Ints(const int* ints) : _ints(new int)
    //_str((char *) std::calloc(1 + std::strlen(str), sizeof (char)))
{
    if(_ints != nullptr)
    {

        //std::strcpy(_str, str);
    }
}

Ints::Ints(const Ints& other)
{
    if (other._ints != nullptr)
    {
        //_str = (char*)std::calloc(1 + std::strlen(other._str), sizeof(char));
        _ints = new int;
        //std::strcpy(_str, other._str);
    }
    else
    {
        _ints = nullptr;
    }
}

Ints& Ints::operator = (const Ints& other)
{
    if (this != &other && other._ints != nullptr)
    {
        if(_ints != nullptr)
        {
            delete _ints;
            //std::free(_str);
        }
        //_str = (char*)std::calloc(1 + std::strlen(other._str), sizeof(char));
        _ints = new int;
        //std::strcpy(_str, other._str);
    }
    return *this;
}

Ints::~Ints()
{
    if(_ints)
    {
        delete _ints;
        //std::free(_str);
    }
}

Ints::operator const int*() const
{
    return _ints;
}
