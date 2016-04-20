#include "Helper.h"
#include "Car.h"

class User{
	static int ID;
	string name, address, destination;
	vector <User> familiar; //TODO: o que e isto?
	vector <Car> vehicles;
public:
	User();
	User(string name, string address);
	void addCar(Car c1);
	string returnName();
	string returnAddress();
	string returnDestination();
	int returnID();


	friend bool operator==(const User &u1,const User &u2){
		if(u1.name == u2.name){
			return true;
		}
		return false;
	}
};





