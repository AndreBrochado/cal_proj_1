#include "User.h"


using namespace std;

int User::ID = 0;

User::User(string name,string address){
	this->name = name;
	this->address = address;
	ID++;

}

void User::addCar(Car c1){
	vehicles.push_back(c1);
};

string User::returnName(){
	return name;
};


