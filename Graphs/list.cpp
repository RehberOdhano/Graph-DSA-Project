#include <iostream>
using namespace std;

struct list_node {
	int d;
	int s;
	list_node* next = NULL;
};

class List {
	public:
		list_node* head;
		list_node* tail;

	public:
		List();
		// ~List();
		void insert(int node);
		void erase(int x);	
		bool isEmpty();
		// list_node* begin();
		void display_list();
};

List::List() {
	head = tail = NULL;
}

void List::display_list() {
	list_node* temp = head;
	while(temp != NULL) {
		cout<<temp->d<<" ";
	}
	cout<<endl;
}

bool List::isEmpty() {
	if(head == NULL) return true;
	else return false;
}

// list_node* List::begin() {
// 	if(head != NULL) return head;
// }

void List::insert(int node) {
	list_node* new_node = new list_node();
	if(head == NULL) head = tail = new_node;
	else {
		tail->next = new_node;
		tail = new_node;	
	}
	new_node->d = distance;
	new_node->s = source;
}

void List::erase(int x) {
	list_node* del = NULL;
	if(head->d == x) {
		del = head;
		head = head->next;
		delete del;
	} else {
		list_node* temp = head->next;
		list_node* prev = head;
		while(temp != NULL) {
			if(temp->d == x) break;
			else {
				prev = temp;
				temp = temp->next;
			}
		}
		del = temp;
		prev->next = temp->next;
		delete del;
	}
}