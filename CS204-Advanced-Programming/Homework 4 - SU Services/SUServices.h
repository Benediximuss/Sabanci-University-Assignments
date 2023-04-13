#ifndef _SUSERVICES_H
#define _SUSERVICES_H

#include <iostream>
#include <string>

#include "PrimaryNodes.h"
#include "DynamicQueue.h"
#include "StaticQueue.h"
#include "DynamicStack.h"

using namespace std;

class SUServices
{
public:
	SUServices();

	functionNode* createServicesList(); // asks input file names to user, creates a linked list consists of function nodes and returns the head function node pointer
	functionNode* getHeadFunction(); // returns headFunction pointer
	void setHeadFunction(functionNode* ptr); // assigns headFunction = ptr

	void printServices(); // prints all available functions with their commands
	
	// menu operations
	void addInstructorRequest(); 
	void addStudentRequest();
	void processARequest();
	void processARequest(string functionName); 
private:
	functionNode* headFunction; // head function node pointer of the first service (created and linked based on input files)
	
	DynamicQueue studentsQueue; // students' request queue = FIFO dynamic queue
	StaticQueue instructorsQueue; // instructors' request queue = FIFO static(fixed sized) queue
	DynamicStack SharedStack; // shared stack for commands = FILO dynamic stack
	
	functionNode* isFunctionExist(string targetFn); // if targetfunctionname exists return it's pointer, if not returns NULL

	functionNode* createFunctionNode(string fileName); // creates a function node by opening the file name given as parameter and returns the pointer for that node
	
};
	
#endif