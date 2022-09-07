#include "mystring.h"

String::String()
{
    buffer = new char[1];
    strcpy(buffer, "");
}
String::String(const char* input)
{
    if(input != nullptr)
    {
        buffer = new char[strlen(input) + 1];
        strcpy(buffer, input);
    } else buffer = nullptr;
}
String::String(std::initializer_list<char> vals)
{
    if(vals.size() == 0)
    {
        buffer = new char[1];
        strcpy(buffer, "");
    }
    else
    {
        size_t sz = vals.size() + 1;
        buffer = new char[sz];
        size_t idx = 0;
        for(auto it = vals.begin(); it != vals.end(); ++it, ++idx)
            buffer[idx] = *it;
        buffer[++idx] = '\0';
        cout << "std::initializer_list<char> vals.size() = " << vals.size() << endl;
    }
}

String::~String()
{
    //cout << "MyString " << buffer << " destroyed. " << endl;
    if(buffer != nullptr) delete[] buffer;
}

String::String(const String& copy)
{
    if(copy.buffer != nullptr)
    {
        //создание собственного буфера
        buffer = new char[strlen(copy.buffer) + 1];
        //копирование из оригинала в локальный буфер
        strcpy(buffer, copy.buffer);
    } else buffer = nullptr;
}
String& String::operator= (const String& copy)
{
    if(this != &copy && copy.buffer != nullptr)
    {
        if(buffer != nullptr) delete[] buffer;
        //создание собственного буфера
        buffer = new char[strlen(copy.buffer) + 1];
        //копирование из оригинала в локальный буфер
        strcpy(buffer, copy.buffer);
    }
    return *this;
}
String::String(String &&movesrc)
{
    if(movesrc.buffer != nullptr)
    {
        buffer = movesrc.buffer;
        movesrc.buffer = nullptr;
    }
}
String& String::operator = (String&& movesrc)
{
    if((movesrc.buffer != nullptr) && (&movesrc != this))
    {
        delete buffer;
        buffer = movesrc.buffer;
        movesrc.buffer = nullptr;
    }
    return *this;
}

const char& String::operator[](int idx) const{ if(idx < getLength()) return buffer[idx]; }
String::operator const char*(){ return buffer; }
String String::operator + (const String& addString)
{
    String NewString;
    if(addString.buffer != nullptr)
    {
        NewString.buffer = new char[getLength() + strlen(addString.buffer) + 1];
        strcpy(NewString.buffer, buffer);
        strcat(NewString.buffer, addString.buffer);
    }
    return NewString;
}

int String::getLength() const{ return strlen(buffer); }
const char* String::getString() const{ return buffer; }

//-------------------------------------------------------------------------------------------------
ostream& operator << (ostream& os, const String& str)
{
    os << str.getString();
    return os;
}
//-------------------------------------------------------------------------------------------------
