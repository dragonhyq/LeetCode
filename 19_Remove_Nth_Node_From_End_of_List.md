题目链接：https://leetcode.com/problems/remove-nth-node-from-end-of-list/

Given a linked list, remove the n-th node from the end of list and return its head.

Example:

Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:

Given n will always be valid.

Follow up:

Could you do this in one pass?

---
要不就是先数list里面一共有多少node，然后找到那个node，这是two passes。要不就是用一个slow, 用一个fast，fast比slow快`n`个node，这是one pass。从运算上one pass 不比two pass快，因为没有省运算。

特例：如果list里面只有一个node，然后`n=1`，那么删掉之后list就空了，所以我们应该建一个prehead，指向原来的链表头，然后返回`prehead->next`。

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *prehead = new ListNode(0), *fast = prehead, *slow = prehead;
        prehead -> next = head;
        for (int i = 0; i < n; i++) fast = fast->next;
        while (fast -> next != NULL) {
            fast = fast -> next;
            slow = slow -> next;
        }
        slow->next = slow -> next -> next;
        return prehead->next;
    }
};
```