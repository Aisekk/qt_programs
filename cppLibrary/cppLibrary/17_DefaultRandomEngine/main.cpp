#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    //создаем генератор случайных чисел по умолчанию
    default_random_engine dre;

    //используем генератор для порождения целых чисел
    //в интервале от 10 до 20 (включая оба числа)
    uniform_int_distribution<int> di(10,20);
    for(int i = 0; i < 20; ++i) cout << di(dre) << " ";
    cout << endl;

    //используем генератор для порождения чисел с плавающей точкой
    //в интервале от 10.0 до 20.0 (включая 10.0 и исключая 20.0)
    uniform_real_distribution<double> dr(10,20);
    for(size_t i = 0; i < 8; ++i) cout << dr(dre) << " ";
    cout << endl;

    //используем генератор для перетасовки элементов
    vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    shuffle(v.begin(), v.end(), dre);
    for(size_t i = 0; i < v.size(); ++i) cout << v[i] << " ";
    cout << endl;

    system("pause");
    return 0;
}
