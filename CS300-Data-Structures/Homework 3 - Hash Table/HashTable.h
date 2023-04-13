#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct DocumentItem
{
	string documentName;
	int count;
};

struct WordItem
{
	string word;
	vector<DocumentItem> documentList;

	WordItem() {}

	WordItem(string newWord, string docName)
		: word(newWord), documentList(1)
	{
		documentList[0].documentName = docName;
		documentList[0].count = 1;
	}

	WordItem(int n)
		: word("-1"), documentList(0) {}

};

inline bool operator == (const WordItem& lhs, const WordItem& rhs) {
	return lhs.word == rhs.word;
}
inline bool operator != (const WordItem& lhs, const WordItem& rhs) {
	return lhs.word != rhs.word;
}
inline bool operator < (const WordItem& lhs, const WordItem& rhs) {
	return lhs.word < rhs.word;
}
inline bool operator > (const WordItem& lhs, const WordItem& rhs) {
	return lhs.word > rhs.word;
}
inline bool operator <= (const WordItem& lhs, const WordItem& rhs) {
	return lhs.word <= rhs.word;
}
inline bool operator >= (const WordItem& lhs, const WordItem& rhs) {
	return lhs.word >= rhs.word;
}

template <class HashedObj>
class HashTable
{
public:
	HashTable(int);

	bool insert(HashedObj& x);
	void remove(HashedObj& x);
	
	int isExist(HashedObj&);
	HashedObj& find(HashedObj&);

	void printAfterPre();

	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj& e=HashedObj(), EntryType i=EMPTY)
			: element(e), info(i) {}
	};

	bool isPrime(int);
	int nextPrime(int);

	int hashFunction(WordItem&);
	int findPos(HashedObj&);

	void rehash();

	vector<HashEntry> array;
	int stored;

};




#endif