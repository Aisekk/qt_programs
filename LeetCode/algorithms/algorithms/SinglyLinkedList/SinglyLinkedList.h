#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <initializer_list>
#include <iostream>

class SinglyLinkedList
{
private:
    struct node
    {
        int val;
        node* next;
        node() : val(0), next(nullptr) {}
        node(int x) : val(x), next(nullptr) {}
        node(int x, node* next) : val(x), next(next) {}
    };
public:
    SinglyLinkedList();
    SinglyLinkedList(std::initializer_list<int> init);
    ~SinglyLinkedList();
    size_t size() const;
    node* head() const;
private:
    node* _head = nullptr;
    size_t _size = 0;
public:
    class Solution
    {
    private:
        int size;
    public:
        Solution(size_t lstSize = 5) : size((int)lstSize){}
        node* removeNthFromEnd(node* head, int n);
    };
};

#endif // SINGLY_LINKED_LIST_H
