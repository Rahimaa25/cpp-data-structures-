//Data Structures — Linked List, Stack, Binary Search Tree
#include <iostream>
#include <string>
using namespace std;

// 1. SINGLY LINKED LIST

struct ListNode {
    int data;
    ListNode* next;
    ListNode(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;

public:
    LinkedList() : head(nullptr) {}

    void push_front(int val) {
        ListNode* node = new ListNode(val);
        node->next = head;
        head = node;
    }

    void push_back(int val) {
        ListNode* node = new ListNode(val);
        if (!head) { head = node; return; }
        ListNode* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }

    bool remove(int val) {
        if (!head) return false;
        if (head->data == val) {
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
            return true;
        }
        ListNode* cur = head;
        while (cur->next && cur->next->data != val)
            cur = cur->next;
        if (!cur->next) return false;
        ListNode* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
        return true;
    }

    void print() const {
        ListNode* cur = head;
        while (cur) {
            cout << cur->data;
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << "\n";
    }

    ~LinkedList() {
        while (head) {
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};

// 2. STACK (template)

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node* top_node;
    int sz;

public:
    Stack() : top_node(nullptr), sz(0) {}

    void push(T val) {
        Node* n = new Node(val);
        n->next = top_node;
        top_node = n;
        sz++;
    }

    T pop() {
        if (!top_node) throw runtime_error("Stack is empty");
        T val = top_node->data;
        Node* tmp = top_node;
        top_node = top_node->next;
        delete tmp;
        sz--;
        return val;
    }

    T top() const {
        if (!top_node) throw runtime_error("Stack is empty");
        return top_node->data;
    }

    bool empty() const { return sz == 0; }
    int  size()  const { return sz; }

    ~Stack() {
        while (top_node) {
            Node* tmp = top_node;
            top_node = top_node->next;
            delete tmp;
        }
    }
};
// 3. BINARY SEARCH TREE

struct BSTNode {
    int key;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, int key) {
        if (!node) return new BSTNode(key);
        if (key < node->key)  node->left  = insert(node->left,  key);
        else if (key > node->key) node->right = insert(node->right, key);
        return node;
    }

    bool search(BSTNode* node, int key) const {
        if (!node) return false;
        if (key == node->key) return true;
        return key < node->key ? search(node->left, key)
                               : search(node->right, key);
    }

    void inorder(BSTNode* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    void destroy(BSTNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    void insert(int key)         { root = insert(root, key); }
    bool search(int key)  const  { return search(root, key); }
    void print_sorted()   const  { inorder(root); cout << "\n"; }

    ~BST() { destroy(root); }
};

int main() {
    cout << "=== Linked List ===\n";
    LinkedList ll;
    ll.push_back(10);
    ll.push_back(20);
    ll.push_back(30);
    ll.push_front(5);
    ll.print();           // 5 -> 10 -> 20 -> 30
    ll.remove(20);
    ll.print();           // 5 -> 10 -> 30

    cout << "\n=== Stack ===\n";
    Stack<int> st;
    for (int x : {1, 2, 3, 4, 5}) st.push(x);
    while (!st.empty())
        cout << st.pop() << " ";  // 5 4 3 2 1
    cout << "\n";

    cout << "\n=== Binary Search Tree ===\n";
    BST tree;
    for (int x : {5, 3, 7, 1, 4, 6, 8}) tree.insert(x);
    tree.print_sorted();           // 1 2 3 4 5 6 7 8
    cout << "Search 4: " << (tree.search(4) ? "found" : "not found") << "\n";
    cout << "Search 9: " << (tree.search(9) ? "found" : "not found") << "\n";

    return 0;
}
