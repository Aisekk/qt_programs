#ifndef ST_H
#define ST_H
#include "item.h"
//линейный поиск
//неупорядоченная таблица символов на основе свзанного списка
//ключи - неотрицательные целые числа: 0 =< key <= M-1
//M - зарезервированное (максимальное) значение ключа
//N - количество элементов в таблице, N <= M
//insert, search ~ N, remove:
//initialize, select, sort:
template<class Key, class Item>
class ST
{
private:
    Item nullitem;
    struct node
    {
        Item item; node *next;
        node(Item x, node *t)
        { item = x; next = t; }
    };
    typedef node* link;
    int N;
    link head;
    Item searchR(link t, Key v)
    {
        if(t == nullptr) return nullitem;
        if(t->item.key() == v) return t->item;
        return searchR(t->next, v);
    }

public:
    ST(){ head = nullptr; N = 0; }
    int count(){ return N; }
    Item search(Key v){ return searchR(head, v); }

    void insert(Item x){ head = new node(x, head); N++; }
    void show(ostream& os = cout)
    { for(link t = head; t != nullptr; t = t->next) t->item.show(os); }
};

#endif // ST_H
