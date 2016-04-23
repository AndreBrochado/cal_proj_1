#include "User.h"


using namespace std;

int User::ID = 0;

User::User(string name,string address){
	this->name = name;
	this->address = address;
	userID = ID;
	ID++;

}

void User::addCar(Car c1){
	vehicles.push_back(c1);
};

string User::returnName(){
	return name;
};

int User::returnID(){
		return ID;
	};


vector <Car> User::getVehicles(){
return vehicles;
};
