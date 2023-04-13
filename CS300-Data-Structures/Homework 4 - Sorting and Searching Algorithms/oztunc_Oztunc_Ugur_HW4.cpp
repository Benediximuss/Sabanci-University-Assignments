#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

#include "SortingAlgorithms.h"

using namespace std;

struct contactEntry
{
	string name;
	string number;
	string city;

	contactEntry() {}

	contactEntry(string a, string b, string c)
		: name(a), number(b), city(c) {}

	bool operator < (const contactEntry& rhs) {
		return name < rhs.name;
	}
	bool operator > (const contactEntry& rhs) {
		return name > rhs.name;
	}
	bool operator == (const contactEntry& rhs) {
		return (name == rhs.name && number == rhs.number && city == rhs.city);
	}
	bool operator != (const contactEntry& rhs) {
		return !(*this == rhs);
	}
	bool operator <= (const contactEntry& rhs) {
		return name <= rhs.name;
	}
	bool operator >= (const contactEntry& rhs) {
		return name >= rhs.name;
	}
};

ostream& operator << (ostream& os, const contactEntry& rhs) {
	os << rhs.name << " " << rhs.number << " " << rhs.city;
	return os;
}

bool partialCheck(const string& dom, const string& target) {
	bool res = false;

	int len = target.length();
	string newStr = dom.substr(0, len);

	if (dom.substr(0, target.length()) == target) {
		res = true;
	}

	return res;
}

int binarySearchExactMatch(const vector<contactEntry>& list, const string& target) {
    int low = 0;
    int high = list.size()-1;
    int mid;

    while (low <= high)	{  
		mid = (low + high)/2;
		if (list[mid].name == target) {
			return mid;
		}
        else if (list[mid].name < target) {
			low = mid + 1;
		}
        else {
			high = mid - 1;
		}
    }

    return -1;
}

int sequentialSearchExactMatch(const vector<contactEntry>& list, const string& target) {
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].name == target) {
			return i;
		}
	}

	return -1;
}

int binarySearchPartial(const vector<contactEntry>& list, const string& target) {
    int low = 0;
    int high = list.size()-1;
    int mid;

    while (low <= high)	{  
		mid = (low + high)/2;
		if (partialCheck(list[mid].name, target) == true && partialCheck(list[mid-1].name, target) == false) {
			return mid;
		}
        else if (list[mid].name < target) {
			low = mid + 1;
		}
        else {
			high = mid - 1;
		}
    }

    return -1;
}

vector<int> sequentialSearchPartial(const vector<contactEntry>& list, const string& target) {
	vector<int> idxs;

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].name >= target) {
			if (partialCheck(list[i].name, target)) {
				idxs.push_back(i);
			}
		}
	}

	return idxs;
}

void strToUpper(string& dom) {
	for (int i = 0; i < dom.length(); i++)
	{
		dom[i] = toupper(dom[i]);
	}
}

template <class Comparable>
double SortShowTime(vector<Comparable>& vector, string sortingAlgorithm) {
	auto start = std::chrono::high_resolution_clock::now();
	if (sortingAlgorithm == "Quick") {
		quicksort(vector);
	} else if (sortingAlgorithm == "Insertion") {
		insertionSort(vector);
	} else if (sortingAlgorithm == "Merge") {
		mergeSort(vector, 0, vector.size()-1);
	} else if (sortingAlgorithm == "Heap") {
		heapsort(vector);
	} else {
		cout << "ZORT_414" << endl;
	}
	auto sortTime = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - start);
	
	cout << sortingAlgorithm << " Sort Time: " << sortTime.count() << " Nanoseconds" << endl;

	return (double) sortTime.count();
}


int main() {
	
	string fName;
	cout << "Please enter the contact file name: \n";
	cin >> fName;

	string queryInput;
	cout << "Please enter the word to be queried: \n";
	cin.ignore();
	cin.clear();
	getline(cin, queryInput);

	cout << endl;

	vector<contactEntry> vector1;
	vector<contactEntry> vector2;
	vector<contactEntry> vector3;
	vector<contactEntry> vector4;

	ifstream input;
	input.open(fName.c_str());

	string line;
	while (getline(input,line))
	{
		line[line.find(' ')] = '_';
	
		contactEntry tempEntry;
		istringstream ss(line);
		ss >> tempEntry.name >> tempEntry.number >> tempEntry.city;

		tempEntry.name[tempEntry.name.find('_')] = ' ';
		strToUpper(tempEntry.name);

		vector1.push_back(tempEntry);
		vector2.push_back(tempEntry);
		vector3.push_back(tempEntry);
		vector4.push_back(tempEntry);
	}

	input.close();

	cout << "Sorting the vector copies" << endl;
	cout << "======================================" << endl;

	double quickTime = SortShowTime(vector1, "Quick");
	double insertionTime = SortShowTime(vector2, "Insertion");
	double mergeTime = SortShowTime(vector3, "Merge");
	double heapTime = SortShowTime(vector4, "Heap");

	cout << endl;

	
	cout << "Searching for " << queryInput << endl;
	cout << "======================================" << endl;
	strToUpper(queryInput);

	double searchSpeedUp = 0;

	if (count(queryInput.begin(), queryInput.end(), ' ') == 1) {

		auto start = std::chrono::high_resolution_clock::now();
		int idxBS = binarySearchExactMatch(vector1, queryInput);
		auto searchTime = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - start);

		if (idxBS == -1) {
			cout << queryInput << " does NOT exist in the dataset" << endl;
		}
		else {
			cout << vector1[idxBS] << endl;
		}
		cout << "Binary Search Time: " << searchTime.count() << " Nanoseconds" << endl << endl;


		cout << "Search results for Sequential Search:" << endl;

		auto start2 = std::chrono::high_resolution_clock::now();
		int idxSS = sequentialSearchExactMatch(vector1, queryInput);
		auto searchTime2 = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - start);

		if (idxSS == -1) {
			cout << queryInput << " does NOT exist in the dataset" << endl;
		}
		else {
			cout << vector1[idxSS] << endl;
		}

		cout << "Sequential Search Time: " << searchTime2.count() << " Nanoseconds" << endl;

		searchSpeedUp = searchTime2.count() / searchTime.count();
	}

	else {

		auto start = std::chrono::high_resolution_clock::now();

		int idxBS = binarySearchPartial(vector1, queryInput);

		if (idxBS == -1) {
			cout << queryInput << " does NOT exist in the dataset" << endl;
		}
		else {
			while (true) {
				cout << vector1[idxBS] << endl;
				idxBS++;
				if (!partialCheck(vector1[idxBS].name, queryInput)) {
					break;
				}
			}
		}

		auto searchTime = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - start);
		cout << "Binary Search Time: " << searchTime.count() << " Nanoseconds" << endl << endl;


		cout << "Search results for Sequential Search:" << endl;

		auto start2 = std::chrono::high_resolution_clock::now();

		vector<int> foundsList2(sequentialSearchPartial(vector4, queryInput));

		if (foundsList2.size() == 0) {
			cout << queryInput << " does NOT exist in the dataset" << endl;
		}
		else {
			for (int i = 0; i < foundsList2.size(); i++)
			{
				cout << vector4[foundsList2[i]] << endl;
			}
		}

		auto searchTime2 = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - start);
		cout << "Sequential Search Time: " << searchTime2.count() << " Nanoseconds" << endl;
		
		searchSpeedUp = searchTime2.count() / searchTime.count();
	}

	cout << endl;

	cout << "SpeedUp between Search Algorithms" << endl;
	cout << "======================================" << endl;
	cout << "(Sequential Search / Binary Search) SpeedUp = " << searchSpeedUp << endl;

	cout << endl;

	cout << "SpeedUps between Sorting Algorithms" << endl;
	cout << "======================================" << endl;
	cout << "(Insertion Sort / Quick Sort) SpeedUp = " << insertionTime/quickTime << endl;
	cout << "(Merge Sort / Quick Sort) SpeedUp = " << mergeTime/quickTime << endl;
	cout << "(Heap Sort / Quick Sort) SpeedUp = " << heapTime/quickTime << endl;


	cout << endl;

	return 0;
}