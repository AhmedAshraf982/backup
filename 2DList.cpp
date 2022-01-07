#include<iostream>
#include<vector>
#define NULLPTR 0
using namespace std;

class Node{
	int key;
	Node* next;
	Node* down;
	
	public:
		Node(){
			next = NULLPTR;
			down = NULLPTR;
		}
		Node(int key){
			this->key = key;
			next = NULLPTR;
			down = NULLPTR;
		}
		Node* getNext(){
			return next;
		}
		Node* getDown(){
			return down;
		}
		int getKey(){
			return key;
		}
		void setNext(Node* next){
			this->next = next;
		}
		void setDown(Node* down){
			this->down = down;
		}
};

class List{
	Node* head;
	
	public:
		List(){
			head = NULLPTR;
		}
		bool isEmpty(){
			if(head == NULLPTR){
				return true;
			}
			return false;
		}
		Node* getHead(){
			return head;
		}
		void insert(int key){
			if(isEmpty()){
				head = new Node(key);
				return;
			}
			Node* node;
			for(node = head; node->getNext() != NULLPTR; node = node->getNext());
			Node* newNode = new Node(key);
			node->setNext(newNode);
		}
		vector<Node*> getNodes(){
			vector<Node*> nodes;
			for(Node* node = head; node != NULLPTR; node = node->getNext()){
				nodes.push_back(node);
			}
			return nodes;
		}
};
Node* make2DList(int matrix[100][100], int n){
	List lists[n];
	vector<Node*> nodes[n];
	for(int x = 0; x < n; x++){
		for(int y = 0; y < n; y++){
			lists[x].insert(matrix[x][y]);
		}
		nodes[x] = lists[x].getNodes();
		if(x != 0){
			for(int y = 0; y < n; y++){
				nodes[x-1][y]->setDown(nodes[x][y]);
			}
		}
	}
	return lists[0].getHead();
}
void traverse(Node* head){
	Node* down = NULLPTR;
	Node* node = head;
	bool flag = true;
	while(1){
		cout << node->getKey() << " ";
		if(flag){
			down = node->getDown();	
			flag = false;
		}
		node = node->getNext();
		if(node == NULLPTR){
			flag = true;
			node = down;
			if(node == NULLPTR){
				break;
			}
		}
	}
}
int main(){
	int n;
	cout << "Enter N: ";
	cin >> n;
	cout << "Enter elements of the n*n matrix:";
	int matrix[100][100];  //any arbitrary size
	for(int x = 0; x < n; x++){
		for(int y = 0; y < n; y++){
			cin >> matrix[x][y];
		}
	}
	Node* head = make2DList(matrix, n);
	traverse(head);
}
