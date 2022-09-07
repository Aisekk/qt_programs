#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

int main()
{
    shared_ptr<string> spNico(new string("nico"),
                              [](string *p){ cout << "delete: " << *p << endl; delete p; });
    shared_ptr<string> spJutta(new string("jutta"));

    (*spNico)[0] = 'N';
    spJutta->replace(0,1,"J");

    vector<shared_ptr<string>> whoMadeCoffee;
    whoMadeCoffee.push_back(spJutta);
    whoMadeCoffee.push_back(spJutta);
    whoMadeCoffee.push_back(spNico);
    whoMadeCoffee.push_back(spJutta);
    whoMadeCoffee.push_back(spNico);

    for(auto sp : whoMadeCoffee)
        cout << *sp << " ";
    cout << endl;

    *spNico = "Nicolai";

    for(auto sp : whoMadeCoffee)
        cout << *sp << " ";
    cout << endl;

    //выводим внутренние данные
    cout << "use_count: " << whoMadeCoffee[0].use_count() << endl;

    spNico = nullptr;
    whoMadeCoffee.resize(2);

    cout << endl;
    unique_ptr<string> upPiter(new string("Piter"));
    cout << "size of shared_ptr: " << sizeof(spJutta) << endl;
    cout << "size of unique_ptr: " << sizeof(upPiter) << endl;
    cout << "size of shared_ptr::get(): " << sizeof(spJutta.get()) << endl;
    cout << "size of unique_ptr::get(): " << sizeof(upPiter.get()) << endl;

    system("pause");
    return 0;
}
