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
int func1(){ return doSomething('.'); }
int func2(){ return doSomething('+'); }

int main()
{
    cout << "starting func1() in background" << " and func2() in foreground: " << endl;
    //начинаем асинхронное выполнение func1() (сейчас, позднее или никогда)
    std::future<int> result1(std::async(func1));
    int result2 = func2(); //вызываем функцию func2() синхронно (здесь и сейчас)

    //выводим результат (ждем завершения функции func1() и добавляем ее результат
    //к переменной result2
    int result = result1.get() + result2;
    cout << "\nresult of func1()+func2() = " << result << endl;

    system("pause");
    return 0;
}
