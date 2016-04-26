#include <exception>

#include "GraphViewer.h"
#include "Graph.h"
#include "Handler.h"
#include "User.h"
#include "Exceptions.h"



class App{
		vector <User*> users;
		vector <Car*> cars;
		vector <Ride*> rides;
public:

		friend void ReadData(App &a, string filename);
		void AddUser(string name, string address);
		void AddCar(User u, int Capacity, string licensePlate, string brand);
		void AddRide(int ID, time_t departureTime, time_t estimatedArrival, time_t departureTolerance, time_t arrivalTolerance, int noSeats);
		vector <User*> getUsers();
		vector <Car*> getCars();
		vector <Ride*> getRides();
};
