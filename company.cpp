#include<iostream>
#include<vector>
using namespace std;

void initializeOrders(vector<int>& orders){
	for(int x = 1; x <= 10; x++){
		orders.push_back(x);
	}
}

void removeElement(vector<int>& list, int elem){
	vector<int> hold;
	for(int x = 0; x < list.size(); x++){
		if(list[x] != elem){
			hold.push_back(list[x]);
		}
	}
	list = hold;
}
void executeQueries(vector<int>& pending, vector<int>& delivered, vector<int>& cancelled, vector<int>& queries, int num){
	for(int x = 0; x < num*2; x+=2){
		int id, order;
		id = queries[x];
		order = queries[x+1];
		if(id == 1){
			//pending to delivered
			removeElement(pending, order);
			delivered.push_back(order);
		}else if(id == 2){
			//delivered to cancelled
			removeElement(delivered, order);
			cancelled.push_back(order);
		}else if(id == 3){
			//pending to cancelled
			removeElement(pending, order);
			cancelled.push_back(order);
		}else if(id == 4){
			//cancelled to delivered
			removeElement(cancelled, order);
			delivered.push_back(order);
		}
	}
	
}
int main(){
	vector<int> pending;
	vector<int> delivered;
	vector<int> cancelled;
	initializeOrders(pending);
	cout << "Enter number of queries: ";
	int queries;
	cin >> queries;
	vector<int> query;
	for(int x = 0; x < queries; x++){
		int id, order;
		cin >> id >> order;
		query.push_back(id);
		query.push_back(order);
	}
	executeQueries(pending, delivered, cancelled, query, queries);
	cout << "Pending: ";
	for(int x = 0; x < pending.size(); x++){
		cout << pending[x] << " ";
	}
	cout << endl << "Delivered: ";
	for(int x = 0; x < delivered.size(); x++){
		cout << delivered[x] << " ";
	}
	cout << endl << "Cancelled: ";
	for(int x = 0; x < cancelled.size(); x++){
		cout << cancelled[x] << " ";
	}
}
