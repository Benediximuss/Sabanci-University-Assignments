#include <iostream>
#include <string>

#include "PrimaryNodes.h"
#include "StaticQueue.h"
#include "DynamicQueue.h"
#include "DynamicStack.h"
#include "SUServices.h"

using namespace std;

// UGUR OZTUNC 28176 CS204 HW4 - STACKS_QUEUES SU SERVICES

void processMainMenu(SUServices& x) {
	while (true) {
		cout << endl;
		cout<<"**********************************************************************"<<endl
			<<"**************** 0 - EXIT PROGRAM *************"<<endl
			<<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST *************"<<endl
			<<"**************** 2 - ADD A STUDENT SERVICE REQUEST *************"<<endl
			<<"**************** 3 - SERVE (PROCESS) A REQUEST *************"<<endl
			<<"**********************************************************************"<<endl;
		cout << endl;
		int option;
		cout << "Pick an option from above (int number from 0 to 3): ";
		cin>>option;
		switch (option)
		{
		case 0:
			cout<<"PROGRAM EXITING ... "<<endl;
			exit(0);
		case 1:
			x.addInstructorRequest();
			break;
		case 2:
			x.addStudentRequest();
			break;
		case 3:
			x.processARequest();
			break;
		default:
			cout<<"INVALID OPTION!!! Try again"<<endl;
		}
	}
}

int main() {
	SUServices ServiceNetwork; // creating the main object
	ServiceNetwork.setHeadFunction(ServiceNetwork.createServicesList()); // assigning it's headfunction pointer by reading files

	if (ServiceNetwork.getHeadFunction() != NULL) { // if headfunction pointer is NULL, terminates the program
		ServiceNetwork.printServices();
		processMainMenu(ServiceNetwork);
	}

	return 0;
}