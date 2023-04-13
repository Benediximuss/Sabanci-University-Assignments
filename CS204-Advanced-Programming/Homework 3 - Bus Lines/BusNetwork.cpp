#include "BusNetwork.h"

BusNetwork::BusNetwork()
{
    head = NULL;
}

BusNetwork::BusNetwork(busLine* initPtr)
{
	head = initPtr;
}

bool BusNetwork::isLineExist(string a)
{
	bool result = false;
	busLine* ptr = head;
	while(ptr != NULL) {
		if (a == ptr->busLineName) {
			result = true;
			break;
		}
		ptr = ptr->next;
	}
	return result;
}

bool BusNetwork::isStopExist(string a, string b)
{
	bool result = false;
	busStop* ptr = findLine(a)->busStops;
	while(ptr != NULL) {
		if (b == ptr->busStopName) {
			result = true;
			break;
		}
		ptr = ptr->right;
	}
	return result;
}

bool BusNetwork::isStopExist(busStop* a, string b)
{
	bool result = false;
	busStop* ptr = a;
	while(ptr != NULL) {
		if (b == ptr->busStopName) {
			result = true;
			break;
		}
		ptr = ptr->right;
	}
	return result;
}

busLine* BusNetwork::findLine(string a)
{
	busLine* target;
	busLine* ptr = head;
	while(ptr != NULL) {
		if (a == ptr->busLineName) {
			target = ptr;
			break;
		}
		ptr = ptr->next;
	}
	return target;
}

busStop* BusNetwork::findStop(busLine* a,string b)
{
	busStop* target;
	busStop* ptr = a->busStops;
	while(ptr != NULL) {
		if (b == ptr->busStopName) {
			target = ptr;
			break;
		}
		ptr = ptr->right;
	}
	return target;
}

void BusNetwork::printNetwork()
{
	busLine* ptr = head;
	while(ptr != NULL) {
		cout <<  ptr->busLineName << ": ";
		busStop* ptr2 = ptr->busStops;
		while(ptr2 != NULL) {
			cout << ptr2->busStopName;	
			if (ptr2->right != NULL) {
				cout << " <-> ";
			}
			ptr2 = ptr2->right;
		}
		ptr = ptr->next;
		cout << endl;
	}
}

bool BusNetwork::consistencyCheck()
{
	busLine* currBL = head;
	while(currBL) {
		busStop* currBS = currBL->busStops;
		while(currBS) {
			busStop* rightBS = currBS->right;
			if(rightBS && rightBS->left != currBS) {
				cout << "Inconsistency for " << currBL->busLineName << " " << currBS->busStopName << endl;
				return false;
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return true;
}

void BusNetwork::addBusLine()
{
	string temp_newLineName;
	cout << "Enter the name of the new bus line (0 for exit to main menu)." << endl;
	cin >> temp_newLineName;
	if (temp_newLineName != "0") {
		while(isLineExist(temp_newLineName)) {
			cout << "Bus line already exists: enter a new one (0 for exit)" << endl;
			cin >> temp_newLineName;
			if (temp_newLineName == "0") {
				break;
			}
		}
		if (temp_newLineName != "0") { 
			string temp_newNextStop;
			busStop* headStop = NULL;
			busStop* temp;
			while(true) {
				cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
				cin >> temp_newNextStop;
				if (temp_newNextStop != "0") {
					if (headStop == NULL) {
						headStop = new busStop(temp_newNextStop);
						temp = headStop;
					}
					else {
						while(isStopExist(headStop,temp_newNextStop)) {
							cout << "Bus stop already exists in the line" << endl;
							cin >> temp_newNextStop;
						}
						busStop* temp_newStop = new busStop(temp_newNextStop);
						while(temp->right != NULL) {
							temp = temp->right;
						}
						temp->right = temp_newStop;
						temp_newStop->left = temp;
					}
				}
				else if (temp_newNextStop == "0" && headStop == NULL) {
					cout << "You are not allowed to add an empty bus line" << endl;
					break;
				}
				else if (temp_newNextStop == "0" && headStop != NULL) {
					cout << "The bus line information is shown below" << endl;
					cout << temp_newLineName << ": ";
					busStop* ptr = headStop;
					while(ptr != NULL) {
						cout << ptr->busStopName;	
						if (ptr->right != NULL) {
							cout << " <-> ";
						}
						ptr = ptr->right;
					}
					string sure;
					cout << endl << "Are you sure? Enter (y/Y) for yes (n/N) for no?" << endl;
					cin >> sure;
					if (sure == "y" || sure == "Y") {
						busLine* new_busLine = new busLine(temp_newLineName,headStop);
						new_busLine->next = head;
						head = new_busLine;
						cout << endl;
						printNetwork();
						break;
					}
					else {
						break;
					}
				}
			}

		}
	}
}

void BusNetwork::addBusStop()
{
	cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)" << endl;
	string targetLineName;
	cin >> targetLineName;
	if (targetLineName != "0") {
		if (isLineExist(targetLineName)) {
			cout << "The bus line information is shown below" << endl;
			busLine* targetLine = findLine(targetLineName);
			cout << targetLine->busLineName << ": ";
			busStop* ptr = targetLine->busStops;
			while(ptr != NULL) {
				cout << ptr->busStopName;	
				if (ptr->right != NULL) {
					cout << " <-> ";
				}
				ptr = ptr->right;
			}
			cout << endl << "Enter the name of the new bus stop" << endl;
			string newStopName;
			cin >> newStopName;
			if (isStopExist(targetLine->busStops,newStopName)) {
				cout << "Bus stop already exists. Going back to previous menu." << endl;
			}
			else {
				cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)" << endl;
				string previousStopName;
				cin >> previousStopName;
				busStop* newStop;
				if (previousStopName == "0") {
					newStop = new busStop(newStopName);
					targetLine->busStops->left = newStop;
					newStop->right = targetLine->busStops;
					targetLine->busStops = newStop;
					cout << endl;
					printNetwork();
				}
				else {
					while(!isStopExist(targetLine->busStops,previousStopName)) {
						cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)" << endl;
						cin >> previousStopName;
						if (previousStopName == "0") {
							previousStopName = "exit";
							break;
						}
					}
					if (previousStopName != "exit") {
						busStop* previousStop = findStop(targetLine,previousStopName);
						newStop = new busStop(newStopName);
						if (previousStop->right != NULL) {
							newStop->right = previousStop->right;
							newStop->left = previousStop;
							previousStop->right->left = newStop;
							previousStop->right = newStop;
							cout << endl;
							printNetwork();
						}
						else {
							previousStop->right = newStop;
							newStop->left = previousStop;
							printNetwork();
						}
					}
				}
			}
		}
		else {
			cout << "Bus line cannot be found. Going back to previous menu." << endl;
		}
	}
}

void BusNetwork::deleteBusLine()
{
	cout << "Enter the name of the bus line to delete" << endl;
	string targetLineName;
	cin >> targetLineName;
	if (isLineExist(targetLineName)) {
		busLine* targetLine = findLine(targetLineName);
		busStop* ptr = targetLine->busStops;
		//busStop* temp;
		while (ptr->right != NULL) {
			//temp = ptr;
			targetLine->busStops = ptr->right;
			targetLine->busStops->left = NULL;
			delete ptr;
			ptr = targetLine->busStops;
		}
		delete targetLine->busStops;
		if (targetLine == head) {
			head = targetLine->next;
			delete targetLine;
		}
		else {
			busLine* previousLine = head;
			while (previousLine != NULL) {
				if (previousLine->next == targetLine) {
					previousLine->next = targetLine->next;
					break;
				}
				previousLine = previousLine->next;
			}
			delete targetLine;
		}
		printNetwork();
	}
	else {
		cout << "Bus line cannot be found. Going back to the previous (main) menu." << endl;
	}

}

void BusNetwork::deleteBusStop()
{
	cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)" << endl;
	string targetLineName;
	cin >> targetLineName;
	if (targetLineName != "0") {
		if (isLineExist(targetLineName)) {
			cout << "The bus line information is shown below" << endl;
			busLine* targetLine = findLine(targetLineName);
			cout << targetLine->busLineName << ": ";
			busStop* ptr = targetLine->busStops;
			while(ptr != NULL) {
				cout << ptr->busStopName;	
				if (ptr->right != NULL) {
					cout << " <-> ";
				}
				ptr = ptr->right;
			}
			cout << endl << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
			string targetStopName;
			cin >> targetStopName;
			if (targetStopName != "0") {
				while (!isStopExist(targetLine->busStops,targetStopName)) {
					cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)" << endl;
					cin >> targetStopName;
					if (targetStopName == "0") {
						targetStopName = "exit";
						break;
					}
				}
				if (targetStopName != "exit") {
					busStop* targetStop = findStop(targetLine,targetStopName);
					if (targetStop->left == NULL && targetStop->right == NULL) {
						delete targetLine->busStops;
						if (targetLine == head) {
							head = targetLine->next;
							delete targetLine;
						}
						else {
							busLine* previousLine = head;
							while (previousLine != NULL) {
								if (previousLine->next == targetLine) {
									previousLine->next = targetLine->next;
									break;
								}
								previousLine = previousLine->next;
							}
							delete targetLine;
						}
					}
					else if (targetStop->left == NULL) {
						targetLine->busStops = targetStop->right;
						targetStop->right->left = NULL;
						delete targetStop;
					}
					else if (targetStop->right == NULL) {
						targetStop->left->right = NULL;
						delete targetStop;
					}
					else {
						targetStop->left->right = targetStop->right;
						targetStop->right->left = targetStop->left;
						delete targetStop;
					}
					printNetwork();
				}
			}
		}
		else {
			cout << "Bus line cannot be found. Going back to previous (main) menu." << endl;
		}
	}

}

bool BusNetwork::isStopExist_inNetwork(string a)
{
	bool result = false;
	busLine* ptr = head;
	while(ptr != NULL) {
		busStop* ptr2 = ptr->busStops;
		while(ptr2 != NULL) {
			if (ptr2->busStopName == a) {
				result = true;
				break;
			}
			ptr2 = ptr2->right;
		}
		if (result) {
			break;
		}
		ptr = ptr->next;
	}
	return result;
}

bool BusNetwork::isBothStopsExist_inLine(busLine* a,string b,string c)
{
	bool result = false;
	int k = 0;
	busStop* ptr = a->busStops;
	while(ptr != NULL) {
		if (ptr->busStopName == b || ptr->busStopName == c) {
			k++;
			if (k == 2) {
				result = true;
				break;
			}
		}
		ptr = ptr->right;
	}
	return result;
}

void BusNetwork::pathFinder()
{
	cout << "Where are you now?" << endl;
	string startStopName,endStopName;
	cin >> startStopName;
	cout << "Where do you want to go?" << endl;
	cin >> endStopName;
	if (isStopExist_inNetwork(startStopName) && isStopExist_inNetwork(endStopName)) {
		bool directPath = false;
		busLine* ptr = head;
		while (ptr != NULL) {
			if (isBothStopsExist_inLine(ptr,startStopName,endStopName)){
				cout << "You can go there by " << ptr->busLineName << ": ";
				directPath = true;
				busStop* ptr2 = ptr->busStops;
				int stopCount = 1,startStopCount,endStopCount;
				while (ptr2 != NULL) {
					if (ptr2->busStopName == startStopName) {
						startStopCount = stopCount;
					}
					else if (ptr2->busStopName == endStopName) {
						endStopCount = stopCount;
					}
					stopCount++;
					ptr2 = ptr2->right;
				}
				busStop* startStop = findStop(ptr,startStopName);
				busStop* endStop = findStop(ptr,endStopName);
				busStop* ptr3;
				if (startStopCount < endStopCount) { // soldan saga
					ptr3 = startStop;
					while (ptr3 != endStop) {
						cout << ptr3->busStopName << "->";
						ptr3 = ptr3->right;
					}
					cout << endStop->busStopName << endl;
				}
				else if (startStopCount > endStopCount) { // sagdan sola
					ptr3 = startStop; 
					while (ptr3 != endStop) {
						cout << ptr3->busStopName << "->";
						ptr3 = ptr3->left;
					}
					cout << endStop->busStopName << endl;
				}
				else {
					cout << "NOLUYO MK" << endl;
				}
			}
			ptr = ptr->next;
		}
		if (!directPath) {
			cout << "Sorry, no direct path from " << startStopName << " to " << endStopName << " could be found." << endl;
			// AKTARMALI BONUS!!!
		}
	}
	else {
		cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
	}

}
