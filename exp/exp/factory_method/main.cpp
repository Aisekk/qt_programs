#include <iostream>
#include <string>
using namespace std;

struct Product
{
    virtual string getName() = 0;
    virtual ~Product(){}
};

struct ConcreteProductA: Product
{
    string getName(){return "ConcreteProductA";}
};

struct ConcreteProductB: Product
{
    string getName(){return "ConcreteProductB";}
};

struct Creator
{
    virtual Product* factoryMethod() = 0;
};

struct ConcreteCreatorA: Creator
{
    Product* factoryMethod(){return new ConcreteProductA();}
};

struct ConcreteCreatorB: Creator
{
    Product* factoryMethod(){return new ConcreteProductB();}
};


int main()
{
    ConcreteCreatorA CreatorA;
    ConcreteCreatorB CreatorB;
    // An array of creators
    Creator* creators[] = {&CreatorA, &CreatorB};
    // Iterate over creators and create products
    for(auto&& creator: creators){
        Product* product = creator->factoryMethod();
        cout << product->getName() << endl;
        delete product;
    }
    return 0;
}
