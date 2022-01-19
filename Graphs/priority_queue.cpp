#include <iostream>
using namespace std;

struct node {
	int data;
	node* next = NULL;
};

class Priority_Queue {
	public:
		node* front;
		node* rear;
	public:
		Priority_Queue();
		// ~Priority_Queue(); 
		bool isEmpty();
		void push(int x);
		int pop();
		void display();
};

Priority_Queue::Priority_Queue() { 
	front = rear = NULL;
}

void Priority_Queue::display() {
	node* temp = front;
	while(temp != NULL) {
		cout<<temp->data<<" ";
		temp = temp->next;
	}
	cout<<endl;
}

bool Priority_Queue::isEmpty() {
	if(front == NULL) return true;
	else return false;
}

void Priority_Queue::push(int x) {
	node* new_node = new node();
	if(front == NULL) front = rear = new_node;
	else {
		if(x <= front->data) {
			new_node->next = front;
			front = new_node;
		} else if(x >= rear->data) {
			rear->next = new_node;
			rear = new_node;
		}
		else {
			node* temp = front->next;
			node* prev = front;
			while(temp->next != NULL) {
				if(x < temp->data) break;
				else {
					prev = temp;
					temp = temp->next;
				}
			}
			prev->next = new_node;
			new_node->next = temp;
		}
	}
	new_node->data = x;
}

int Priority_Queue::pop() {
	node* temp = front;
	int x = temp->data;
	if(front != NULL) {
		if(front->next == NULL) front = rear = NULL;
		else front = front->next;
		delete temp;
	}
	return x;
}   