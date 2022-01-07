#include "SymbolTable.h"
using namespace std;

int list_num = 0;

class Node{  // Node class to hold the information of each node is splay tree
    public:
    int key;
    string name;
    string type;
    int splay;
    int comp;
    Node *left;
	Node *right;
	
	Node(){
		left = NULL;
		right = NULL;
		splay = 1;
		comp = 0;
	}
	Node(int key, string name, string type){
		this->key = key;
		this->name = name;
		this->type = type;
		left = NULL;
		right = NULL;
		splay = 0;
		this->comp = 0;
	}
};
 
 
class STree{  //splay tree implementation
	
	int splay_op;
	int index;
	private:
		Node *rightRotate(Node *x){  //to rotate the subtree right
		    Node *y = x->left;
		    x->left = y->right;
		    y->right = x;
		    return y;
		}
        Node *leftRotate(Node *x){ //to rotate the subtree left
		    Node *y = x->right;
		    x->right = y->left;
		    y->left = x;
		    return y;
		}
		Node *splay(Node *root, int key){  //to perform splay operation
   
            if (root == NULL || root->key == key)
                return root;
                
             if (root->key > key){
                if (root->left == NULL) return root;
 
                if (root->left->key > key){
            splay_op++;
                    root->left->left = splay(root->left->left, key);
 
    
                    root = rightRotate(root);
                }
                else if (root->left->key < key) 
				{
             
                 splay_op++;
                     root->left->right = splay(root->left->right, key);
 
                if (root->left->right != NULL)
                    root->left = leftRotate(root->left);
                }
 
                return (root->left == NULL)? root: rightRotate(root);
            }else 
            {
                 if (root->right == NULL) return root;
 
                if (root->right->key > key){
                    root->right->left = splay(root->right->left, key);
 
                    if (root->right->left != NULL)
                        root->right = rightRotate(root->right);
				}else if (root->right->key < key)
                {

                    root->right->right = splay(root->right->right, key);
                    root = leftRotate(root);
				}

                return (root->right == NULL)? root: leftRotate(root);
            }
        }
 
    public:
    	Node* root;
    	int getSplay(){
    		return splay_op;
		}
    	STree(){  //default constructor
    		root = NULL;
    		splay_op = 0;
    		index = 0;
		}
		void insert(int key, string name, string type){  //wrapper function to insert a node in tree
			bool check = true;
			if(root == NULL){
				check = false;
			}
			root = insert_(root, key, name, type);
			getComp(root, root);
			if(check){
				root->splay++;
			}
			if(key == 0){
				root->comp--;
			}
			if(key > 0 && root->comp > 1){
				root->comp--;
			}
		}
        Node *insert_(Node *root, int k, string name, string type){  //actual insertion
            if (root == NULL) return newNode(k, name, type);
 
            root = splay(root, k);

            Node *new_node = newNode(k, name, type);
            if (root->key > k){
                new_node->right = root;
                new_node->left = root->left;
                root->left = NULL;
			}

           else{
                new_node->left = root;
                new_node->right = root->right;
                root->right = NULL;
			}
			return new_node; 
        }

    void traverse_(Node *root){  //to print the tree
        if (root != NULL){
		    cout<<root->name << "//" << root->key<< " ";
            traverse_(root->left);
            traverse_(root->right);
		}
    }
    void traverse(){  //wrapper function to traverse the tree
	    traverse_(root);
    }
	Node* newNode(int key, string name, string type){  //to make a new node and return
		Node* node = new Node(key, name, type);
		return (node);
	}
	int* isPresent_(Node* node, string name, int* arr){  //check if a variable is present in the tree, if yes, return the levels of all same named variables
		if (node != NULL){
			if(name.compare(node->name) == 0){
				arr[index] = node->key;
				index++;
			}
            return isPresent_(node->left, name, arr);
            return isPresent_(node->right, name, arr);
		}
		return arr;
	}
	int* isPresent(string name){  //wrppaer function to call the actual above isPresent
		int * arr = new int[100];  //any random size
		for(int x = 0; x < 100; x++){
			arr[x] = -1;
		}
		index = 0;
		return isPresent_(root, name, arr);
	}
	int lookup_(Node* node, string name){  //to look for a variable
		if (node != NULL){
			if(name.compare(node->name) == 0){
				return node->key;
			}
            return lookup_(node->left, name);
            return lookup_(node->right, name);
		}
		return -1;  //does not exist
	}
	int lookup(string name){  //wrapper function
		return lookup_(root, name);
	}
	void getComp(Node* node, Node* root){   //to get the number of comparisons for a node in the tree
		if (root != NULL){
			if(node->key == root->key){
				node->comp++;
			}
            getComp(node, root->left);
            getComp(node, root->right);
		}
	}
	string getType_(Node* node, string name, int level){ // to get the type of a variable or a function
		if(node != NULL){
			if(node->name == name && node->key == level){
				return node->type;
			}
			return getType_(node->left, name, level);
			return getType_(node->right, name, level);
		}
		return "NULL";   //not declared
	}
	string getType(string name, int level){
		return getType_(root, name, level);
	}
};

string* split(string input, char splitter){  //helping function to split a string into substrings
	string* parts = new string[10];  //max size of 10, can be any
	for(int x = 0; x < 10; x++){
		parts[x] = "";
	}
	int x = 0;
	int index = 0;
	while(x < input.length()){
		while(input[x] != splitter){
			parts[index] += input[x];
			x++;
			if(x == input.length()){
				break;
			}
		}
		index++;
		x++;
	}
	return parts;
}
string trim(string word){  //to trim a string
	string hold;
	for(int x = 2; x < word.length(); x++){
		hold.push_back(word[x]);
	}
	return hold;
}
string* getParams(string value){  //to get a list of parameters of a function as substrings
	string* params = new string[100]; //max size 100, can be changed
	for(int x = 0; x < 100; x++){
		params[x] = "NULL";
	}
	string* parts = new string[3];
	for(int x = 0; x < 3; x++){
		parts[x] = "NULL";
	}
	parts = split(value, '(');
	params = split(parts[1], ',');
	int x = 0;
	while(params[x] != "")    //finding the index fo the last element
		x++;
	parts = split(params[x-1], ')');
	params[x-1] = parts[0];
	string return_type = trim(parts[1]);
	params[x] = return_type;
	return params;
}

string addBracket(string value_list){  //helping function
	string hold = "(";
	for(int x = 0; x < value_list.length(); x++){
		hold += value_list[x];
	}
	return hold;
}
bool value_type(string value, string type){
	if(value[0] == '\''){
	     if(type == "string"){
	     	return true;
		 }	else if(type == "number"){
		 	return false;
		 }
	}else{
		if(type == "string"){
	     	return false;
		 }	else if(type == "number"){
		 	return true;
		 }
	}
}

bool isNumber(const string& str){  //to check if a string has numbers only
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

string checkType(string value, STree tree, int level){  //to check type of variable
	string* parts = new string[10];
	for(int x = 0; x < 10; x++){
		parts[x] = "NULL";
	}
	parts = split(value, '(');
	if(parts[0].compare(value) == 0){  //either integer or single variable
	
	    if(isNumber(value)){
	    	list_num++;
	    	return "number";
		}else if(value[0] == '\''){
			list_num++;
			return "string";
		}
		string type = tree.getType(value, level);
		list_num = 2;
		return type;
	}else{  //function
	    string name = tree.getType(parts[0], 0);
	    int params_num = 0;
	    int values_num = 0;
	    string* params = new string[100];
	    for(int x = 0; x < 100; x++){
	    	params[x] = "";
		}
	    params = getParams(name);
	    int z = 0;
	    while(params[z] != "") z++;
	    ///removing the return type
	    string return_type = params[z-1];
	    params[z-1] = "";
	    string* values = new string[100];
	    for(int x = 0; x < 100; x++){
	    	values[x] = "";
		}
		string* value_parts = new string[3];
		for(int x = 0; x < 3; x++){
			value_parts[x] = "";
		}
		value_parts = split(value, '(');
		value_parts[1] = addBracket(value_parts[1]);
		values = getParams(value_parts[1]);
		while(params[params_num] != "") params_num++;
		while(values[values_num] != "") values_num++;
		if(params_num != values_num){
			return "NULL";
		}
		int x = 0;
		while(values[x] != ""){
			list_num++;
			if(!value_type(values[x], params[x])){
				return "NULL";
			}
			x++;
		}
		list_num++;
		return return_type;
	}
}

string* getLines(string filename){  //to get all the lines of inputs from given filename
	fstream file;
	file.open(filename, ios::in);
	string* lines = new string[100];  //max size
	for(int x = 0; x < 100; x++){
		lines[x] = "";
	}
	int x = 0;
	while(!file.eof()){
		getline(file, lines[x]);
		x++;
	}
	return lines;
}
void SymbolTable::run(string filename){  //implemntation of given run funciton
	int x = 0;
	string* input = new string[100];
	for(int x = 0; x < 100; x++){
		input[x] = "";
	}
	input = getLines(filename);
	int y = 0;
	while(input[y] != ""){
		y++;
	}
	int total_lines = y;
	STree tree;
    int level = 0;
	for(int x = 0; x < total_lines; x++){
	    string* parts = new string[10];
	    parts = split(input[x], ' ');
	    if(parts[0] == "INSERT"){
		    string name = parts[1];
		    string type = parts[2];
		    string global = parts[3];
		    int key = level;
		    if(global.compare("true") == 0){
			    key = 0;
		    }
		    if(parts[2][0] == '('){  //checking a function
			    if(key == 0){
				    int* re_key = tree.isPresent(name);
				    if(re_key[0] == -1){
//					    Node* node = new Node(key, name, type);
		                tree.insert(key, name, type);
		                cout << tree.root->comp << " " << tree.root->splay << endl;
				    }else{
//					    cout << "Redeclared: " << input[x] << endl;
					    throw Redeclared(input[x]);
			        }
			    }else{
//				    cout << "InvalidDeclaration: " << input[x] << endl;
				    throw InvalidDeclaration(input[x]);
			    }
		    }else{
			    int* re_key = new int[100];
			    re_key = tree.isPresent(name);
			    if(re_key[0] != -1){
				    bool check = false;
				    for(int x = 0; x < 10; x++){
					    if(level == re_key[x]){
						    check = true;
					    }
				    }
				    if(check){
					    throw Redeclared(input[x]);
				    }else{
//					    Node* node = new Node(key, name, type);
			            tree.insert(key, name, type);
			            cout << tree.root->comp << " " << tree.root->splay << endl;
				    }
			    }else{
//				    Node* node = new Node(key, name, type);
			        tree.insert(key, name, type);
			        cout << tree.root->comp << " " << tree.root->splay << endl;
			    }
	        }
 	    }else if(parts[0].compare("ASSIGN") == 0){
		    string name = parts[1];
		    string value = parts[2];
		    string type = tree.getType(name, level);
		    string value_type = checkType(value, tree, level);
		    bool flag = true;
		    if(type == "number"){
			    if(value_type != "number"){
//				    cout << "TypeMismatch: " << input[x] << endl;
                    throw TypeMismatch(input[x]);
			        flag = false;
			    }
		    }else if(type == "string"){
			    if(value_type != "string"){
//				    cout << "TypeMismatch: " << input[x] << endl;
                    throw TypeMismatch(input[x]);
			        flag = false;
			    }
		    }else if(value_type.compare("NULL") == 0){
//			    cout << "TypeMismatch: " << input[x] << endl;
                throw TypeMismatch(input[x]);
			    flag = false;
		    }
	    if(type.compare("NULL") == 0 && flag){
//		    cout << "Undeclared: " << input[x] << endl;
		    throw Undeclared(input[x]);
		    flag = false;
	    }
	    if(flag){
		    cout << list_num << " " << 1 << endl;
	        list_num = 0;
	    }
	}else if(parts[0].compare("BEGIN") == 0){
		level++;
	}else if(parts[0].compare("END") == 0){
		level--;
	}else if(parts[0].compare("LOOKUP") == 0){
		string name = parts[1];
		int lvl = tree.lookup(name);
		if(lvl == -1){
//			cout << "Undeclared: " << input[x] << endl;
            throw Undeclared(input[x]);
		}else{
			cout << lvl << endl;
		}
	}else if(parts[0].compare("PRINT") == 0){
		tree.traverse();   //show tree
	}
	}

	if(level < 0){
//		cout << "UnknownBlock: END" << endl;
		throw UnknownBlock();
	}else if(level > 0){
//		cout << "UnclosedBlock: BEGIN" << endl;
		throw UnclosedBlock(level);
    }
}
