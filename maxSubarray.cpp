#include<iostream>
#include<time.h>
using namespace std;
int maxSub(int* arr, int low, int high){
	int size = high - low;
	if(size <= 2){
		//return
		if(size == 1){
			return arr[low];
		}
		int sum1 = arr[low];
		int sum2 = arr[high-1];
		int sum_ = sum1 + sum2;
		if(sum_ > sum1 && sum_ > sum2){
			return sum_;
		}else if(sum1 > sum2){
			return sum1;
		}else
		    return sum2;
	}
	int mid = size/2;
	int left[size];
	int right[size];
	int y = 0;
	for(int x = low; x < mid; x++){
		left[y] = arr[x];
		y++;
	}
	y = 0;
	for(int x = mid; x < high; x++){
		right[y] = arr[x];
		y++;
	}
	int sum1 = maxSub(arr, low, mid);
	bool right_most = false;
	if(sum1 == arr[low]){  //only left
		right_most = false;
	}
	if(sum1 == arr[mid-1]){
		right_most = true;
	}
	else if(sum1 == arr[low] + arr[mid-1]){
		right_most = true;
	}
	int sum2 = maxSub(arr, mid, high);
	bool left_most = false;
	if(sum2 == arr[high-1]){
		left_most = false;
	}
	if(sum2 == arr[mid]){  //only left
		left_most = true;
	}
	else if(sum2 == arr[mid] + arr[high-1]){
		left_most = true;
	}
	int sum = 0;
	if(left_most && right_most){
		sum = (sum1 + sum2);
	}else if(sum1 > sum2){
		sum = sum1;
	}else{
		sum = sum2;
	}
	return sum;
}
int main(){
	int num = 10;
	int arr[num] = {1, 4};
	int sum = maxSub(arr, 0, 4);
	cout << sum;
}
