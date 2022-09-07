#ifndef ST_H
#define ST_H
#include "item.h"
//BST - cтандартное дерево бинарного поиска, более полный набор функций
//ключи - неотрицательные целые числа: 0 =< key <= M-1
//M - зарезервированное (максимальное) значение ключа
//N - количество элементов в таблице, N <= M
//search: = 1.39lgN в среднем, ~ N в худшем;
//insert: = 1.39lgN в среднем, ~ N в худшем;
//join: ~ N в худшем случае;
//balance() ~ N => повторную балансировку крупных деревьев нежелательно выполнять слишком часто
template<class Key, class Item>
class ST
{
private:
    struct node
    {
        Item item; node *l, *r; int N;
        node(Item x){ item = x; l = nullptr; r = nullptr; N = 1; }
        void upd()
        {
            if(l != nullptr && r != nullptr) N = 1 + l->N + r->N;
            else if(l != nullptr && r == nullptr) N = 1 + l->N;
            else if(l == nullptr && r != nullptr) N = 1 + r->N;
            else if(l == nullptr && r == nullptr) N = 1;
        }
    };
    typedef node* link;
    link head; Item nullitem;
    Item searchR(link h, Key v)
    {
        if(h == nullptr) return nullitem;
        Key t = h->item.key();
        if(v == t) return h->item;
        if(v < t) return searchR(h->l, v);
        else return searchR(h->r, v);
    }
    Item selectR(link h, int k)
    {
        if(h == nullptr) return nullitem;
        int t = (h->l == nullptr) ? 0 : h->l->N;
        if(t > k) return selectR(h->l, k);
        if(t < k) return selectR(h->r, k-t-1);
        return h->item;
    }
    link joinR(link a, link b)
    {
        if(b == nullptr) return a;
        if(a == nullptr) return b;
        insertT(b, a->item);
        b->l = joinR(a->l, b->l);
        b->r = joinR(a->r, b->r);
        delete a; b->upd(); return b;
    }
    link joinLR(link a, link b)
    { if(b == nullptr) return a; partR(b, 0); b->l = a; b->upd(); return b; }

    void insertR(link& h, Item x)
    {
        //аргумент ссылки изменяется в последнем рекурсивном вызове
        if(h == nullptr){ h = new node(x); return; }
        if(x.key() < h->item.key()) insertR(h->l, x);
        else insertR(h->r, x);
        h->N++;
    }
    void insertT(link& h, Item x)
    {
        if(h == nullptr){ h = new node(x); return; }
        if(x.key() < h->item.key()){ insertT(h->l, x); rotR(h); }
        else{ insertT(h->r, x); rotL(h); }
        h->N++;
    }
    void showR(link h, ostream& os)
    {
        //поперечный обход дерева дает отсортированный массив
        if(h == nullptr) return;
        showR(h->l, os);//отображаем элементы в левом поддереве
        h->item.show(os);//отображаем элемент в корне
        showR(h->r, os);//отображаем элементы в правом поддереве
    }  
    void partR(link& h, int k)
    {
        int t = (h->l == nullptr) ? 0 : h->l->N;
        if(t > k){ partR(h->l, k); rotR(h); }
        if(t < k){ partR(h->r, k-t-1); rotL(h); }
    }
    void removeR(link& h, Key v)
    {
        if(h == nullptr) return;
        Key w = h->item.key();
        if(v < w) { removeR(h->l, v); h->l->upd(); }
        if(w < v) { removeR(h->r, v); h->r->upd(); }
        if(v == w){ link t = h; h = joinLR(h->l, h->r); delete t; }
    }
    void balanceR(link& h)
    {
        if((h == nullptr) || (h->N == 1)) return;
        partR(h, h->N/2);
        balanceR(h->l);
        balanceR(h->r);
    }
    void rotR(link& h){ link x = h->l; h->l = x->r; x->r = h; x->r->upd(); h = x; h->upd(); }
    void rotL(link& h){ link x = h->r; h->r = x->l; x->l = h; x->l->upd(); h = x; h->upd(); }
public:
    ST(){ head = nullptr; }
    Item search(Key v){ return searchR(head, v); }
    Item select(int k){ return selectR(head, k); }
    int count() const{ return head->N; }

    void insertStd(Item x){ insertR(head, x); head->upd(); }
    void insert(Item x){ insertT(head, x); head->upd(); }//вставка в корень
    void remove(Item x){ removeR(head, x.key()); head->upd(); }
    void join(ST<Key, Item>& b){ head = joinR(head, b.head); }
    void balance(){ balanceR(head); }
    //вывод в отсортированном виде
    void show(ostream& os = cout){ showR(head, os); }
};

#endif // ST_H
