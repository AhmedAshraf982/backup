#include<iostream>
using namespace std;
float* divided_difference(float x[], float fx[], int points){
	float* dff = new float[points];
	float* hold = new float[points];
	dff[0] = fx[0];
	for(int i = 0; i < points; i++){
		hold[i] = fx[i];
	}
	for(int i = 0; i < points-1; i++){
		float* hold2 = new float[points-i-1];
		for(int j = 0; j < points-i-1; j++){
			hold2[j] = (hold[j+1] - hold[j]) / (x[j+i+1] - x[j]);
		}
		for(int j = 0; j < points-i-1; j++){
			hold[j] = hold2[j];
		}
		dff[i+1] = hold[0];
	}
	return dff;
}
int main(){
	int num;
	cin >> num;
	float x[num];
	float fx[num];
	for(int i = 0; i < num; i++){
		cin >> x[i] >> fx[i];
	}
	float req;
	cin >> req;
	float sum = 0;
	float* diff = divided_difference(x, fx, num);
	cout << endl;
	for(int i = 0; i < num; i++){
		float product = 1;
		for(int j = 0; j < i; j++){
			product *= (req - x[j]);
		}
		sum += product*diff[i];
	}
	cout << sum;
}
