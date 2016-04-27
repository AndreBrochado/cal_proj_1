#include "App.h"
#include "RideRequest.h"
#include "RideOffer.h"

void App::readData(string filename) {
    ifstream in;
    in.open(filename.c_str(), ios::in);
    if (in.good()) {
        while (in.good()) {
            string dummy;
            string name, address, licensePlate, brand;
            int capacity;

            getline(in, dummy, '-');

            if (dummy == "<") {
                getline(in, name, '_');
                getline(in, address, '>');

                addUser(name, address);
            }

            if (!in.eof())
                in.ignore(1000, '\n');

            if (in.eof()) {
                return;
            }

        }
    }
    if (in.fail())
        throw FileReadingError();

    in.close();
}

void App::addUser(string name, string address){
    User* u1 = new User(name,address);
    users.push_back(u1);
};

vector <User*> App::getUsers(){
    return users;
};

vector <Car*> App::getCars(){
    return cars;
};


void App::addCar(User user, int capacity, string licensePlate, string brand){
    Car* c1 = new Car(capacity,licensePlate,brand);
    for (unsigned i = 0; i < users.size(); i++){
        if(user ==  (*users[i])){
            users[i]->addCar(*c1);
        }
    }
};

void App::addRideRequest(User* user , uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats){
    Ride* r = new RideRequest(departurePlace, arrivalPlace, departureTime,departureTolerance,arrivalTolerance, noSeats, user);
    requests.push_back(r);
    tryToMatchRide(r);
};

void App::addRideOffer(User* user , uint departurePlace, uint arrivalPlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats){
    Ride* r = new RideOffer(departurePlace, arrivalPlace, departureTime, departureTolerance,arrivalTolerance, noSeats, user);
    offers.push_back(r);
    tryToMatchRide(r);
}

void App::showUsersInfo() {
    for(size_t i = 0; i < users.size(); i++){
        cout<< users[i]->getUserID() << " " << users[i]->getName() << " " << users[i]->getAddress() << endl;
    }
}

bool isPossible(RideOffer offer, RideRequest request,list<uint> route, list<double> dist){
    time_t srcTime, destTime;
    time_t arrivalTime = request.getDepartureTime() - offer.getDepartureTime();
    uint newSrc = request.getDeparturePlace();
    uint newDest = request.getArrivalPlace();

    cout << "Uau!!!!!" << endl;

    list<uint>::iterator itr = route.begin();
    list<double>::iterator itd = dist.begin();

    while(itr != route.end() && itd != dist.end()){
        if(newSrc == *itr)
            srcTime = (time_t)(*itd / velAvr);
        if(newDest == *itr)
            destTime = (time_t)(*itd / velAvr);

        itr++;
        itd++;
    }

    cout << srcTime  << " " << (arrivalTime - request.getDepartureTolerance()) << endl;
    cout << srcTime  << " " << (arrivalTime + request.getDepartureTolerance()) << endl;
    cout << destTime - srcTime  << " " << request.getEstimatedArrival() - request.getArrivalTolerance() << endl;
    cout << destTime - srcTime  << " " << request.getEstimatedArrival() + request.getArrivalTolerance() << endl;

    if(((srcTime >(arrivalTime - request.getDepartureTolerance()) && srcTime <(arrivalTime + request.getDepartureTolerance())) &&
            (destTime - srcTime > request.getEstimatedArrival() - request.getArrivalTolerance()) && (destTime - srcTime < request.getEstimatedArrival() + request.getArrivalTolerance())))
        cout << "Is possible" << endl;

    return ((srcTime >(arrivalTime - request.getDepartureTolerance()) && srcTime <(arrivalTime + request.getDepartureTolerance())) &&
            ((destTime - srcTime) > request.getEstimatedArrival() - request.getArrivalTolerance()) && (destTime - srcTime < request.getEstimatedArrival() + request.getArrivalTolerance()));

}

bool App::matchRides(RideOffer offer, RideRequest request){

    cout << offer.getNoSeats() << " - " << request.getNoSeats() << endl;

    if(offer.getNoSeats() < request.getNoSeats()){
        return false;
    }

    RoadMap* rm = RoadMap::getInstance();

    list<uint> newPath = offer.getRoute();
    list<double> dist;

    rm->bestPath(request.getDeparturePlace(), request.getArrivalPlace(), newPath, dist);


    if(isPossible(offer, request,newPath, dist)){
        vector<RideRequest> requests = offer.getRequests();

        for (int i = 0; i < requests.size(); ++i) {
            if(!isPossible(offer, requests[i],newPath, dist))
                return false;
        }

        offer.decreaseNoSeats(request.getNoSeats());

        offer.addRequest(request);
        offer.setRoute(newPath);
        return true;
    }
    else
        return false;
}

void App::tryToMatchRide(Ride* newRide){

    if (dynamic_cast<RideOffer*>(newRide) == NULL){
        cout << "E uma offer" << endl;
        RideRequest* newRequest = dynamic_cast<RideRequest*>(newRide);
        for (int i = 0; i < offers.size(); ++i) {
            RideOffer* offer = dynamic_cast<RideOffer*>(offers[i]);
            if(matchRides(*offer,*newRequest)){
                cout << "Match found!!!";
                return;
            }
        }
    }


    if (dynamic_cast<RideRequest*>(newRide) == NULL){
        cout << "E uma offer" << endl;
        RideOffer* newOffer = dynamic_cast<RideOffer*>(newRide);
        for (int i = 0; i < requests.size(); ++i) {
            cout << "Hello" << endl;
            RideRequest* request = dynamic_cast<RideRequest*>(requests[i]);
            if(matchRides(*newOffer,*request)){
                requests.erase(requests.begin()+i);
                cout << "Match found!!!";
                return;
            }
        }
    }
}
