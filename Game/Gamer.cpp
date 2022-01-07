#include"Gamer.h"
#include<iostream>
using namespace std;
Gamer::Gamer(const string &name, int regNo): Person(name), scores{}, accumulative_scores{}{
	this->regNo = regNo;
}

int Gamer::getRegNo() const {
	return this->regNo;
}

void Gamer::addScore(float score,string difficulty){
	this->accumulative_scores[difficulty] = score;
}


ostream& operator<<(ostream &str, const Gamer &s){
	float min = 100,  max = 0, avg = 0;
	for(auto hold: s.scores){
		if(max < hold.second){
			max = hold.second;
		}
		if(min > hold.second){
			min = hold.second;
		}
		avg += hold.second;
	}
	avg /= s.scores.size();
	cout << s.getName() << " " << s.getRegNo() << " " << max << " " << min << " " << avg;
	return str;
}
