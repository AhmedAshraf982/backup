#include<iostream>
#include<vector>
#define NULLPTR 0
using namespace std;
class Node{
	int key;
	Node* next;
	public:
		Node(){
			next = NULLPTR;
		}
		Node(int key){
			this->key = key;
			next = NULLPTR;
		}
		void setNext(Node* node){
			next = node;
		}
		Node* getNext(){
			return next;
		}
		int getKey(){
			return key;
		}
};
class List{
	Node* head;
	int size_;
	
	public:
		List(){
			head = NULLPTR;
			size_ = 0;
		}
		bool isEmpty(){
			if(head == NULLPTR) 
				return true;
			return false;
		}
		void insertKey(int key){
			size_++;
			if(isEmpty()){
				head = new Node(key);
				return;
			}
			Node* curr = head;
			for(; curr->getNext()!=NULLPTR; curr = curr->getNext());
			Node* newNode = new Node(key);
			curr->setNext(newNode);
		}
		int size(){
			return size_;
		}
		vector<int> getElements(){
			vector<int> keys;
			for(Node* node = head; node != NULLPTR; node = node->getNext()){
				keys.push_back(node->getKey());
			}
			return keys;
		}
};
class HashTable{
	int size;
	List* lists;
	
	private:
		vector<int> getKeys(){
			vector<int> keys;
			for(int x =0 ; x < size/2; x++){
				if(!lists[x].isEmpty()){
					vector<int> hold = lists[x].getElements();
					for(int y = 0; y < hold.size(); y++){
						keys.push_back(hold[y]);
					}
				}
			}
			return keys;
		}
		void remake(){
			size *= 2;
			cout << "Hash Table overloaded!\nHash Table\'s size increased. New size = " << size << endl << "Re-inserting Values:" << endl;
			vector<int> keys = getKeys(); //holding keys
			lists = new List[size];
			for(int x = 0; x < keys.size(); x++){
				insert(keys[x]);
			}
		}
	public:
		HashTable(){
		}
		HashTable(int size){
			cout << "Hash Table created of size: " << size << endl;
			this->size = size;
			lists = new List[size];
		}
		int getHash(int key){
			return key % size;
		}
		void insert(int key){
			int hash = getHash(key);
			cout << "Key inserted \'" << key << "\' at hash " << hash << endl;
			if(lists[hash].size() == 3){
				remake();
			}
			lists[hash].insertKey(key);
		}
};
int main(){
	HashTable hashtable(10);
	hashtable.insert(10);
	hashtable.insert(15);
	hashtable.insert(20);
	hashtable.insert(25);
	hashtable.insert(30);
	hashtable.insert(35);
	hashtable.insert(43);
	hashtable.insert(45);
	hashtable.insert(90);
	hashtable.insert(87);
	hashtable.insert(65);
	hashtable.insert(98);
	hashtable.insert(76);
	hashtable.insert(70);
	hashtable.insert(32);
	hashtable.insert(43);
	hashtable.insert(56);
	hashtable.insert(97);
}
