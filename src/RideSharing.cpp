#include "RoadMap.h"
#include "App.h"
#include "Handler.h"
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
				return 1;
			}
			int n, counter = 0;
				do{
					do{
						if (counter != 0){
							system("cls");
							cout << "Introduziu uma opcao invalida!\n" << endl;
						}
						cout << setw(2) << "1" << "- placeholder" << endl;
						cout << setw(2) << "0" << "- Sair do programa" << endl;

						cout << "Introduza um numero: ";
						cin >> n;
						counter ++;
					}while( (n < 0) || (n > 2));
					counter = 0;

					switch(n){
					case 1:
						RideHandler(application);
						break;
					case 0:
						return 0;
					}
				}while(1);

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
