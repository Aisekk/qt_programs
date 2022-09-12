#include "SinglyLinkedList.h"

SinglyLinkedList::SinglyLinkedList() :
    _head(new node),
    _size(0)
{}

SinglyLinkedList::SinglyLinkedList(std::initializer_list<int> init) :
    _head(new node),
    _size(init.size())
{
    node* cur = _head;
    auto it = init.begin();
    while(it != init.end())
    {
        node* newNode = new node(*it);
        cur->next = newNode;
        cur = cur->next;
        ++it;
    }
}

SinglyLinkedList::~SinglyLinkedList()
{
    auto cur = _head->next;
    while(cur)
    {
        auto temp = cur;
        cur = cur->next;
        delete temp;
    }
    delete _head;
}

size_t SinglyLinkedList::size() const
{
    return _size;
}

SinglyLinkedList::node* SinglyLinkedList::head() const
{
    return _head;
}

SinglyLinkedList::node* SinglyLinkedList::Solution::removeNthFromEnd(node* head, int n)
{
    if(n < 1 || n > size)
        return nullptr;
    auto cur = head;
    int i = 0;
    while(true)
    {
        if(i == size - n)
        {
            auto nodeToDelete = cur->next;
            cur->next = nodeToDelete->next;
            delete nodeToDelete;
            size -= 1;
            break;
        }
        ++i;
        cur = cur->next;
    }
    return cur;
}
