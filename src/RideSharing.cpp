#include "RoadMap.h"
#include "App.h"
#include <iomanip>

using namespace std;

int main(){

	string txtfile;
	App application;


	cout << "Introduza nome do ficheiro" << endl;
	cin >> txtfile;

	try{
		ReadData(application, txtfile);
	} catch(ErroLeituraFicheiro &e) {
		cout << "Ocorreu um erro a ler o ficheiro.\n";
		return 1;
	}

	//Teste GraphViewer
	RoadMap rd("Nodes.csv","Roads.csv","Subroads.csv");

	rd.viewMap();



/*

*/
	/*
	application.AddUser("Bruno", "porto");
	User* u = new User("Bruno" , "porto");
	application.AddCar(*u, 5, "adsk", "coisa");
*/
	getchar();

	return 0;
}





