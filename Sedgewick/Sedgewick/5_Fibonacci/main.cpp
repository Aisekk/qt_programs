#include <iostream>
#include "FibonacciR.h"
using namespace std;
//Раздел 5.3, Глава 5. Рекурсия и деревья

int main()
{
    cout << "Compute Fibonacci number of index (< 10): ";
    int N = 1;
    cin >> N;
    //---------------------------------------------------------------------------------------------
    //число Фибоначчи (итерация): O(N) ~ N
    int *f = new int[N];
    f[0] = 0; f[1] = 1;
    for(int i = 2; i <= N; i++)
        f[i] = f[i-1] + f[i-2];
    cout << "Fibonacci number of index " << N << "(iteration): " << f[N] << endl;
    //---------------------------------------------------------------------------------------------
    //число Фибоначчи (рекурсия): O(N) ~ exp(N)
    int fR = FibonacciR(N);
    cout << "Fibonacci number of index " << N << " (recursion) : " << fR << endl;
    //---------------------------------------------------------------------------------------------
    //нисходящее динамическое программирование: O(N) ~ N
    int fD = F(N);
    cout << "Fibonacci number of index " << N << " (top-down dynamic programming) : " << fD << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
