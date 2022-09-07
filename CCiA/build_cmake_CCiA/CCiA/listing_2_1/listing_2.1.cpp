#include <thread>
#include <iostream>

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
        std::cout << "i = " << i << "";
        for(unsigned j=0;j<1000000;++j)
        {
            do_something(i);
        }
        std::cout << "i = " << i << std::endl;
    }
};


void oops()
{
    int some_local_state=0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}

int main()
{
    oops();
    std::cout << " | " << std::endl;
    return 0;
}
