#include <iostream>
#include "SinglyLinkedList.h"
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

void outList(const SinglyLinkedList& lst);
void outFront();

void Test_RemoveNthNode();
void Test_PushFront();
void Test_PopFront();
void Test_InsertAfter();
void Test_EraseAfter();
void Test_Reverse();
void Test_Iterators();
void Test_RangeFor();
void Test_Empty();
void Test_Swap();
void Test_StdInserter();
void Test_CopyConstructor();
void Test_CopyOperator();
void Test_MoveOperator();

int main()
{
    //Test_RemoveNthNode();
    //Test_PushFront();
    //Test_PopFront();
    //Test_InsertAfter();
    //Test_EraseAfter();
    //Test_Reverse();
    //Test_Iterators();
    //Test_RangeFor();
    //Test_Empty();
    //Test_Swap();
    //Test_StdInserter();
    //Test_CopyConstructor();
    //Test_CopyOperator();
    Test_MoveOperator();

    //cout << "" << endl;
    return 0;
}

void outList(const SinglyLinkedList& lst)
{
    if(lst.head() == nullptr)
    {
        cout << "list is null" << endl;
        return;
    }
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

    lst.pop_front();
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
    SinglyLinkedList lst{1,3,5,7,8};
    for(const auto& elem : lst)
        cout << elem << " ";
    cout << endl;
}

void Test_Empty()
{
    SinglyLinkedList lst{0,1,2,3,4,5};
    outList(lst);
    cout << "empty = " << lst.empty() << endl;

    lst.clear();
    outList(lst);
    cout << "empty = " << lst.empty() << endl;

    lst.push_front(7);
    lst.push_front(5);
    lst.push_front(1);
    outList(lst);
    cout << "empty = " << lst.empty() << endl;
}

void Test_Swap()
{
    SinglyLinkedList lst1{1,2,3,4};
    SinglyLinkedList lst2{5,6,7,8};
    outList(lst1);
    outList(lst2);

    lst1.swap(lst2);

    outList(lst1);
    outList(lst2);

}

void Test_StdInserter()
{
     std::vector<int> vec {1, 2, 3, 4, 5};
     SinglyLinkedList lst {0, 6, 7, 8};

     //std::copy(lst.begin(), lst.end(), std::inserter(vec, std::next(vec.begin())));
     //std::copy(vec.begin(), vec.end(), std::inserter(lst, lst.begin()));

     for(auto num : vec)
         cout << num << " ";
     cout << endl;
}

void Test_CopyConstructor()
{
    SinglyLinkedList lst {1, 2, 3, 4, 5};
    SinglyLinkedList lst1(lst);
    outList(lst1);
}

void Test_CopyOperator()
{
    SinglyLinkedList lst1 {1, 2, 3, 4, 5};
    SinglyLinkedList lst2 {6, 7, 8, 9};

    lst2 = lst1;
    outList(lst1);
    outList(lst2);
}

void Test_MoveOperator()
{
    SinglyLinkedList lst1 {1, 2, 3, 4, 5};
    SinglyLinkedList lst2 {6, 7, 8, 9};

    lst2 = std::move(lst1);
    outList(lst1);
    outList(lst2);
}
