#include "Helper.h"
#include "Car.h"

class User{
	static int ID;
	int userID;
	string name, address;
	vector <Car> vehicles;
public:
	User(string name, string address);
	void addCar(Car c1);
	vector <Car> getVehicles();

    int getUserID() const {
        return userID;
    }
    const string &getName() const {
        return name;
    }
    const string &getAddress() const {
        return address;
    }

    void print(ostream &out) const {};

	friend bool operator==(const User &u1,const User &u2){
		return u1.userID == u2.userID;
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





