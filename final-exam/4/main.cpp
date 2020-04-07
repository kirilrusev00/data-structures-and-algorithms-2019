#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Node {
	Node* left;
	Node* right;
	int value;
	Node(int value) {
		this->value = value;
		this->left = NULL;
		this->right = NULL;
	}
};

class BST {

public:
	BST() {
		root = NULL;
	}

	void insert(int value) {
		root = insert(root, value);
	}

	void printLeftProfile() {
		queue<Node*> q;
		q.push(root);
		int level = 0;
		int elements_in_level = 1;
		cout << q.front()->value << " ";
		while (!q.empty()) {
			elements_in_level--;
			Node* top_node = q.front();
			q.pop();
			if (top_node->left) {
				q.push(top_node->left);
			}
			if (top_node->right) {
				q.push(top_node->right);
			}
			if (elements_in_level == 0 && !q.empty()) {
				cout << q.front()->value << " ";
				level++;
				elements_in_level = q.size();
			}
		}
		//TODO: implement this function
	}

private:
	//you can write helper functions if needed
	Node* root;

	Node* insert(Node* curNode, int value) {
		if (curNode == NULL) {
			curNode = new Node(value);
		}
		else if (curNode->value < value) {
			curNode->right = insert(curNode->right, value);
		}
		else if (curNode->value > value) {
			curNode->left = insert(curNode->left, value);
		}
		else {
			//if we already have this value at the tree - do nothing
		}
		return curNode;
	}
};

int main() {
	int n;
	cin >> n;
	int value;
	BST tree;
	for (int i = 0; i < n; i++) {
		cin >> value;
		tree.insert(value);
	}
	tree.printLeftProfile();
	return 0;
}