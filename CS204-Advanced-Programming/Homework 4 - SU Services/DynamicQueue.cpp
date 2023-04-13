#include <iostream>
#include <string>
#include <fstream>
#include "DynamicQueue.h"

using namespace std;

DynamicQueue::DynamicQueue()
{
	front = NULL;
	rear = NULL;
}

bool DynamicQueue::isEmpty()
{
	if (front == NULL) {
		return true;
	}
	else {
		return false;
	}
}

void DynamicQueue::enqueueRequest(string name, int id, functionNode* fn)
{
	if (front == NULL) {
		front = new studentRequestNode(name,id,fn);
		rear = front;
	}
	else {
		rear->next = new studentRequestNode(name,id,fn);;
		rear = rear->next;
	}
}

void DynamicQueue::dequeueRequest(studentRequestNode& request)
{
	if (!isEmpty()) {
		request.studentName = front->studentName;
		request.studentID = front->studentID;
		request.requestedFunction = front->requestedFunction;
		request.next = NULL;
		studentRequestNode* temp = front;
		front = front->next;
		delete temp;
	}
	else {
		cout << "_ERROR 619: dynamic queue is BOSCH_" << endl; // for debugging
	}
}