#include<iostream>
using namespace std;
class Node{  //book class to hold the book details
    int key;
    Node* next;
	public:
	    Node(){  //default constructor
	    	next = NULL;
		}
		Node(int key){  //paramterized constructor that sets the key of a particular node
			this->key = key;
			next = NULL;
		}
		void setNext(Node* next){  //to set the next pointer to point a new node
			this->next = next;
		}
	    int getKey(){
	    	return key;
		}
		Node* getNext(){  //returns the next pointer of a node
			return next;
		}
};
class List{   //list class to hold keys(integers) in a singly linked list
	Node* head;
	public:
		List(){
			head = NULL;   //setting the head as null as emptiness of  the list
		}
		bool isEmpty(){  //checks if the list is empty by the same concept as described in the default constructor
			if(head == NULL)
			   return true;
			else
			   return false;
		}
		void insert(int key){  //inserts the key(number) at the back
			if(isEmpty()){
			    head = new Node(key);	
			    return;
			}
			Node* node;
			for(node = head; node->getNext() != NULL; node = node->getNext()){}
			Node* newNode = new Node(key);
			node->setNext(newNode);
		}
		void traverse(){  //prints the entire list
			for(Node* node = head; node != NULL; node = node->getNext()){
				cout << node->getKey() << " ";
			}
		}
		int size(){  //to get the size i.e. the number of keys in a list
			int count = 0;
			Node* node;
			for(node = head; node != NULL; node = node->getNext()){
				count++;
			}
			return count;
		}
		int getFirst(){  //returns the first elemenst in the list
			return head->getKey();
		}
		int getLast(){  //returns the last element in the list
			Node* node;
			for(node = head; node->getNext() != NULL; node = node->getNext()){}
			return node->getKey();
		}
		int remove(){   //removes the first elemt from the list
			if(isEmpty()){
				return -1;  //-1 shows that the list is empty
			}
			Node* node = head->getNext();
			int key = head->getKey();
			delete head;  //to free the memory occupied by the first node
			head = node;
			return key;
		}
};

class Queue{
	List list;
	public:
		Queue(){
			
		}
		
		//function's name explains the use itself!
		void enqueue(int key){
			list.insert(key);
		}
		int dequeue(){
			return list.remove();
		}
		int getFront(){
			return list.getFirst();
		}
		int getBack(){
			return list.getLast();
		}
		void traverse(){  //prints the queue
			list.traverse();
		}
		bool isEmpty(){
			return list.isEmpty();
		}
		int size(){
			return list.size();
		}
};
int main(){
	Queue queue;
	//testing the given tests cases
	if(queue.isEmpty()){
		cout << "1. Queue is currently empty!" << endl;
	}else{
		cout << "1. Queue is not empty!" << endl;
	}
	queue.enqueue(7);
	cout << "2. Data enqueued: 7" << endl;
	queue.enqueue(4);
	cout << "3. Data enqueued: 4" << endl;
	if(queue.isEmpty()){
		cout << "4. Queue is currently empty!" << endl;
	}else{
		cout << "4. Queue is not empty!" << endl;
	}
	cout << "5. Data dequeued: " << queue.dequeue() << endl;
	cout << "6. Number of elements in the queue: " << queue.size() << endl;
	queue.enqueue(5);
	cout << "7. Data enqueued: 5" << endl;
	cout << "8. Number of elemets in the queue: " << queue.size() << endl;
		if(queue.isEmpty()){
		cout << "9. Queue is currently empty!" << endl;
	}else{
		cout << "9. Queue is not empty!" << endl;
	}
	cout << "10. Data at the front: " << queue.getFront() << endl;
	cout << "11. Data at the back: " << queue.getBack() << endl;
	cout << "12. Entire Queue is: ";
	queue.traverse();
}
