#include "Ridesharing.h"
#include "RoadMap.h"



using namespace std;

int main(){

	//Teste GraphViewer
	RoadMap rd("Nodes.csv","Roads.csv","Subroads.csv");

	rd.viewMap();

	App application;

	application.AddUser("Bruno", "porto");
	User* u = new User("Bruno" , "porto");
	application.AddCar(*u, 5, "adsk", "coisa");

	getchar();

	return 0;
}





