#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;
class Node{  //class to hold the details of software package
	string code;
	string name;
	string version;
	float price;
	Node* left;
	Node* right;
	public:
		Node(){   //defualt constructor
			left = NULL;
			right = NULL;
		}
		Node(string code, string name, string version, float price){  //parameterized constructor to set the details of the package
			this->code = code;
			this->name = name;
			this->version = version;
			this->price = price;
			left = NULL;
			right = NULL;
		}
		void setLeft(Node* left){  //to set the left node 
			this->left = left;
		}
		void setRight(Node* right){  //to set the right node
			this->right = right;
		}
		string getCode(){  //to get the code of the packge
			return code;
		}
		string getName(){  //to get the name
			return name;
		}
		string getVersion(){  //to get the version
			return version;
		}
		float getPrice(){  //to get the price
			return price;
		}
		Node* getLeft(){  //to get the left node
			return left;
		}
		Node* getRight(){  //to get the right node
			return right;
		}
		void setCode(string code){   // to set the code
			this->code = code;
		}
};
class Tree{   // the binary search tree class
	Node* root;
	bool status;  // to check if the value in the tree is inserted or removed successfully, it is set to be true if yes, else false
	private:
		bool isEmpty(){  //checks if the tree is empty
			if(root == NULL){
				return true;
			}
			return false;
		}
		Node* insert_(Node* node, Node package){   //to insert the node
			if(isEmpty()){
				root = new Node(package.getCode(), package.getName(), package.getVersion(), package.getPrice());
				return root;
			}
			if(node == NULL){
				node = new Node(package.getCode(), package.getName(), package.getVersion(), package.getPrice());
				return node;
			}
			if(package.getCode() < node->getCode()){
				node->setLeft(insert_(node->getLeft(), package));
			}else if(package.getCode() > node->getCode()){
				node->setRight(insert_(node->getRight(), package));
			}else{
				status = false;   // if same code is found, we raise an error and the node is not inserted
			}
			return node;
		}
        Node* minValueNode(Node* node){  // to find the minimum code value in the tree, this function is used in removing a node
            Node* current = node;
            while (current && current->getLeft() != NULL)
                current = current->getLeft();
            return current;
		}
        Node* remove_(Node* node, string code){  //to remove the node
		    if (node == NULL){
		    	status = false;
		    	return node;
			}
		    if (code < node->getCode())
		        node->setLeft(remove_(node->getLeft(), code));
		    else if (code > node->getCode())
		        node->setRight(remove_(node->getRight(), code));
		    else {
		        if (node->getLeft() == NULL && node->getRight() == NULL)
		            return NULL;
		        else if (node->getLeft() == NULL) {
		            Node* temp = root->getRight();
		            delete node;
		            return temp;
		        }
		        else if (node->getRight() == NULL) {
		            Node* temp = node->getLeft();
		            delete node;
		            return temp;
		        }
		        Node* temp = minValueNode(node->getRight());
		        node->setCode(temp->getCode());
		        node->setRight(remove_(node->getRight(), temp->getCode()));
		    }
		    return node;
		}
		void traverse_(Node* node){  //to print the tree values
			if(node == NULL){
				return;
			}
			traverse_(node->getLeft());
			if(node->getName() != ""){
				cout << "Code: " << node->getCode() << endl << "Name: " << node->getName() << endl << "Version: " << node->getVersion() << endl << "Price: " << node->getPrice() << endl << "----------------------------------" << endl; 
			}
			traverse_(node->getRight());
		}
		void clearStatus(){  //sets the status back to true
			status = true;
		}
	public:
		Tree(){
			root = NULL;
			status = true;
		}
		bool insert(Node package){  //wrapper function to call the actual insert function
			insert_(root, package);
			bool temp = status;
			clearStatus();
			return temp;
		}
		bool remove(string code){  //wrapper function to call the actual remove function
			remove_(root, code);
			bool temp = status;
			clearStatus();
			return temp;
		}
		void traverse(){ //wrapper function to call the actual traverse function
			traverse_(root);
		}
};
void loadPackages(Tree& tree){   //funtion to load the software packages from the software.txt file to the binary search tree
	fstream file;
	file.open("software.txt", ios::in);
	while(!file.eof()){
		string code, name, version;
		float price;
		getline(file, code);
		getline(file, name);
		getline(file, version);
		Node* node = new Node(code, name, version, price);
		tree.insert(*node);
	}
	file.close();
}
void insertInFile(Node node){  //funtion to insert a software package to the file
	fstream file;
	file.open("software.txt", ios::app);
	file << endl << node.getCode() << endl;
	file << node.getName() << endl;
	file << node.getVersion() << endl;
	file << node.getPrice();
	file.close();
}
void removeFromFile(string code_){   //function to remove a software package from the file
	fstream file;
	file.open("software.txt", ios::in);
	fstream temp;
	temp.open("temp.txt", ios::out);
	while(!file.eof()){
		string code, name, version;
		float price;
		file >> code >> name >> version >> price;
		if(code != code_ && code != ""){
			temp << code << endl << name << endl << version << endl << price << endl;
		}
	}
	file.close();
	temp.close();
	remove("software.txt");
	rename("temp.txt", "software.txt");
}
int main(){  //driver code to test the cases
	Tree tree;
	loadPackages(tree);
	while(1){
		cout << "\nEnter option number:\n1. Press '1' to show the packages in the record.\n2. Press '2' to add a new software package.\n3. Press '3' to delete a software package.\n4. Press any other key to exit."; 
        int option;
        cin >> option;
        switch(option){
        	case 1:   //print the packages
        		{
        			tree.traverse();
        			break;
				}
			case 2:   //add a new software 
				{
					string code, name, version;
					float price;
					cout << "Enter the details of the software package:" << endl;
					cout << "Enter Code: ";
					cin >> code;
					cout << "Enter Name: ";
					fflush(stdin);
					getline(cin, name);
					cout << "Enter Version: ";
					cin >> version;
					cout << "Enter Price: ";
					cin >> price;
					Node* node = new Node(code, name, version, price);
					if(tree.insert(*node)){
						cout << "Software package has been inserted!" << endl;
						insertInFile(*node);
					}else{
						cout << "Software with given code \'" << code << "\' is already available!";
					}
					break;
				}
			case 3:  //delete a software package
				{
					cout << "Enter code of the software package to remove: ";
					string code;
					cin >> code;
					if(tree.remove(code)){
						cout << "Software package has been removed!";
					}else{
						cout << "No such software exists with code \'" << code << "\'!"<< endl;
					}
					break;
				}
			default:  //exits the application 
				exit(0);
		}
		
	}
}
