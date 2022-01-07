#include<iostream>
//include files here.


using namespace std;

void gameOptions(){
	cout << "1) Play Game.\n2) Your statistcs\n3) Display top 10\n4) Exit game";
}

void managerOptions(){
	cout << "1) Reset Game.\n2) Change game levels\n3) Add another layout\n4) Set the word file\n5) Exit game";
}
using namespace std;
int main(){
	 cout << "Enter option number:\n1. Press '1' to select \'Manager\'.\n2. Press '2' to select \'Gamer\'.\n";
	 int option;
	 cin >> option;
	 if(option == 1){
	 	managerOptions();
	 }else if(option == 2){
	 	gameOptions();
	 }
}
