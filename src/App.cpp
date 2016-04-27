#include "App.h"
#include "RideRequest.h"
#include "RideOffer.h"


void ReadData(App &a, string filename) {
	ifstream in;
	string file = filename + ".txt";
	in.open(file.c_str(), ios::in);
	if (in.good()) {
		while (in.good()) {
			string dummy;
			string name, address, licensePlate, brand;
			int capacity;

			getline(in, dummy, '-');

			if (dummy == "<") {
				getline(in, name, '_');
				getline(in, address, '>');

				a.addUser(name, address);
			}

			if (dummy == ">") {
				getline(in, dummy, '_');
				capacity = atoi(dummy.c_str());
				getline(in, licensePlate, '_');
				getline(in, brand, '>');
				User* u = a.getUsers().back();
				a.addCar((*u), capacity, licensePlate, brand);

			}

			if (!in.eof())
				in.ignore(1000, '\n');

			if (in.eof()) {
				return;
			}

		}
	}
	if (in.fail())
		throw FileReadingError();

	in.close();
}

void App::addUser(string name, string address){
	User* u1 = new User(name,address);
	users.push_back(u1);
};

vector <User*> App::getUsers(){
	return users;
};

vector <Car*> App::getCars(){
	return cars;
};


void App::addCar(User u, int Capacity, string licensePlate, string brand){
	Car* c1 = new Car(Capacity,licensePlate,brand);
	for (unsigned i = 0; i < users.size(); i++){
		if(u ==  (*users[i])){
			users[i]->addCar(*c1);
		}
	}
};

void App::addRideRequest(User* user , uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats){
	Ride* r = new RideRequest(departurePlace, arrivalPlace, departureTime,departureTolerance,arrivalTolerance, noSeats, user);
	requests.push_back(r);
};

void App::addRideOffer(User* user , uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats){
    Ride* r = new RideOffer(departurePlace, arrivalPlace, departureTime, departureTolerance,arrivalTolerance, noSeats, user);
    requests.push_back(r);
};
