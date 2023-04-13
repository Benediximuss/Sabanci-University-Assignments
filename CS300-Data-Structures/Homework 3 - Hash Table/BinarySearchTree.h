#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H

#include <iostream>
#include <string>

using namespace std;

template <class Comparable>
class BinarySearchTree;

template<class Comparable>
class BinaryNode
{
	Comparable data;
	BinaryNode* left;
	BinaryNode* right;

	BinaryNode(const Comparable &theData, BinaryNode* lt, BinaryNode* rt) 
		: data(theData), left(lt), right(rt) {}

	friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree
{
public:
	explicit BinarySearchTree(const Comparable &notFound);
	
	BinarySearchTree(const BinarySearchTree<Comparable>& rhs)
		: ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), root(NULL)
	{
		*this = rhs;
	}

	~BinarySearchTree();

	Comparable& find(const Comparable& x);
	const Comparable& findMin() const;
	const Comparable& findMax() const;

	void insert(const Comparable& x);
	void remove(const Comparable& x);

	void makeEmpty();
	bool isEmpty() const;

	void printTree() const;

	const BinarySearchTree<Comparable>& operator=(const BinarySearchTree& rhs);

private:
	BinaryNode<Comparable> *root;
	Comparable ITEM_NOT_FOUND;

	Comparable& elementAt(BinaryNode<Comparable>* t);

	BinaryNode<Comparable>* find(const Comparable& x, BinaryNode<Comparable>* t);
	BinaryNode<Comparable>* findMin(BinaryNode<Comparable>* t) const;
	BinaryNode<Comparable>* findMax(BinaryNode<Comparable>* t) const;

	void insert(const Comparable& x, BinaryNode<Comparable>* &t) const;
	void remove(const Comparable& x, BinaryNode<Comparable>* &t) const;

	void makeEmpty(BinaryNode<Comparable>* &t) const;

	void printTree(BinaryNode<Comparable>* t) const;
	
	BinaryNode<Comparable>* clone(BinaryNode<Comparable>* t) const;

};

#endif