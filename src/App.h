#include "GraphViewer.h"
#include "Graph.h"

#include "Group.h"


class App{
		vector <User*> users;
		vector <Car*> cars;
		vector <Group*> groups;
public:
		void AddUser(string name, string adress);
		void AddCar(User u, int Capacity, string licensePlate, string brand);
};
