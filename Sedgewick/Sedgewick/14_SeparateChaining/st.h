#ifndef ST_H
#define ST_H
#include "item.h"
#include "hashf.cpp"
//Цепочки переполнения (раздельное связывание)
//ключи - неотрицательные целые числа: 0 =< key <= M0-1
//M0 - зарезервированное (максимальное) значение ключа
//N - количество элементов в таблице, N <= M0; M - размер таблицы; M < N
//a = N/M > 1 - среднее количество элементов в одном списке
//insert: O(1) - т.к. вставка в начало списка; search: O(N/M) - линейный поиск; remove:
template<class Key, class Item>
class ST
{
private:
    Item nullitem; int (*hashF)(int,int); Value *values{};
    struct node
    {
        Item item; node *next; int cnt{};
        node(Item x, node *t, int N){ item = x; next = t; cnt = N; }
        int count(){ return cnt; }
    };
    typedef node* link; int N, M; link *heads;
    Item searchR(link t, Key v)
    {
        if(t == nullptr) return nullitem;
        if(t->item.key() == v) return t->item;
        return searchR(t->next, v);
    }
public:
    ST(int maxN, int (*hashf)(int,int))
    {
        N = 0; M = maxN/5; heads = new link[M];
        for(int i = 0; i < M; ++i) heads[i] = nullptr;
        hashF = hashf;
    }
    ~ST(){ if(values != nullptr) delete[] values; }
    int count(){ return N; }
    int size() const{ return M; }
    Item search(Key v){ return searchR(heads[hashF(v, M)], v); }

    void insert(Item x)
    { int i = hashF(x.key(), M); heads[i] = new node(x, heads[i], ++N); }
    Value* removeLastElems(int NumOfLastElems)
    {
        int N_remain = N - NumOfLastElems;
        if(N_remain < 0 || N_remain == N) return nullptr;
        if(values != nullptr) delete[] values; values = nullptr;
        values = new Value[NumOfLastElems + 1]; int k{};
        for(int i = 0; i < M; ++i)
            for(link x = heads[i], x0 = x, prev = x; x != nullptr; x = x->next)
            {
                if(x != nullptr)
                    if(x->count() > N_remain)
                    {
                        values[k++] = x->item.value();
                        if(x == x0){ x0 = x->next; heads[i] = x0; prev = x0; }
                        else{ prev->next = x->next; x = nullptr; } N--;
                    }
                if(x == nullptr) x = prev; else prev = x;
            }
        values[k] = -1;
        if(N_remain < N) return values;
        return nullptr;
    }
    void show(ostream& os = cout)
    {
        for(int i = 0; i < M; ++i)
        {
            link t = heads[i];
            if(t == nullptr){ os << "hash null: null" << endl; continue; }
            int key = t->item.key(); os << "hash " << hashF(key, M) << ": ";
            for(; t != nullptr; t = t->next)
            { t->item.showValue(os); os << "\t"; }
            os << endl;
        }
    }
    void showCounts(ostream& os = cout)
    {
        for(int i = 0; i < M; ++i)
        {
            link t = heads[i];
            if(t == nullptr){ os << "hash null: null" << endl; continue; }
            int key = t->item.key(); os << "hash " << hashF(key, M) << ": ";
            for(; t != nullptr; t = t->next)
            { t->item.showValue(os); os << "(" << t->count() << ")\t"; }
            os << endl;
        }
    }
};

#endif // ST_H
