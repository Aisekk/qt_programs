#include <iostream>
#include "SinglyLinkedList.h"
using namespace std;

void outList(const SinglyLinkedList& lst);
void outFront();

void Test_RemoveNthNode();
void Test_Empty();
void Test_PushFront();
void Test_PopFront();
void Test_InsertAfter();
void Test_EraseAfter();
void Test_Reverse();
void Test_Iterators();
void Test_RangeFor();


int main()
{
    //Test_RemoveNthNode();
    //Test_PushFront();
    //Test_PopFront();
    //Test_InsertAfter();
    //Test_EraseAfter();
    //Test_Reverse();
    //Test_Iterators();
    Test_RangeFor();

    //cout << "" << endl;
    return 0;
}

void outList(const SinglyLinkedList& lst)
{
    auto cur = lst.head()->next;
    if(!cur)
        cout << "empty list";
    while(cur)
    {
        std::cout << cur->val << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}

void outFront(const SinglyLinkedList& lst)
{
    cout << "front = " << lst.front() << endl;
}

void Test_RemoveNthNode()
{
    void outList(const SinglyLinkedList& lst);
    SinglyLinkedList lst = {1,2,3,4,5};
    outList(lst);
    SinglyLinkedList::Solution sol(lst.size());
    sol.removeNthFromEnd(lst.head(), 2);
    outList(lst);
    sol.removeNthFromEnd(lst.head(), 1);
    outList(lst);
    sol.removeNthFromEnd(lst.head(), 3);
    outList(lst);
}

void Test_PushFront()
{
    SinglyLinkedList lst;

    lst.push_front(7);
    outFront(lst);
    outList(lst);

    lst.push_front(1);
    outFront(lst);
    outList(lst);

    lst.push_front(3);
    outFront(lst);
    outList(lst);
}

void Test_PopFront()
{
    SinglyLinkedList lst{5,4,3,2,1};

    lst.pop_front();
    outList(lst);

    lst.pop_front();
    outList(lst);

    lst.pop_front();
    outList(lst);
}

void Test_InsertAfter()
{
    SinglyLinkedList lst;
    lst.insert_after(0, 4);
    outList(lst);
    lst.push_front(3);
    lst.push_front(2);
    lst.push_front(1);
    outList(lst);
    lst.insert_after(2, 5);
    outList(lst);
}

void Test_EraseAfter()
{
     SinglyLinkedList lst{1,2,3,4,5,6};
     lst.erase_after(0);
     outList(lst);
     lst.erase_after(1);
     outList(lst);
     lst.erase_after(2);
     outList(lst);
     lst.clear();
     outList(lst);
}

void Test_Reverse()
{
    SinglyLinkedList lst{1,2,3,4,5,6};
    outList(lst);
    lst.reverse();
    outList(lst);
}

void Test_Iterators()
{
    SinglyLinkedList lst{1,3,5,7,9};
    auto it = lst.begin();
    for(;it != lst.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void Test_RangeFor()
{
    const SinglyLinkedList lst{1,3,5,7,8};
    for(const auto& elem : lst)
        cout << elem << " ";
    cout << endl;
}

void Test_Empty()
{

}

