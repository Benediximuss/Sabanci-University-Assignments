#include "BinarySearchTree.h"

#include <iostream>
#include <string>

using namespace std;

template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable &notFound)
	: ITEM_NOT_FOUND(notFound), root(NULL) {}

template <class Comparable>
Comparable& BinarySearchTree<Comparable>::elementAt(BinaryNode<Comparable>* position) {
	if (position == NULL) {
		return ITEM_NOT_FOUND;
	}
	else {
		return position->data;
	}
}

template <class Comparable>
Comparable& BinarySearchTree<Comparable>::find(const Comparable& x) {
	return elementAt(find(x, root));
}

template <class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::find(const Comparable& x, BinaryNode<Comparable>* t) {
	if (t == NULL) {
		return NULL;
	}
	else if (x < t->data) {
		return find(x, t->left);
	}
	else if (x > t->data) {
		return find(x, t->right);
	}
	else {
		return t;
	}
}

template<class Comparable>
const Comparable& BinarySearchTree<Comparable>::findMin() const {
	return elementAt(findMin(root));
}

template <class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable>* t) const {
	if (t == NULL) {
		return NULL;
	}
	else if (t->left == NULL) {
		return t;
	}
	else {
		return findMin(t->left);
	}
}

template<class Comparable>
const Comparable& BinarySearchTree<Comparable>::findMax() const {
	return elementAt(findMax(root));
}

template <class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::findMax(BinaryNode<Comparable>* t) const {
	if (t == NULL) {
		return NULL;
	}
	else if (t->right == NULL) {
		return t;
	}
	else {
		return findMax(t->right);
	}
}

template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x) {
	insert(x, root);
}

template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x, BinaryNode<Comparable>* &t) const {
	BinaryNode<Comparable>* newNode = new BinaryNode<Comparable>(x, NULL, NULL);

	if (t == NULL) {
		t = newNode;
	}
	else {
		int isEqual = 0;

		BinaryNode<Comparable>* iterator = t;
		BinaryNode<Comparable>* iterator2 = NULL;

		while(iterator != NULL) {
			iterator2 = iterator;
			if (x < iterator->data) {
				iterator = iterator->left;
			}
			else if (x > iterator->data) {
				iterator = iterator->right;
			}
			else {
				isEqual = 1;
				break;
			}
		}

		if (isEqual == 0) {
			
			if (x < iterator2->data) {
				iterator2->left = newNode;
			}
			else if (x > iterator2->data) {
				iterator2->right = newNode;
			}
			else {
				cout << "ERROR 6205:..insert_exact_match..." << endl;
			}
		}
	}
}

template <class Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& x) {
	remove(x, root);
}

template <class Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& x, BinaryNode<Comparable>* &t) const {
	if (t != NULL) {
		if (x < t->data) {
			remove(x, t->left);
		}
		else if (x > t->data) {
			remove(x, t->right);
		}
		else {
			if (t->left != NULL && t->right != NULL) {
				t->data = findMin(t->right)->data;
				remove(t->data, t->right);
			}
			else {
				BinaryNode<Comparable>* oldNode = t;
				if (t->left != NULL) {
					t = t->left;
				}
				else {
					t = t->right;
				}
				delete oldNode;
			}
		}
	}
}

template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty() {
	makeEmpty(root);
}

template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode<Comparable>* &t) const {
	if (t != NULL) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}

	t = NULL;
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const {
	return (root == NULL) ? true: false;
}

template <class Comparable>
void BinarySearchTree<Comparable>::printTree() const {
	if (!isEmpty()) {
		printTree(root);
	}
}

template <class Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode<Comparable>* t) const {
	if (t != NULL) {
		printTree(t->left);
		cout << t->data << endl;
		printTree(t->right);
	}
}

template <class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::clone(BinaryNode<Comparable>* t) const {

	if (t == NULL) {
		return NULL;
	}
	else {
		return new BinaryNode<Comparable>(t->data, clone(t->left), clone(t->right));
	}
}

template <class Comparable>
const BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree& rhs) {
	if (this != &rhs) {
		makeEmpty();
		root = clone(rhs.root);
	}
	return *this;

}


template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree() {
	makeEmpty();
}

template <class Comparable>
ostream& operator << (ostream& os, const BinarySearchTree<Comparable>& rhs) {
	os << "TREE OS:" << endl;
	rhs.printTree();
	return os;
}