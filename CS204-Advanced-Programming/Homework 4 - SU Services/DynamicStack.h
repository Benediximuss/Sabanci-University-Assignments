#ifndef _DYNAMICSTACK_H
#define _DYNAMICSTACK_H

#include <iostream>
#include <string>
#include "PrimaryNodes.h"
using namespace std;

struct commandinStackNode // item struct that will be stored in stack
{
	string data; // example: "function_2: define x"
	commandinStackNode* next;

	commandinStackNode(string a) {
		data = a;
		next = NULL;
	}
};

class DynamicStack
{
public:
	DynamicStack();

	void pushCommand(string command);
	void popCommand(string& command);
	bool isEmpty();
private:
	commandinStackNode* top;

};

#endif