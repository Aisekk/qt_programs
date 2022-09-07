#ifndef LINKEDLISTS_H
#define LINKEDLISTS_H
#include <initializer_list>
#include <iostream>

class SinglyLinkedList
{
public:
    SinglyLinkedList(std::initializer_list<int> init) : head(new ListNode), size(init.size())
    {
        ListNode* cur = head;
        auto it = init.begin();
        while(it != init.end())
        {
            ListNode* newNode = new ListNode(*it);
            cur->next = newNode;
            cur = cur->next;
            ++it;
        }
    }
    //Definition for singly-linked list.
//private:
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
//private:
    ListNode* head = nullptr;
    int size = 0;
public:
    class Solution
    {
    private:
        int size;
    public:
        Solution(int lstSize = 5) : size(lstSize){}
        ListNode* removeNthFromEnd(ListNode* head, int n)
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
    };
};



void RemoveNthNode()
{
    void outputList(const SinglyLinkedList& lst);
    SinglyLinkedList lst = {1,2,3,4,5};
    outputList(lst);
    SinglyLinkedList::Solution sol(lst.size);
    sol.removeNthFromEnd(lst.head, 2);
    outputList(lst);
    sol.removeNthFromEnd(lst.head, 1);
    outputList(lst);
    sol.removeNthFromEnd(lst.head, 3);
    outputList(lst);
}

void outputList(const SinglyLinkedList& lst)
{
    auto cur = lst.head->next;
    while(cur)
    {
        std::cout << cur->val << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}

#endif // LINKEDLISTS_H
