#include<iostream>
using namespace std;

void pop_back(string& hold){
	string temp;
	for(int x = 0; x < hold.length()-1; x++){
		temp.push_back(hold[x]);
	}
	hold = temp;
}
void powerSet(string members, string hold, int pos){
	for(int x = pos; x < members.length(); x++){
		hold.push_back(members[x]);
		cout << "{";
		for(int y = 0; y < hold.length(); y++){
			cout << hold[y];
			if(y != hold.length()-1){
				cout << ", ";
			}
		}
		cout << "}, ";
		powerSet(members, hold, x+1);
		pop_back(hold);
	}
}
int main(){
	int num;
	cout << "Enter number of set elements: ";
	cin >> num;
	cout << "Enter elements of set:";
	string members;
	for(int x = 0; x < num; x++){
		cout << "Enter element# " << x+1 << ": ";
		char element;
		cin >> element;
		members.push_back(element);
	}
	cout << "The power set would be: {}, ";
	string hold;
	powerSet(members, hold, 0);
	cout << "\b\b ";
}
