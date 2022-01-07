#include <math.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Difference {
    private:
    vector<int> elements;
  
  	public:
  	int maximumDifference;
	// Add your code here
    Difference(){}
    Difference(vector<int> elements){
        this->elements = elements;
    }
    int computeDifference(){
        int max = 0;
        for(int x = 0; x < elements.size() - 1; x++){
            for(int y = x+1; y < elements.size(); y++){
                max = abs(elements[x] - elements[y]) > max ? abs(elements[x] - elements[y]) : max;
            }
        }
        return max;
    }
}; // End of Difference class

int main() {
    int N;
    cin >> N;
    
    vector<int> a;
    
    for (int i = 0; i < N; i++) {
        int e;
        cin >> e;
        
        a.push_back(e);
    }
    
    Difference d(a);
    
    d.computeDifference();
    
    cout << d.maximumDifference;
    
    return 0;
}
