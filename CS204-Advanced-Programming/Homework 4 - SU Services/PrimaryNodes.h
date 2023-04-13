#ifndef _PRIMARYNODES_H
#define _PRIMARYNODES_H

#include <iostream>
#include <string>
using namespace std;


// function and command nodes for storing data from reading txt files
// they are fundemental nodes that will be used in all other files, thus i used a seperate header file to keep them in for avoiding too much 'include'ing conflicts

struct commandNode
{
	string commandName;
	commandNode* next;

	commandNode(string a) {
		commandName = a;
		next = NULL;
	}
};

struct functionNode
{
	string functionName;
	commandNode* headCommand;
	functionNode* next;

	functionNode() {
		headCommand = NULL;
		next = NULL;
	}
};

#endif