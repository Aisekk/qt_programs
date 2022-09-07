#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>
using namespace std;

void doSomething(int num, char c)
{
    try{
        //генератор случайных чисел
        //(значение с используется для генерирования разных последовательностей)
        std::default_random_engine dre(42*c);
        std::uniform_int_distribution<int> id(10,1000);
        //цикл вывода символов после случайного момента времени
        for(int i = 0; i < num; ++i)
        {
            this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
            cout.put(c).flush();
        }
    }
    catch(const exception& e){
        cerr << "THREAD-EXCEPTION (thread "
             << this_thread::get_id() << "): " << e.what() << endl;
    }
    catch(...){
        cerr << "THREAD-EXCEPTION (thread "
             << this_thread::get_id() << ")" << endl;
    }
}

int main()
{
    try{
        thread t1(doSomething,5,'.');//выводим пять точек в отдельном потоке
        cout << "-started fg thread " << t1.get_id() << endl;

        //выводим другие символы в других фоновых потоках
        for(int i = 0; i < 5; ++i){
            thread t(doSomething,10,'a'+i);//выводим 10 символов в отдельном потоке
            cout << "-detach started bg thread " << t.get_id() << endl;
            t.detach();// отсоединяем поток в фоновый режим
        }
        cin.get();//ожидаем любого ввода (возвращения)
        cout << "- join fg thread " << t1.get_id() << endl;
        t1.join();//ждать завершения t1
    }
    catch(const exception& e){ cerr << "EXCEPTION: " << e.what() << endl; }

    //system("pause");
    return 0;
}
