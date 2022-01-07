#include<iostream>

using namespace std;
int main(){
	int n = 10;
	for(int x = 0; x < n; x++){
		for(int j = 0; j < n; j+=x){
			cout << "hello world" << endl;
			break;
		}
	}
}
