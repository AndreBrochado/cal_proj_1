/*
 * RideOffer.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Inês
 */

#include "RideOffer.h"

RideOffer::RideOffer(time_t departureTime, time_t estimatedArrival, time_t departureTolerance, time_t arrivalTolerance, int noSeats, User* driver):
	Ride(departureTime, estimatedArrival, departureTolerance, arrivalTolerance, noSeats), driver(driver){
	// TODO Auto-generated constructor stub

}

RideOffer::~RideOffer() {
	// TODO Auto-generated destructor stub
}

