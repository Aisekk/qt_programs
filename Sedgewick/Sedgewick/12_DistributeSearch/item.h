#ifndef ITEM_H
#define ITEM_H
#include <iostream>
using namespace std;

static int maxKey = 1000;
typedef int Key;
class Item
{
    Key keyval;
    float info;
public:
    Item(){ keyval = maxKey; }
    Key key(){ return keyval; }
    int null(){ return keyval == maxKey; }
    void init(int i){ keyval = i; info = i*2.0; }
    void rand(){ keyval = 100*(::rand()/RAND_MAX); info = 1000.0*::rand()/RAND_MAX; }
    //int scan(istream& is = cin){ return (is >>  keyval >> info) != 0; }
    void show(ostream& os = cout){ os << keyval << " " << info << endl; }
    void showValue(ostream& os = cout){ os << " " << info << endl; }
};
ostream& operator<<(ostream& os, Item& x){ x.show(os); return os; }

#endif // ITEM_H
