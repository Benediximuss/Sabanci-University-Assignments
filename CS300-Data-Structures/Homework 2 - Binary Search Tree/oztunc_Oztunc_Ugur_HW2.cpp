#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"
#include "avlTree.h"
#include "avlTree.cpp"
#include "notebookstructs.h"

using namespace std;

// UGUR OZTUNC 28176
// I increased stack size by VS project properties while doing homework, so I did not use '#pragma comment". If it is necessary please add it while grading. 

void swapSpaceDash(string &str) { // changing dashes in the line to spaces and vice-versa in before using string stream, and after parsing the line swapping again
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == '-') {
			str[i] = ' ';
		}
		else if (str[i] == ' ') {
			str[i] = '-';
		}
	}
}

void generateNotebooks(BinarySearchTree<sectionNode<BinarySearchTree<sectionItem>>> &notebookBST, AVLTree<sectionNode<AVLTree<sectionItem>>> &notebookAVL, const sectionItem &itemNOT) {
	cout << "Welcome to the Notebook!" << endl << endl;

	ifstream input;
	string fname = "data.txt";
	input.open(fname.c_str());

	sectionNode<BinarySearchTree<sectionItem>>* currentSectionPtrBST = NULL;
	sectionNode<AVLTree<sectionItem>>* currentSectionPtrAVL = NULL;	

	string line;

	long long currentSectionTimerAVL = 0;
	long long currentSectionTimerBST = 0;

	// At file reading part, the program first creates the whole item tree, then insert it to the sectionNode and insert that sectionNode to the notebook.
	// To do this, I used 'currentSectionPtrBST' and 'currentSectionPtrAVL' which used for dynamic memory allocation in order to preserve section title and item info after each while loop.

	auto startr = chrono::high_resolution_clock::now();
	while(getline(input, line)) {
		
		if (line[0] != '-') { // If current line is a section title..
			if (currentSectionPtrBST != NULL) { // ..and if it is not the firs line, insert section to the main notebooks
				auto start1 = chrono::high_resolution_clock::now();
				notebookAVL.insert(*currentSectionPtrAVL);
				auto end1 = chrono::high_resolution_clock::now();
				currentSectionTimerAVL += (end1-start1).count() / 1000.0;

				cout << "Section \"" << currentSectionPtrAVL->sectionTitle << "\" has been inserted into the AVL notebook." << endl;
				
				cout << "[AVL] Elapsed time: " << currentSectionTimerAVL << " microseconds" << endl;
				currentSectionTimerAVL = 0;

				auto start2 = chrono::high_resolution_clock::now();
				notebookBST.insert(*currentSectionPtrBST);
				auto end2 = chrono::high_resolution_clock::now();
				currentSectionTimerBST += (end2-start2).count() / 1000.0;

				cout << "Section \"" << currentSectionPtrBST->sectionTitle << "\" has been inserted into the BST notebook." << endl;
				
				cout << "[BST] Elapsed time: " << currentSectionTimerBST << " microseconds" << endl;
				currentSectionTimerBST = 0;

				delete currentSectionPtrAVL;
				delete currentSectionPtrBST;

				cout << endl;
			}

			currentSectionPtrBST = new sectionNode<BinarySearchTree<sectionItem>>(line, itemNOT);
			currentSectionPtrAVL = new sectionNode<AVLTree<sectionItem>>(line, itemNOT);
		}
		else { // if current line is an item
			swapSpaceDash(line);
			string currentItemTitle, currentItemInfo;
			istringstream ss(line);
			ss >> currentItemTitle >> currentItemInfo;
			swapSpaceDash(currentItemTitle);
			swapSpaceDash(currentItemInfo);
			sectionItem currentItem(currentItemTitle, currentItemInfo);

			auto start3 = chrono::high_resolution_clock::now();
			currentSectionPtrAVL->itemTree.insert(currentItem);
			auto end3 = chrono::high_resolution_clock::now();
			currentSectionTimerAVL += (end3-start3).count() / 1000.0;

			auto start4 = chrono::high_resolution_clock::now();
			currentSectionPtrBST->itemTree.insert(currentItem);
			auto end4 = chrono::high_resolution_clock::now();
			currentSectionTimerBST += (end4-start4).count() / 1000.0;
		}
	}
	
	input.close();

	auto start5 = chrono::high_resolution_clock::now();
	notebookAVL.insert(*currentSectionPtrAVL); // insert last section after reading file ended
	auto end5 = chrono::high_resolution_clock::now();
	currentSectionTimerAVL += (end5-start5).count() / 1000.0;

	cout << "Section \"" << currentSectionPtrAVL->sectionTitle << "\" has been inserted into the AVL notebook." << endl;
	
	cout << "[AVL] Elapsed time: " << currentSectionTimerAVL << " microseconds" << endl;

	auto start2 = chrono::high_resolution_clock::now();
	notebookBST.insert(*currentSectionPtrBST);
	auto end2 = chrono::high_resolution_clock::now();
	currentSectionTimerBST += (end2-start2).count() / 1000.0;

	cout << "Section \"" << currentSectionPtrBST->sectionTitle << "\" has been inserted into the BST notebook." << endl;
	
	cout << "[BST] Elapsed time: " << currentSectionTimerBST << " microseconds" << endl;
	currentSectionTimerBST = 0;

	delete currentSectionPtrBST;
	delete currentSectionPtrAVL;
}

int sectionMenu(BinarySearchTree<sectionNode<BinarySearchTree<sectionItem>>> &notebookBST, AVLTree<sectionNode<AVLTree<sectionItem>>> &notebookAVL, const sectionItem &itemNOT, const sectionNode<BinarySearchTree<sectionItem>> &BSTsectionNOT, const sectionNode<AVLTree<sectionItem>> &AVLsectionNOT) {
	string currentSectionTitle;
	cout << "Enter the title of the section: ";
	cin >> currentSectionTitle;

	// sectionNodes to pass to find function in order to find target sectionTitle
	sectionNode<AVLTree<sectionItem>> currentSectionNodeAVL(currentSectionTitle, itemNOT);
	sectionNode<BinarySearchTree<sectionItem>> currentSectionNodeBST(currentSectionTitle, itemNOT);

	// assigning find results to referance variables in order not to call find function to find current section again and again, and lose time
	sectionNode<AVLTree<sectionItem>>& sectionPtrAVL = notebookAVL.find(currentSectionNodeAVL);
	sectionNode<BinarySearchTree<sectionItem>>& sectionPtrBST = notebookBST.find(currentSectionNodeBST);
	
	int menuPrint = 3;

	if (sectionPtrAVL == AVLsectionNOT) {
		cout << "Invalid title!" << endl;
		menuPrint =  -1;
	}
	else {
		cout << endl << "Selected section -> " << currentSectionTitle << endl;
		cout << "Please enter an input between [1 - 7]:" << endl;
		cout << "1- Display the items [AVL]" << endl;
		cout << "2- Display the items [BST]" << endl;
		cout << "3- Display the information of a item" << endl;
		cout << "4- Add new item" << endl;
		cout << "5- Update the information of a item" << endl;
		cout << "6- Delete an item" << endl;
		cout << "7- Return to main menu" << endl; 
		
		int choice = 0;
		while(choice != 7) {
			cout << "Input: ";
			cin >> choice;

			if (choice == 1) {
				cout << endl << "*****" << endl;
				sectionPtrAVL.itemTree.printTree();
				cout << "*****" << endl << endl;
			}
			else if (choice == 2) {
				cout << endl << "*****" << endl;
				sectionPtrBST.itemTree.printTree();
				cout << "*****" << endl << endl;
			}
			else if (choice == 3) {
				string targetItemTitle;
				cout << "Enter the title of the item: ";
				cin >> targetItemTitle;

				sectionItem targetItem(targetItemTitle);

				auto start1 = chrono::high_resolution_clock::now();
				sectionItem& dummy1 = sectionPtrAVL.itemTree.find(targetItem);
				auto end1 = chrono::high_resolution_clock::now();
				long long timer1 = (end1-start1).count() / 1000.0;
				cout << "[AVL] Elapsed time: " << timer1 << " microseconds" << endl;

				auto start2 = chrono::high_resolution_clock::now();
				sectionItem& dummy2 = sectionPtrBST.itemTree.find(targetItem);
				auto end2 = chrono::high_resolution_clock::now();
				long long timer2 = (end2-start2).count() / 1000.0;
				cout << "[BST] Elapsed time: " << timer2 << " microseconds" << endl;

				if (dummy1 == itemNOT) {
					cout << "Invalid title." << endl << endl;
				}
				else {
					cout << dummy1.itemInfo << endl << endl;
				}
			}
			else if (choice == 4) {
				string newItemTitle;
				cout << "Enter a title for the item: ";
				cin >> newItemTitle;
				
				sectionItem newItem(newItemTitle);

				if (sectionPtrAVL.itemTree.find(newItem) != itemNOT) {
					cout << "Item \"" << newItemTitle << "\" already exists in the \"" << currentSectionTitle << "\"." << endl << endl;
				}
				else {
					string newItemInfo;
					cout << "Enter the description for the item: ";
					cin >> newItemInfo;

					newItem.itemInfo = newItemInfo;

					auto start1 = chrono::high_resolution_clock::now();
					sectionPtrAVL.itemTree.insert(newItem);
					auto end1 = chrono::high_resolution_clock::now();
					long long timer1 = (end1-start1).count() / 1000.0;
					cout << "[AVL] Elapsed time: " << timer1 << " microseconds" << endl;

					auto start2 = chrono::high_resolution_clock::now();
					sectionPtrBST.itemTree.insert(newItem);
					auto end2 = chrono::high_resolution_clock::now();
					long long timer2 = (end2-start2).count() / 1000.0;
					cout << "[BST] Elapsed time: " << timer2 << " microseconds" << endl;
					

					cout << "The new item \"" << newItemTitle << "\" has been inserted." << endl << endl;
				}
			}
			else if (choice == 5) {
				string targetItemTitle;
				cout << "Enter the title of the item: ";
				cin >> targetItemTitle;

				sectionItem targetItem(targetItemTitle);

				auto start1 = chrono::high_resolution_clock::now();
				sectionItem& dummy1 = sectionPtrAVL.itemTree.find(targetItem);
				auto end1 = chrono::high_resolution_clock::now();
				long long timer1 = (end1-start1).count() / 1000.0;
				cout << "[AVL] Elapsed time: " << timer1 << " microseconds" << endl;

				auto start2 = chrono::high_resolution_clock::now();
				sectionItem& dummy2 = sectionPtrBST.itemTree.find(targetItem);
				auto end2 = chrono::high_resolution_clock::now();
				long long timer2 = (end2-start2).count() / 1000.0;
				cout << "[BST] Elapsed time: " << timer2 << " microseconds" << endl;

				if (dummy1 == itemNOT) {
					cout << "The item \"" << targetItemTitle << "\" does not exist in the \"" << currentSectionTitle << "\"." << endl << endl; 
				}
				else {
					string newItemInfo;
					cout << "Enter the new information: ";
					cin >> newItemInfo;

					dummy1.itemInfo = newItemInfo;
					dummy2.itemInfo = newItemInfo;

					cout << "The content " << targetItemTitle << " has been updated." << endl << endl;
				}			
			}
			else if (choice == 6) {
				string targetItemTitle;
				cout << "Enter the title of the item: ";
				cin >> targetItemTitle;

				sectionItem targetItem(targetItemTitle);
				
				if (sectionPtrAVL.itemTree.find(targetItem) == itemNOT) {
					cout << "The item \"" << targetItemTitle << "\" does not exist in the \"" << currentSectionTitle << "\"." << endl << endl;
				}
				else {
					auto start1 = chrono::high_resolution_clock::now();
					sectionPtrAVL.itemTree.remove(targetItem);
					auto end1 = chrono::high_resolution_clock::now();
					long long timer1 = (end1-start1).count() / 1000.0;
					cout << "[AVL] Elapsed time: " << timer1 << " microseconds" << endl;

					auto start2 = chrono::high_resolution_clock::now();
					sectionPtrBST.itemTree.remove(targetItem);
					auto end2 = chrono::high_resolution_clock::now();
					long long timer2 = (end2-start2).count() / 1000.0;
					cout << "[BST] Elapsed time: " << timer2 << " microseconds" << endl;
					
					cout << "The item \"" << targetItemTitle << "\" has been deleted." << endl << endl;
				}
			}
		}
	}

	cout << endl;

	return menuPrint;
}

void mainMenu(BinarySearchTree<sectionNode<BinarySearchTree<sectionItem>>> &notebookBST, AVLTree<sectionNode<AVLTree<sectionItem>>> &notebookAVL, const sectionItem &itemNOT, const sectionNode<BinarySearchTree<sectionItem>> &BSTsectionNOT, const sectionNode<AVLTree<sectionItem>> &AVLsectionNOT) {
	int choice = 0;
	while(choice != 6) {
		if (choice == 0 || choice == 3) { // menu options will be printed only at first loop and after returning from the 3rd option
			cout << "MENU\nPlease enter an input between [1 - 6]:" << endl;
			cout << "1- Display the sections [AVL]" << endl;
			cout << "2- Display the sections [BST]" << endl;
			cout << "3- Select a section" << endl;
			cout << "4- Add new section" << endl;
			cout << "5- Delete a section" << endl;
			cout << "6- Exit" << endl;
		}

		cout << "Input: ";
		cin >> choice;
		
		
		if (choice == 1) {
			cout << endl << "*****" << endl;
			notebookAVL.printTree();
			cout << "*****" << endl << endl;
		}
		else if (choice == 2) {
			cout << endl << "*****" << endl;
			notebookBST.printTree();
			cout << "*****" << endl << endl;
		}
		else if (choice == 3) {
			choice = sectionMenu(notebookBST, notebookAVL, itemNOT, BSTsectionNOT, AVLsectionNOT);
		}
		else if (choice == 4) {
			string newSectionTitle;
			cout << "Enter a title for the section: ";
			cin >> newSectionTitle;
			sectionNode<AVLTree<sectionItem>> newSectionNodeAVL(newSectionTitle, itemNOT);

			if (notebookAVL.find(newSectionNodeAVL) != AVLsectionNOT) {
				cout << "Section \"" << newSectionTitle << "\" already exists." << endl << endl;
			}
			else {
				sectionNode<BinarySearchTree<sectionItem>> newSectionNodeBST(newSectionTitle, itemNOT);

				notebookAVL.insert(newSectionNodeAVL);
				notebookBST.insert(newSectionNodeBST);

				cout << "New section \"" << newSectionTitle << "\" has been inserted." << endl << endl;
			}
		}
		else if (choice == 5) {
			string targetSectionTitle;
			cout << "Enter the title of the section: ";
			cin >> targetSectionTitle;

			sectionNode<AVLTree<sectionItem>> targetSectionNodeAVL(targetSectionTitle, itemNOT);

			if (notebookAVL.find(targetSectionNodeAVL) == AVLsectionNOT) {
				cout << "Section \"" << targetSectionTitle << "\" does not exist." << endl << endl;
			}
			else {
				sectionNode<BinarySearchTree<sectionItem>> targetSectionNodeBST(targetSectionTitle, itemNOT);

				notebookAVL.remove(targetSectionNodeAVL);
				notebookBST.remove(targetSectionNodeBST);

				cout << "The section has been deleted." << endl << endl;
			}
		}
	}

}


int main() {
	
	// initializing NOT_FOUND objects for each node type
	const sectionItem item_NOT_FOUND;
	const sectionNode<BinarySearchTree<sectionItem>> BSTsection_NOT_FOUND(-1, item_NOT_FOUND);
	const sectionNode<AVLTree<sectionItem>> AVLsection_NOT_FOUND(-1, item_NOT_FOUND);

	// initializing main notebooks
	BinarySearchTree<sectionNode<BinarySearchTree<sectionItem>>> notebookBST(BSTsection_NOT_FOUND);
	AVLTree<sectionNode<AVLTree<sectionItem>>> notebookAVL(AVLsection_NOT_FOUND);

	generateNotebooks(notebookBST, notebookAVL, item_NOT_FOUND);

	cout << endl;

	mainMenu(notebookBST, notebookAVL, item_NOT_FOUND, BSTsection_NOT_FOUND, AVLsection_NOT_FOUND);

	return 0;
}