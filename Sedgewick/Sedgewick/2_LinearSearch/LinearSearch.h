#ifndef LINEARSEARCH_H
#define LINEARSEARCH_H

int search(int a[], int v, int l, int r)
{
    for(int i = l; i <= r; ++i)
        if(v == a[i]) return i;
    return -1;
}

#endif // LINEARSEARCH_H
