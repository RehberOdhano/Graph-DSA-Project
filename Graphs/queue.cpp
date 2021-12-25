
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


Priority_Queue::Priority_Queue() { 
	front = rear = NULL;
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
			while(temp->next != rear) {
				prev = temp;
				if(x < temp->data) break;
				else temp = temp->next;
			}
			prev->next = new_node;
			new_node->next = temp;
		}
		new_node->data = x;
	}
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
