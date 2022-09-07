#ifndef ITEM_H
#define ITEM_H
#include <iostream>
using namespace std;

static int maxKey = 0;
typedef int Key;
class Item
{
    Key keyval;
    float info{-1};
public:
    Item(){ keyval = maxKey; }
    Key key(){ return keyval; }
    int null(){ return keyval == maxKey; }

    void init(int key){ keyval = key; info = key*2.0; }
    void rand(){ keyval = 100*(::rand()/RAND_MAX); info = 1000.0*::rand()/RAND_MAX; }
    void show(ostream& os = cout){ os << keyval << "\t" << info; }
    void showValue(ostream& os = cout)
    { if(info == -1){ os << "null"; return; } os << " " << info; }
};
ostream& operator<<(ostream& os, Item& x){ x.show(os); return os; }

#endif // ITEM_H
