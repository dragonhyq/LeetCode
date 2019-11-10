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
        std::cout << "get " << key << std::endl;
        std::cout << "before" << std::endl;
        Node *temp = prehead -> next;
        while (temp != NULL) {
            std::cout << "(" << temp->key << " : " << temp->value << "), ";
            temp = temp -> next;
        }
        std::cout << std::endl;
        if (map.find(key) == map.end()) {
            return -1;
        }    
        Node * node = map[key];
        if (node != end) {
            delete_node(node);
            insert_to_back(node);
        }
        std::cout << "after" << std::endl;
        temp = prehead -> next;
        while (temp != NULL) {
            std::cout << "(" << temp->key << " : " << temp->value << "), ";
            temp = temp -> next;
        }
        std::cout << std::endl;
        
        return node->value;
    }
    
    void put(int key, int value) {
        std::cout << "put " << key << " " << value << std::endl;
        std::cout << "before" << std::endl;
        Node *temp = prehead -> next;
        while (temp != NULL) {
            std::cout << "(" << temp->key << " : " << temp->value << "), ";
            temp = temp -> next;
        }

        if (map.find(key) != map.end()) {
            update(key, value);
        }
        else {
            std::cout << std::endl;
            if (len == cap) evict();
            Node * node = new Node(key, value);
            map[key] = node;
            insert_to_back(node);
            len++;
        }
        
        std::cout << "after" << std::endl;
        temp = prehead -> next;
        while (temp != NULL) {
            std::cout << "(" << temp->key << " : " << temp->value << "), ";
            temp = temp -> next;
        }
        std::cout << std::endl;
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
        std::cout << "before evicting" << std::endl;
        Node *temp = prehead -> next;
        while (temp != NULL) {
            std::cout << "(" << temp->key << " : " << temp->value << "), ";
            temp = temp -> next;
        }
        std::cout << std::endl;
        int key = prehead->next->key;
        std::cout << key << " evicted" << std::endl;
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
        
        std::cout << "after evicting" << std::endl;
        temp = prehead -> next;
        while (temp != NULL) {
            std::cout << "(" << temp->key << " : " << temp->value << "), ";
            temp = temp -> next;
        }
        std::cout << std::endl;
        
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

 int main() {
    LRUCache cache(2);
    cache.get(2);
    cache.put(2, 6);
    cache.get(1);
    cache.put(1, 5);
    cache.put(1, 2);
    cache.get(1);
    cache.get(2);
    return 0;
 }