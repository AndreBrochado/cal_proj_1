#include "Handler.h"
#include "App.h"

bool validDay(int year, int month, int day) {
    switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            return day <= 30;
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return day <= 31;
        case 2: {
            bool leapyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (leapyear)
                return day <= 29;
            else
                return day <= 28;
        }
        default:
            return false;
    }
}


	bool validHour(int hour, int minute) {
  	    return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59;
  	}

  	bool operator>(tm d1, tm d2){
  	    return mktime(&d1) > mktime(&d2);
  	}

  	bool operator==(tm d1, tm d2){
  	    return mktime(&d1) == mktime(&d2);
  	}

  	tm getToday(){
  		time_t now = time(NULL);
  		tm *today = localtime(&now);
  		return *today;
  	}

  	bool readString(const string &prompt, string &returnString) {

  	    string testString;
  	    cout << prompt;
  	    getline(cin, testString);
  	    cout << endl;
  	    if (cin.fail()) {
  	        if (!cin.eof())
  	            cin.ignore(1000, '\n');
  	        cin.clear();
  	        return false;
  	    }
  	    if (testString == "" || testString == "\n")
  	        return false;
  	    returnString = testString;
  	    return true;
  	}

  	void getDate(tm &date) {
  	    string returnString = "";
  	    do {
  	        while (!readString("Please insert the starting date year: ", returnString)) {
  	            cout << "Please insert a valid starting date year" << endl;
  	        }
  	        date.tm_year = atoi(returnString.c_str()) - 1900;
  	        while (!readString("Please insert the starting date month: ", returnString)) {
  	            cout << "Please insert a valid starting date month" << endl;
  	        }
  	        date.tm_mon = atoi(returnString.c_str()) - 1;
  	        while (!readString("Please insert the starting date day: ", returnString)) {
  	            cout << "Please insert a valid starting date day" << endl;
  	        }
  	        date.tm_mday = atoi(returnString.c_str());

  	        if (!validDay(date.tm_year + 1900, date.tm_mon + 1, date.tm_mday))
  	            cout << "Invalid date! Insert a correct one: " << endl;

  	    } while (!validDay(date.tm_year + 1900, date.tm_mon + 1, date.tm_mday));
  	    do {
  	        while (!readString("Please insert the starting hour: ", returnString)) {
  	            cout << "Please insert a valid starting hour" << endl;
  	        }
  	        date.tm_hour = atoi(returnString.c_str());
  	        while (!readString("Please insert the starting minute: ", returnString)) {
  	            cout << "Please insert a valid starting minute" << endl;
  	        }
  	        date.tm_min = atoi(returnString.c_str());
  	        if (!validHour(date.tm_hour, date.tm_min))
  	            cout << "Invalid hour! Insert a correct one: " << endl;
  	    } while (!validHour(date.tm_hour, date.tm_min));
  	}






void RideOfferHandler(App &a){
	bool valid = false;
	bool validID = false;
	int ID;
	int timevar;

	do {
	cout << "Introduce your personal ID: \n";
	cin >> ID;
	for (unsigned z = 0; z < a.getUsers().size(); z++){
		vector <User*> users = a.getUsers();
		if( (*users[z]).returnID() == ID){
			validID = true;
		}
	}
	}while(!validID);



	tm date;
	do {

	cin.ignore();
	getDate(date);
	tm today = getToday();
	if (today >date) {
		cout << "Invalid date, please choose a date older than the one specified.";

	}
	else {
		printf("%d/%d/%d\n", date.tm_mday, date.tm_mon+1, date.tm_year+1900);
		valid = true;
	}
	}while(!valid);

	cout <<"Introduce tolerance for your departure in minutes: \n";
	cin >> timevar;
	time_t tolerance= timevar *60;

	cout <<"Introduce tolerance for your arrival in minutes: \n";
	cin >> timevar;
	time_t arrivaltolerance = timevar *60;
  a.AddRide(ID,mktime(&date),tolerance,arrivaltolerance,mktime(&date),5);

	return;
};
