#ifndef ITEM_H
#define ITEM_H
#include <iostream>
using namespace std;

static int maxKey = 1000;
typedef int Key;
typedef float Value;
class Item
{
    Key keyval;
    float val{-1};
public:
    Item(){ keyval = maxKey; }
    Key key() const{ return keyval; }
    int null() const{ return keyval == maxKey; }
    Value value() const{ return val; }
    void init(int key){ keyval = key; val = key*2.0; }
    void rand(){ keyval = 100*(::rand()/RAND_MAX); val = 1000.0*::rand()/RAND_MAX; }
    void show(ostream& os = cout){ os << keyval << "\t" << val; }
    void showValue(ostream& os = cout)
    { if(val == -1){ os << " null"; return; } os << " " << val; }
};
ostream& operator<<(ostream& os, Item& x){ x.show(os); return os; }

#endif // ITEM_H
