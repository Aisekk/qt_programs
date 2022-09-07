#ifndef FACTORIALR_H
#define FACTORIALR_H

int factorialR(int N)
{
    if(N == 0) return 1;
    return N*factorialR(N-1);
}

#endif // FACTORIALR_H
