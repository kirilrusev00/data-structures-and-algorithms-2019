#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Tree {
    int height;
    int numOfSmallerTrees;
    int index;
    
    Tree(int height = 0, int numOfSmallerTrees = 0, int index = 0) {
        this->height = height;
        this->numOfSmallerTrees = numOfSmallerTrees;
        this->index = index;
    }
};

struct Node {
    Tree tree;
    Node* next;
    Node* prev;
    
    Node(Tree tree) {
        this->tree = tree;
        next = nullptr;
        prev = nullptr;
    }
};

class LinkedStack {
    public:
        LinkedStack() {
            head = nullptr;
            tail = nullptr;
        }
    
        bool empty() {
            return (head == nullptr);
        }
    
        void push(Tree tree) {
            Node* newNode = new Node(tree);
            if (tail == nullptr) {
                head = tail = newNode;
            }
            else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    
        void pop() {
            if(!empty()) {
                if (head == tail) {
                    delete tail;
                    head = tail = nullptr;
                } else {
                    tail = tail->prev;
                    delete tail->next;
                }
            }
        }
        
        Tree top() {
            return tail->tree;
        }
    
        ~LinkedStack() {
            while(head != nullptr) {
                pop();
            }
        }
    
    private:
        Node* head;
        Node* tail;
};

int getMaxNum(vector<int> trees, int length) {
    LinkedStack maxTrees;
    
    for (int i = 0; i < length; i++) {
        if(maxTrees.empty()) {
            Tree tree(trees[i], 1, i);
            maxTrees.push(tree);
        }
        Tree currTree(trees[i], 1, i);
        while(currTree.height > maxTrees.top().height) {
            if(currTree.numOfSmallerTrees - 1 <= maxTrees.top().numOfSmallerTrees) {
                currTree.numOfSmallerTrees = maxTrees.top().numOfSmallerTrees + 1;
                currTree.index = maxTrees.top().index;
            }
            maxTrees.pop();
            if(maxTrees.empty()) {
                break;
            }
        }
        if(maxTrees.empty()) {
            maxTrees.push(currTree);
        }
        maxTrees.push(currTree);
    }
    
    int indMaxNum = maxTrees.top().index;
    int numTrees = maxTrees.top().numOfSmallerTrees;
    maxTrees.pop();
    while(!maxTrees.empty()) {
        if(maxTrees.top().numOfSmallerTrees > numTrees) {
            numTrees = maxTrees.top().numOfSmallerTrees;
            indMaxNum = maxTrees.top().index;
        }
        if(maxTrees.top().numOfSmallerTrees == numTrees && maxTrees.top().index < indMaxNum) {
            numTrees = maxTrees.top().numOfSmallerTrees;
            indMaxNum = maxTrees.top().index;
        }
        maxTrees.pop();
    }
    return indMaxNum;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    vector<int> trees;
    for(int i = 0; i < n; i++) {
        int height;
        cin >> height;
        trees.push_back(height);
    }
    cout << getMaxNum(trees, n);
    return 0;
}
