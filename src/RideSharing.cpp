#include "RoadMap.h"
#include "App.h"
#include <iomanip>

using namespace std;

int main(){


	string txtfile;
	App application;

	cout << "Introduce filename:" << endl;
	cin >> txtfile;
		try{
			ReadData(application, txtfile);
			} catch(FileReadingError &e) {
				cout << "Error reading file.\n";
			}

	//Teste GraphViewer
	RoadMap rd("Nodes.csv","Roads.csv","Subroads.csv");

	rd.viewMap();



	getchar();

	return 0;
}





