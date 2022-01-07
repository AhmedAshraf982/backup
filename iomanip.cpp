#include<iostream>
#include<iomanip>
using namespace std;
int main(){
	float a = 9.2323;
	std::fixed(cout);
	cout << setprecision(3)  << a;
}
