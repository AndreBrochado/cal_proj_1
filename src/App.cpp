#include "App.h"



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

				a.AddUser(name, address);
			}

			if (dummy == ">") {
				getline(in, dummy, '_');
				capacity = atoi(dummy.c_str());
				getline(in, licensePlate, '_');
				getline(in, brand, '>');
				User* u = a.getUsers().back();
				a.AddCar((*u), capacity, licensePlate, brand);

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

void App::AddUser(string name, string address){
	User* u1 = new User(name,address);
	users.push_back(u1);
};

vector <User*> App::getUsers(){
	return users;
};

vector <Car*> App::getCars(){
	return cars;
};


void App::AddCar(User u, int Capacity, string licensePlate, string brand){
	Car* c1 = new Car(Capacity,licensePlate,brand);
	for (unsigned i = 0; i < users.size(); i++){
		if(u ==  (*users[i])){
			users[i]->addCar(*c1);
		}
	}
};

void App :: AddRide(int ID ,time_t departureTime, time_t estimatedArrival, time_t departureTolerance, time_t arrivalTolerance, int noSeats){
	Ride* r1 = new Ride(departureTime,estimatedArrival,departureTolerance,arrivalTolerance, noSeats);
	for (unsigned j = 0; j < users.size(); j++){
				if(ID == (*users[j]).returnID()){
					users[j]->setRide(r1);
				}
	}
};
