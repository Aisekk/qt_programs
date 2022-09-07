#ifndef LIST_H
#define LIST_H

typedef int Item;
struct node{ Item item; node *next; };
typedef node* link;
typedef link Node;

void construct(int);
Node newNode(int);
void deleteNode(link);
void insert(link, link);
Node remove(link);
Node next(link);
Item item(link);

link first();
int count(link x);


#endif // LIST_H
