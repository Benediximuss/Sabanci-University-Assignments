#ifndef _DYNAMICQUEUE_H
#define _DYNAMICQUEUE_H

#include <iostream>
#include <string>
#include "PrimaryNodes.h"
using namespace std;

struct studentRequestNode // item struct that will be stored in dynamic queue
{
	string studentName;
	int studentID;
	functionNode* requestedFunction;
	studentRequestNode* next;

	studentRequestNode() {}
	studentRequestNode(string a, int b, functionNode* c) {
		studentName = a;
		studentID = b;
		requestedFunction = c;
		next = NULL;
	}
};

class DynamicQueue
{
public:
	DynamicQueue();

	bool isEmpty();
	void enqueueRequest(string name, int id, functionNode* fn);
	void dequeueRequest(studentRequestNode& request);
private:
	studentRequestNode* front;
	studentRequestNode* rear;

};

#endif