#include <iostream>
#include <tuple>
#include <string>
#include <complex>
using namespace std;

int main()
{
    tuple<string,int,int,complex<double>> t;
    tuple<int,float,string> t1(41,6.3,"nico");
    //проходим по элементам
    cout << get<0>(t1) << " ";
    cout << get<1>(t1) << " ";
    cout << get<2>(t1) << " ";
    cout << endl;

    auto t2 = make_tuple(22,44,"nico");
    //присваиваем второе значение кортежа t2 кортежу t1
    get<1>(t1) = get<1>(t2);

    cout << get<0>(t1) << " ";
    cout << get<1>(t1) << " ";
    cout << get<2>(t1) << " ";
    cout << endl;

    //сравнение и присвоение
    //включая преобразование типа из tuple<int,int,const char*>
    //в tuple<int,float,string>
    if(t1 < t2) t1 = t2;

    cout << get<0>(t1) << " ";
    cout << get<1>(t1) << " ";
    cout << get<2>(t1) << " ";
    cout << endl;

    system("pause");
    return 0;
}
