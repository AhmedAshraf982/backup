#include<iostream>
#include<vector>

using namespace std;
int main(){
	vector<string> sentence;
	for(int x = 0; x < 5; x++){
		string hold;
		cin >> hold;
		sentence.push_back(hold);
	}
	for(int x =0; x < sentence.size(); x++){
		cout << sentence[x] << " ";
	}
}
