#ifndef ST_H
#define ST_H
#include "item.h"
//BST - cтандартное дерево бинарного поиска
//ключи - неотрицательные целые числа: 0 =< key <= M-1
//M - зарезервированное (максимальное) значение ключа
//N - количество элементов в таблице, N <= M
template<class Key, class Item>
class ST
{
private:
    struct node
    {
        Item item; node *l, *r;
        node(Item x){ item = x; l = nullptr; r = nullptr; }
    };
    typedef node* link;
    link head; Item nullitem; int N;
    Item searchR(link h, Key v)
    {
        if(h == nullptr) return nullitem;
        Key t = h->item.key();
        if(v == t) return h->item;
        if(v < t) return searchR(h->l, v);
        else return searchR(h->r, v);
    }
    void insertR(link& h, Item x)
    {
        //аргумент ссылки изменяется в последнем рекурсивном вызове
        if(h == nullptr){ h = new node(x); return; }
        if(x.key() < h->item.key()) insertR(h->l, x);
        else insertR(h->r, x);
    }
    void showR(link h, ostream& os)
    {
        //поперечный обход дерева дает отсортированный массив
        if(h == nullptr) return;
        showR(h->l, os);//отображаем элементы в левом поддереве
        h->item.show(os);//отображаем элемент в корне
        showR(h->r, os);//отображаем элементы в правом поддереве
    }
public:
    //построение BST-дерева вставками сводится к сортировке элементов
    ST(){ head = nullptr; N = 0; }
    Item search(Key v){ return searchR(head, v); }
    int count() const{ return N; }

    void insert(Item x){ insertR(head, x); N++; }
    //нерекурсивная вставка
    void insertNonR(Item x)
    {
        Key v = x.key();
        if(head == nullptr){ head = new node(x); return; }
        link p = head;
        //необходимо отслеживание родительского узла p при перемещении вниз по дереву
        for(link q = p; q != nullptr; p = q ? q : p)
            q = (v < q->item.key()) ? q->l : q->r;
        if(v < p->item.key()) p->l = new node(x);
        else p->r = new node(x);
    }
    //вывод в отсортированном виде
    void show(ostream& os = cout){ showR(head, os); }
};

#endif // ST_H
