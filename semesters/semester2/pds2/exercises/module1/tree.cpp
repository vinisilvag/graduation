#include <iostream>

using namespace std;

struct TNode {
	int data;
	TNode *left;
	TNode *right;
};

struct BST {
	TNode *root = nullptr;

	TNode* createNode(int data) {
		TNode *aux = new TNode();
		aux->data = data;
		aux->left = nullptr;
		aux->right = nullptr;

		return aux;
	}

	void insertNodeHelper(TNode *root, int data) {
		if(data < root->data) {
			if(root->left == nullptr) {
				root->left = createNode(data);
			} else {
				insertNodeHelper(root->left, data);
			}
		} else if(data > root->data) {
			if(root->right == nullptr) {
				root->right = createNode(data);
			} else {
				insertNodeHelper(root->right, data);
			}
		}
	}

	void insertNode(int data) {
		if(root != nullptr) {
			insertNodeHelper(root, data);
		} else {
			root = createNode(data);
		}
	}

	void inorder(TNode *root) {
		if(root) {
			inorder(root->left);
			cout << root->data << " ";
			inorder(root->right);
		}
	}

	void display() {
		inorder(root);
		cout << endl;
	}
};

int main() {
	BST *tree = new BST();

	tree->insertNode(9);
	tree->insertNode(7);
	tree->insertNode(0);
	tree->insertNode(5);
	tree->insertNode(1);
	tree->insertNode(3);
	tree->insertNode(8);
	tree->insertNode(6);
	tree->insertNode(4);
	tree->insertNode(2);

	tree->display();

	return 0;
}