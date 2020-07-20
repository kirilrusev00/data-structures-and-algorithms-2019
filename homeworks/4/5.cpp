#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node{
    int data;
    Node* next;
    
    Node(int data){
        this->data = data;
        next = nullptr;
    }
};

class LinkedStack{
    public:
        LinkedStack(){
            head = nullptr;
            tail = nullptr;
        }
    
        void push_back(int data) {
            Node* newNode = new Node(data);
            if (tail == nullptr){
                head = tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
        }
    
        Node* top() {
            return tail;
        }
    private:
        Node* head;
        Node* tail;
};

bool isPossible(vector<int> trucks, int numOfTrucks){
    LinkedStack* lstack = new LinkedStack();
    bool isTrue = true;
    for(int i = 0; i < numOfTrucks - 1; i++){
        if(trucks[i] > trucks[i+1]){
            if(lstack->top() != nullptr && lstack->top()->data < trucks[i]){
                isTrue = false;
            }
            lstack->push_back(trucks[i]);
        }
    }
    delete lstack;
    return isTrue;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n;
        cin >> n;
        vector<int> trucks;
        for (int i = 0; i < n; i++)
        {
            int a;
            cin >> a;
            trucks.push_back(a);
        }
        if (isPossible(trucks, n)){
            cout << "yes" << endl;
        }
        else cout << "no" << endl;
    }
    
    return 0;
}

