#include <thread>
#include <iostream>
#include <string>
#include <algorithm>

class thread_guard
{
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_):
        t(t_)
    {}
    ~thread_guard()
    {
        if(t.joinable())
        {
            t.join();
        }
    }
    thread_guard(thread_guard const&)=delete;
    thread_guard& operator=(thread_guard const&)=delete;
};

void do_something(int& i)
{
    ++i;
}

struct func
{
    int& i;

    func(int& i_):i(i_){}

    void operator()()
    {
        for(unsigned j=0;j<1000000;++j)
        {
            do_something(i);
        }
    }
};

void invert_string(std::string& s);
void do_something_in_current_thread()
{
    //int *pn = nullptr;
    //*pn = 1;
    //std::cout << *pn << std::endl;
    const char* cstr = "abcdef";
    std::string stroka(cstr);
    std::cout << stroka << std::endl;
    invert_string(stroka);
    std::cout << stroka << std::endl;
}

void invert_string(std::string& s)
{
    std::size_t len = s.size();
    for(int i = 0; i < len/2; ++i)
    {
        std::swap(s[i], s[len-i-1]);
    }
}

void f()
{
    int some_local_state;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);
        
    do_something_in_current_thread();
}

int main()
{
    f();
}
