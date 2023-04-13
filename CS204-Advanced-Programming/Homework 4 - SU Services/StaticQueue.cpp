#include <iostream>
#include <string>
#include <fstream>
#include "StaticQueue.h"

using namespace std;

StaticQueue::StaticQueue()
{
	queueArray = new instructorRequestNode[instructors];
	queueSize = instructors;
	front = -1;
	rear = -1;
	numItems = 0;
}


StaticQueue::StaticQueue(int a)
{
	queueArray = new instructorRequestNode[a];
	queueSize = a;
	front = -1;
	rear = -1;
	numItems = 0;
}

void StaticQueue::enqueueRequest(string name, int id, functionNode* fn)
{
	if (!isFull()) {
	rear = (rear + 1) % queueSize;
	queueArray[rear].instructorName = name;
	queueArray[rear].instructorID = id;
	queueArray[rear].requestedFunction = fn;
	numItems++;
	}
	else {
		cout << "_HATA 512: static queue DOLU_" << endl; // for debugging
	}

}

void StaticQueue::dequeueRequest(instructorRequestNode& request)
{
	if (!isEmpty()) {
	front = (front + 1) % queueSize;
	request.instructorName = queueArray[front].instructorName;
	request.instructorID = queueArray[front].instructorID;
	request.requestedFunction = queueArray[front].requestedFunction;
	numItems--;
	}
	else {
		cout << "_HATA 342: static queue BOSCH_" << endl; // for debugging
	}
}

bool StaticQueue::isEmpty()
{
	if (numItems > 0)
		return false;
	else
		return true;	
}

bool StaticQueue::isFull()
{
	if (numItems < queueSize)
		return false;
	else
		return true;
}
