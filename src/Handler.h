#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
//#include <windows.h>
#include <utility>
#include <ctime>
#include "Exceptions.h"


using namespace std;


class App;

void createRide(App &a, int offerType);

bool validDay(int year, int month, int day);

bool validHour(int hour, int minute);

bool operator>(tm d1, tm d2);

bool operator==(tm d1, tm d2);

bool readString(const string &prompt, string &returnString);

void getDate(tm &date);
