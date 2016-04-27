#include <exception>

#include "GraphViewer.h"
#include "Graph.h"
#include "Handler.h"
#include "RideOffer.h"
#include "RideRequest.h"
#include "Exceptions.h"

/*
 * @class App holds the program main data and user-interaction functions
 */
class App {
    vector<User *> users;
    vector<Car *> cars;
    vector<Ride *> requests, offers, completed;
public:
    /**
     * Default constructor for the App Class
     */
    App() { };

    /**
     * Reads database data from a file
     * @param filename name of the data-containing file
     */
    void readData(string filename);

    /**
     * Creates an user with given name and address and adds it to the users vector
     * @param name user name
     * @param address user address
     */
    void addUser(string name, string address);

    /**
     * Creates a car with given data and adds it to the cars vector
     * @param u owner of the car
     * @param capacity car capacity
     * @param licensePlate car license plate
     * @param brand car brand
     */
    void addCar(User user, int capacity, string licensePlate, string brand);

    /**
     * Creates a Ride Request and adds it to the requests vector
     * @param user ride-requesting user
     * @param departurePlace number of the i-node of the departure place
     * @param arrivalPlace number of the i-node of the arrival place
     * @param departureTime date of desired departure
     * @param departureTolerance time tolerance relative to the departure time
     * @param arrivalTolerance time tolerance relative to the arrival time
     * @param noSeats number of seats requested for the car
     */
    void addRideRequest(User *user, uint departurePlace, uint arrivalPlace, time_t departureTime,
                        time_t departureTolerance, time_t arrivalTolerance, int noSeats);

    /**
     * Creates a Ride Offer and adds it to the offers vector
     * @param user ride-offering user
     * @param departurePlace number of the i-node of the departure place
     * @param arrivalPlace number of the i-node of the arrival place
     * @param departureTime date of desired departure
     * @param departureTolerance time tolerance relative to the departure time
     * @param arrivalTolerance time tolerance relative to the arrival time
     * @param noSeats number of seats requested for the car
     */
    void addRideOffer(User *user, uint departurePlace, uint arrivalPlace, time_t departureTime,
                      time_t departureTolerance, time_t arrivalTolerance, int noSeats);

    void matchRides(RideOffer offer, RideRequest request);

    /**
     * Shows All Users Information
     */
    void showUsersInfo();

    /**
     * @returns the users vector
     */
    vector<User *> getUsers();

    /**
     * @returns the cars vector
     */
    vector<Car *> getCars();
};
