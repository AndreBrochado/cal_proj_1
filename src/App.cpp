#include "App.h"


void App::AddUser(string name, string adress){
	User* u1 = new User(name,adress);
	users.push_back(u1);
};



void App::AddCar(User u, int Capacity, string licensePlate, string brand){
	Car* c1 = new Car(Capacity,licensePlate,brand);
	for (unsigned i = 0; i < users.size(); i++){
		if(u.returnID() == users[i]->returnID()){
			users[i]->addCar(*c1);
			cout << "added";
		}
		else cout << "not";
	}
};
