#include "SinglyLinkedList.h"

SinglyLinkedList::SinglyLinkedList() :
    _head(new node)
{}

SinglyLinkedList::SinglyLinkedList(std::initializer_list<int> init) :
    _head(new node)
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
    if(_head)
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
}

SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList& other)
{
    if(other._head)
    {
        _head = new node;
        auto cur = other._head->next;
        node* prev = _head;
        while(cur)
        {
            node* newNode = new node(cur->val);
            prev->next = newNode;
            prev = newNode;
            cur = cur->next;
        }
    }
}

SinglyLinkedList& SinglyLinkedList::operator=(const SinglyLinkedList& other)
{
    if(other._head)
    {
        clear();
        delete _head;

        _head = new node;
        auto cur = other._head->next;
        node* prev = _head;
        while(cur)
        {
            node* newNode = new node(cur->val);
            prev->next = newNode;
            prev = newNode;
            cur = cur->next;
        }
    }
    return *this;
}

SinglyLinkedList::SinglyLinkedList(SinglyLinkedList&& other) noexcept
{
    if(other._head && _head != other._head)
    {
        _head = other._head;
        other._head = nullptr;
    }
}

SinglyLinkedList& SinglyLinkedList::operator=(SinglyLinkedList&& other) noexcept
{
    if(other._head && _head != other._head)
    {
        clear();
        delete _head;
        _head = other._head;
        other._head = nullptr;
    }
    return *this;
}

size_t SinglyLinkedList::size() const
{
    size_t size_ = 0;
    auto nod = _head->next;
    while(nod)
    {
        ++size_;
        nod = nod->next;
    }
    return size_;
}

bool SinglyLinkedList::empty() const
{
    if(_head->next)
        return false;
    return true;
}

SinglyLinkedList::node* SinglyLinkedList::head() const
{
    return _head;
}

SinglyLinkedList::node* SinglyLinkedList::back() const
{
    node* last = nullptr;
    auto nod = _head->next;
    while(nod)
    {
        last = nod;
        nod = nod->next;
    }
    return last;
}

const int& SinglyLinkedList::front() const
{
    return _head->next->val;
}

void SinglyLinkedList::push_front(const int& value)
{
    auto old_front = _head->next;
    node* newNode = new node(value, old_front);
    _head->next = newNode;
}

void SinglyLinkedList::pop_front()
{
    auto front = _head->next;
    _head->next = _head->next->next;
    delete front;
}

void SinglyLinkedList::insert_after(int pos, const int& value)
{
    auto cur = _head->next;
    if(pos == 0 && !cur)
    {
        node* newNode = new node(value);
        _head->next = newNode;
        return;
    }
    int pos_ = 0;
    while(cur)
    {
        if(pos_ == pos)
        {
            auto next = cur->next;
            node* newNode = new node(value, next);
            cur->next = newNode;
            break;
        }
        cur = cur->next;
        ++pos_;
    }
}

void SinglyLinkedList::erase_after(int pos)
{
    auto cur = _head->next;
    if(pos == 0 && !cur)
    {
        return;
    }
    int pos_ = 0;
    while(cur)
    {
        if(pos_ == pos)
        {
            auto nod = cur->next;
            auto next = nod->next;
            delete nod;
            cur->next = next;
            break;
        }
        cur = cur->next;
        ++pos_;
    }
}

void SinglyLinkedList::clear()
{
    auto cur = _head->next;
    while(cur)
    {
        auto temp = cur;
        cur = cur->next;
        delete temp;
    }
    _head->next = nullptr;
}

void SinglyLinkedList::reverse() noexcept
{
    auto front = _head->next;
    if(!front)
        return;
//    node* newHead = new node;
//    while(front)
//    {
//        auto next = newHead->next;
//        newHead->next = front;
//        front = front->next;
//        newHead->next->next = next;
//    }
//    _head = newHead;
    node* newNext = nullptr;
    while(front)
    {
        _head->next = front;
        front = front->next;
        _head->next->next = newNext;
        newNext = _head->next;
    }
}

void SinglyLinkedList::swap(SinglyLinkedList& other) noexcept
{
    std::swap(_head, other._head);
}

SinglyLinkedList::iterator SinglyLinkedList::begin() const
{
    return iterator(_head->next);
}

SinglyLinkedList::iterator SinglyLinkedList::end() const
{
    return iterator(nullptr);
}


SinglyLinkedList::node* SinglyLinkedList::Solution::removeNthFromEnd(node* head, int n)
{
    if(n < 1 || n > _size)
        return nullptr;
    auto cur = head;
    int i = 0;
    while(true)
    {
        if(i == _size - n)
        {
            auto nodeToDelete = cur->next;
            cur->next = nodeToDelete->next;
            delete nodeToDelete;
            _size -= 1;
            break;
        }
        ++i;
        cur = cur->next;
    }
    return cur;
}
