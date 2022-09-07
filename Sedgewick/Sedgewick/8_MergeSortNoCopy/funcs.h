#ifndef FUNCS_H
#define FUNCS_H

template <class Item>
void exch(Item& A, Item& B){ Item t = A; A = B; B = t; }

template <class Item>
void compexch(Item& A, Item& B){ if(B < A) exch(A,B); }

//сортировка вставками
template <class Item>
void insertion(Item a[], int l, int r)
{
    int i;
    for(i = r; i > l; i--) compexch(a[i-1], a[i]);
    for(i = l+2; i <= r; i++)
    {
        int j = i; Item v = a[i];
        while(v < a[j-1])
        { a[j] = a[j-1]; j--; }
        a[j] = v;
    }
}


#endif // FUNCS_H
