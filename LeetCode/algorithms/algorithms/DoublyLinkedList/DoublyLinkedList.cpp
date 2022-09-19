#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList() : _head(new node), _tail(_head) {}

size_t DoublyLinkedList::size() const noexcept
{
    //std::distance(begin(), end());
    return 0;
}

bool DoublyLinkedList::empty() const noexcept
{
    if(_head == _tail)
        return true;
    return false;
}

const int& DoublyLinkedList::front() const
{
    return _head->next->val;
}

void DoublyLinkedList::push_front(const int& value)
{
    auto old_prev = _head;
    auto old_next = _head->next;
    node* newNode = new node(value, old_prev, old_next);
    _head->next = newNode;

    if(_head == _tail)
    {
        _tail = newNode;
        _tail->prev = _head;
        _tail->next = nullptr;
    }
}

void DoublyLinkedList::pop_front()
{

}

const int& DoublyLinkedList::back() const
{
    return _tail->val;
}

void DoublyLinkedList::push_back(const int& value)
{
    auto old_prev = _tail->prev;
    auto old_next = _tail->next;
    node* newNode = new node(value, old_prev, old_next);
    old_prev->next = newNode;
    _tail = newNode;
}

void DoublyLinkedList::pop_back()
{

}

