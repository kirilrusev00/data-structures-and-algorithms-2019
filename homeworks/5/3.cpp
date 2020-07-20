#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct Student {
    int group;
    int enterTime;
    int leaveTime;
    string name;
    
    Student() {
        this->group = 0;
        this->enterTime = 0;
        this->leaveTime = 0;
        this->name = '\0';
    }
    
    Student(int group, int enterTime, string name) {
        this->group = group;
        this->enterTime = enterTime;
        this->leaveTime = 0;
        this->name = name;
    }
};

struct Node {
    Student student;
    Node* next;
    
    Node(Student student) {
        this->student.group = student.group;
        this->student.enterTime = student.enterTime;
        this->student.leaveTime = 0;
        this->student.name = student.name;
        //this->student(student.group, student.enterTime, student.name);
        next = nullptr;
    }
};

class LinkedQueue {
public:
    LinkedQueue(int m = 0) {
        first = nullptr;
        end = nullptr;
        friends = new Node*[m + 1];
    }

    void push(Node* node) {
        int group = node->student.group;
        if (friends[group] != nullptr) {
            get_in_queue(node, friends[group]);
            friends[group] = node;
        } else {
            get_in_queue(node, end);
            friends[group] = node;
        }
    }
    
    Node* front() {
        return first;
    }
    
    bool empty() {
        return (first == nullptr);
    }
    
    void pop() {
        Student temp = first->student;
        delete first;
        first = first->next;
        if (!empty() && temp.group != first->student.group) {
            friends[temp.group] = nullptr;
        }
    }
    
    ~LinkedQueue() {
        delete_all();
        delete[] friends;
    }
    
private:
    Node* get_in_queue(Node* node, Node* previous) {
        if (first == nullptr) {
            first = end = node;
            return node;
        }
        Node* tmpNext = previous->next;
        previous->next = node;
        node->next = tmpNext;
        if(previous == end) {
            end = node;
        }   
        return node;
    }
    
    void delete_all() {
        while (first != nullptr) {
            pop();
        }
    }
    
    Node* first;
    Node* end;
    Node** friends;
};

int main() {
    int n, m;
    cin >> n;
    cin >> m;
    LinkedQueue lqueue(m);
    for (int i = 0; i <= n * 2; i++) {
        if(i < n) {
            string name;
            int group;
            cin >> name;
            cin >> group;
            Student newStudent(group, i, name);
            Node* newNode = new Node(newStudent);
            lqueue.push(newNode);
            
        }
        if(i > 0 && i % 2 == 0) {
            Student oldStudent = lqueue.front()->student;
            lqueue.pop();
            oldStudent.leaveTime = i;
            cout << oldStudent.name << " " << oldStudent.enterTime << " " << oldStudent.leaveTime << endl;
        }
    }
    
    return 0;
}
