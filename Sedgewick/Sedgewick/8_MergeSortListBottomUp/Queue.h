#ifndef QUEUE_H
#define QUEUE_H

template <class Item>
class QUEUE
{
private:
    struct node
    {
        Item item; node *next;
        node(Item x)
        { item = x; next = nullptr;}
    };
    typedef node* link;
    link head, tail;
public:
    QUEUE(int)
    { head = nullptr; }

    int empty() const
    { return head == nullptr; }

    void put(Item x)
    {
        link t = tail;
        tail = new node(x);
        if(head == nullptr)
            head = tail;
        else t->next = tail;
    }

    Item get()
    {
        Item v = head->item;
        link t = head->next;
        delete head; head = t; return v;
    }
};

#endif // QUEUE_H
