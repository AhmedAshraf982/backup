#include<iostream>
#include<vector>
using namespace std;
vector<int> getPrevSmall(vector<int> list){
	vector<int> small;
	for(int x = 0; x < list.size(); x++){
		if(x == 0){
			small.push_back(-1);
		}else{
			bool flag = true;
			for(int y = x-1; y >= 0; y--){
				if(list[y] < list[x]){
					small.push_back(list[y]);
					flag = false;
					break;
				}
			}
			if(flag){
				small.push_back(-1);
			}
		}
	}
	return small;
}
int main(){
	cout << "Enter size of the list: ";
	int num;
	cin >> num;
	vector<int> list;
	int hold;
	for(int x = 0; x < num; x++){
		cin >> hold;
		list.push_back(hold);
	}
	vector<int> prevSmall = getPrevSmall(list);	
	for(int x = 0; x < prevSmall.size(); x++){
		cout << prevSmall[x] << " ";
	}
}
