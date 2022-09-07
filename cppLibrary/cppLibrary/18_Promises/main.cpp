#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <functional>
#include <utility>
using namespace std;

void doSomething(std::promise<string>& p)
{
    try{
        //вводим символ и генерируем исключение, если символ равен 'x'
        cout << "read char ('x' for exception): ";
        char c = cin.get();
        if(c == 'x'){ throw std::runtime_error(string("char ") + c + " read"); }
        string s = string("char ") + c + " processed";
        p.set_value(std::move(s));//сохраняем результат
    }
    catch(...){ p.set_exception(std::current_exception()); /* сохраняем исключение */}
}

int main()
{
    try{
        //запускаем поток, используя обещание для хранения результата
        std::promise<string> p;
        thread t(doSomething, std::ref(p));//выводим пять точек в отдельном потоке
        t.detach();

        //создаем фьючерс для обработки результата
        future<string> f(p.get_future());

        //обрабатываем результат
        cout << "result: " << f.get() << endl;
    }
    catch(const exception& e){ cerr << "EXCEPTION: " << e.what() << endl; }
    catch(...){ cerr << "EXCEPTION " << endl; }

    system("pause");
    return 0;
}
