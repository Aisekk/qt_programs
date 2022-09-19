#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H


class DoublyLinkedList
{
private:
    struct node
    {
        int val;
        node* prev;
        node* next;
        node() : val(0), prev(nullptr), next(nullptr) {}
        node(int x) : val(x), prev(nullptr), next(nullptr) {}
        node(int x, node* prev, node* next) : val(x), prev(prev), next(next) {}
    };
    node* _head = nullptr;
    node* _tail = nullptr;
public:
    DoublyLinkedList();

    size_t size() const noexcept;
    bool empty() const noexcept;

    const int& front() const;
    void push_front(const int& value);
    void pop_front();

    const int& back() const;
    void push_back(const int& value);
    void pop_back();
};

#endif // DOUBLYLINKEDLIST_H
