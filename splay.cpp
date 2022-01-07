#include<iostream>

using namespace std;

int list_num = 0;

class Node{
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
 
 
class STree{
	
	int splay_op;
	int index;
	private:
		Node *rightRotate(Node *x){
		    Node *y = x->left;
		    x->left = y->right;
		    y->right = x;
		    return y;
		}
        Node *leftRotate(Node *x){
		    Node *y = x->right;
		    x->right = y->left;
		    y->left = x;
		    return y;
		}
		Node *splay(Node *root, int key){
   
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
    	STree(){
    		root = NULL;
    		splay_op = 0;
    		index = 0;
		}
		void insert(int key, string name, string type){
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
        Node *insert_(Node *root, int k, string name, string type){
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

    void traverse_(Node *root){
        if (root != NULL){
		    cout<<root->name << "//" << root->key<< " ";
            traverse_(root->left);
            traverse_(root->right);
		}
    }
    void traverse(){
	    traverse_(root);
    }
	Node* newNode(int key, string name, string type){
		Node* node = new Node(key, name, type);
		return (node);
	}
	int* isPresent_(Node* node, string name, int* arr){
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
	int* isPresent(string name){
		int * arr = new int[100];  //any random size
		for(int x = 0; x < 100; x++){
			arr[x] = -1;
		}
		index = 0;
		return isPresent_(root, name, arr);
	}
	int lookup_(Node* node, string name){
		if (node != NULL){
			if(name.compare(node->name) == 0){
				return node->key;
			}
            return lookup_(node->left, name);
            return lookup_(node->right, name);
		}
		return -1;  //does not exist
	}
	int lookup(string name){
		return lookup_(root, name);
	}
	void getComp(Node* node, Node* root){
		if (root != NULL){
			if(node->key == root->key){
				node->comp++;
			}
            getComp(node, root->left);
            getComp(node, root->right);
		}
	}
	string getType_(Node* node, string name, int level){
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

string* split(string input, char splitter){
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
string trim(string word){
	string hold;
	for(int x = 2; x < word.length(); x++){
		hold.push_back(word[x]);
	}
	return hold;
}
string* getParams(string value){
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

string addBracket(string value_list){
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

bool isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

string checkType(string value, STree tree, int level){
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
int main()
{
    STree tree;
    int** output = new int*[100];
    string errors[100];
    for(int x = 0; x < 100; x++){
    	output[x] = new int[5];
	}
    int level = 0;
    int num_output = 0;
    	int num_error = 0;
    	string input[10];
    	for(int x = 0; x < 5; x++){
    		getline(cin, input[x]);
		}
	for(int x = 0; x < 5; x++){
	if(input[x] == "stop"){
		if(level < 0){
			output[num_output][0] = -1;
			errors[num_error] = "UnknownBlock: END";
			num_output++;
		}else if(level > 0){
			output[num_output][0] = -1;
			errors[num_error] = "UnclosedBlock: BEGIN";
			num_output++;
		}
		break;
	}
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
					Node* node = new Node(key, name, type);
		            tree.insert(key, name, type);
		            output[num_output][0] = tree.root->comp;
		            output[num_output][1] = tree.root->splay;
				}else{
					errors[num_error] = "Redeclared: " + input[x];
				    num_error++;
				    output[num_output][0] = -1;
			    }
			}else{
				errors[num_error] = "InvalidDeclaration: " + input[x];
				num_error++;
				output[num_output][0] = -1;
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
				errors[num_error] = "Redeclared: " + input[x];
				num_error++;
				output[num_output][0] = -1;
			}else{
				Node* node = new Node(key, name, type);
		        tree.insert(key, name, type);
		        output[num_output][0] = tree.root->comp;
		        output[num_output][1] = tree.root->splay;
			}
		}else{
			Node* node = new Node(key, name, type);
		    tree.insert(key, name, type);
		    output[num_output][0] = tree.root->comp;
		    output[num_output][1] = tree.root->splay;
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
				errors[num_error] = "TypeMismatch: " + input[x];
			    num_error++;
			    output[num_output][0] = -1;
			    flag = false;
			}
		}else if(type == "string"){
			if(value_type != "string"){
				errors[num_error] = "TypeMismatch: " + input[x];
			    num_error++;
			    output[num_output][0] = -1;
			    flag = false;
			}
		}else if(value_type.compare("NULL") == 0){
			errors[num_error] = "TypeMismatch: " + input[x];
			    num_error++;
			    output[num_output][0] = -1;
			    flag = false;
		}
	if(type.compare("NULL") == 0){
		errors[num_error] = "Undeclared: " + input[x];
		num_error++;
		output[num_output][0] = -1;
		flag = false;
	}
	if(flag){
		output[num_output][0] = list_num;
    	output[num_output][1] = 1;
	    list_num = 0;
	}
	}else if(parts[0].compare("BEGIN") == 0){
		num_output--;
		level++;
	}else if(parts[0].compare("END") == 0){
		num_output--;
		level--;
	}else if(parts[0].compare("LOOKUP") == 0){
		string name = parts[1];
		int lvl = tree.lookup(name);
		if(lvl == -1){
			errors[num_error] = "Undeclared: " + input[x];
			num_error++;
			output[num_output][0] = -1;
		}else{
			output[num_output][0] = lvl;
		    output[num_output][1] = -1;
		}
	}else if(parts[0].compare("PRINT") == 0){
		output[num_output][0] = -2;   //show tree
	}
	num_output++;
}

int y = 0;
for(int x = 0; x < num_output; x++){
	if(output[x][0] == -1){  //check error
		cout << errors[y];
		y++;
	}else if(output[x][0] == -2){
		tree.traverse();
	}else{
		cout << output[x][0] << " ";
		if(output[x][1] != -1){
			cout << output[x][1];
		}
	}
	cout << endl;
}

}

