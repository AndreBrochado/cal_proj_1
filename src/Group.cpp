#include "Group.h"

using namespace std;

Group::Group(Car c){
	this->c= c;
}

void Group::addUser(User u){
	users.push_back(u);
}

void Group::changeCar(Car c){
	this->c = c;
}

vector <User> Group::returnUsers(){
	return users;
}

Car Group::returnCar(){
	return c;
}
