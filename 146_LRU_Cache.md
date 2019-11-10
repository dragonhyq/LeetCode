核心是删除的时候要求O(1)。用双向链表来做。

`get()`：如果找到key，就把对应的Node从链表里面删除，然后插入链表的最后。

`put()`：如果找到key，就更新对应的Node。如果没找到，先检查是否capacity已经达到。如果已经达到capacity，就`evict()`，然后把新的node在链表尾部插入。

`update()`：更新node的value。删除node，然后在链表最后插入。

`evict()`：把链表最前面的node删掉。

```cpp
#include <iostream>
#include <unordered_map>

struct Node {
    int key;
    int value;
    Node *pre;
    Node *next;
    Node (int key, int value): key(key), value(value), pre(NULL), next(NULL) {}
};

class LRUCache {
public:
    LRUCache(int capacity) {
        cap = capacity;
        
    }
    
    int get(int key) {
        if (map.find(key) == map.end()) {
            return -1;
        }    
        Node * node = map[key];
        if (node != end) {
            delete_node(node);
            insert_to_back(node);
        }   
        return node->value;
    }
    
    void put(int key, int value) {
            if (map.find(key) != map.end()) {
            update(key, value);
        }
        else {
            if (len == cap) evict();
            Node * node = new Node(key, value);
            map[key] = node;
            insert_to_back(node);
            len++;
        }
    }

    void update(int key, int value) {
        Node *node = map[key];
        node -> value = value;
        if (node != end) {
            delete_node(node);
            insert_to_back(node);
        }
    }

    

    void evict() {
        int key = prehead->next->key;
        map.erase(key);
        Node * node = prehead->next;
        if (node == end) {
            end = prehead;
            prehead->next = NULL;
        }
        else {
            prehead->next = node->next;
            node->next->pre = prehead;
        }
        len--;      
    }

    void delete_node(Node *node) {
        // delete node from the linked list
        node -> pre -> next = node -> next;
        node -> next -> pre = node -> pre;
    }

    void insert_to_back(Node * node) {
        // insert node to the back of the linked list
        end -> next = node;
        node -> pre = end;
        node -> next = NULL;
        end = node;

    }

private:
    int cap;
    int len = 0;
    Node * prehead = new Node(0, 0);
    Node * end = prehead;
    std::unordered_map<int, Node *> map;

};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```