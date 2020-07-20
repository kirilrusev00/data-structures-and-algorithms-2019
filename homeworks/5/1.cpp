#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int data) {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;
    
    Node* insert(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }
        if (data > node->data) {
            node->right = insert(node->right, data);
        }
        if (data < node->data) {
            node->left = insert(node->left, data);
        }
        return node;
    }
    
    int search(Node* root, int data) {
        if (root == nullptr) {
            return -1;
        }
        if (data < root->data) {
            int dist = search(root->left, data);
            if (dist != -1) {
                return 1 + dist;
            } else return -1;
        }
        if (data > root->data) {
            int dist = search(root->right, data);
            if (dist != -1) {
                return 1 + dist;
            } else return -1;
        }
        return 0;
    }
    
    Node* delete_all(Node* root) {
        if (root != nullptr) {
            delete_all(root->left);
            delete_all(root->right);
            delete root;
        }
        return nullptr;
    }
    
public:
    BST() {
        root = nullptr;
    }
    
    void insert(int data) {
        if (root == nullptr) {
            root = new Node(data);
        }
        else {
            insert(root, data);
        }
    }
    
    int search(int data) {
        return search(root, data);
    }
    
    ~BST() {
        delete_all(root);
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    BST bst;
    int n, k;
    cin >> n;
    cin >> k;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        bst.insert(x);
    }
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        cout << bst.search(x) << endl;
    }
    
    return 0;
}
