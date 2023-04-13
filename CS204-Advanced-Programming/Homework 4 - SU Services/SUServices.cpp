#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "SUServices.h"

using namespace std;

SUServices::SUServices() // default constructor
{
	headFunction = NULL;
}

functionNode* SUServices::getHeadFunction() // returns headfunction pointer
{
	return headFunction;
}

void SUServices::setHeadFunction(functionNode* ptr) // sets headfunction pointer
{
	headFunction = ptr;
}

functionNode* SUServices::isFunctionExist(string targetFn) { // if target function name exists return it's pointer, if not returns NULL
	functionNode* result = NULL;
	functionNode* temp = headFunction;
	while (temp != NULL) {
		if (temp->functionName == targetFn) {
			result = temp;
			break;
		}
		temp = temp->next;
	}
	return result;
}

functionNode* SUServices::createFunctionNode(string fileName)
{
	functionNode* head = new functionNode;
	ifstream input;
	input.open(fileName.c_str());
	if (!input.fail()) {
		string line;
		int k = 0;
		commandNode* temp;
		while(getline(input,line)) {
			line.pop_back();
			if (k == 0) {
				head->functionName = line;
				k++;
			}
			else {
				if (head->headCommand == NULL) {
					head->headCommand = new commandNode(line);
					temp = head->headCommand;
				}
				else {
					temp->next = new commandNode(line);
					temp = temp->next;
				}
			}
		}
		input.close();
		return head;
	}
	else {
		cout << "There is no such file named '" << fileName << "' or can not be opened!" << endl;
		cout << "Terminating the program..." << endl;
		input.close();
		return NULL; // return NULL for createServicesList() function in order to terminate main program
	}
}

functionNode* SUServices::createServicesList() { // if this function returns NULL, main program will be terminated
	functionNode* head = NULL;
	functionNode* temp;
	string choice;
	cout << "If you want to open a service <function> defining file," << endl << "then press <Y/y> for 'yes', otherwise press any single key " << endl;
	cin >> choice;
	while (choice == "Y" || choice == "y") {
		cout << "Enter the input file name: ";
		cin >> choice;
		functionNode* newFunction = createFunctionNode(choice); // if 'createFunctionNode' function returns NULL, it means file cannot be found
		if (newFunction != NULL) {
			if (head == NULL) {
				head = newFunction;
				temp = head;
			}
			else {
				temp->next = newFunction;
				temp = temp->next;
			}
		}
		else {
			return NULL; // entered file name cannot be found, function returns NULL in order to terminate program
		}
		cout << "Do you want to open another service defining file?" << "Pres <Y/y> for 'yes', otherwise press anykey" << endl;
		cin >> choice;
	}
	if (head == NULL) { // if head remained NULL, it means no file has opened and function will return NULL (as you can see in 4 lines below) in order to terminate program
		cout << "No file has opened to create database." << endl;
		cout << "Terminating the program..." << endl;
	}
	return head;
}

void SUServices::printServices()
{
	cout << "-------------------------------------------------------------------" << endl;
	cout << "PRINTING AVAILABLE SERVICES <FUNCTIONS> TO BE CHOSEN FROM THE USERS" << endl;
	cout << "-------------------------------------------------------------------" << endl << endl << endl;
	functionNode* temp = headFunction;
	while (temp != NULL) {
		cout << temp->functionName << ":" << endl;
		commandNode* temp2 = temp->headCommand;
		while (temp2 != NULL) {
			cout << temp2->commandName;
			if (temp2->next != NULL) {
				cout << ", ";
			}
			else {
				cout << "." << endl << endl;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}


void SUServices::addInstructorRequest()
{
	cout << "Add a service <function> that the instructor wants to use:" << endl;
	string fnName;
	cin >> fnName;
	functionNode* requestedFunction = isFunctionExist(fnName);

	if (requestedFunction == NULL) {
		cout << "The requested service <function> does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
	else {
		string instructorName;
		int instructorID;
		cout << "Give instructor's name: ";
		cin >> instructorName;
		cout << "Give instructor's ID <an int>: ";
		cin >> instructorID;
		
		instructorsQueue.enqueueRequest(instructorName,instructorID,requestedFunction); // adding instructor request to the queue

		cout << "Prof. " << instructorName << "'s service request of " << fnName << " has been put in the instructor's queue." << endl;
		cout << "Waiting to be served..." << endl;
	}
}

void SUServices::addStudentRequest()
{
	cout << "Add a service <function> that the student wants to use:" << endl;
	string fnName;
	cin >> fnName;
	functionNode* requestedFunction = isFunctionExist(fnName);

	if (requestedFunction == NULL) {
		cout << "The requested service <function> does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
	else {
		string studentName;
		int studentID;
		cout << "Give student's name: ";
		cin >> studentName;
		cout << "Give student's ID <an int>: ";
		cin >> studentID;
		
		studentsQueue.enqueueRequest(studentName,studentID,requestedFunction); // adding student requst to the queue

		cout << studentName << "'s service request of " << fnName << " has been put in the student's queue." << endl;
		cout << "Waiting to be served..." << endl;
	}
}

void SUServices::processARequest()
{
	if (!instructorsQueue.isEmpty())
	{
		instructorRequestNode currentRequest;
		instructorsQueue.dequeueRequest(currentRequest); // getting the first request in order to be operated and removing it from queue
		
		cout << "Processing instructors queue..." << endl;
		cout << "Porcessing prof." << currentRequest.instructorName << "'s request <with ID " << currentRequest.instructorID << "> of service <function>:" << endl;
		cout << currentRequest.requestedFunction->functionName << endl;
		cout << "------------------------------------------------------" << endl;

		processARequest(currentRequest.requestedFunction->functionName);
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
	else if (!studentsQueue.isEmpty())
	{
		studentRequestNode currentRequest;
		studentsQueue.dequeueRequest(currentRequest); // getting the first request in order to be operated and removing it from queue

		cout << "Instructor queue is empty. Proceeding with students queue..." << endl;
		cout << "Porcessing " << currentRequest.studentName << "'s request <with ID " << currentRequest.studentID << "> of service <function>:" << endl;
		cout << currentRequest.requestedFunction->functionName << endl;
		cout << "------------------------------------------------------" << endl;

		processARequest(currentRequest.requestedFunction->functionName);
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
	else {
		cout << "Both instructor's and student's queue is empty.\nNo request is processed."<< endl;		cout << "GOING BACK TO MAIN MENU" << endl;
	}
}

void SUServices::processARequest(string functionName)
{
	functionNode* currentService = isFunctionExist(functionName);
	commandNode* ptr = currentService->headCommand;
	int counter = 0; // counter for determining how many items will this function push into the stack, which laterly used for popping from stack

	while (ptr != NULL)
	{
		string currentCommandLine = ptr->commandName;
		istringstream ss(currentCommandLine);
		string command1, command2;
		ss >> command1 >> command2;

		if(command1 == "define")
		{
			string commandToPush = functionName + ": " + currentCommandLine;
			SharedStack.pushCommand(commandToPush); // pushing define command into the stack as string. example: "function_2: define a"
			counter++;
		}
		else if (command1 == "call")
		{
			cout << "Calling " << command2 << " from " << functionName << endl;
			processARequest(command2);
		}
		else {
			cout << "PRINTING THE STACK TRACE:" << endl;

			if (SharedStack.isEmpty()) {
				cout << "The stack is empty" << endl;
			}

			else { // printing the items in stack
				DynamicStack tempStack;
				while (!SharedStack.isEmpty()) {
					string dummy;
					SharedStack.popCommand(dummy);
					tempStack.pushCommand(dummy);
				}
				while (!tempStack.isEmpty()) {
					string dummy;
					tempStack.popCommand(dummy);
					cout << dummy << endl;
					SharedStack.pushCommand(dummy);
				}
			}

		}

		ptr = ptr->next; // moving on to the next command line in function node
	}
	
	for (int i = 0; i < counter; i++) { // popping items from stack counter times
		string dummy;
		SharedStack.popCommand(dummy);
	}

	cout << functionName << " is finished. Clearing the stack from it's data... " << endl;
	system("pause");
}