#ifndef _STACK_H
#define _STACK_H

template <class nodeType>
class Stack {
public:
	Stack() {
		top = NULL;
	}

	~Stack() {
		while(!isEmpty()) {
			popCommand();
		}
	}

	void push(nodeType* newnode) {
		if (top == NULL) {
			top = newnode;
		}
		else {
			newnode->next = top;
			top = newnode;
		}
	}

	void popCommand() {
		if (!isEmpty()) {
			nodeType* temp = top;
			top = top->next;
			delete temp;
		}
		else {
			cout << "_ERROR 8261: dynamic stack is BOSCH_" << endl; // for debugging
		}
	}

	bool isEmpty() {
		if (top == NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	nodeType* getTop() {
		return top;
	}

private:
	nodeType* top;
};


#endif