/*
 * RideOffer.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Ines
 */

#include "RideOffer.h"

RideOffer::RideOffer(unsigned int arrivalPlace, unsigned int departurePlace, time_t departureTime, time_t departureTolerance, time_t arrivalTolerance, int noSeats):
	Ride(arrivalPlace, departurePlace, departureTime, departureTolerance, arrivalTolerance, noSeats){
	// TODO Auto-generated constructor stub
    // TODO: Uncomment when points are implemented
	//route.push_back(departurePoint);
    //route.push_back(arrivalPoint);

}

RideOffer::~RideOffer() {
	// TODO Auto-generated destructor stub
}

