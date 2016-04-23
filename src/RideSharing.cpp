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
	vector <User*> vec = application.getUsers();
	for (unsigned z = 0; z < vec.size(); z++){
		cout << (*vec[z]);
	};

	//Teste GraphViewer
	RoadMap rd("Nodes.csv","Roads.csv","Subroads.csv");
	list<unsigned int>mustPass;

	getchar();

	rd.viewMap();

	mustPass.push_back(1370572198);
	mustPass.push_back(1370572106);
	mustPass.push_back(1370572229);
	mustPass.push_back(1410061482);

	rd.bestPath(1367705879, 1370572294, mustPass);

	getchar();

	return 0;
}
