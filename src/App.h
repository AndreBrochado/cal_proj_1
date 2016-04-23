#include <exception>

#include "GraphViewer.h"
#include "Graph.h"
#include "Handler.h"
#include "User.h"


class App{
		vector <User*> users;
		vector <Car*> cars;
public:

		friend void ReadData(App &a, string filename);
		void AddUser(string name, string adress);
		void AddCar(User u, int Capacity, string licensePlate, string brand);
		vector <User*> getUsers();
		vector <Car*> getCars();
};
