#include<iostream>
#include<vector>
using namespace std;
bool isValidSeq(vector<int> array, vector<int> sub){
	vector<int> index;
	for(int x = 0; x < sub.size(); x++){
		bool check = true;
		for(int y = 0; y < array.size(); y++){
			if(array[y] == sub[x]){
				index.push_back(y);
				if(y < index[index.size()-2]){
					return false;
				}
				check = false;
			}
		}
		if(check){
			return false;
		}
	}
	return true;
}
int main(){
	vector<int> array, sub;
	array.push_back(5);
	array.push_back(1);
	array.push_back(22);
	array.push_back(25);
	array.push_back(6);
	array.push_back(-1);
	array.push_back(8);
	array.push_back(10);
	sub.push_back(1);
	sub.push_back(25);
	sub.push_back(22);
	cout << isValidSeq(array, sub);
}
