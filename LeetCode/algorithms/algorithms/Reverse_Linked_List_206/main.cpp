#include <iostream>

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
    ListNode* reverseList(ListNode* head) {
        if (!head)
            return nullptr;
        ListNode* prev = nullptr;
        auto cur = head;
        while (cur) {
            auto next = cur->next;
            auto temp = cur;
            temp->next = prev;
            prev = temp;
            cur = next;
        }
        return prev;
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

ListNode* case_1() {
    ListNode* head = new ListNode(1);
    ListNode* cur = head;
    for (int val = 2; val < 6; ++val) {
        cur->next = new ListNode(val);
        cur = cur->next;
    }
    return head;
}

int main()
{
    auto list = case_1();
    out(list);

    Solution sol;
    auto reversedList = sol.reverseList(list);

    out(reversedList);

    return 0;
}
