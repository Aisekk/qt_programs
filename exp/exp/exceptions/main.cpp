#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;
typedef bool _FILE;
// исключение: позволяет передавать управление и информацию от точки исполнения программы
// обработчику исключения, связанному с данным участком программы
struct FileError // пользовательский класс исключения
{
    int m_nCode, m_szFile, m_nLine;
    FileError(int errorCode, int __FILE, int __LINE)
        : m_nCode(errorCode), m_szFile(__FILE), m_nLine(__LINE) {}
};

_FILE *openData()
{
    _FILE *pf = nullptr;
    if(!pf)
        //throw FileError(0, 1, 2);
        throw std::system_error();
    return pf;
}
void loadData()
{
    _FILE *fp = nullptr;
    try
    {
        fp = openData();
        // ...
    }
    catch(const FileError& rcError)
    {
        cout << "Error " << rcError.m_nCode << ", file "
             << rcError.m_szFile << ", line " << rcError.m_nLine << endl;
    }
    catch(const std::exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch(...)
    {
        if(fp) *fp = true;
        cout << "catch(...): " << *fp << endl;
    }
    //
    if(fp) *fp = true;
}
//-------------------------------------------------------------------------------------------------
// правила генерирования исключений:
class BaseError
{
public:
    virtual const char* f(){ return "base"; }
};
class NewError : public BaseError
{
public:
   const char* f(){ return "new"; }
};
void process()
{
    try
    {
        NewError err;
        BaseError &rBase = err;
        throw rBase;
    }
    catch(const NewError& e){ cout << "new error" << endl; }
    catch(const BaseError& e){ cout << "base error" << endl; }
}
//-------------------------------------------------------------------------------------------------
// спецификация исключений:
struct GoodError{};
struct BadError{ void f(){ cout << " ::f " << endl; } };
void my_unexpected()
{
    cout << "my unexpected" << endl;
    throw GoodError();
}
void process_2() throw(GoodError, std::bad_exception) //, BadError)
{
    throw BadError();
}
void exception_specification()
{
    std::set_unexpected(my_unexpected);
    try
    {
        process_2();
    }
    catch(const BadError& e)
    {
        cout << "BadError catched" << endl;
        //e.f();
    }
    catch(const GoodError& e)
    {
        cout << "GoodError catched" << endl;
        //e.f();
    }
    catch(const std::exception& e)
    {
        cout << "std::bad_exception: " << e.what() << endl;
    }
}
//-------------------------------------------------------------------------------------------------
// повторная генерация исключений:
struct UncaughtError{};
struct SomeError
{
    SomeError(){}
    SomeError(const SomeError&){ throw UncaughtError(); }
};
struct Data
{
    ~Data(){ throw UncaughtError(); }
};
void process_3()
{
    try
    {
        //Data d;
        //throw SomeError();
        cout << "uncaught exception: " << std::uncaught_exception() << endl;
    }
    catch(SomeError)
    { }
    catch(const UncaughtError&)
    {
        cout << "UncaughtError catched in process" << endl;
    }
    //cout << std::uncaught_exception() << endl;
}
void try_catch_UncaughtError()
{
    try
    {
        process_3();
        //cout << std::uncaught_exception() << endl;
    }
    catch(const UncaughtError&)
    {
        cout << "UncaughtError catched" << endl;
    }
}
//-------------------------------------------------------------------------------------------------
// вложенные исключения С++11:
void f1()
{
    throw std::runtime_error("f1()");
}
void f2()
{
    try
    {
        f1();
    }
    catch(...)
    {
        std::throw_with_nested(std::runtime_error("f2()"));
    }// nested_exception
}// runtime_error
void f3()
{
    try
    {
        f2();
    }
    catch(...)
    {
        std::throw_with_nested(std::runtime_error("f3()"));
    }
}
void print(const std::exception& rcException)
{
    std::cerr << "Exception: " << rcException.what() << endl;
    try
    {
        std::rethrow_if_nested(rcException);
    }
    catch(const std::exception& rcSubException)
    {
        print(rcSubException);
    }
}
void nested()
{
    try
    {
        f3();
    }
    catch(const std::exception& rcSubException)
    {
        print(rcSubException);
    }
}
//-------------------------------------------------------------------------------------------------
int main()
{
    loadData();
    process();
    exception_specification();
    //std::terminate();
    try_catch_UncaughtError();
    nested();

    return 0;
}
