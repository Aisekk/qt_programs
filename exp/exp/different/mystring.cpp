#include "mystring.h"


String::String(const char* str) // : _str((char *) std::calloc(1 + std::strlen(str), sizeof (char)))
{
    if(str != nullptr)
    {
        _str = new char[std::strlen(str) + 1] ;
        std::strcpy(_str, str);
    }
}

String::String(const String& other)
{
    if (other._str != nullptr)
    {
        //_str = (char*)std::calloc(1 + std::strlen(other._str), sizeof(char));
        _str = new char[std::strlen(other._str) + 1];
        std::strcpy(_str, other._str);
    }
    else
    {
        _str = nullptr;
    }
}

String& String::operator = (const String& other)
{
    if (this != &other && other._str != nullptr)
    {
        if(_str != nullptr)
        {
            delete [] _str;
            //std::free(_str);
        }
        //_str = (char*)std::calloc(1 + std::strlen(other._str), sizeof(char));
        _str = new char[std::strlen(other._str) + 1];
        std::strcpy(_str, other._str);
    }
    return *this;
}

String::String(String&& other)
{
    if(other._str)
    {
        _str = other._str;
        other._str = nullptr;
    }
}

String& String::operator = (String&& other)
{
    if(other._str && this != &other)
    {
        delete [] _str;
        _str = other._str;
        other._str = nullptr;
    }
    return *this;
}

String::~String()
{
    if(_str)
    {
        delete _str;
        //std::free(_str);
    }
}

String::operator const char*() const
{
    return _str;
}
