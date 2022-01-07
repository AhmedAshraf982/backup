#include<iostream>
using namespace std;
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
int main(){
	string input;
	getline(cin, input);
	string* parts = new string[10];
	parts = split(input, ' ');
	
	if(parts[0] == "INSERT"){
		cout << "insert command:" << endl;
		string identifier = parts[1];
		string type = parts[2];
		string global = parts[3];
	}
}
