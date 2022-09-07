#ifndef GCD_H
#define GCD_H
//GCD(a,b) = GCD(b, a Mod b)

int GCD(int a, int b)
{
    while(b != 0)
    {
        //вычисляем остаток
        int r = a % b;
        //находим НОД для n и остатка
        a = b;
        b = r;
    }
    //НОД для m и 0 - это m
    return a;
}

int GCDR(int a, int b)
{
    if(b == 0) return a;
    return GCDR(b, a % b);
}

#endif // GCD_H
