#include <stdlib.h>
#include "list.h"

link freelist;
link firstElem;
void construct(int N)
{
    freelist = new node[N+1];
    firstElem = freelist;
    for(int i = 0; i < N; i++)
        freelist[i].next = &freelist[i+1];
    freelist[N].next = nullptr;
}
link newNode(int i)
{
    link x = remove(freelist);
    x->item = i; x->next = x;
    return x;
}
void deleteNode(link x)
{ insert(freelist, x); }
void insert(link x, link t)
{ t->next = x->next; x->next = t; }
link remove(link x)
{ link t = x->next; x->next = t->next; return t; }
link next(link x)
{ return x->next; }
Item item(link x)
{ return x->item; }

link first()
{
    return firstElem;
}
int count(link x)
{
    if(x == nullptr) return 0;
    return (1 + count(x->next));
}
