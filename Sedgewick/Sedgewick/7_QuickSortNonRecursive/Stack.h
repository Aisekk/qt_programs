#ifndef STACK_H
#define STACK_H

template <class Item>
class Stack
{
    Item *s; int N;
public:
    Stack(int maxN)
    { s = new Item[maxN]; N = 0; }
    int empty() const{ return N == 0; }
    void push(Item item){ s[N++] = item; }
    Item pop(){ return s[--N]; }
};

#endif // STACK_H
