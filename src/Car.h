#include <string>

using namespace std;

class Car{
	int capacity;
	string licensePlate, brand;

public:
	Car(){capacity =0;};
	Car(int capacity, string licensePlate, string brand);
	int returnCapacity();
	void setCapacity(int cap);
};



