#include<iostream>
#include<vector>
using namespace std;
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
			for(int x = 0; x < stack.size(); x++){
				cout << stack[size() - 1 - x] << " ";
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

void roll(Stack<char>& stack, int n, int k){
	if(n < 0 || k < 0 || n > stack.size()){
		//error
		cout << "roll: argument out of range." << endl;
		return;
	}
	for(int x = 0; x < k; x++){ ///outer  ==   number of times to roll
		char hold = stack.top();
		char temp;
		for(int y = n-1; y > 0; y--){
			temp = stack.getItem(stack.size()- 1 - y);
			stack.update(stack.size()-1 - y, hold);
			hold = temp;
		}
		stack.update(stack.size() - 1, hold);
	}
}
int main(){
	Stack<char> stack;
	stack.push('A');
	stack.push('B');
	stack.push('C');
	stack.push('D');
	roll(stack, 3, 2);
	stack.showStack();
}
