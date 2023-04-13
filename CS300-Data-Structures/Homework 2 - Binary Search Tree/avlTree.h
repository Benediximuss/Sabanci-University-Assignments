#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <iostream>
#include <string>

using namespace std;

template <class Comparable>
class AVLTree;

template<class Comparable>
class AVLNode
{
	Comparable data;
	AVLNode* left;
	AVLNode* right;
	int height;

	AVLNode(const Comparable &theData, AVLNode* lt, AVLNode* rt, int h = 0)
		: data(theData), left(lt), right(rt), height(h) {}

	friend class AVLTree<Comparable>;
};

template <class Comparable>
class AVLTree
{
public:
	explicit AVLTree(const Comparable &notFound);
	
	AVLTree(const AVLTree<Comparable>& rhs)
		: ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), root(NULL)
	{
		*this = rhs;
	}
	~AVLTree();

	Comparable& find(const Comparable& x);
	const Comparable& findMin() const;
	const Comparable& findMax() const;

	void insert(const Comparable& x);
	void remove(const Comparable& x);

	void makeEmpty();
	bool isEmpty() const;

	void printTree() const;

	const AVLTree<Comparable>& operator=(const AVLTree& rhs);

private:
	AVLNode<Comparable> *root;
	Comparable ITEM_NOT_FOUND;

	Comparable& elementAt(AVLNode<Comparable>* t);

	AVLNode<Comparable>* find(const Comparable& x, AVLNode<Comparable>* t);
	AVLNode<Comparable>* findMin(AVLNode<Comparable>* t) const;
	AVLNode<Comparable>* findMax(AVLNode<Comparable>* t) const;

	void insert(const Comparable& x, AVLNode<Comparable>* &t) const;
	void remove(const Comparable& x, AVLNode<Comparable>* &t) const;

	void makeEmpty(AVLNode<Comparable>* &t) const;

	void printTree(AVLNode<Comparable>* t) const;
	AVLNode<Comparable>* clone(AVLNode<Comparable>* t) const;

	int height(AVLNode<Comparable>* t) const;
	int max(int lhs, int rhs) const;

	void rotateWithLeftChild(AVLNode<Comparable>* &k2) const;
    void rotateWithRightChild(AVLNode<Comparable>* &k1) const;
    void doubleWithLeftChild(AVLNode<Comparable>* &k3) const;
    void doubleWithRightChild(AVLNode<Comparable>* &k1) const;
};








#endif