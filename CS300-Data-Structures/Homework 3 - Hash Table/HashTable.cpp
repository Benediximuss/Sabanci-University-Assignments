#include "HashTable.h"

#include <iostream>

using namespace std;

template<class HashedObj>
HashTable<HashedObj>::HashTable(int n)
	: array(nextPrime(n)), stored(0) {}

template <class HashedObj>
bool HashTable<HashedObj>::isPrime(int n) {
	if (n == 2) { return true; }
	else {
		int divs = 0;

		for (int i = 2; i < n; i++) {
			if (n % i == 0) { divs += 1; break; }
		}

		if (divs == 0) { return true; }
		else { return false; }
	}
}

template <class HashedObj>
int HashTable<HashedObj>::nextPrime(int n) {
	if (n % 2 == 0) {
		n++;
	}

	while(!isPrime(n)) {
		n += 2;
	}

	return n;
}

//template <class HashedObj>
//int HashTable<HashedObj>::hashFunction(WordItem& input) { // DISARI ATILABiLiR
//	int sum = 0;
//
//	for (int i = 0; i < input.word.length(); i++) {
//		sum = sum + input.word[i];
//	}
//
//    return (sum % array.size());
//}

template <class HashedObj>
int HashTable<HashedObj>::hashFunction(WordItem& input) {
    int hashVal = 0;
	string key = input.word;
  
    for (int i = 0; i < key.length();i++) 
	  hashVal = 37 * hashVal + key[ i ];

    hashVal = hashVal % array.size();

    if (hashVal < 0) 
	  hashVal += array.size();

   return hashVal;
}

//template <class HashedObj>
//int HashTable<HashedObj>::findPos(HashedObj& x) {
//	int currentPos = hashFunction(x);
//	
//	int i = 1; // linear probing
//	while(array[currentPos].info != EMPTY && array[currentPos].element != x) {
//		if (i == 25) {
//			cout << "YARRRAKK" << endl;
//		}
//
//		currentPos += i;
//		i++;
//
//		if (currentPos >= array.size()) {
//			currentPos -= array.size();
//		}
//
//		cout << "__" << i << endl;
//	}
//
//	return currentPos;
//}

template <class HashedObj>
int HashTable<HashedObj>::findPos(HashedObj& x) {
	int currentPos = hashFunction(x);
	int collisionNum = 0;
	
	while(array[currentPos].info != EMPTY && array[currentPos].element != x) {

		currentPos += 2 * ++collisionNum - 1;

		if (currentPos >= array.size()) {
			currentPos -= array.size();
		}

	}

	return currentPos;
}

template <class HashedObj>
bool HashTable<HashedObj>::insert(HashedObj& x) {
	int targetPos = findPos(x);
	
	if (array[targetPos].info == ACTIVE) {
		return false;
	}
	else {
		array[targetPos] = HashEntry(x, ACTIVE);
		stored++;

		if (stored >= array.size() / 1.25) {
			rehash();
		}

		return true;
	}
}

template <class HashedObj>
void HashTable<HashedObj>::remove(HashedObj& x) {
	int targetPos = findPos(x);

	if (array[targetPos].info == ACTIVE) {
		array[targetPos].info = DELETED;
		stored--;
	}
}

template <class HashedObj>
void HashTable<HashedObj>::rehash() {
	vector<HashEntry> oldArray = array;
	
	array.resize(nextPrime(2*oldArray.size())); // oldArray.size() yerine direk capacity olabilir !!!!
	for (int i = 0; i < array.size(); i++) // resize tricki yeni elemeanlar boþ olcak ama eskilere kadarý empty yapsak yeter
	{
		array[i].info = EMPTY;
	}

	stored = 0;
	for (int i = 0; i < oldArray.size(); i++)
	{
		if (oldArray[i].info == ACTIVE) {
			insert(oldArray[i].element);
		}
	}

	cout << "rehashed..." << endl;
	cout << "previous table size:" << oldArray.size() << ", new table size: " << array.size() << ", current unique word count: ";
	cout << stored << ", current load factor: " << double(stored)/array.size() << endl;
}

template <class HashedObj>
int HashTable<HashedObj>::isExist(HashedObj& x) {
	int currentPos = findPos(x);
	
	if (array[currentPos].info == ACTIVE) {
		return currentPos;
	}

	else {
		return -1;
	}
}

//template <class HashedObj>
//HashedObj& HashTable<HashedObj>::find(int idx) {
//	return array[idx];
//}

template <class HashedObj>
HashedObj& HashTable<HashedObj>::find(HashedObj& x) {
	return array[findPos(x)].element;
}

template <class HashedObj>
void HashTable<HashedObj>::printAfterPre() {
	cout << "After preprocessing, the unique word count is " << stored << ". Current load ratio is " << double(stored)/array.size() << endl;
}


