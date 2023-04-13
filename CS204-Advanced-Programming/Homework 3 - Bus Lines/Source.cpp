#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "BusNetwork.h"

using namespace std;

busLine* createNetwork(string &fileName) { //	creates the network of lines and stops, returns the head pointer for bus lines

	ifstream input;
	input.open(fileName.c_str());

	busLine* headLine = NULL; 
	busLine* temp;
	string line;
	while(getline(input,line)) { // linking lines
		
		istringstream ss(line);
		string temp_BusLineName, temp_BusStopName;
		ss >> temp_BusLineName;
		temp_BusLineName.pop_back();

		busStop* temp_HeadStop = NULL;
		busStop* temp2;
		while(ss >> temp_BusStopName) { //	linking stops
			if (temp_HeadStop == NULL) {
				temp_HeadStop = new busStop(temp_BusStopName);
				temp2 = temp_HeadStop;
			}
			else {
				busStop* temp_newStop = new busStop(temp_BusStopName);
				while(temp2->right != NULL) {
					temp2 = temp2->right;
				}
				temp2->right = temp_newStop;
				temp_newStop->left = temp2;
			}
		}
		
		if (headLine == NULL) {
			headLine = new busLine(temp_BusLineName,temp_HeadStop);
			temp = headLine;
		}
		else {
			while(temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = new busLine(temp_BusLineName,temp_HeadStop);
		}
	}
	input.close();
	return headLine;
}

void printMainMenu() {
	cout << endl;
	cout <<"|***********************************************|"<<endl
	<<"| 0 - EXIT PROGRAM                              |"<<endl
	<<"| 1 - PRINT LINES                               |"<<endl
	<<"| 2 - ADD BUS LINE                              |"<<endl
	<<"| 3 - ADD BUS STOP                              |"<<endl
	<<"| 4 - DELETE BUS LINE                           |"<<endl
	<<"| 5 - DELETE BUS STOP                           |"<<endl
	<<"| 6 - PATH FINDER                               |"<<endl
	<<"|***********************************************|"<<endl
	<<">>"<<endl;
}

void processMainMenu(BusNetwork &network) {
	char input;
	do
	{
		if (!network.consistencyCheck()) {
			cout << "There are inconsistencies. Exit." << endl;
			return;
		}
		printMainMenu();
		cout << "Please enter your option " << endl;
		cin >> input;
		switch (input) {
			case '0': //	exit
			cout << "Thanks for using our program" << endl;
			return;
			case '1': //	printnetwork
				network.printNetwork();
			break;
			case '2': //	addline
				network.addBusLine();
			break; //	addstop
			case '3':
				network.addBusStop();
			break; // deleteline
			case '4':
				network.deleteBusLine();
			break; //	deletestop
			case '5':
				network.deleteBusStop();
			break;
			case '6': // pathfinder
				network.pathFinder();
			break;
			default:
			cout << "Invalid option: please enter again" << endl;
		}
	} while(true);
}


int main() {

	string x = "busLines.txt";
	BusNetwork network(createNetwork(x));
	processMainMenu(network);

	return 0;
}
