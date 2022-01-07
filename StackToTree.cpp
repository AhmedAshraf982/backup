#include<iostream>
#include<vector>
#define NULLPTR 0
using namespace std;
class Node{
	char operator_;
	int value;
	Node* left;
	Node* right;
	public:
		Node(){
			left = NULLPTR;
			right = NULLPTR;
		}
		Node(int val, char opr){
			operator_ = opr;
			value = val;  // opr != N, val = -1
			left = NULLPTR;
			right = NULLPTR;
		}
		void showItem(){
			if(value == -1)
				cout << operator_ << " ";
			else
				cout << value << " ";
		}
		Node* getLeft(){
			return left;
		}
		Node* getRight(){
			return right;
		}
		void setLeft(Node* lft){
			left = lft;
		}
		void setRight(Node* rgt){
			right = rgt;
		}
		int getValue(){
			return value;
		}
};
template <class A>
class Stack{
	vector<A> stack;
	public:
		Stack(){
		}
		void push(A element){
			stack.push_back(element);
		}
		A pop(){
			A hold = stack[stack.size()-1];
			stack.pop_back();
			return hold;
		}
		void showStack(){
			for(int x = stack.size()-1; x >=0 ; x--){
				stack[size() - 1 - x]->showItem();
			}
			cout << endl;
		}
		int size(){
			return stack.size();
		}
		A top(){
			return stack[stack.size()-1];
		}
		void update(int pos, A value){
			stack[pos] = value;
		}
		A getItem(int pos){
			return stack[pos];
		}
};
Node* makeTree(Stack<Node*>& expression){
	static int pos = 1;
	if(expression.size() == 0 || pos == expression.size())
		return NULLPTR;
	Node* node = expression.getItem(expression.size() - pos);   //at pos == 1, node == root
	pos++;
	Node* left = expression.getItem(expression.size() - pos);
	node->setLeft(left);
	if(left->getValue() == -1)
		makeTree(expression);
	pos++;
	Node* right = expression.getItem(expression.size() - pos);
	node->setRight(right);
	if(right->getValue() == -1)
		makeTree(expression);
	return node;
}
void infix(Node* node){   //to check, we print the tree in infix form
	if(node == NULLPTR)
		return;
		infix(node->getLeft());
		node->showItem();
		infix(node->getRight());
}
int main(){
	Stack<Node*> stack;
	Node* node = new Node(3, ' ');
	stack.push(node);
	node = new Node(6, ' ');
	stack.push(node);
	node = new Node(5, ' ');
	stack.push(node);
	node = new Node(-1, '*');
	stack.push(node);
	node = new Node(7, ' ');
	stack.push(node);
	node = new Node(2, ' ');
	stack.push(node);
	node = new Node(-1, '*');
	stack.push(node);
	node = new Node(-1, '+');
	stack.push(node);
	node = new Node(-1, '+');
	stack.push(node);
	cout << "Before Making Tree:" << endl;
	stack.showStack();
	Node* root = NULLPTR;
	cout << "After Making Tree: " << endl;
	root = makeTree(stack);
	infix(root);
}
