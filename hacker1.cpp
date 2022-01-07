#include<iostream>
using namespace std;
void popback(string& str){
	string hold;
	for(int x = 0; x < str.length()-1; x++){
		hold.push_back(str[x]);
	}
	str = hold;
}
long getMax(string newName, string oldName){
	long count = 0;
	for(long x = 0; x < oldName.length(); x++){
		for(long y = x; y < oldName.size(); y++){
			string hold;
			for(long z = x; z <=y; z++){
				hold.push_back(oldName[z]);
			}
			if(hold == newName){
				count++;
			}
		}
	}
	return count;
}
int main(){
	string newName, oldName;
	cin >> newName >> oldName;
	string prev;
	cout << getMax(newName, oldName);
}
