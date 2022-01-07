#include<iostream>
#include<vector>
using namespace std;
long getSum(vector<int> temp){
	long sumEven = 0;
	long sumOdd = 0;
	for(long x = 0; x < temp.size(); x++){
		if(x % 2 == 0){
			sumEven += temp[x];
		}else{
			sumOdd += temp[x];
		}
	}
	long sum = sumEven - sumOdd;
	return sum*sum;
}
void printVector(vector<int> temp){
	for(int x = 0; x < temp.size(); x++){
		cout << temp[x] << "\t";
	}
	cout << endl;
}
long getMax(vector<int> arr, int pos){
	long max = 0;
	for(long x = 0; x < arr.size(); x++){
		for(long y = x; y < arr.size(); y++){
			vector<int> temp;
			for(long z = x; z <=y; z++){
				temp.push_back(arr[z]);
			}
			long sum = getSum(temp);
			if(sum > max){
				max = sum;
			}
		}
	}
	return max;
}
int main(){
	int num;
	cin >> num;
	vector<int> arr;
	int hold;
	for(int x = 0 ; x < num; x++){
		cin >> hold;
		arr.push_back(hold);
	}
	vector<int> temp;
	cout << getMax(arr, 0);
}
