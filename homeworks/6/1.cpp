#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Node
{
    double value;
    int height = 0;
    Node* left;
    Node* right;

    Node(double value, Node* left, Node* right)
    {
        this->value = value;
        this->left = left;
        this->right = right;
    }

    void calculateHeight() {
        height = 0;
        if (left) {
            height = max(height, left->height + 1);
        }
        if (right) {
            height = max(height, right->height + 1);
        }
    }

    int leftHeight() const{
        if (left) {
            return left->height + 1;
        }
        return 0;
    }

    int rightHeight() const {
        if (right) {
            return right->height + 1;
        }
        return 0;
    }

    int balance() const {
        return leftHeight() - rightHeight();
    }

    void rotateRight() {
        if (!left) {
            return;
        }

        Node* leftRight = this->left->right;
        Node* oldRight = this->right;

        swap(this->value, this->left->value);
        this->right = this->left;
        this->left = this->left->left;
        this->right->left = leftRight;
        this->right->right = oldRight;
    }

    void rotateLeft() {
        if (!left) {
            return;
        }

        Node* rightLeft = this->right->left;
        Node* oldLeft = this->left;

        swap(this->value, this->right->value);
        this->left = this->right;
        this->right = this->right->right;
        this->left->left = oldLeft;
        this->left->right = rightLeft;
    }

    void recalculateHeights() {
        if (left) {
            left->calculateHeight();
        }
        if (right) {
            right->calculateHeight();
        }
        this->calculateHeight();
    }

    void balanceTree() {
        if (balance() < -1) { // Right is heavier
            if (right->balance() <= -1) { // RR
                this->rotateLeft();
                recalculateHeights();
            }
            else if (right->balance() >= 1) { // RL
                right->rotateRight();
                this->rotateLeft();
                recalculateHeights();
            }
        }
        else if (balance() > 1) { // Left is heavier
            if (left->balance() >= 1) { // LL
                this->rotateRight();
                recalculateHeights();
            }
            else if (left->balance() <= -1) { // LR
                left->rotateLeft();
                this->rotateRight();
                recalculateHeights();
            }
        }
    }
};

class AVLTree
{
private:
    Node* root;

    bool containsRecursive(Node* current, double value)
    {
        if (current == NULL)
        {
            return false;
        }

        if (current->value == value)
        {
            return true;
        }

        if (value < current->value)
        {
            return containsRecursive(current->left, value);
        }
        else
        {
            return containsRecursive(current->right, value);
        }
    }

    void printRecursive(Node* current)
    {
        if (current == NULL)
        {
            return;
        }

        printRecursive(current->left);
        cout << current->value << " ";
        printRecursive(current->right);
    }

    Node* add(double value, Node* current) {
        if (!current) {
            return new Node(value, nullptr, nullptr);
        }
        if (value == current->value) {
            cout << value << " already added" << endl;
        }
        else if (value < current->value) {
            current->left = add(value, current->left);
        }
        else if (value > current->value) {
            current->right = add(value, current->right);
        }

        current->calculateHeight();
        current->balanceTree();
        return current;
    }

    Node* remove(double value, Node* current) {
        if (!current) {
            cout << value << " not found to remove" << endl;
            return nullptr;
        }

        if (value < current->value) {
            current->left = remove(value, current->left);
        }
        else if (value > current->value) {
            current->right = remove(value, current->right);
        }
        else { 
            if (!current->left && !current->right) {
                delete current;
                return nullptr;
            }
            else if (!current->left) {
                Node* tempRight = current->right;
                delete current;
                return tempRight;
            }
            else if (!current->right) {
                Node* tempLeft = current->left;
                delete current;
                return tempLeft;
            }
            else {
                Node* temp = current->right;
                while (temp->left) {
                    temp = temp->left;
                }

                current->value = temp->value;
                current->right = remove(temp->value, current->right);
            }
        }

        current->calculateHeight();
        current->balanceTree();

        return current;

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
    AVLTree()
    {
        root = NULL;
    }

    void add(double value)
    {
        root = add(value, root);
    }

    void remove(double value)
    {
        root = remove(value, root);
    }

    bool contains(double value)
    {
        if (root == NULL)
        {
            return false;
        }

        return containsRecursive(root, value);
    }

    void print()
    {
        if (root == NULL)
        {
            return;
        }

        printRecursive(root);
        cout << endl;
    }

    ~AVLTree() {
        delete_all(root);
    }
};

int main()
{
    AVLTree tree;
    string operation;
    double number;
    int N;

    cin >> N;
    cout << fixed;

    for (size_t i = 0; i < N; i++)
    {
        cin >> operation;
        if (operation != "print")
        {
            cin >> number;
        }

        if (operation == "add")
        {
            tree.add(number);
        }
        else if (operation == "remove")
        {
            tree.remove(number);
        }
        else if (operation == "contains")
        {
            if (tree.contains(number))
            {
                cout << "yes" << endl;
            }
            else
            {
                cout << "no" << endl;
            }
        }
        else if (operation == "print")
        {
            tree.print();
        }
    }

    return 0;
}
