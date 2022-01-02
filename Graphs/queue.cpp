
struct node {
	int data;
	node* next = NULL;
};

class Queue {
	public:
		node* front;
		node* rear;

	public:
		Queue();
		// ~Queue();
		bool isEmpty();
		void push(int x);
		int pop();
};

Queue::Queue() { 
	front = rear = NULL;
}

bool Queue::isEmpty() {
	if(front == NULL) return true;
	else return false;
}

void Queue::push(int x) {
	node* new_node = new node();
	if(front == NULL) front = rear = new_node;
	else {
		rear->next = new_node;
		rear = new_node;
	}
	new_node->data = x;
}

int Queue::pop() {
	node* temp = front;
	int x = temp->data;
	if(front != NULL) {
		if(front->next == NULL) front = rear = NULL;
		else front = front->next;
		delete temp;
	}
	return x;
}
