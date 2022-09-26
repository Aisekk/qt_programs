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
    node* _head = nullptr;
public:
    SinglyLinkedList();
    SinglyLinkedList(std::initializer_list<int> init);
    ~SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList& other);
    SinglyLinkedList& operator=(const SinglyLinkedList& other);
    SinglyLinkedList(SinglyLinkedList&& other) noexcept;
    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;
    node* head() const;
    node* back() const;
    const int& front() const;
    void push_front(const int& value);
    void pop_front();
    void insert_after(int pos, const int& value);
    void erase_after(int pos);
    void clear();
    void reverse() noexcept;
    void swap(SinglyLinkedList& other) noexcept;

    class iterator
    {
        friend class SinglyLinkedList;
    private:
        node* _node = nullptr;
        iterator(node* node_) : _node(node_) {}
    public:
        iterator& operator++()
        {
            _node = _node->next;
            return *this;
        }
        iterator operator++(int)
        {
            iterator copy(_node);
            _node = _node->next;
            return copy;
        }
        int& operator*() const
        {
            return _node->val;
        }
        node* operator->() const
        {
            return _node;
        }
        bool operator==(const iterator& other)
        {
            if(_node == other._node)
                return true;
            return false;
        }
        bool operator!=(const iterator& other)
        {
            return !operator==(other);
        }
    };

    iterator begin() const;
    iterator end() const;

public:
    class Solution
    {
    private:
        int _size;
    public:
        Solution(size_t lstSize = 5) : _size((int)lstSize){}
        node* removeNthFromEnd(node* head, int n);
    };
};

#endif // SINGLY_LINKED_LIST_H
