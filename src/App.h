#include <exception>

#include "GraphViewer.h"
#include "Graph.h"
#include "Handler.h"
#include "User.h"
#include "Exceptions.h"



class App{
		vector <User*> users;
		vector <Car*> cars;
		vector <Ride*> requests, offers, completed;
public:
		App(){};
		friend void ReadData(App &a, string filename);
		void addUser(string name, string address);
		void addCar(User u, int Capacity, string licensePlate, string brand);
		void addRideRequest(int ID, time_t departureTime, time_t estimatedArrival, time_t departureTolerance, time_t arrivalTolerance, int noSeats);
	    void addRideOffer(int ID, time_t departureTime, time_t estimatedArrival, time_t departureTolerance, time_t arrivalTolerance, int noSeats);
		vector <User*> getUsers();
		vector <Car*> getCars();
};
