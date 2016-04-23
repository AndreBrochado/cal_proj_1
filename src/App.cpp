#include "App.h"
#include "Exceptions.h"



void ReadData(App &a, string filename) {
	ifstream in;
	string file = filename + ".txt";
	in.open(file.c_str(), ios::in);
	if (in.good()) {
		while (in.good()) {
			string dummy;
			string name, adress, licensePlate, brand;
			int capacity;

			getline(in, dummy, '-');

			if (dummy == "<") {
				getline(in, name, '_');
				getline(in, adress, '>');

				a.AddUser(name, adress);
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

void App::AddUser(string name, string adress){
	User* u1 = new User(name,adress);
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
