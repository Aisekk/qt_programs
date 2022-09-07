#include "complexclass.h"
//#include <cstdlib>
#include <cstring>

ComplexClass::ComplexClass(const char* str, int num, const std::string& stroka) :
    _str(new char[std::strlen(str) + 1]),
    _num(num),
    _stroka(stroka)
{
    if(_str)
        std::strcpy(_str, str);
}

ComplexClass::ComplexClass(ComplexClass&& other)
{
    if(other._str)
    {
        _str = other._str;
        other._str = nullptr;
    }
    _num = std::move(other._num);
    _stroka = std::move(other._stroka);
}

ComplexClass& ComplexClass::operator=(ComplexClass&& other)
{
    if(this != &other)
    {
        if(other._str)
        {
            delete [] _str;
            _str = other._str;
            other._str = nullptr;
        }
        _num = std::move(other._num);
        _stroka = std::move(other._stroka);
    }
    return *this;
}

void ComplexClass::out() const
{
    if(_str)
        std::cout << "_str = " << _str << "; " << "_num = " << _num << "; _stroka = " << _stroka << std::endl;
}
