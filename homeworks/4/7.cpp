#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    int placeInStudents;
    int placeInTeams;
    Node* prev;
    Node* next;

    Node(int data) {
        this->data = data;
        placeInStudents = 0;
        placeInTeams = 0;
        prev = nullptr;
        next = nullptr;
    }
};

struct Student {
    int skills;
    int placeInTeams;
    Node* placeInList;

    Student(int skills = 0, int placeInTeams = 0, Node * placeInList = nullptr) {
        this->skills = skills;
        this->placeInList = placeInList;
        this->placeInTeams = placeInTeams;
    }
};

class DoublyLinkedList {
public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void insert(int data, int pos) {
        Node* node = new Node(data);
        if (pos == 0) {
            if (head == nullptr) {
                head = tail = node;
            }
            else {
                head->prev = node;
                node->next = head;
                head = node;
            }
            return;
        }
        Node* tmp = head;
        for (int i = 0; i < pos - 1; i++)
        {
            if (tmp != tail) {
                tmp = tmp->next;
            }
            else break;
        }
        if (tmp == tail) {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        else {
            Node* tmpNext = tmp->next;
            tmp->next = node;
            node->prev = tmp;
            node->next = tmpNext;
            tmpNext->prev = node;
        }
    }

    void insert_end(int data) {
        Node* node = new Node(data);
        if (tail == nullptr) {
            head = tail = node;
        }
        else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    void delete_node(Node* node) {
        if (head == nullptr) {
            return;
        }
        if (node == head) {
            if (head->next == nullptr) {
                delete node;
                head = tail = nullptr;
            }
            else {
                Node* tmp = head->next;
                tmp->prev = nullptr;
                delete head;
                head = tmp;
            }
            return;
        }
        if (node == tail) {
            Node* tmp = tail->prev;
            tmp->next = nullptr;
            delete tail;
            tail = tmp;
        }
        else {
            Node* tmpPrev = node->prev;
            Node* tmpNext = node->next;
            tmpPrev->next = tmpNext;
            tmpNext->prev = tmpPrev;
            delete node;
        }
    }

    void delete_all() {
        while (head != nullptr) {
            delete_node(head);
        }
    }
    
    Node* getTail() {
        return tail;
    }
    
    void optimalTeams(vector<Student>& students, vector<int>& teams, int n, int k) {
        int numTeam = 1;
        for (int i = 0; i < n; i++) {
            if (teams[students[i].placeInTeams] != 0) {
                continue;
            }
            Node* maxNode = students[i].placeInList;
            for (int j = 0; j < k; j++) {
                if (maxNode->next == nullptr) {
                    break;
                }
                Node* tmp = maxNode->next;
                teams[tmp->placeInTeams] = numTeam;
                delete_node(tmp);
            }
            for (int j = 0; j < k; j++) {
                if (maxNode->prev == nullptr) {
                    break;
                }
                Node* tmp = maxNode->prev;
                teams[tmp->placeInTeams] = numTeam;
                delete_node(tmp);
            }
            teams[maxNode->placeInTeams] = numTeam;
            delete_node(maxNode);
            if (head == nullptr) {
                break;
            }
            if (numTeam == 1) {
                numTeam = 2;
            }
            else numTeam = 1;
        }
    }

    ~DoublyLinkedList() {
        delete_all();
    }

private:
    Node* head;
    Node* tail;
};

void merge(vector<Student>& students, vector<Student>& mergeStudents, int start, int middle, int end) {
    int left = start;
    int right = middle + 1;
    int k = start;
    while (left <= middle && right <= end)
    {
        if (students[left].skills > students[right].skills)
        {
            mergeStudents[k] = students[left];
            left++;
        }
        else
        {
            mergeStudents[k] = students[right];
            right++;
        }
        k++;
    }
    while(left <= middle)
    {
        mergeStudents[k++] = students[left++];
    }
    while(right <= end)
    {
        mergeStudents[k++] = students[right++];
    }
    for(int i = start; i <= end; i++)
    {
        students[i] = mergeStudents[i];
    }
}

void mergeRecursion(vector<Student>& students, vector<Student>& mergeStudents, int left, int right) {
    if(left < right)
    {
        int middle = left + (right - left)/2;
        mergeRecursion(students, mergeStudents, left, middle);
        mergeRecursion(students, mergeStudents, middle + 1, right);
        merge(students, mergeStudents, left, middle, right);
    }
}

void mergeSort(vector<Student>& students, int length) {
    vector<Student> mergeStudents;
    for(int i = 0; i < length; i++) {
        mergeStudents.push_back(Student());
    }
    mergeRecursion(students, mergeStudents, 0, length - 1);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n, k;
    cin >> n;
    cin >> k;
    DoublyLinkedList llist;
    vector<Student> students;
    vector<int> teams;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        llist.insert_end(x);
        Student newStudent(x, i, llist.getTail());
        students.push_back(newStudent);
        teams.push_back(0);
    }

    mergeSort(students, n);
    
    for (int i = 0; i < n; i++) {
        students[i].placeInList->placeInStudents = i;
        students[i].placeInList->placeInTeams = students[i].placeInTeams;
    }

    llist.optimalTeams(students, teams, n, k);
    
    
    for (int i = 0; i < n; i++) {
        cout << teams[i];
    }

    return 0;
}
