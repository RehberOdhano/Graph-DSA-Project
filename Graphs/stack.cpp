#include <iostream>
using namespace std;


struct stk {
	int data;
	stk* next = NULL;
};

class Stack {
	public:
		stk* top;

	public:
		Stack();
		// ~Stack();
		bool isEmpty();
		void push(int x);
		int pop();
		void display();
};

Stack::Stack() { 
	top = NULL;
}

void Stack::display() {
	if(top == NULL) cout<<"EMPTY!"<<endl;
	else {
		stk* temp = top;
		while(temp != NULL) {
			cout<<temp->data<<" ";
			temp = temp->next;
		}
		cout<<endl;
		// cout<<top->data<<endl;
	}
}

bool Stack::isEmpty() {
	if(top == NULL) return true;
	else return false;
}

void Stack::push(int x) {
	stk* new_node = new stk();
	if(top == NULL) top = new_node;
	else {
		new_node->next = top;
		top = new_node;
	}
	new_node->data = x;
}

int Stack::pop() {
	stk* temp = top;
	int x = temp->data;
	if(top != NULL) {
		if(top->next == NULL) top = NULL;
		else top = top->next;
		delete temp;
	}
	return x;
}    
