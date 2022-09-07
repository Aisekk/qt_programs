#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>
using namespace std;

int doSomething(char c)
{
    //генератор случайных чисел
    //(значение с используется для генерирования разных последовательностей)
    std::default_random_engine dre(c);
    std::uniform_int_distribution<int> id(10,1000);

    //цикл вывода символов после случайного момента времени
    for(int i = 0; i < 10; ++i)
    {
        this_thread::sleep_for(chrono::milliseconds(id(dre)));
        cout.put(c).flush();
    }
    return c;
}
int main()
{
    cout << "starting two operations asynchronously " << endl;
    //начинаем два цикла на фоне для выводы символа . или +
    future<void> f1 = async([]{ doSomething('.'); });
    future<void> f2 = async([]{ doSomething('+'); });

    //если хотя бы одна из фоновых задач выполняется
    if(f1.wait_for(chrono::seconds(0)) != future_status::deferred ||
            f2.wait_for(chrono::seconds(0)) != future_status::deferred)
    {
        //опрашиваем, не выполнен ли хотя бы один цикл
        while(f1.wait_for(chrono::seconds(0)) != future_status::ready &&
            f2.wait_for(chrono::seconds(0)) != future_status::ready)
        {
            //...
            this_thread::yield();//подсказка изменить расписание для следующего потока
        }
    }
    cout.put('\n').flush();

    //ожидаем, пока не будут завершены все циклы, и обрабатываем все исключения
    try{ f1.get(); f2.get(); }
    catch(const exception& e){ cout << "\nEXCEPTION: " << e.what() << endl; }
    cout << "\ndone" << endl;

    system("pause");
    return 0;
}
