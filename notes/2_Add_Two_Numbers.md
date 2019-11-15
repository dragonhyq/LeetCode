题目链接：https://leetcode.com/problems/add-two-numbers/

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)\
Output: 7 -> 0 -> 8\
Explanation: 342 + 465 = 807.

---
简单题。但要做好，同学。能说的就是最后要是carry不是0就还要再建一个Node。
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == NULL && l2 == NULL) return NULL;
        int carry = 0;
        ListNode prehead = ListNode(0), *h = &prehead;
        while (l1 != NULL || l2 != NULL || carry) {
            int val = carry;
            if (l1 != NULL) {
                val += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL) {
                val += l2->val;
                l2 = l2->next;
            }
            ListNode *h_new = new ListNode(val % 10);
            carry = val / 10;
            h->next = h_new;
            h = h_new;
        }          
        return prehead.next; 
    }
};
```