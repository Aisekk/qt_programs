#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <iostream>

void do_work(unsigned id)
{
    std::cout << id << " [" << std::this_thread::get_id() << "] ";// << std::rand() % 10;
    //std::this_thread::sleep_for(std::chrono::milliseconds(200-id*10));
}

void f()
{
    std::cout << std::thread::hardware_concurrency() << std::endl;
    std::vector<std::thread> threads;
    for(unsigned i=0;i<40;++i)
    {
        threads.push_back(std::thread(do_work,i));
    }
    std::for_each(threads.begin(),threads.end(),
        std::mem_fn(&std::thread::join));
}

int main()
{
    f();
    std::cout << '\n';
}
