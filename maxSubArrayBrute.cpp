#include<iostream>
#include<time.h>
#include<cmath>
using namespace std;
int maxSubArray(int* arr, int size){ 
    int max = 0;
	for(int x = 0; x < size; x++){
		int sum = 0;
		for(int y = x; y < size; y++){
			sum += arr[y];
			if(sum > max){
				max = sum;
			}
		}
	}
	return max;
}

int maxSumDp(int* arr, int size){
	int max_sum = arr[0];
	int curr_sum = arr[0];
	for(int x = 1; x < size; x++){
		curr_sum = max(arr[x], arr[x] + curr_sum);
		max_sum = max(max_sum, curr_sum);
	}
	return max_sum;
}
int main(){
	int num = 10;
	srand(time(NULL));
	int arr[num];
	for(int x = 0; x < num; x++){
		arr[x] = rand()%10 - 5;
		cout << arr[x] << " ";
	}
	cout << endl;
	int sum1 = maxSubArray(arr, num);
	int sum2 = maxSumGreedy(arr, num);
	cout << sum1 << " " << sum2;
}
