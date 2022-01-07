#include<iostream>
#include<cstring>
using namespace std;
int main(){
	char* arr = new char[20];
	char* hold = gets(arr);
	hold = !hold;
	cout << hold;
}
