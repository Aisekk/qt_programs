#include <iostream>
#include <vector>
using namespace std;


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty())
            return nullptr;
        ListNode* first = nullptr;
        for (auto node : lists) {
            if (!node)
                continue;
            if (!first) {
                first = node;
                continue;
            }
            first = merge2Lists(first, node);
        }
        return first;
    }

    ListNode* merge2Lists(ListNode* l1, ListNode* l2) {
           auto cur2 = l2;
           auto cur1 = l1;
           while (cur2) {
               bool inserted = false;
               while (cur1) {
                  if (cur2->val < cur1->val) {
                       auto next1 = cur1;
                       auto next2 = cur2->next;
                       cur1 = cur2;
                       cur1->next = next1;
                       cur2 = next2;
                       l1 = cur1;
                       inserted = true;
                       break;
                   } else if (!cur1->next) {
                       if (cur2->val >= cur1->val) {
                           cur1->next = cur2;
                           cur2 = nullptr;
                           cur1 = l1;
                           inserted = true;
                           break;
                       } else if (cur2->val < cur1->val) {
                           auto next1 = cur1;
                           auto next2 = cur2->next;
                           cur1 = cur2;
                           cur1->next = next1;
                           cur2 = next2;
                           l1 = cur1;
                           inserted = true;
                           break;
                       }
                   } else if (cur2->val >= cur1->val && cur2->val <= cur1->next->val) {
                       auto next2 = cur2->next;

                       auto next1 = cur1->next;
                       cur1->next = cur2;
                       cur1->next->next = next1;

                       cur2 = next2;
                       cur1 = l1;
                       inserted = true;
                       break;
                   } else {
                       cur1 = cur1->next;
                   }
               }
               if (!inserted && cur2)
                   cur2 = cur2->next;
           }
           return cur1;
       }
};

std::vector<ListNode*> case_1() {
    std::vector<ListNode*> lists;

    ListNode* list1 = new ListNode(1);
    list1->next = new ListNode(4);
    list1->next->next = new ListNode(5);

    ListNode* list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);

    ListNode* list3 = new ListNode(2);
    list3->next = new ListNode(6);

    lists.push_back(list1);
    lists.push_back(list2);
    lists.push_back(list3);

    return lists;
}

std::vector<ListNode*> case_71() {
    std::vector<ListNode*> lists;

    ListNode* list1 = new ListNode(1);
    list1->next = new ListNode(4);
    list1->next->next = new ListNode(5);

    ListNode* list2 = new ListNode(0);
    list2->next = new ListNode(2);

    lists.push_back(list1);
    lists.push_back(list2);

    return lists;
}

int main()
{
    auto lists = case_1();
    lists = case_71();

    Solution sol;
    ListNode* res =  sol.mergeKLists(lists);

    auto cur = res; //list1;
    while (cur) {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << " " << endl;

    return 0;
}
