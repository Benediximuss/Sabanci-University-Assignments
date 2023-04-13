#ifndef _NOTEBOOKSTRUCTS_H
#define _NOTEBOOKSTRUCTS_H

#include <string>

using namespace std;

struct sectionItem
{
	string itemTitle;
	string itemInfo;
	int notFound;

	sectionItem() { // FOR NOT_FOUND OBJECT
		notFound = -1;
	}

	sectionItem(string &title) { // ONLY TITLE (i.e: for using to pass to find function)
		itemTitle = title;
		notFound = 0;
	}

	sectionItem(string &title, string &info) {
		itemTitle = title;
		itemInfo = info;
		notFound = 0;
	}

	const sectionItem& operator = (const sectionItem& rhs) {
		this->itemTitle = rhs.itemTitle;
		this->itemInfo = rhs.itemInfo;
		this->notFound = rhs.notFound;
		return *this;
	}
};

bool operator == (const sectionItem& lhs, const sectionItem& rhs) {
	return (lhs.itemTitle == rhs.itemTitle && lhs.notFound == rhs.notFound);
}
bool operator != (const sectionItem& lhs, const sectionItem& rhs) {
	return lhs.itemTitle != rhs.itemTitle;
}
bool operator < (const sectionItem& lhs, const sectionItem& rhs) {
	return lhs.itemTitle < rhs.itemTitle;
}
bool operator > (const sectionItem& lhs, const sectionItem& rhs) {
	return lhs.itemTitle > rhs.itemTitle;
}
bool operator <= (const sectionItem& lhs, const sectionItem& rhs) {
	return lhs.itemTitle <= rhs.itemTitle;
}
bool operator >= (const sectionItem& lhs, const sectionItem& rhs) {
	return lhs.itemTitle >= rhs.itemTitle;
}
ostream& operator << (ostream& os, const sectionItem& rhs) {
	os<< rhs.itemTitle;
	return os;
}



template <class TreeType>
struct sectionNode
{
	string sectionTitle;
	int notFound;
	TreeType itemTree;

	sectionNode(const sectionNode<TreeType>& rhs) // COPY CONSTRUCTOR
		: sectionTitle(rhs.sectionTitle), notFound(rhs.notFound), itemTree(rhs.itemTree) {}

	sectionNode(int a, sectionItem b) // FOR NOT_FOUND OBJECT
		: notFound(a), itemTree(b) {}

	sectionNode(string &title, sectionItem b)
		: sectionTitle(title), notFound(0), itemTree(b) {}
};

template <class TreeType>
bool operator == (const sectionNode<TreeType>& lhs, const sectionNode<TreeType>& rhs) {
	return (lhs.sectionTitle == rhs.sectionTitle && lhs.notFound == rhs.notFound);
}
template <class TreeType>
bool operator != (const sectionNode<TreeType>& lhs, const sectionNode<TreeType>& rhs) {
	return lhs.sectionTitle != rhs.sectionTitle;
}
template <class TreeType>
bool operator < (const sectionNode<TreeType>& lhs, const sectionNode<TreeType>& rhs) {
	return lhs.sectionTitle < rhs.sectionTitle;
}
template <class TreeType>
bool operator > (const sectionNode<TreeType>& lhs, const sectionNode<TreeType>& rhs) {
	return lhs.sectionTitle > rhs.sectionTitle;
}
template <class TreeType>
bool operator <= (const sectionNode<TreeType>& lhs, const sectionNode<TreeType>& rhs) {
	return lhs.sectionTitle <= rhs.sectionTitle;
}
template <class TreeType>
bool operator >= (const sectionNode<TreeType>& lhs, const sectionNode<TreeType>& rhs) {
	return lhs.sectionTitle >= rhs.sectionTitle;
}
template <class TreeType>
ostream& operator << (ostream& os, const sectionNode<TreeType>& rhs) {
	os << rhs.sectionTitle;
	return os;
}



#endif