#include "Helper.h"
#include "Car.h"
#include "Ride.h"


class User{
	static int ID;
	int userID;
	string name, address, destination;
	vector <User> familiar; //TODO: o que e isto?
	vector <Car> vehicles;
	Ride r;
public:
	User();
	User(string name, string address);
	void addCar(Car c1);
	string returnName();
	string returnAddress();
	string returnDestination();
	vector <Car> getVehicles();
	int returnID();
	void print(ostream &out) const {};
	void setRide(Ride* ride);

	friend bool operator==(const User &u1,const User &u2){
		if(u1.userID== u2.userID){
			return true;
		}
		return false;
	}

	friend ostream& operator<<(ostream& os, const User& u)
	{
		if ( !u.vehicles.empty()){
			for (unsigned i = 0; i < u.vehicles.size(); i++){
			os << u.name << " @" << u.address << "--"<< u.vehicles[i] << endl;
			}

		}
		else {
			os << u.name << " @" << u.address <<endl;
		}
	    return os;
	}

};





