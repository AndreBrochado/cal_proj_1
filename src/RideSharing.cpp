#include "RoadMap.h"
#include "App.h"
#include "Handler.h"

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
			int choice, counter = 0;
				do{
					do{
						if (counter != 0){
							cout << "You have introduced an invalid option!\n" << endl;
						}
						cout << setw(2) << "2" << " - Request Ride" << endl;
						cout << setw(2) << "1" << " - Offer Ride" << endl;
						cout << setw(2) << "0" << " - Exit Application" << endl;

						cout << "Choose appropriate numerical option: ";
						cin >> choice;
						counter ++;
					}while( (choice < 0) || (choice > 3));
					counter = 0;

					switch(choice){
                        case 3:
                            //TODO: SHOW INFO
                            //application.displayAllInfo();
                        case 2:
						case 1:
							createRide(application, choice);
                            break;
					    case 0:
						    return 0;
                        default:
                            return 3;
					}
				}while(1);
}
