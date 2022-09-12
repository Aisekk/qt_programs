#include <iostream>
#include "SinglyLinkedList.h"
using namespace std;

void outputList(const SinglyLinkedList& lst);
void RemoveNthNode();

int main()
{
    RemoveNthNode();

    //cout << "" << endl;
    return 0;
}

void outputList(const SinglyLinkedList& lst)
{
    auto cur = lst.head()->next;
    while(cur)
    {
        std::cout << cur->val << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}

void RemoveNthNode()
{
    void outputList(const SinglyLinkedList& lst);
    SinglyLinkedList lst = {1,2,3,4,5};
    outputList(lst);
    SinglyLinkedList::Solution sol(lst.size());
    sol.removeNthFromEnd(lst.head(), 2);
    outputList(lst);
    sol.removeNthFromEnd(lst.head(), 1);
    outputList(lst);
    sol.removeNthFromEnd(lst.head(), 3);
    outputList(lst);
}
