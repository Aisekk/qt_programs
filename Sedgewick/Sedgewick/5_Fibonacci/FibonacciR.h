#ifndef FIBONACCIR_H
#define FIBONACCIR_H

int FibonacciR(int i)
{
    if(i < 1) return 0;
    if(i == 1) return 1;
    return FibonacciR(i-1) + FibonacciR(i-2);
}

//нисходящее динамическое программирование
const int maxN = 10;
int F(int i)
{
    static int knownF[maxN];
    if(knownF[i] != 0) return knownF[i];
    int t = i;
    if(i < 0) return 0;
    if(i > 1) t = F(i-1) + F(i-2);
    return knownF[i] = t;
}

#endif // FIBONACCIR_H
