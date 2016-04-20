/*
 * RideCompleted.cpp
 *
 *  Created on: 20/04/2016
 *      Author: Inês
 */

#include "RideCompleted.h"

RideCompleted::RideCompleted(time_t departureTime, time_t estimatedArrival, time_t departureTolerance, time_t arrivalTolerance, int noSeats, RideOffer* rideOffer):
	Ride(departureTime, estimatedArrival, departureTolerance, arrivalTolerance, noSeats), rideOffer(rideOffer){

}

RideCompleted::~RideCompleted() {
	// TODO Auto-generated destructor stub
}

