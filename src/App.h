#include <exception>

#include "GraphViewer.h"
#include "Graph.h"
#include "Handler.h"
#include "RideOffer.h"
#include "RideRequest.h"
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
		void addRideRequest(User* user , uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats);
	    void addRideOffer(User* user , uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats);
	    void matchRides(RideOffer offer, RideRequest request);
	    vector <User*> getUsers();
		vector <Car*> getCars();
};
