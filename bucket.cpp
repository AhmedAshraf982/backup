#include<iostream>
#include<time.h>
#define MAX_SIZE 100
using namespace std;
int array[MAX_SIZE];
int count[MAX_SIZE+10];
int sorted[MAX_SIZE];
int num;
void makeArray(){
	srand(time(0));
	for(int x = 0; x < num; x++){
		array[x] = rand()%num;
		count[x] = 0;
	}
}
void countingSort(){
	for(int x = 0; x < num; x++){  //increasing the count
		count[array[x]]++;
	}
	for(int x = 1; x < num; x++){
		count[x] += count[x-1]; 
	}
	for(int x = 0; x < num; x++){
		sorted[count[array[x]]] = array[x];
		count[array[x]]--;
	}
}
int main(){
	num = MAX_SIZE;
	makeArray();
	for(int x = 0; x < num; x++){
		cout << array[x] << " ";
	}
	countingSort();
	cout << endl;
	for(int x = 1; x <= num; x++){
		cout << sorted[x] << " ";
	}
}
