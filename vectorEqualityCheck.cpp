#include<iostream>
#include<vector>
using namespace std;
int main(){
	vector<int> v1, v2;
	for(int x = 0; x < 10; x++){
		v2.push_back(x);
		v1.push_back(x);
	}
	v1.push_back(12323);
	if(v1 == v2){
		cout << "equal";
	}
}
