#include <future>
#include <thread>
#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

int queryNumber()
{
    // считываем число
    cout << "read number: ";
    int num;
    cin >> num;
    // генерируем исключение, если ничего не введено
    if(!cin) throw runtime_error(" no number read");
    return num;
}

void doSomething(char c, shared_future<int> f)
{
    try{
        // получаем количество символов, подлежащих выводу
        int num = f.get(); // get result of queryNumber()
        // цикл вывода символов после случайного момента времени
        for(int i = 0; i < num; ++i)
        {
            this_thread::sleep_for(chrono::milliseconds(100));
            cout.put(c).flush();
        }
    }
    catch(const exception& e)
    {
        cerr << "EXCEPTION in thread " << this_thread::get_id() << ": " << e.what() << endl;
    }
}

int main()
{
    try{
        // запускаем поток для запроса числа
        shared_future<int> f = async(queryNumber);

        // запускаем три потока, каждый из которых обрабатывает это число в цикле
        auto f1 = async(launch::async, doSomething, '.', f);
        auto f2 = async(launch::async, doSomething, '+', f);
        auto f3 = async(launch::async, doSomething, '*', f);

        // ждем завершения всех трех циклов
        f1.get();
        f2.get();
        f3.get();
    }
    catch(const exception& e){ cout << "\nEXCEPTION: " << e.what() << endl; }

    cout << "\ndone" << endl;
    system("pause");
    return 0;
}
