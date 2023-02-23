#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!l1)
            return l2;
        if (!l2)
            return l1;

        auto cur1 = l1;
        auto cur2 = l2;
        int add = 0;
        ListNode* lsum = nullptr;
        ListNode* last = cur1;
        ListNode* cache = nullptr;
        while (cur1 || cur2) {
            int sum = 0;
            if (cur1 && cur2) {
                lsum = cur1;
                sum = cur1->val + cur2->val + add;
            } else if (cur1 && !cur2) {
                lsum = cur1;
                sum = cur1->val + add;
            } else if (!cur1 && cur2) {
                lsum = cur2;
                sum = cur2->val + add;
            }

            add = (sum > 9) ? 1 : 0;
            if (add == 1) {
                sum -= 10;
            }

            if (cur1 && cur2) {
                lsum->val = sum;
                last = lsum;
                cur1 = cur1->next;
                auto temp = cur2;
                cur2 = cur2->next;
                if (cache) {
                    delete temp;
                } else {
                    cache = temp;
                    cache->next = nullptr;
                }
                lsum->next = cur1;
            } else if (cur1 && !cur2) {
                lsum->val = sum;
                last = lsum;
                cur1 = cur1->next;
                lsum->next = cur1;
            } else if (!cur1 && cur2) {
                lsum->val = sum;
                last->next = cur2;
                last = lsum;
                cur2 = cur2->next;
                lsum->next = cur2;
            }
        }
        if (add == 1) {
            cache->val = add;
            last->next = cache;
        }

        return l1;
    }
};

void out(ListNode* list) {
    auto cur = list;
    while (cur) {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << " " << endl;
}

ListNode* num_342() {
    ListNode* head = new ListNode(2);
    ListNode* cur = head;
    cur->next = new ListNode(4);
    cur = cur->next;
    cur->next = new ListNode(3);
    return head;
}

ListNode* num_465() {
    ListNode* head = new ListNode(5);
    ListNode* cur = head;
    cur->next = new ListNode(6);
    cur = cur->next;
    cur->next = new ListNode(4);
    return head;
}

ListNode* num_9(int n) {
    ListNode* head = new ListNode(9);
    ListNode* cur = head;
    for (int i = 0; i < n - 1; ++i) {
        cur->next = new ListNode(9);
        cur = cur->next;
    }
    return head;
}

void case_1() {
    auto l1 = num_342();
    auto l2 = num_465();
    out(l1);
    out(l2);

    Solution sol;
    ListNode* sumList =  sol.addTwoNumbers(l1,l2);

    out(sumList);
    cout << '\n';
}

void case_3() {
    auto l1 = num_9(7);
    auto l2 = num_9(4);
    out(l1);
    out(l2);

    Solution sol;
    ListNode* sumList =  sol.addTwoNumbers(l1,l2);

    out(sumList);
    cout << '\n';
}

int main()
{
    case_1();
    case_3();

    return 0;
}
