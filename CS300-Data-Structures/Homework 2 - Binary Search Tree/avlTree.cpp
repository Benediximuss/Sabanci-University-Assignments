#include "avlTree.h"

#include <iostream>
#include <string>

using namespace std;

template <class Comparable>
AVLTree<Comparable>::AVLTree(const Comparable &notFound)
	: ITEM_NOT_FOUND(notFound), root(NULL) {}

template <class Comparable>
Comparable& AVLTree<Comparable>::elementAt(AVLNode<Comparable>* position) {
	if (position == NULL) {
		return ITEM_NOT_FOUND;
	}
	else {
		return position->data;
	}
}

template <class Comparable>
Comparable& AVLTree<Comparable>::find(const Comparable& x) {
	return elementAt(find(x, root));
}

template <class Comparable>
AVLNode<Comparable>* AVLTree<Comparable>::find(const Comparable& x, AVLNode<Comparable>* t) {
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
const Comparable& AVLTree<Comparable>::findMin() const {
	return elementAt(findMin(root));
}

template <class Comparable>
AVLNode<Comparable>* AVLTree<Comparable>::findMin(AVLNode<Comparable>* t) const {
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
const Comparable& AVLTree<Comparable>::findMax() const {
	return elementAt(findMax(root));
}

template <class Comparable>
AVLNode<Comparable>* AVLTree<Comparable>::findMax(AVLNode<Comparable>* t) const {
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
void AVLTree<Comparable>::insert(const Comparable& x) {
	insert(x, root);
}

template <class Comparable>
void AVLTree<Comparable>::insert(const Comparable& x, AVLNode<Comparable>* &t) const {
	if (t == NULL) {
		t = new AVLNode<Comparable>(x, NULL, NULL);
	}
	else if (x < t->data) {
		insert(x, t->left);

		if (height(t->left) - height(t->right) == 2) {
			if (x < t->left->data) {
				rotateWithLeftChild(t);
			}
			else {
				doubleWithLeftChild(t);
			}
		}
	}
	else if (x > t->data) {
		insert(x, t->right);

		if (height(t->right) - height(t->left) == 2) {
			if (x > t->right->data) {
				rotateWithRightChild(t);
			}
			else {
				doubleWithRightChild(t);
			}
		}
	}

	t->height = max(height(t->left), height(t->right)) + 1;
}

template <class Comparable>
void AVLTree<Comparable>::remove(const Comparable& x) {
	remove(x, root);
}

template <class Comparable>
void AVLTree<Comparable>::remove(const Comparable& x, AVLNode<Comparable>* &t) const {
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
				AVLNode<Comparable>* oldNode = t;
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
void AVLTree<Comparable>::makeEmpty() {
	makeEmpty(root);
}

template <class Comparable>
void AVLTree<Comparable>::makeEmpty(AVLNode<Comparable>* &t) const {
	if (t != NULL) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}

	t = NULL;
}

template <class Comparable>
bool AVLTree<Comparable>::isEmpty() const {
	return (root == NULL) ? true: false;
}

template <class Comparable>
void AVLTree<Comparable>::printTree() const {
	if (!isEmpty()) {
		printTree(root);
	}
}

template <class Comparable>
void AVLTree<Comparable>::printTree(AVLNode<Comparable>* t) const {
	if (t != NULL) {
		printTree(t->left);
		cout << t->data << endl;
		printTree(t->right);
	}
}

template <class Comparable>
AVLNode<Comparable>* AVLTree<Comparable>::clone(AVLNode<Comparable>* t) const {
	if (t == NULL) {
		return NULL;
	}
	else {
		return new AVLNode<Comparable>(t->data, clone(t->left), clone(t->right));
	}
}

template <class Comparable>
const AVLTree<Comparable>& AVLTree<Comparable>::operator=(const AVLTree& rhs) {
	if (this != &rhs) {
		makeEmpty();
		root = clone(rhs.root);
	}
	return *this;
}

template <class Comparable>
int AVLTree<Comparable>::height(AVLNode<Comparable>* t) const {
	return (t == NULL) ? -1: t->height;
}

template <class Comparable>
int AVLTree<Comparable>::max(int lhs, int rhs) const {
	return (lhs > rhs) ? lhs: rhs;
}

template <class Comparable>
void AVLTree<Comparable>::rotateWithLeftChild(AVLNode<Comparable>* &k2) const {
	AVLNode<Comparable>* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
}

template <class Comparable>
void AVLTree<Comparable>::rotateWithRightChild(AVLNode<Comparable>* &k1) const {
	AVLNode<Comparable> *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;
	k1 = k2;
}

template <class Comparable>
void AVLTree<Comparable>::doubleWithLeftChild(AVLNode<Comparable>* &k3) const {
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

template <class Comparable>
void AVLTree<Comparable>::doubleWithRightChild(AVLNode<Comparable>* &k1) const {
	rotateWithLeftChild(k1->right);
	rotateWithRightChild(k1);
}

template <class Comparable>
AVLTree<Comparable>::~AVLTree() {
	makeEmpty();
}

template <class Comparable>
ostream& operator << (ostream& os, const AVLTree<Comparable>& rhs) {
	os << "TREE OS:" << endl;
	rhs.printTree();
	return os;
}