#ifndef ST_H
#define ST_H
#include "item.h"
//Красно-черное BST-дерево без дубликатов (дубликаты приведут к серьезному дисбалансу)
/* это нисходящее 2-3-4-дерево, в котором каждый узел помечен как красный(R) либо черный(B),
 * с наложением дополнительного ограничения, чо никакие два красных узла не могут появляться
 * друг за другом в любом пути от внешней связи к корню. */
//Ключи - неотрицательные целые числа: 0 =< key <= M-1
//M - зарезервированное (максимальное) значение ключа
//N - количество элементов в таблице, N <= M
//search: = 1.002log_2(N) в среднем, ~ 2log_2(N)+2 - в худшем;
//insert: = 1.002log_2(N) в среднем, ~ 2log_2(N)+2 - в худшем;
//join: ~ N в худшем случае; balance() ~ N
template<class Key, class Item>
class ST
{
private:
    struct node
    {
        Item item; node *l, *r; int N; int red; //0 - black, 1 - red
        node(Item x){ item = x; l = nullptr; r = nullptr; N = 1; red = 1; }
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

    int red(link x){ if(x == nullptr) return 0; return x->red; }
    void RBinsert(link& h, Item x, int sw)
    {
        //аргумент ссылки изменяется в последнем рекурсивном вызове
        if(h == nullptr){ h = new node(x); return; }
        //проверка наличия 4-узла по пути вниз и его разбиение при наличии
        if(red(h->l) && red(h->r)){ h->red = 1; h->l->red = 0; h->r->red = 0; }
        if(x.key() < h->item.key())
        {
            RBinsert(h->l, x, 0);
            h->N++;
            //две R-связи с различными ориентациями (ротация от нижнего узла):
            if(red(h) && red(h->l) && sw) rotR(h);
            //две R-связи с одинаковой ориентацией (ротация от верхнего узла):
            if(red(h->l) && red(h->l->l)){ rotR(h); h->red = 0; h->r->red = 1; }
        }
        else
        {
            RBinsert(h->r, x, 1);
            h->N++;
            //две R-связи с различными ориентациями (ротация от нижнего узла):
            if(red(h) && red(h->r) && !sw) rotL(h);
            //две R-связи с одинаковой ориентацией (ротация от верхнего узла):
            if(red(h->r) && red(h->r->r)){ rotL(h); h->red = 0; h->l->red = 1; }
        }
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
    void showR_TopDown(link h, ostream& os)
    {
        //прямой обход дерева сверху вних
        if(h == nullptr) return;
        h->item.show(os);//отображаем элемент в корне
        link t = h;
        t = h->l; t->item.show(os);
        t = h->r; t->item.show(os);
        link u{};
        t = h->l;
        int sw = 0;
        for(;t != nullptr; )
        {
            if(sw == 0) { u = t; t = t->l; sw = 1; t->item.show(os); t = u; }
            else { t = u->r; sw = 0; t->item.show(os); }
        }
        //link l = h->l; link r = h->r;
        //showR_TopDown(h->l, os, sw);
        //showR_TopDown(h->r, os, sw);

        //showR_TopDown(l, os, sw);//отображаем элемент в левом поддереве
        //showR_TopDown(r, os);//отображаем элемент в правом поддереве
    }
    void sumOfKeysR(link h, Key& sum)
    {
        if(h == nullptr) return;
        sumOfKeysR(h->l, sum);//суммируем элементы в левом поддереве
        sum += h->item.key();//суммируем элемент в корне
        sumOfKeysR(h->r, sum);//суммируем элементы в правом поддереве
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

    void insertStd(Item x){ RBinsert(head, x, 0); head->red = 0; head->upd(); }
    void insert(Item x){ RBinsert(head, x, 0); head->red = 0; head->upd(); }
    void remove(Item x){ removeR(head, x.key()); head->upd(); }
    void join(ST<Key, Item>& b){ head = joinR(head, b.head); }
    void balance(){ balanceR(head); }
    //вывод в отсортированном виде (обход слева направо)
    void show(ostream& os = cout){ showR(head, os); }
    //обход сверху вниз
    void showTopDown(ostream& os = cout){ showR_TopDown(head, os); }
    //суммирование всех ключей
    void sumOfKeys(ostream& os = cout){ int sum = 0; sumOfKeysR(head, sum); os << "Sum of all keys: " << sum << endl; }
};

#endif // ST_H
