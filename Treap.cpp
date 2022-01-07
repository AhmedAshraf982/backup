#include<iostream>
#define NULLPTR 0
using namespace std;
class User{
	string name;
	string password;
	public:
		User(){
			
		}
		User(string name, string password){
			this->name = name;
			this->password = password;
		}
		string getName(){
			return name;
		}
		string getPass(){
			return password;
		}
		void setUser(string name, string password){
			this->name = name;
			this->password = password;
		}
};
class Node{
	User user;
	int priority;
	Node* left;
	Node* right;
	public:
		Node(){
			left = NULLPTR;
			right = NULLPTR;
		}
		Node(User value, int priority){
			user = value;
			this->priority = priority;
			left = NULLPTR;
			right = NULLPTR;
		}
		string getName(){
			return user.getName();
		}
		string getPass(){
			return user.getPass();
		}
		Node* getLeft(){
			return left;
		}
		Node* getRight(){
			return right;
		}
		void setLeft(Node* left){
			this->left = left;
		}
		void setRight(Node* right){
			this->right = right;
		}
};
class Treap{
	Node* root;
	int priority;  //the user who logs in first has greater priority than the following ones, or in simple words, priority is the rank of the user in registration
	private:
		bool isEmpty(){
			if(root == NULLPTR){
				return true;
			}
			return false;
		}
		void increasePrio(){
			priority++;
		}
		Node* insert_(Node* node, User user){
			if(isEmpty()){
				root = new Node(user, priority);
				increasePrio();
				return NULLPTR;
			}
			if(node == NULLPTR){
				node = new Node(user, priority);
				increasePrio();
				return node;
			}
			if(user.getName() < node->getName()){
				node->setLeft(insert_(node->getLeft(), user));
			}else{
				node->setRight(insert_(node->getRight(), user));
			}
			return node;
		}
		bool checkUser_(Node* node, User user){
			if(node == NULLPTR){
				return false;
			}
			if(node->getName() == user.getName() && node->getPass() == user.getPass()){
				return true;
			}
			if(checkUser_(node->getLeft(), user)){
				return true;
			}
			if(checkUser_(node->getRight(), user)){
				return true;
			}
			return false;
		}
		bool checkUsername_(Node* node, User user){
			if(node == NULLPTR){
				return false;
			}
			if(node->getName() == user.getName()){
				return true;
			}
			if(checkUser_(node->getLeft(), user)){
				return true;
			}
			if(checkUser_(node->getRight(), user)){
				return true;
			}
			return false;
		}
		void displayUsers_(Node* node){
			if(node == NULLPTR){
				return;
			}
			//infix traversal
			displayUsers_(node->getLeft());
			cout << node->getName() << endl;
			displayUsers_(node->getRight());
		}
	public:
		Treap(){
			priority = 1;
			root = NULLPTR;
		}
		void insert(User user){
			insert_(root, user);
		}
		bool checkUser(User user){   //if the user is already registered or not
			return checkUser_(root, user);
		}
		bool checkUsername(User user){
		return checkUsername_(root, user);
		}
		void displayUsers(){
			displayUsers_(root);
		}
		
};
int main(){
	//filling the tree with some random users
	Treap treap;
	User user("Ahmed", "9026040");
	treap.insert(user);
	user.setUser("Bilal", "123456");
	treap.insert(user);
	user.setUser("Abdul", "234234");
	treap.insert(user);
	cout << "Some stored users: " << endl;
	treap.displayUsers();
	
	string name, pass;
	cout << "Enter Username: ";
	cin >> name;
	cout << "Enter Password: ";
	cin >> pass;
	user.setUser(name, pass);
	if(treap.checkUser(user)){
		cout << "Welcome back!";
	}else{
		cout << "User not found! Do you want to register?(y/n)";
		char option;
		cin >> option;
		if(option == 'y' || 'Y'){
			//register the user
			while(1){
				cout << "Enter a Username: ";
				cin >> name;
				cout << "Enter a Password: ";
				cin >> pass;
				user.setUser(name, pass);
				if(!treap.checkUsername(user)){
					treap.insert(user);
					break;
				}
			}
			treap.displayUsers();  //showing users again
		}else{
			cout << "Thanks for visiting!";
		}
	}
}
