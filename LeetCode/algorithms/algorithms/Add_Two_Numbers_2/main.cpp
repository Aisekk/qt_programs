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
        int num1 = calcNumber(l1);
        int num2 = calcNumber(l2);
        int sum = num1 + num2;

        std::vector<char> digits;
        while (sum != 0) {
            char digit = (char)(sum % 10);
            digits.push_back(digit);
            sum /= 10;
        }

        auto cur1 = l1;
        int counter = 0;
        while (cur1) {
            counter++;
            cur1 = cur1->next;
        }
        // if (counter < digits.size()) {
        //     cur1 = l2;
        //     counter++;
        // }
        if (counter < (int)digits.size()) {
            cur1 = l2;
            while (cur1) {
                counter++;
                if (counter == (int)digits.size()) {
                    break;
                }
                cur1 = cur1->next;
            }
        }
        while (cur1) {
            auto next = cur1->next;
            delete cur1;
            cur1 = next;
        }

        cur1 = l1;
        for (auto digit : digits) {
            cur1->val = (int)digit;
            cur1 = cur1->next;
            if (!cur1) {
                break;
            }
        }
        // while (cur1) {
        //     auto next = cur1->next;
        //     delete cur1;
        //     cur1 = next;
        // }
        return l1;
    }

    int calcNumber(ListNode* list) {
        std::vector<char> digits;
        digits.reserve(10);
        auto cur = list;
        while (cur) {
            digits.push_back((char)cur->val);
            cur = cur->next;
        }
        if (digits.empty())
            return 0;
        int num = 0;
        int m = std::pow(10, (int)digits.size() - 1);
        for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
            num += ((int)*it) * m;
            m /= 10;
        }
        return num;
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

int main()
{
    auto l1 = num_342();
    auto l2 = num_465();
    out(l1);
    out(l2);

    Solution sol;
    ListNode* sumList =  sol.addTwoNumbers(l1,l2);

    out(sumList);

    return 0;
}
