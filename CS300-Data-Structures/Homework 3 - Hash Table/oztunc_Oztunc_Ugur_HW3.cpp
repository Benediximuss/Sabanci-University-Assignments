#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "HashTable.h"
#include "HashTable.cpp"

#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"

using namespace std;

// UGUR OZTUNC 28176
// CS300 HW3 HASH TABLES

void clearSpecials(string& dom) {
	for (int i = 0; i < dom.length(); i++)
	{
		if (isalpha(dom[i])) {
			dom[i] = tolower(dom[i]);
		}
		else {
			dom[i] = ' ';
		}
	}
}

int getIndex(vector<string>& list, string target) {
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == target) {
			return i;
		}
	}
}

bool isInVector(vector<DocumentItem>& list, string target) {
	bool res = false;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].documentName == target) {
			res = true;
			break;
		}
	}
	return res;
}

bool isAllTrue(vector<bool>& list) {
	bool res = true;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == false) {
			res = false;
		}
	}
	return res;
}

void queryHASH(string query, int& fileNumber, HashTable<WordItem>& hash, vector<string>& fileNames, int h, int o) {
	clearSpecials(query);
	istringstream ss(query);
	string qWord;

	vector<string> qWords;

	vector<vector<bool>> zart2;

	bool hic = false;

	int k = 0;
	while(ss >> qWord) {
		qWords.push_back(qWord);

		vector<bool> zart(fileNumber,true);

		WordItem newItem(qWord, "query");
		WordItem& tempItemHASH = hash.find(newItem);

		for (int i = 0; i < zart.size(); i++)
		{
			if (isInVector(tempItemHASH.documentList, fileNames[i]) == false) {
				zart[i] = false;
			}
		}

		zart2.push_back(zart);
		k++;
	}

	int kk = 0;
	while(kk != fileNumber) {

		vector<bool> bools(k, true);

		for (int i = 0; i < zart2.size(); i++)
		{
			if (zart2[i][kk] == false) {
				bools[i] = false;
			}
		}

		if (isAllTrue(bools) == true && h == o-1) {
			hic = true;

			cout << "in Document " << fileNames[kk] << ", ";

			for (int l = 0; l < qWords.size(); l++)
			{
				WordItem newItem(qWords[l], "query");
				WordItem& tempItemHASH = hash.find(newItem);
				int wCount;

				for (int abs = 0; abs < tempItemHASH.documentList.size(); abs++)
				{
					if (tempItemHASH.documentList[abs].documentName == fileNames[kk]) {
						wCount = tempItemHASH.documentList[abs].count;
					}
				}

				cout << ", " << qWords[l] << " found " << wCount << " times";
			}

			cout << "." << endl;
		}

		kk++;
	}


	if (hic == false && h == o-1) {
		cout << "No document contains the given query" << endl;
	}
}

void queryBST(string query, int& fileNumber, BinarySearchTree<WordItem>& BST, vector<string>& fileNames, int h, int o) {
	clearSpecials(query);
	istringstream ss(query);
	string qWord;

	vector<string> qWords;

	bool hic = false;

	vector<vector<bool>> zart2;

	int k = 0;
	while(ss >> qWord) {
		qWords.push_back(qWord);

		vector<bool> zart(fileNumber,true);

		WordItem newItem(qWord, "query");
		WordItem& tempItemHASH = BST.find(newItem);

		for (int i = 0; i < zart.size(); i++)
		{
			if (isInVector(tempItemHASH.documentList, fileNames[i]) == false) {
				zart[i] = false;
			}
		}

		zart2.push_back(zart);
		k++;
	}

	int kk = 0;
	while(kk != fileNumber) {

		vector<bool> bools(k, true);

		for (int i = 0; i < zart2.size(); i++)
		{
			if (zart2[i][kk] == false) {
				bools[i] = false;
			}
		}

		if (isAllTrue(bools) == true && h == o-1) {
			hic = true;

			cout << "in Document " << fileNames[kk] << ", ";

			for (int l = 0; l < qWords.size(); l++)
			{
				WordItem newItem(qWords[l], "query");
				WordItem& tempItemHASH = BST.find(newItem);
				int wCount;

				for (int abs = 0; abs < tempItemHASH.documentList.size(); abs++)
				{
					if (tempItemHASH.documentList[abs].documentName == fileNames[kk]) {
						wCount = tempItemHASH.documentList[abs].count;
					}
				}

				cout << ", " << qWords[l] << " found " << wCount << " times";
			}

			cout << "." << endl;
		}

		kk++;
	}

	if (hic == false && h == o-1) {
		cout << "No document contains the given query" << endl;
	}
}


int main() {

	int fileNumber;
	cout << "Enter number of input files: ";
	cin >> fileNumber;

	vector<string> fileNames(fileNumber);

	for (int i = 1; i <= fileNumber; i++)
	{
		cout << "Enter " << i << ". file name: ";
		cin >> fileNames[i-1];
	}

	//int fileNumber = 2;
	//vector<string> fileNames(fileNumber);
	//fileNames[0] = "a.txt";
	//fileNames[1] = "b.txt";
	////fileNames[2] = "c.txt";

	const WordItem WordItem_NOTFOUND(-1);
	BinarySearchTree<WordItem> bst(WordItem_NOTFOUND);
	HashTable<WordItem> hash(50);
	
	for (int i = 0; i < fileNumber; i++)
	{
		ifstream input;
		string fileName = fileNames[i];
		input.open(fileName.c_str());

		string line;
		int no = 1;
		while(getline(input, line)) {
			//if (i == 1) {
			//	cout << no << ".line" << endl;
			//	no++;
			//	if (no == 4) {
			//		cout << "yarraklIK VAR" << endl;
			//	}

			//}

			clearSpecials(line);
			istringstream ss(line);
			string word;

			while(ss >> word) {
				WordItem newItem(word, fileName);
				
				if (bst.find(newItem) == WordItem_NOTFOUND) {
					bst.insert(newItem);
				}
				else {
					WordItem& tempItemBST = bst.find(newItem);

					bool isDocumentExist = false;

					for (int j = 0; j < tempItemBST.documentList.size(); j++)
					{
						if (tempItemBST.documentList[j].documentName == fileName) {
							isDocumentExist = true;
							tempItemBST.documentList[j].count++;
						}
					}

					if (isDocumentExist == false) {
						DocumentItem newDocumentItem;
						newDocumentItem.documentName = fileName;
						newDocumentItem.count = 1;

						tempItemBST.documentList.push_back(newDocumentItem);

					}
				}

				if (hash.isExist(newItem) == -1) {
					hash.insert(newItem);
				}
				else {
					WordItem& tempItemHASH = hash.find(newItem);

					bool isDocumentExist2 = false;

					for (int k = 0; k < tempItemHASH.documentList.size(); k++)
					{
						if (tempItemHASH.documentList[k].documentName == fileName) {
							isDocumentExist2 = true;
							tempItemHASH.documentList[k].count++;
						}
					}

					if (isDocumentExist2 == false) {
						DocumentItem newDocumentItem2;
						newDocumentItem2.documentName = fileName;
						newDocumentItem2.count = 1;

						tempItemHASH.documentList.push_back(newDocumentItem2);
					}
				}
			}
		}
		input.close();
	}

	cout << endl;
	hash.printAfterPre();

	string query;
	cout << "Enter queried words in one line: ";
	cin.clear();
	cin.ignore();
	getline(cin, query);


	int k = 20;
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
	{
		queryBST(query, fileNumber, bst, fileNames, i, k);
	}
	auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
	(std::chrono::high_resolution_clock::now() - start);
	
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
	{
		queryHASH(query, fileNumber, hash, fileNames, i, k);
	}
	auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
	(std::chrono::high_resolution_clock::now() - start);

	cout << "\nTime: " << BSTTime.count() / k << "\n";

	cout << "\nTime: " << HTTime.count() / k << "\n";
	
	cout << "Speed Up: " << (double)BSTTime.count()/HTTime.count() << endl;




	return 0;
}

