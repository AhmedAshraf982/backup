#include "Manager.h"

using namespace std;

Manager::Manager(const string &name, int regNo): Person(name){
	this->regNo = regNo;
}

int Manager::getRegNo() const {
	return this->regNo;
}
