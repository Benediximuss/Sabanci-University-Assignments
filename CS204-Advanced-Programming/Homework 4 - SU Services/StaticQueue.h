#ifndef _STATICQUEUE_H
#define _STATICQUEUE_H

#include <iostream>
#include <string>
#include "PrimaryNodes.h"
using namespace std;

const int instructors = 5; // predefined count of instructors for initialization of static queue of instructors' requests

struct instructorRequestNode // item struct that will be stored in static queue
{
	string instructorName;
	int instructorID;
	functionNode* requestedFunction;

	instructorRequestNode() {}
};

class StaticQueue
{
public:
	StaticQueue();
	StaticQueue(int a);

	void enqueueRequest(string name, int id, functionNode* fn);
  	void dequeueRequest(instructorRequestNode& request);
  	bool isEmpty();
  	bool isFull();
	
private:
	instructorRequestNode* queueArray;
	int queueSize;
	int front;
	int rear;
	int numItems;
};

#endif 