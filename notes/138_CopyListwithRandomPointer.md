题目链接：https://leetcode.com/problems/copy-list-with-random-pointer/


A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

![](https://discuss.leetcode.com/uploads/files/1470150906153-2yxeznm.png) 

Example 1:

Input:
{"$id":"1","next":{"$id":"2","next":null,"random":{"$ref":"2"},"val":2},"random":{"$ref":"2"},"val":1}

Explanation:\
Node 1's value is 1, both of its next and random pointer points to Node 2.\
Node 2's value is 2, its next pointer points to null and its random pointer points to itself.

Note: You must return the copy of the given head as a reference to the cloned list.

---
首先一种做法就是平行地建立新的链表，然后用一个map来存放(original node pointer: new node pointer)。
```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> map;
        Node prehead = Node(0, NULL, NULL), *h0 = head, *h = &prehead;
        while (h0 != NULL) {
            Node *h_new = new Node(0, NULL, NULL);
            map[h0] = h_new; // old node : new node
            h->next = h_new;
            h = h_new;
            h0 = h0->next;
        }
        h0 = head;
        h = prehead.next;
        while (h0 != NULL) {
            h->val = h0->val;
            if (h0->next != NULL) h->next = map[h0->next];
            if (h0->random != NULL) h->random = map[h0->random];    
            h0 = h0->next;
            h = h->next;
        }
        return prehead.next;
    }
};
```
第二种方法，不使用map的，是把每一个新建立的node放在原始node的后面。
> node1 -> node1_copy -> node2 -> node2_copy -> ...

一个人画了个[图](https://leetcode.com/problems/copy-list-with-random-pointer/discuss/43491/A-solution-with-constant-space-complexity-O(1)-and-linear-time-complexity-O(N)/42652)，一看就清楚了。
```cpp
class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node prehead = Node(0, NULL, NULL), *h0 = head, *headNew;
        if (head == NULL) return NULL;
        // make copies of every node
        while (h0 != NULL) {
            Node *h_new = new Node(h0->val, NULL, NULL);
            h_new->next = h0->next;
            h0->next = h_new;
            h0 = h_new->next;
        } 
        // set the "random" pointer of new nodes
        h0 = head;
        Node *h_new;
        while (h0 != NULL) {
            h_new = h0->next;
            if (h0->random != NULL) h_new->random = h0->random->next;
            h0 = h_new->next;
        }

        // set the "next" pointer of new nodes and separate old and new list
        // recover the old list
        h0 = head;
        Node *h0next;
        headNew = h0->next;
        while (h0 != NULL) {
            h_new = h0->next;
            h0next = h_new->next;
            if (h0next != NULL) h_new->next = h0next->next;
            h0->next = h0next;
            h0 = h0next;
        }   
        return headNew;
    }
};
```