#include <future>
#include <list>
#include <iostream>
#include <exception>
using namespace std;

void task1()
{
    //бесконечная вставка и выделение памяти
    //-рано или поздно это приведет к исключению; плохая практика
    list<int> v;
    while(true)
    {
        for(int i = 0; i < 1000000; ++i) v.push_back(i);
        cout.put('.').flush();
    }
}

int main()
{
    cout << "starting two tasks" << endl;
    cout << "-task1: process endless loop of memory consumption" << endl;
    cout << "-task2: wait for <return> and then for task1" << endl;

    auto f1 = async(task1);

    cin.get();//вводим символ как getchar()

    cout << "\nwait for the end of task1: " << endl;
    try{ f1.get(); /* ожидаем завершения task1() или исключения */ }
    catch(const exception& e){ cerr << "EXCEPTION: " << e.what() << endl;}

    system("pause");
    return 0;
}
