#include <iostream>
#include <string>
#include <fstream>
#include "DynamicStack.h"

using namespace std;

DynamicStack::DynamicStack()
{
	top = NULL;
}

void DynamicStack::pushCommand(string command)
{
	commandinStackNode* temp = new commandinStackNode(command);

	if (top == NULL) {
		top = temp;
	}
	else {
		temp->next = top;
		top = temp;
	}
}

void DynamicStack::popCommand(string& command)
{
	if (!isEmpty()) {
		commandinStackNode* temp;
		command = top->data;
		temp = top;
		top = top->next;
		delete temp;
	}
	else {
		cout << "_ERROR 8261: dynamic stack is BOSCH_" << endl; // for debugging
	}
}

bool DynamicStack::isEmpty()
{
	if (top == NULL) {
		return true;
	}
	else {
		return false;
	}
}